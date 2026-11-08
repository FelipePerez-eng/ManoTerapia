#include <ESP32Servo.h>

// ============================================================
// MANOTERAPIA - Firmware integrado v1.0
// ESP32 WROOM-32D (placa de 38 pines)
// Conserva la calibracion y el control manual del firmware base.
// Protocolo nuevo: CMD|id|accion|argumentos...\n
// IMPORTANTE:
// - Inicia con los servos desactivados.
// - Los gestos automaticos son posiciones ORDENADAS, no posiciones
//   fisicas verificadas (no hay sensores en la mano esclava).
// - Los limites de angulo conservan los valores originales 0..180.
//   Verificar mecanicamente el recorrido antes de probar movimientos.
// ============================================================

const int NUM = 5;
const char* NOMBRE[NUM] = {"PULGAR", "INDICE", "MEDIO", "ANULAR", "MENIQUE"};
const int PINES_POT[NUM]   = {33, 32, 35, 34, 36};
const int PINES_SERVO[NUM] = {18, 19, 21, 22, 23};

const int PIN_LED   = 13;
const int PIN_BOTON = 4; // Pulsador a GND

// Calibracion original de la mano maestra
const float potAbierto[NUM]  = {0, 0, 0, 0, 0};
const float potCerrado[NUM]  = {240, 1000, 1100, 700, 750};

// Angulos originales (pulgar invertido)
const float servoAbierto[NUM] = {0, 0, 0, 0, 0};
const float servoCerrado[NUM] = {180, 180, 180, 180, 180};

const float ALPHA = 0.2f;
const unsigned long INTERVALO_REPORTE_MS = 250;
const unsigned long INTERVALO_RAMPA_MS = 20;
const int PASO_RAMPA_GRADOS = 2;
const int TOLERANCIA_ANGULO = 1;

float filtrado[NUM];
int minVisto[NUM], maxVisto[NUM];

Servo servos[NUM];
bool servosActivos = false;
unsigned long ultimaImpresion = 0;

// Modos del sistema
// MANUAL, ROUTINE y GESTURE_PRACTICE siguen a la mano maestra.
// GESTURE_DEMO mantiene la posicion ordenada y permite rampas.
enum SystemMode {
  MODE_MANUAL,
  MODE_ROUTINE,
  MODE_GESTURE_DEMO,
  MODE_GESTURE_PRACTICE
};
SystemMode modoActual = MODE_MANUAL;

int anguloActual[NUM]  = {180, 0, 0, 0, 0};
int anguloObjetivo[NUM] = {180, 0, 0, 0, 0};
bool poseEnMovimiento = false;
unsigned long ultimaRampa = 0;
String nombrePoseActual = "CUSTOM";

String bufferSerial;
const size_t MAX_BUFFER_SERIAL = 128;

// ------------------------------------------------------------
// Utilidades
// ------------------------------------------------------------
int leerPot(int pin) {
  long suma = 0;
  for (int k = 0; k < 16; k++) suma += analogRead(pin);
  return (int)(suma / 16);
}

const char* estadoDedo(float pct) {
  if (pct < 15.0f) return "ABIERTO";
  if (pct > 85.0f) return "CERRADO";
  return "medio";
}

const char* nombreModo(SystemMode modo) {
  switch (modo) {
    case MODE_MANUAL: return "MANUAL";
    case MODE_ROUTINE: return "ROUTINE";
    case MODE_GESTURE_DEMO: return "GESTURE_DEMO";
    case MODE_GESTURE_PRACTICE: return "GESTURE_PRACTICE";
    default: return "MANUAL";
  }
}

int anguloDesdePorcentaje(int dedo, float porcentaje) {
  float t = constrain(porcentaje, 0.0f, 100.0f) / 100.0f;
  float ang = servoAbierto[dedo] + t * (servoCerrado[dedo] - servoAbierto[dedo]);
  return constrain((int)roundf(ang), 0, 180);
}

void enviarAck(const String& id) {
  Serial.printf("ACK|%s|OK\n", id.c_str());
}

void enviarError(const String& id, const String& motivo) {
  Serial.printf("ERR|%s|%s\n", id.c_str(), motivo.c_str());
}

