# Gestos en tarjeta y finalización explícita

Dashboard: ManoTerapia_dashboard_gestos.html. No requiere cambiar el firmware.

Al elegir un gesto se despliega un único panel dentro de su tarjeta, con Automático, Manual y Finalizar. El panel existente se mueve, sin duplicar controles o identificadores. Automático utiliza MODE GESTURE_DEMO y POSE como antes. Manual utiliza GESTURE_PRACTICE y la evaluación de la mano maestra; no sustituye el control espejo general. Se conservan los gestos y la referencia deshabilitada del corazón.

El usuario eligió impedir el cambio de sección hasta pulsar Finalizar. Durante un gesto o una rutina, los intentos de navegar muestran un aviso y conservan la sección. Se bloquea también la selección de otro gesto y el cambio entre Automático/Manual mientras el actual esté activo. El bloqueo incluye los envíos iniciales para evitar navegar mientras se inicia una actividad. Las sesiones de datos no bloquean la navegación.

Completar una demostración o alcanzar el objetivo manual no libera el gesto: Finalizar sigue siendo necesario. Finalizar en gestos envía STOP, que en el firmware existente detiene la actividad y desactiva las señales de los servos. La interfaz informa envío, no confirmación de posición física. Si falla la escritura, conserva el bloqueo y permite reintentar; no oculta el fallo. Una desconexión libera el estado local, sin afirmar que apagó el hardware.

Las rutinas mantienen su botón de Finalizar y su comportamiento de terminación existente. Conservan el margen de ±20 para flexión intermedia, ±15 para otros pasos y el tiempo de 1,2 segundos. No se añade cancelación automática al navegar.

Pruebas simuladas superadas: panel en tarjeta, bloqueo de sección y selección, demostración terminada sin desbloqueo prematuro, práctica, Finalizar con STOP, error de envío sin desbloqueo, rutina, desconexión, protocolo, seguimiento y CSV. El controlador no se conecta automáticamente ni envía órdenes al seleccionar una tarjeta. No hay diagnóstico visible. No se realizó inspección visual en navegador ni prueba física en esta sesión.