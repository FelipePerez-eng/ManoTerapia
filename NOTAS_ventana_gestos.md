# Ventana de gestos sin desplazar tarjetas

Archivo: ManoTerapia_dashboard_ventana_gestos.html. No requiere cambiar firmware.

Sustituye el panel desplegable dentro de la tarjeta por una ventana flotante no modal, de posición fija. La cuadrícula no cambia tamaño ni distribuye de nuevo las otras tarjetas al elegir un gesto. La ventana tiene altura máxima y desplazamiento propio para caber en pantallas pequeñas.

- Elegir gesto abre Automático, Manual y Finalizar en la ventana.
- Minimizar conserva selección y actividad y muestra una barra con Abrir y Finalizar.
- Cerrar sin actividad oculta la ventana y limpia la selección.
- Cerrar con una actividad en curso la oculta y conserva la barra; no equivale a finalizar ni envía órdenes.
- Escape sigue la misma acción que Cerrar.
- Intentar cambiar de sección con actividad sigue bloqueado y restaura la ventana para acceder a Finalizar.
- Finalizar desde la ventana o la barra utiliza el mismo STOP existente.

Se conservan rutinas ajustadas, sesiones, CSV, gestos y los controles de conexión. Sin diagnóstico visible. Abrir, cerrar y minimizar no activan hardware.

Pruebas simuladas superadas para apertura, minimización, restauración, cierre activo/inactivo, navegación bloqueada, finalización, fallo de envío, rutinas y desconexión. No se realizó inspección visual en navegador ni prueba física en esta sesión.