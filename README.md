# ManoTerapia

**METIE · Universidad de Ibagué · Ingeniería Electrónica**

**Equipo:** Felipe Perez · Brenda Guzman · David Solorzano

Prototipo de mano robótica maestro–esclavo con ESP32, cinco potenciómetros y cinco servomotores MG90S. El dashboard permite usar control espejo, practicar gestos, ejecutar demostraciones, realizar rutinas y guardar resultados de pruebas en CSV.

## Qué archivo usar

| Necesitas… | Abre este archivo |
|---|---|
| Usar la interfaz | [dashboard/ManoTerapia.html](dashboard/ManoTerapia.html) |
| Cargar el programa al ESP32 | [firmware/ManoTerapia_ESP32/ManoTerapia_ESP32.ino](firmware/ManoTerapia_ESP32/ManoTerapia_ESP32.ino) |
| Abrir el proyecto electrónico | [hardware/kicad/Placa.kicad_pro](hardware/kicad/Placa.kicad_pro) |
| Consultar el esquema | [hardware/kicad/Placa.kicad_sch](hardware/kicad/Placa.kicad_sch) |
| Consultar la PCB | [hardware/kicad/Placa.kicad_pcb](hardware/kicad/Placa.kicad_pcb) |
| Ver pendientes y pruebas | [docs/estado.md](docs/estado.md) |
| Revisar los saltos esporádicos | [docs/estabilidad_electrica.md](docs/estabilidad_electrica.md) |

## Estructura

```text
ManoTerapia/
├── README.md
├── dashboard/
│   └── ManoTerapia.html
├── firmware/
│   └── ManoTerapia_ESP32/
│       └── ManoTerapia_ESP32.ino
├── hardware/
│   └── kicad/
│       ├── Placa.kicad_pro
│       ├── Placa.kicad_sch
│       ├── Placa.kicad_pcb
│       ├── fp-lib-table
│       ├── sym-lib-table
│       └── Library.pretty/
├── docs/
└── tests/
    └── verificar.cjs
```

Hay una sola copia vigente del dashboard y del firmware. Las versiones anteriores se consultan en el historial de Git, sin llenar la carpeta de archivos numerados. La organización no cambia el código operativo ni obliga a volver a cargarlo si ya estás usando la última versión.

## Puesta en marcha

1. Para programar la placa, abre el `.ino` en Arduino IDE desde su carpeta del mismo nombre. Selecciona tu placa ESP32 y puerto, e instala la biblioteca `ESP32Servo` si no está disponible.
2. Cierra el Monitor Serial antes de conectar el dashboard: utiliza una sola aplicación conectada al puerto a la vez.
3. Abre `dashboard/ManoTerapia.html` con Chrome o Edge de escritorio y pulsa **Conectar ESP32**. La comunicación usa **115200 baudios**. Si el navegador no admite Web Serial desde un archivo local, utiliza un contexto seguro compatible, como localhost.
4. Comprueba primero los porcentajes con los servos desactivados. Después activa el sistema y prueba movimientos lentos.
5. Para cambiar de sección durante una rutina o un gesto, primero pulsa **Finalizar**.

El HTML incorpora estilos, JavaScript y banner METIE; no necesita bibliotecas web externas. El historial de sesiones se guarda en el navegador. Exporta el CSV para conservar tus resultados. Cambiar de archivo, navegador u origen puede impedir acceder al historial anterior; exporta los datos antes de migrar.

## Funciones actuales

