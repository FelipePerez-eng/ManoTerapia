# Cambios principales

## 8 de noviembre de 2026 · rutina con servos confirmados

- Conservar el esquema editado localmente por el usuario, sin sobrescribirlo con la copia remota anterior; la PCB y el firmware siguen sin cambios en esta entrega.
- Iniciar o reanudar rutina mediante SERVO ON, MODE ROUTINE y STATUS GET. Solo entrar en curso tras recibir el estado ON/ROUTINE del ESP32.
- Pausar al recibir apagado o salida de modo; no aceptar objetivos ni avanzar en pausa. Reanudar explícitamente conserva el paso y reinicia la retención temporal.
- Si no se confirma el estado en 3,5 segundos o falla el inicio, intentar enviar STOP y mostrar el error. No asumir éxito físico de una orden enviada.
- Añadir pruebas simuladas de confirmación, pausa, reanudación, timeout, desconexión y escritura fallida. No cambia el .ino ni reactiva automáticamente los servos después de una pausa.

## 8 de noviembre de 2026 · activación según mano maestra

- Calcular cinco objetivos a partir de lecturas nuevas de los potenciómetros antes de habilitar PWM. Evita imponer siempre 0° al activar.
- Mantener calibración, pines, filtro, antirrebote y límites existentes. No se escalona la alimentación ni se afirma medir la posición real del servo.
- Añadir pruebas simuladas de activación. Pendiente compilación Arduino/ESP32 y prueba física de corriente y movimiento.
- ERC sigue anunciando 28 incidencias sin un informe detallado recuperable; ver docs/ERC_estado.md. PCB y límites mecánicos no se modifican.

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