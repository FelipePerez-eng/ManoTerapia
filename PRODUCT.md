# ManoTerapia

<!-- impeccable:product-schema 1 -->

## Platform

web

## Stack

Dashboard autónomo en HTML, CSS y JavaScript, sin dependencias externas. Archivo vigente: `dashboard/ManoTerapia.html`.

## Users

Usuarios principales confirmados: docentes y evaluadores durante la muestra académica. El equipo desarrolla el prototipo y prepara sus demostraciones.

## Product Purpose

Presentar y operar un prototipo de mano robótica maestro–esclavo, observar las señales de la mano maestra y registrar los resultados de las pruebas. La interfaz debe facilitar que los evaluadores comprendan qué hace el sistema y distingan las lecturas reales de las estimaciones.

## Operating Context

Proyecto académico de Ingeniería Electrónica, METIE, Universidad de Ibagué. Equipo: Felipe Perez, Brenda Guzman y David Solorzano.

Conexión con ESP32 por Web Serial a 115200 baudios. Uso en navegador de escritorio compatible, con permisos de puerto y contexto seguro admitido por el navegador. No hay despliegue público confirmado.

## Capabilities and Constraints

- Conservar control espejo, controles de servos, parada, calibración min/max, rutinas guiadas, gestos, sesiones, historial y exportaciones CSV.
- Conservar protocolo `CMD|id|acción|argumentos` con salto de línea, nombres de modos y compatibilidad con el firmware de referencia V1.
- Cinco señales de la mano maestra; esta versión no mide la posición física de la mano esclava. Una secuencia de órdenes terminada no demuestra que la postura física se haya alcanzado.
- Rutinas y práctica evalúan objetivos de los sensores maestros, con las condiciones y tolerancias existentes. No presentarlas como protocolos clínicos ni como validación terapéutica.
- Pistolita y dedo medio están incorporados mediante combinaciones de extremos existentes. Sus comandos se comprobaron en simulación; falta validar la calibración y su reproducción física.
- El corazón se presenta como referencia deshabilitada. La oposición del pulgar y los movimientos laterales necesarios no están disponibles en el control actual; no inventar una postura funcional equivalente.
- Historial local en el navegador y CSV. No garantizar migración automática entre archivos, navegadores u orígenes.
- Las mejoras visuales deben preservar el comportamiento existente. Mantener respaldos y distinguir las pruebas simuladas de las realizadas con hardware.

## Brand Commitments

Nombre: ManoTerapia. Identidad explícita: METIE · Universidad de Ibagué. Mostrar los nombres del equipo tal como fueron proporcionados.

Preferencias confirmadas: interfaz clara blanca y azul, presentación académica cuidada, navegación sin duplicaciones y banner de tamaño contenido. El usuario prefiere emojis representativos en los gestos a identificadores como G01. Mantener el resto de la interfaz sobrio y con pocos emojis.

## Evidence on Hand

- Dashboard vigente en dashboard/ManoTerapia.html y firmware en firmware/ManoTerapia_ESP32/ManoTerapia_ESP32.ino.
- Esquema, PCB y bibliotecas locales en hardware/kicad, a partir de la carpeta Placa confirmada por el usuario.
- Banner METIE aportado por el usuario e incorporado en el dashboard.
- Pruebas simuladas en tests/verificar.cjs. Versiones previas recuperables desde el historial de Git.
- Usuario confirma servos MG90S y fuente externa de 5 V; amperaje desconocido. Persisten pequeños saltos sin tocar el circuito y respuesta intermitente del pulsador.
- Flex sin implementar. La versión actual exige Finalizar antes de cambiar de sección durante una actividad y utiliza ventana flotante minimizable para gestos.
- No afirmar validación física completa ni diseño KiCad libre de incidencias.

## Product Principles

1. Preservar las funciones ya probadas al mejorar la presentación.
2. Hacer comprensible el funcionamiento del prototipo durante la evaluación académica.
3. Diferenciar señales medidas, estimaciones y capacidades pendientes.
4. Mantener identidad institucional y autoría del equipo.

## Open Decisions

No se han confirmado requisitos específicos de accesibilidad, uso clínico ni modificaciones mecánicas o de firmware para el corazón. No asumirlos.