- **Control espejo:** la mano robótica sigue las lecturas de la mano maestra, con filtrado adaptativo, órdenes graduales e histéresis angular para reducir movimientos pequeños no deseados.
- **Activación:** antes de habilitar los servos, lee los cinco potenciómetros y calcula sus objetivos con la calibración vigente. Ya no impone siempre la posición abierta al activarlos. Esto no conoce la postura física previa ni garantiza eliminar el pico de corriente.
- **Rutinas:** activan los servos y esperan que el ESP32 confirme `SERVO ON` y modo `ROUTINE` antes de empezar. Si se apagan los servos o cambia el modo, la rutina queda en pausa y no valida ejercicios; **Reanudar rutina** vuelve a solicitar activación y conserva el paso. Muestran el objetivo y la lectura de cada dedo. La flexión intermedia admite de 30 % a 70 %; los demás pasos mantienen su margen de ±15 puntos. La posición se mantiene durante 1,2 segundos con recepción continua de datos.
- **Gestos:** mano abierta, puño, pulgar arriba, paz, señalamiento, pistolita y dedo medio. Una ventana flotante ofrece **Automático**, **Manual** y **Finalizar**, con opciones de minimizar y cerrar sin desplazar las tarjetas. Ocultar la ventana no finaliza una actividad.
- **Seguimiento:** sesiones locales, ciclos, muestras, actividades e informes CSV.

El corazón aparece como referencia deshabilitada: su reproducción requiere validar movimientos mecánicos que el control actual no implementa. Los sensores flex no se usan en el firmware vigente, aunque sus conectores aparecen en el diseño electrónico.

## Conexiones vigentes del firmware

| Dedo | GPIO del potenciómetro | GPIO del servo | RAW abierto | RAW cerrado |
|---|---:|---:|---:|---:|
| Pulgar | 33 | 23 | 4095 | 3800 |
| Índice | 32 | 22 | 4095 | 2700 |
| Medio | 35 | 21 | 4095 | 2500 |
| Anular | 34 | 19 | 4095 | 2800 |
| Meñique | 36 | 18 | 4095 | 3100 |

Estas correspondencias conservan las correcciones del usuario. No equivalen necesariamente al orden numérico de los conectores en la placa.

- Pulsador: **GPIO 4 a GND**, con `INPUT_PULLUP` y antirrebote de 60 ms.
- LED: **GPIO 13**, con resistencia de 330 Ω hacia el LED y GND.
- Potenciómetros: alimentación de **3,3 V**.
- Servos: **MG90S**, fuente externa de **5 V** indicada por el usuario. Capacidad en amperios pendiente de confirmar.
- Mantener una referencia GND común entre señales del ESP32 y alimentación de los servos.

La lectura disminuye al cerrar la mano. La calibración utiliza esos extremos sin invertir las señales de los servos. Un RAW que permanezca fijo en 4095 al mover el potenciómetro requiere revisar la lectura y sus conexiones; cambiar la calibración no repara una conexión intermitente.

## KiCad

Los archivos proceden del proyecto `Placa` de METIE, creado con **KiCad 10**. Abre `Placa.kicad_pro` para trabajar con esquema y PCB. Se incluyen el símbolo ESP32 y sus huellas locales. En esta copia se normalizó la tabla de huellas para evitar entradas duplicadas y se añadió una tabla de símbolos con ruta relativa.

El esquema y la PCB no se rediseñaron durante la organización. Los modelos 3D externos no se incluyen; las huellas pueden conservar referencias a `KICAD_USER_3DMODEL_DIR`. No publicar archivos de fabricación como validados hasta revisar el diseño y su correspondencia con el montaje.

## Estado y límites

El usuario reportó mejoras tras resoldar conexiones y probar las variantes de calibración y filtrado. **Siguen pendientes los pequeños saltos esporádicos de los servos y la respuesta intermitente del pulsador.** No se consideran resueltos por la reorganización.

El dashboard mide señales de los potenciómetros de la mano maestra. No mide la posición física de la mano esclava. Una demostración terminada indica que acabó la secuencia de órdenes, no que la postura física se haya verificado. Las rutinas son demostraciones del prototipo académico, no un protocolo clínico validado.

## Pruebas y versiones

Con Node.js, desde la carpeta principal:

```sh
node tests/verificar.cjs
```

Las pruebas son simuladas y no sustituyen compilar el firmware en Arduino IDE ni probar el prototipo. Consultar [docs/estado.md](docs/estado.md) para distinguir las verificaciones realizadas de las pendientes.

Repositorio privado: [FelipePerez-eng/ManoTerapia](https://github.com/FelipePerez-eng/ManoTerapia). Cada cambio debe quedar descrito en un commit; las versiones antiguas se recuperan desde ese historial. No subir datos personales de participantes, CSV de sesiones ni credenciales.