void informarModo() {
  Serial.printf("EVT|MODE|%s\n", nombreModo(modoActual));
}

void reiniciarMinMax() {
  for (int i = 0; i < NUM; i++) {
    minVisto[i] = 4095;
    maxVisto[i] = 0;
  }
}

// ------------------------------------------------------------
// Servos
// ------------------------------------------------------------
void activarServos() {
  if (servosActivos) return;

  for (int i = 0; i < NUM; i++) {
    servos[i].setPeriodHertz(50);
    servos[i].attach(PINES_SERVO[i], 500, 2400);
    anguloActual[i] = (int)servoAbierto[i];
    anguloObjetivo[i] = anguloActual[i];
    servos[i].write(anguloActual[i]);
  }

  servosActivos = true;
  poseEnMovimiento = false;
  digitalWrite(PIN_LED, HIGH);
  Serial.println(">>> SERVOS ACTIVADOS");
  Serial.println("Servos: ACTIVOS");
  Serial.println("EVT|SERVO|ON");
}

void desactivarServos() {
  if (servosActivos) {
    for (int i = 0; i < NUM; i++) servos[i].detach();
  }
  servosActivos = false;
  poseEnMovimiento = false;
  digitalWrite(PIN_LED, LOW);
  Serial.println(">>> SERVOS DESACTIVADOS");
  Serial.println("Servos: apagados");
  Serial.println("EVT|SERVO|OFF");
}

void cambiarModo(const String& nombre) {
  if (nombre == "MANUAL") modoActual = MODE_MANUAL;
  else if (nombre == "ROUTINE") modoActual = MODE_ROUTINE;
  else if (nombre == "GESTURE_DEMO") modoActual = MODE_GESTURE_DEMO;
  else if (nombre == "GESTURE_PRACTICE") modoActual = MODE_GESTURE_PRACTICE;
  else return;

  // Al salir de la demostracion, el siguiente ciclo vuelve a seguir
  // la mano maestra si el nuevo modo lo requiere.
  poseEnMovimiento = false;
  informarModo();
}

bool iniciarPose(const String& nombre, const String& valores) {
  if (!servosActivos) {
    Serial.println("ERR|POSE|SERVO_OFF");
    return false;
  }
  if (modoActual != MODE_GESTURE_DEMO) {
    Serial.println("ERR|POSE|WRONG_MODE");
    return false;
  }

  int objetivosPct[NUM];
  int inicio = 0;
  for (int i = 0; i < NUM; i++) {
    int separador = valores.indexOf(',', inicio);
    String token;
    if (i < NUM - 1) {
      if (separador < 0) return false;
      token = valores.substring(inicio, separador);
      inicio = separador + 1;
    } else {
      token = valores.substring(inicio);
    }
    token.trim();
    if (token.length() == 0) return false;
    for (size_t k = 0; k < token.length(); k++) {
      if (!isDigit(token[k]) && !(k == 0 && token[k] == '-')) return false;
    }
    objetivosPct[i] = constrain((int)token.toInt(), 0, 100);
  }

  nombrePoseActual = nombre;
  for (int i = 0; i < NUM; i++) {
    anguloObjetivo[i] = anguloDesdePorcentaje(i, objetivosPct[i]);
  }
  poseEnMovimiento = true;
  ultimaRampa = millis();
  Serial.printf("EVT|POSE|START|%s\n", nombrePoseActual.c_str());
  return true;
}

void actualizarPoseAutomatica() {
  if (!servosActivos || !poseEnMovimiento) return;
  if (millis() - ultimaRampa < INTERVALO_RAMPA_MS) return;
  ultimaRampa = millis();

  bool todosEnObjetivo = true;
  for (int i = 0; i < NUM; i++) {
    if (anguloActual[i] < anguloObjetivo[i]) {
      anguloActual[i] = min(anguloActual[i] + PASO_RAMPA_GRADOS, anguloObjetivo[i]);
    } else if (anguloActual[i] > anguloObjetivo[i]) {
      anguloActual[i] = max(anguloActual[i] - PASO_RAMPA_GRADOS, anguloObjetivo[i]);
    }
    servos[i].write(anguloActual[i]);
    if (abs(anguloActual[i] - anguloObjetivo[i]) > TOLERANCIA_ANGULO) {
      todosEnObjetivo = false;
    }
  }

  if (todosEnObjetivo) {
    poseEnMovimiento = false;
    Serial.printf("EVT|POSE|DONE|%s\n", nombrePoseActual.c_str());
  }
}

