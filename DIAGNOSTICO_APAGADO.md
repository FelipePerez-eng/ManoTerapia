# Registro del apagado · 7 de noviembre de 2026

Síntoma informado: la interfaz pasa a «Servos apagados». El usuario indica alimentación externa; tensión, capacidad, cableado y estado de conexión durante el fallo aún no confirmados.

Abrir `ManoTerapia_dashboard_diagnostico.html` y cerrar las demás conexiones al puerto (dashboard anterior y Monitor Serial). No es necesario cargar otro firmware para este registro. Ante una nueva aparición del fallo, pulsar «Descargar registro» antes de cerrar o recargar la página.

El registro conserva los últimos 100 eventos: solicitudes de comandos, resultado de escritura, mensajes no sensoriales del ESP32 y cambios de conexión. No añade órdenes ni reactivación automática. No contiene las muestras de sensores ni códigos de sesión. Un registro lleno de mensajes periódicos puede desplazar eventos anteriores; descargarlo en cuanto ocurra el fallo.

Interpretación orientativa, sin atribuir una causa definitiva:

- Una solicitud SERVO OFF o STOP antes del apagado identifica una orden del dashboard.
- EVT|SERVO|OFF sin esa solicitud indica un evento del firmware; no identifica por sí solo si vino del pulsador o de otra entrada serial.
- MANOTERAPIA|FW|1.0 indica un inicio del firmware; no identifica el motivo del reinicio.
- Puerto cerrado o conexión perdida explica por qué el dashboard pasa a su estado desconectado, pero no verifica el estado físico de los servos.

No se modifica el firmware ni se anula el botón GPIO 4. Falta el registro del fallo para decidir una corrección. Sintaxis y pruebas simuladas del dashboard de diagnóstico superadas; sin validación física.