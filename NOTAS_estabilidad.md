# Reducción de pequeños saltos en los servos

El usuario informa pequeños saltos mientras el indicador permanece en Servos activos. No ha confirmado todavía si los RAW varían con la mano quieta. La causa eléctrica o mecánica no está identificada.

Variante: ManoTerapia_ESP32_estable/ManoTerapia_ESP32_estable.ino. Base: respuesta_media, con pines corregidos, calibración actual, filtro adaptativo y antirrebote de 60 ms.

Cambio: en espejo, rutinas y práctica, actualizar el objetivo angular solo cuando difiere en al menos 2 grados del último objetivo admitido. No es un retraso temporal: un movimiento pequeño acumulado de 2 grados sí se admite. Puede quedar una diferencia de un grado respecto del objetivo calculado. Los extremos de apertura y cierre siempre se admiten, por lo que no se recorta el recorrido. Se mantiene el avance máximo de 4 grados por iteración.

Solo se llama a write cuando cambia el ángulo ordenado en ese bloque. ESP32Servo continúa generando PWM después de write; esto no apaga los servos ni elimina ruido de alimentación. La demostración automática y la activación inicial conservan su comportamiento.

No se modifica el pulsador: sigue requiriendo 60 ms de estabilidad al pulsar y al soltar. Para distinguir pulsaciones demasiado breves de un contacto intermitente, probar pulsando 0,3 segundos y soltando 0,3 segundos. Si falla así, hace falta investigar el contacto y los mensajes DIAG del firmware. La modificación de histéresis no pretende reparar el pulsador físico.

Verificación simulada: rechazo de variaciones de un grado, admisión de dos grados, avance al objetivo sin sobrepaso, conservación de extremos y antirrebote intacto. Pendiente compilación ESP32 y prueba física. Si el temblor persiste con RAW estables y órdenes constantes, investigar alimentación, conexiones o servo; no aumentar indefinidamente la tolerancia.