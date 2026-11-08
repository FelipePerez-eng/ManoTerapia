# Saltos esporádicos y pulsador

## Evidencia disponible

El usuario informa pequeños saltos incluso sin tocar el montaje. Antes describió cambios de lectura al mover cables y mejoría tras resoldar. Usa cinco MG90S con fuente externa de 5 V; no se conoce su capacidad en amperios. No hay medición de tensión bajo carga ni captura de señal PWM.

La fuente de los saltos no está confirmada. No aumentar filtros o tolerancias indefinidamente para ocultarlos. Tras la organización se actualiza la activación para tomar los objetivos de lecturas nuevas de la mano maestra, en vez de imponer siempre 0°. Todavía puede existir movimiento al activar, porque el programa no mide dónde está cada servo físicamente; la modificación no constituye una garantía de reducción de corriente.

## Observaciones de la revisión aportada por el usuario

- Antes, activarServos conectaba los cinco servos y ordenaba la posición abierta. La modificación calcula anguloActual y anguloObjetivo de los cinco antes del primer attach y aplica cada objetivo inmediatamente después de attach. No se ha medido el pulso transitorio de la biblioteca al conectar PWM ni se escalona la activación.
- El dato de 0,7 A por MG90S en bloqueo no está verificado para estas unidades. Si se usa como hipótesis, cinco sumarían 3,5 A, sin contar el ESP32 ni margen: una fuente de 3 A no cubriría ese escenario. La ficha del fabricante consultada no publica esa corriente; confirmar fuente y consumos reales.
- 470–1000 µF cerca de la alimentación de servos es una propuesta de desacoplo por validar, no sustituto de una fuente adecuada. Revisar polaridad, tensión nominal, cableado y comportamiento bajo carga antes de aplicarla.
- No se modifican los límites a 10–170° automáticamente: los ángulos seguros deben medirse por dedo con la mecánica real. Mantener 0–180° en el código no demuestra que el montaje tolere todo ese recorrido.
- El ancho de pista de 1,5 mm señalado en la revisión no descarta caídas de tensión o interferencias del retorno compartido. También importan longitud, espesor de cobre, conexiones y corriente. No se ha validado el recorrido de retorno con mediciones.
- El tramo de 295 cuentas del pulgar equivale aproximadamente a 0,61 grados por cuenta para un mapeo nominal de 180°. No se cambia su calibración ni se añade filtrado exclusivo sin una medición de ruido en reposo.
- Espressif publica para ESP32 un rango de medida aproximado de 150–3100 mV con atenuación de 11 dB. Un código 4095 señala el techo de la conversión, pero no confirma por sí solo una tensión exacta ni una pérdida de contacto del cursor.

## Separar seguimiento y comportamiento del servo

1. Con los servos desactivados, observar si los RAW fluctúan con los potenciómetros quietos.
2. Si el recorrido está comprobado y no fuerza la mecánica, ejecutar Mano abierta en modo Automático y observar la postura una vez terminadas las órdenes, antes de Finalizar. En ese modo el firmware no sigue las lecturas de los potenciómetros.
3. Si el temblor solo aparece en espejo, investigar primero la señal analógica y el seguimiento. Si sigue con objetivo fijo en Automático, revisar alimentación, referencia de señal, servo y montaje; esto es una orientación, no una prueba concluyente.
4. Comparar un servo con los cinco, siempre desconectando alimentación antes de modificar conexiones, para detectar una posible relación con la carga de la fuente.

## Revisión del diseño

El esquema aportado no muestra condensadores externos de filtrado en las cinco entradas analógicas ni una resistencia externa de pull-up en el pulsador; el firmware usa la interna. Esto no demuestra que esas ausencias causen el síntoma ni describe necesariamente los componentes internos de la placa ESP32.

- Espressif advierte que el ADC puede ser sensible al ruido y documenta el uso de muestreo múltiple y, según el caso, un condensador cerámico de 100 nF en la entrada. El firmware ya promedia muestras. Evaluar filtrado cerca de la entrada ADC antes de rediseñar; revisar su efecto sobre la respuesta.
- Si se comprueba ruido en GPIO 4, evaluar una resistencia externa de 10 kΩ a 3,3 V y filtrado de 100 nF a GND, manteniendo el pulsador a GND y el antirrebote. Es una propuesta por validar, no un cambio aplicado al esquema.
- Revisar GND común y que los retornos de corriente de los servos no compartan un recorrido inadecuado con las referencias analógicas. Confirmar tensión en los conectores durante el movimiento y corriente disponible de la fuente. No se ha calculado un condensador de reserva ni una fuente requerida sin conocer la carga y el montaje.
- Un objetivo angular fijo no descarta fluctuación del PWM o del propio servo; no se dispone de osciloscopio o medidas físicas en esta sesión.

## Fuentes técnicas

- [Espressif: ADC y reducción de ruido](https://docs.espressif.com/projects/esp-idf/en/v4.4.8/esp32/api-reference/peripherals/adc.html).
- [Pololu: interfaz de control y efecto de variaciones del pulso](https://www.pololu.com/blog/17/servo-control-interface-in-detail).
- [Arduino: diagnóstico de servos y alimentación](https://support.arduino.cc/hc/en-us/articles/360017053760-Troubleshoot-servo-motors).
- [Espressif: rangos ADC por atenuación](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/adc.html).
- [Ficha del fabricante MG90S consultada](https://torqpro.com/product/mg90s/).