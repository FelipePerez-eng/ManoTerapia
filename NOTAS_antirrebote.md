# Pulsador y conexiones confirmadas

Se respeta la tabla del usuario: Pot1 usa GPIO 36, 34, 35, 32 y 33. Flex1 no se implementa. Se conserva el orden funcional previo del firmware: pulgar 33, índice 32, medio 35, anular 34 y meñique 36; no se reasignan dedos a partir del número del conector.

Archivo: ManoTerapia_ESP32_antirrebote/ManoTerapia_ESP32_antirrebote.ino. Es una variante del código aportado por el usuario, no una sustitución silenciosa del respaldo.

El pulsador GPIO 4 a GND conserva INPUT_PULLUP y alterna servos una vez por pulsación aceptada. La versión anterior aceptaba un cambio cuando habían transcurrido 50 ms desde el último cambio aceptado, sin comprobar estabilidad continua. Esta variante requiere 60 ms sin cambios antes de aceptar cada estado. No elimina una pulsación real ni una perturbación que dure más de ese umbral.

Mensajes nuevos, compatibles con el dashboard de diagnóstico:
- DIAG|BUTTON|GPIO4|LOW_STABLE: pulsación aceptada por el firmware.
- DIAG|COMMAND|SERVO_OFF: orden serial de desactivación.
- DIAG|COMMAND|STOP: orden serial de parada.
- DIAG|COMMAND|LEGACY_S: alternancia por comando antiguo s.
- DIAG|FW|BUTTON_DEBOUNCE_60MS: inicio de esta variante.

No cambia pines, porcentajes, calibración, ángulos, modos ni el protocolo de comandos. No incorpora sensores flex. La lectura al 100 % sigue pendiente de obtener valores RAW en las dos posiciones para comprobar la calibración.

El primer registro recibido no capturó un apagado: esta mejora corrige un defecto del antirrebote, pero no demuestra que ese defecto fuera la causa del síntoma. No reactiva servos automáticamente tras un apagado o reinicio.

Verificación: casos simulados de rebote y pulsaciones estables sobre una traducción directa de la función. No se dispone de compilador Arduino/ESP32 en esta sesión; pendiente compilar en Arduino IDE y probar en el prototipo.