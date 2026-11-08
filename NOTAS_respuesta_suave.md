# Respuesta suave y seguimiento de movimientos pequeños

Base: código corregido que el usuario pegó, conservado como `ManoTerapia_ESP32_pines_usuario/ManoTerapia_ESP32_pines_usuario.ino`.

Nueva variante: `ManoTerapia_ESP32_respuesta_suave/ManoTerapia_ESP32_respuesta_suave.ino`.

## Pines y calibración

Orden: pulgar, índice, medio, anular, meñique.
- Potenciómetros: 33, 32, 35, 34, 36.
- Servos corregidos por el usuario: 23, 22, 21, 19, 18.
- RAW abierto: 4095 para los cinco.
- RAW cerrado actualizado: 3800, 2700, 2500, 2800, 3100.

## Ajuste confirmado

El usuario pide seguir antes movimientos pequeños y suavizar la respuesta física. El filtro mantiene el promedio ADC y la ganancia máxima 0,45; aumenta la ganancia mínima de 0,08 a 0,16 para reducir el retraso ante variaciones pequeñas. No aumenta el porcentaje calculado ni adelanta artificialmente el cierre. No añade zona muerta.

En espejo, rutinas y práctica, el ángulo ordenado avanza como máximo 3 grados por iteración hacia su objetivo. Su tiempo depende del bucle; no es una velocidad constante en grados por segundo. El primer grado de movimiento no espera a completar ese paso: si el objetivo está más cerca, se envía el propio objetivo. El suavizado limita el cambio de órdenes, no mide ni garantiza la velocidad física del servo.

La demostración automática conserva su rampa original. La activación de servos sigue ordenando inicialmente la posición abierta, tal como en la base; este ajuste no suaviza esa activación. Se conserva el antirrebote del pulsador, los límites angulares, modos y protocolo. No incluye flex. Las barras y porcentajes siguen representando la señal de la mano maestra, no la posición real de la esclava.

## Comprobación

Pruebas simuladas: extremos de calibración, seguimiento de cambios pequeños, respuesta del filtro frente a la base, límite de 3 grados, convergencia e inversión de sentido sin sobrepaso. No compilado con Arduino/ESP32 ni probado físicamente en esta sesión.

Al cargarlo, comprobar lecturas con servos desactivados, después activar y probar lentamente el control espejo. Un filtro más rápido para movimientos pequeños también puede transmitir más ruido; valorar el resultado en el prototipo. Para un seguimiento más lento, reducir PASO_MANUAL_GRADOS de 3 a 2; para más rápido, subirlo a 4. Conservar la base anterior para comparar.