// ------------------------------------------------------------
// Protocolo serial CMD|id|accion|argumentos...\n
String obtenerCampo(const String& linea, int indice) {
  int inicio = 0;
  int actual = 0;
  while (actual < indice) {
    int separador = linea.indexOf('|', inicio);
    if (separador < 0) return "";
    inicio = separador + 1;
    actual++;
  }
  int fin = linea.indexOf('|', inicio);
  if (fin < 0) fin = linea.length();
  return linea.substring(inicio, fin);
}

void procesarComando(const String& lineaOriginal) {
  String linea = lineaOriginal;
  linea.trim();
  if (linea.length() == 0) return;

  // Compatibilidad con el firmware/dashboard anterior.
  if (linea == "s") {
    Serial.println("DIAG|COMMAND|LEGACY_S");
    servosActivos ? desactivarServos() : activarServos();
    return;
  }
  if (linea == "r") {
    reiniciarMinMax();
    Serial.println(">>> min/max reiniciados");
    Serial.println("EVT|CAL|RESET");
    return;
  }

  if (!linea.startsWith("CMD|")) {
    Serial.println("ERR|0|INVALID_COMMAND");
    return;
  }

  String id = obtenerCampo(linea, 1);
  String accion = obtenerCampo(linea, 2);
  String arg1 = obtenerCampo(linea, 3);

  if (accion == "SERVO") {
    if (arg1 == "ON") activarServos();
    else if (arg1 == "OFF") {
      Serial.println("DIAG|COMMAND|SERVO_OFF");
      desactivarServos();
    }
    else { enviarError(id, "BAD_SERVO_STATE"); return; }
    enviarAck(id);
    return;
  }

  if (accion == "MODE") {
    if (arg1 != "MANUAL" && arg1 != "ROUTINE" &&
        arg1 != "GESTURE_DEMO" && arg1 != "GESTURE_PRACTICE") {
      enviarError(id, "UNKNOWN_MODE");
      return;
    }
    cambiarModo(arg1);
    enviarAck(id);
    return;
  }

  if (accion == "CAL" && arg1 == "RESET") {
    reiniciarMinMax();
    Serial.println("EVT|CAL|RESET");
    enviarAck(id);
    return;
  }

  if (accion == "POSE") {
    String nombre = arg1;
    String valores = obtenerCampo(linea, 4);
    if (valores.length() == 0) { enviarError(id, "BAD_POSE_VALUES"); return; }
    if (!servosActivos) { enviarError(id, "SERVO_OFF"); return; }
    if (modoActual != MODE_GESTURE_DEMO) { enviarError(id, "WRONG_MODE"); return; }
    if (iniciarPose(nombre, valores)) enviarAck(id);
    else enviarError(id, "BAD_POSE_VALUES");
    return;
  }

  if (accion == "STOP") {
    Serial.println("DIAG|COMMAND|STOP");
    // STOP detiene la actividad y desactiva las señales de servo,
    // igual que la desactivacion existente del firmware original.
    modoActual = MODE_MANUAL;
    desactivarServos();
    informarModo();
    enviarAck(id);
    return;
  }

  if (accion == "STATUS" && arg1 == "GET") {
    Serial.printf("STATE|SERVO|%s|MODE|%s\n",
                  servosActivos ? "ON" : "OFF", nombreModo(modoActual));
    enviarAck(id);
    return;
  }

  enviarError(id, "UNKNOWN_COMMAND");
}

void revisarSerial() {
  while (Serial.available() > 0) {
    char c = (char)Serial.read();
    if (c == '\r') continue;

    // Comandos antiguos de un solo caracter, sin salto de linea.
    if (bufferSerial.length() == 0 && (c == 's' || c == 'r')) {
      procesarComando(String(c));
      continue;
    }

    if (c == '\n') {
      procesarComando(bufferSerial);
      bufferSerial = "";
      continue;
    }

    if (bufferSerial.length() < MAX_BUFFER_SERIAL) bufferSerial += c;
    else bufferSerial = ""; // descarta una linea demasiado larga
  }
}

