# Filtro adaptativo de potenciómetros

Variante: `ManoTerapia_ESP32_filtrado/ManoTerapia_ESP32_filtrado.ino`.

El usuario informa que las lecturas parecen funcionar tras resoldar algunas conexiones. Se conserva esa calibración y el antirrebote del pulsador.

Se mantiene el promedio de 16 muestras ADC. El filtro exponencial, antes fijo en 0,2, usa ahora una ganancia continua entre 0,08 y 0,45: más suavizado con variaciones pequeñas y respuesta inicial más rápida ante cambios grandes. La ganancia se ajusta respecto del recorrido RAW de cada dedo; alcanza el máximo al superar un error del 6 % de ese recorrido.

No aumenta la amplitud de movimiento, no cambia pines ni extremos, no añade zona muerta ni oculta una lectura fija o desconexión. Los cambios pequeños sostenidos siguen reflejándose, aunque se suavizan más. El ritmo de envío a la interfaz sigue siendo el original de 250 ms; las pruebas no garantizan una mejora perceptible idéntica en el prototipo.

Parámetros ajustables en el archivo: ALPHA_REPOSO, ALPHA_MOVIMIENTO y FRACCION_MOVIMIENTO. La variante calibrada anterior permanece como respaldo.

Para probar: cargar en Arduino IDE, reconectar el dashboard, comprobar primero lecturas con servos desactivados y después probar movimientos lentos con control espejo. Comparar reposo y movimientos suaves antes de cambiar parámetros.

Pruebas simuladas: menor variación con ruido alternado pequeño, menor error inicial ante un cambio grande, ausencia de sobrepaso, seguimiento de cambios pequeños y conservación de pines, calibración y antirrebote. Pendiente compilación con Arduino/ESP32 y prueba física.