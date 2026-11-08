# Saltos esporádicos y pulsador

## Evidencia disponible

El usuario informa pequeños saltos incluso sin tocar el montaje. Antes describió cambios de lectura al mover cables y mejoría tras resoldar. Usa cinco MG90S con fuente externa de 5 V; no se conoce su capacidad en amperios. No hay medición de tensión bajo carga ni captura de señal PWM.

La fuente de los saltos no está confirmada. No aumentar filtros o tolerancias indefinidamente para ocultarlos. La copia organizada conserva el programa actual.

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