// ------------------------------------------------------------
// Pulsador con antirrebote
// ------------------------------------------------------------
void revisarBoton() {
  static bool lecturaAnterior = HIGH;
  static bool estadoEstable = HIGH;
  static unsigned long ultimoCambioLectura = 0;
  const unsigned long ANTIRREBOTE_MS = 60;
  const unsigned long ahora = millis();
  const bool lectura = digitalRead(PIN_BOTON);

  // Reiniciar el tiempo ante CADA cambio: solo aceptar una entrada estable.
  if (lectura != lecturaAnterior) {
    lecturaAnterior = lectura;
    ultimoCambioLectura = ahora;
  }

  if (lectura != estadoEstable &&
      (unsigned long)(ahora - ultimoCambioLectura) >= ANTIRREBOTE_MS) {
    estadoEstable = lectura;
    if (estadoEstable == LOW) {
      Serial.println("DIAG|BUTTON|GPIO4|LOW_STABLE");
      servosActivos ? desactivarServos() : activarServos();
    }
  }
}

// ------------------------------------------------------------
// Setup y loop
// ------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  pinMode(PIN_BOTON, INPUT_PULLUP);
  analogSetAttenuation(ADC_11db);

  for (int i = 0; i < NUM; i++) filtrado[i] = leerPot(PINES_POT[i]);
  reiniciarMinMax();

  Serial.println();
  Serial.println("MANOTERAPIA|FW|1.0");
  Serial.println("DIAG|FW|BUTTON_DEBOUNCE_60MS");
  Serial.println("Teclas legacy: s=servos on/off | r=reiniciar min/max");
  Serial.println("Protocolo: CMD|id|accion|argumentos\n");
  Serial.println("Servos: apagados");
  informarModo();
}

void loop() {
  revisarBoton();
  revisarSerial();

  float pct[NUM];
  int cerrados = 0;
  int abiertos = 0;

  for (int i = 0; i < NUM; i++) {
    int raw = leerPot(PINES_POT[i]);
    filtrado[i] += ALPHA * (raw - filtrado[i]);
    minVisto[i] = min(minVisto[i], raw);
    maxVisto[i] = max(maxVisto[i], raw);

    float denominador = potCerrado[i] - potAbierto[i];
    float t = (denominador == 0.0f) ? 0.0f : (filtrado[i] - potAbierto[i]) / denominador;
    t = constrain(t, 0.0f, 1.0f);
    pct[i] = t * 100.0f;

    if (pct[i] < 15.0f) abiertos++;
    if (pct[i] > 85.0f) cerrados++;

    // Manual, rutinas y practica de gestos siguen la mano maestra.
    if (servosActivos && modoActual != MODE_GESTURE_DEMO) {
      int ang = anguloDesdePorcentaje(i, pct[i]);
      anguloActual[i] = ang;
      anguloObjetivo[i] = ang;
      servos[i].write(ang);
    }
  }

  // En demostracion automatica se realiza una transicion progresiva.
  if (modoActual == MODE_GESTURE_DEMO) actualizarPoseAutomatica();

  if (millis() - ultimaImpresion >= INTERVALO_REPORTE_MS) {
    ultimaImpresion = millis();
    Serial.println("-----------------------------------------------");
    for (int i = 0; i < NUM; i++) {
      Serial.printf("%-8s raw:%4d  (min %4d max %4d)  %3.0f%%  %s\n",
                    NOMBRE[i], (int)roundf(filtrado[i]), minVisto[i], maxVisto[i],
                    pct[i], estadoDedo(pct[i]));
    }
    if (cerrados == NUM) Serial.println("==> MANO CERRADA");
    else if (abiertos == NUM) Serial.println("==> MANO ABIERTA");
    else Serial.println("==> mano en posicion intermedia");
    Serial.printf("Servos: %s\n", servosActivos ? "ACTIVOS" : "apagados");
  }

  delay(20);
}