# Cambios principales

## 8 de noviembre de 2026 · organización

- Una sola versión vigente en dashboard/ y firmware/.
- Proyecto KiCad Placa incorporado con esquema, PCB, símbolo y huellas locales.
- Tabla de huellas normalizada en la copia organizada: antes había cuatro entradas del mismo nombre, dos hacia una subcarpeta inexistente. Se conserva una ruta local relativa válida.
- README de uso, conexiones y estado; notas sobre ruido eléctrico; pruebas portables consolidadas.
- Código operativo trasladado sin cambios de contenido; respaldos locales fuera de outputs y versiones anteriores conservadas en el historial de Git.

## Evolución conservada en Git

- Identidad académica y banner METIE; interfaz clara y navegación única.
- Calibración decreciente de cinco potenciómetros y pines de servo corregidos por el usuario.
- Antirrebote, filtro adaptativo, respuesta gradual e histéresis angular.
- Rutinas con lectura por dedo y ajuste de flexión intermedia.
- Gestos con ventana flotante, minimizar/cerrar y finalización explícita.

Los saltos esporádicos y la respuesta intermitente del pulsador siguen pendientes de diagnóstico físico. Las pruebas simuladas no equivalen a una validación eléctrica o clínica.