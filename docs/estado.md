# Estado del proyecto · 8 de noviembre de 2026

## Archivos vigentes

- Dashboard: ventana flotante, minimizar/cerrar, finalización explícita y rutinas ajustadas. Las rutinas ahora requieren confirmación del ESP32 de servos activos y modo ROUTINE. Se pausan si los servos se apagan o cambia el modo, sin completar objetivos durante esa pausa; se reanudan explícitamente en el mismo paso.
- Firmware: base `estable`, con activación actualizada para leer los cinco potenciómetros y calcular sus objetivos antes de habilitar PWM. Conserva pines corregidos, calibración vigente, filtrado adaptativo, pasos de 4 grados e histéresis de 2 grados en el seguimiento, además del antirrebote de 60 ms.
- KiCad: se conserva la edición local posterior del esquema realizada por el usuario. La PCB no cambió respecto de la última copia de GitHub. No se sobrescriben el esquema ni el historial interno de KiCad; este último y los archivos de preferencias quedan fuera del repositorio conforme a .gitignore. Los originales de Escritorio no se modifican. Símbolo y huellas incluidos.

## Qué se comprobó

Los archivos operativos y respaldos locales se movieron conservando sus hashes SHA-256 al organizarlos. La modificación posterior de activación está registrada en Git; su base también queda respaldada en work/. Las pruebas funcionales se consolidan en tests/verificar.cjs para no depender de rutas de Descargas o de variantes antiguas. Incluyen tests/arranque.cjs: lectura nueva antes de attach, objetivos abiertos/cerrados/intermedios e idempotencia simulados.

En la conversación se ejecutaron pruebas simuladas de calibración, filtrado, antirrebote, límites de avance, histéresis, protocolo, rutinas, navegación, gestos, ventana flotante, sesiones y CSV. No hay una compilación Arduino/ESP32 ni una inspección visual final en navegador registradas para la última combinación de archivos.

## Pendientes

1. Identificar causa de saltos esporádicos de servos sin tocar el circuito y de pulsaciones que no se reconocen.
2. Confirmar amperaje de la fuente externa de 5 V y revisar alimentación y retorno de los MG90S bajo carga.
3. Verificar repetibilidad de RAW abierto/cerrado con conexiones estables. El pulgar tiene un tramo de calibración corto y todos los extremos abiertos indicados están en 4095.
4. Compilar el firmware, probar el conjunto físico y revisar ERC/DRC de KiCad. El intento anterior de ERC con KiCad 10 informó 28 incidencias, pero el informe detallado no quedó accesible y aparecieron errores de permisos de registro/bloqueo del proyecto. Ese conteo no está actualizado a la nueva edición local del esquema. No se ha clasificado su contenido ni se ha ejecutado DRC. Un archivo subido no significa un diseño validado.
5. Comprobar opcionalmente modelos 3D externos si se necesita la vista 3D.

Los flex se mantienen sin implementar. El corazón continúa como referencia deshabilitada.