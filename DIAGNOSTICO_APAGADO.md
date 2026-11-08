# Registro del apagado · 7 de noviembre de 2026

Síntoma informado: la interfaz pasa a «Servos apagados». El usuario indica alimentación externa; tensión, capacidad, cableado y estado de conexión durante el fallo aún no confirmados.

Abrir `ManoTerapia_dashboard_diagnostico.html` y cerrar las demás conexiones al puerto (dashboard anterior y Monitor Serial). No es necesario cargar otro firmware para este registro. Ante una nueva aparición del fallo, pulsar «Descargar registro» antes de cerrar o recargar la página.

El registro actualizado conserva los últimos 500 eventos: solicitudes de comandos, resultado de escritura, mensajes no sensoriales del ESP32 y cambios de conexión. Omite separadores y estados periódicos repetidos; siempre procesa esos mensajes con la lógica original del dashboard. No añade órdenes ni reactivación automática. No contiene las muestras de sensores ni códigos de sesión. Descargarlo en cuanto ocurra el fallo.

## Primer registro recibido

El fragmento recibido contiene un único cambio de estado: apagados a activos; después permanecen activos. No contiene una transición a apagados, una solicitud de apagado ni un mensaje de reinicio. No permite atribuir el problema al pulsador, a la alimentación ni al dashboard. La versión inicial almacenaba solo 100 eventos y podía desplazar transiciones importantes con mensajes repetidos; se amplía y filtra el registro para la siguiente observación. No se cambió el firmware.

Interpretación orientativa, sin atribuir una causa definitiva:

- Una solicitud SERVO OFF o STOP antes del apagado identifica una orden del dashboard.
- EVT|SERVO|OFF sin esa solicitud indica un evento del firmware; no identifica por sí solo si vino del pulsador o de otra entrada serial.
- MANOTERAPIA|FW|1.0 indica un inicio del firmware; no identifica el motivo del reinicio.
- Puerto cerrado o conexión perdida explica por qué el dashboard pasa a su estado desconectado, pero no verifica el estado físico de los servos.

No se modifica el firmware ni se anula el botón GPIO 4. Falta el registro del fallo para decidir una corrección. Sintaxis y pruebas simuladas del dashboard de diagnóstico superadas; sin validación física.