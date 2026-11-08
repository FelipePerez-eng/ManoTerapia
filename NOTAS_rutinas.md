# Reconocimiento de flexión intermedia

Variante: ManoTerapia_dashboard_rutinas.html. Usar el firmware respuesta_media que el usuario indica que funciona; esta entrega no cambia el .ino.

El ejercicio intermedio antes pedía los cinco dedos entre 35 % y 65 % durante 1,2 segundos consecutivos. En esta variante acepta 30 % a 70 % en ese ejercicio, manteniendo los cinco dedos y el tiempo de retención. Los demás ejercicios y la práctica de gestos mantienen su margen de ±15 puntos.

La vista de rutina muestra lectura actual, objetivo y si cada dedo está dentro del margen. Una salida del margen sigue reiniciando el conteo. El texto identifica qué dedo requiere ajustar y su valor. Los datos siguen siendo de la mano maestra; no verifican la posición física de los servos.

La validación de retención reinicia su tiempo si pasan más de 750 ms entre tramas completas, para no contar como estabilidad un intervalo sin datos. Rechaza tramas incompletas o fuera de 0 a 100. El tiempo de 1,2 segundos solo se comprueba cuando llega una trama; con envío a intervalos de 250 ms, la confirmación normalmente ocurre al llegar la siguiente trama que cumpla ese tiempo.

La causa específica del problema comunicado no está comprobada: el usuario identifica flexión intermedia pero aún no aporta los porcentajes durante la posición. Esta variante mejora el reconocimiento y permite ver qué lectura bloquea el paso. No recalibra sensores ni corrige fallos de conexión.

Pruebas simuladas superadas: flexión intermedia dentro y fuera del margen, margen original de otros ejercicios, pausa sin datos, protocolo, sesiones, CSV y gestos. Pendiente prueba con hardware e inspección visual en navegador.