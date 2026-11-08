# Calibración de la mano maestra

Archivo actualizado: `ManoTerapia_ESP32_calibrado/ManoTerapia_ESP32_calibrado.ino`.

Se modifican únicamente las dos tablas de calibración y su comentario respecto de la variante antirrebote. Se conservan pines, antirrebote estable de 60 ms, estados, gestos, rutinas, ángulos y protocolo. Flex no se implementa.

| Dedo | GPIO | RAW abierto (0 %) | RAW cerrado (100 %) |
|---|---:|---:|---:|
| Pulgar | 33 | 4095 | 3800 |
| Índice | 32 | 4095 | 2900 |
| Medio | 35 | 4095 | 2500 |
| Anular | 34 | 4095 | 3400 |
| Meñique | 36 | 4095 | 2800 |

Datos facilitados por el usuario; se usa 2800 para el último cierre del meñique. La fórmula existente admite un denominador negativo: (RAW filtrado - abierto) / (cerrado - abierto), limitado entre 0 y 1. Por ello no hace falta invertir señales de servo ni modificar el dashboard.

## Prueba

Cerrar la conexión del dashboard antes de cargar el archivo en Arduino IDE. Abrir el .ino en su carpeta homónima y cargarlo en la placa ESP32 correspondiente. Reconectar después el dashboard de diagnóstico. Primero comprobar los cinco porcentajes con los servos desactivados: abiertos cerca de 0 %, cerrados cerca de 100 % y posiciones intermedias variables. Tras comprobar las lecturas, activar servos y probar lentamente el control espejo.

Si RAW permanece en 4095 al mover un potenciómetro, esta calibración lo representará como 0 %. No resuelve una lectura físicamente fija o saturada. Es necesario observar si RAW realmente desciende desde 4095 al cerrar. El filtro puede introducir una demora breve al cambiar de posición. El tramo observado del pulgar es más corto que los demás; no se ha medido su repetibilidad.

## Verificación

Pruebas numéricas de cinco extremos abiertos, cinco extremos cerrados, cinco puntos medios, límites y monotonicidad. Comprobación de que el resto del código conserva exactamente la variante antirrebote. No se ha compilado con Arduino/ESP32 en esta sesión ni se ha probado físicamente. Los respaldos anteriores se conservan.