# ManoTerapia

Proyecto académico · METIE · Universidad de Ibagué.

**Equipo:** Felipe Perez, Brenda Guzman y David Solorzano.

Dashboard autónomo HTML/CSS/JavaScript para operar un prototipo de mano robótica con ESP32: control espejo, rutinas, gestos y seguimiento con exportación CSV.

## Abrir el dashboard

Abrir `ManoTerapia_dashboard_v2.html` con Chrome o Edge de escritorio. Web Serial requiere un contexto seguro admitido por el navegador y acceso al puerto del ESP32 a 115200 baudios. El HTML incluye el banner y no necesita bibliotecas externas.

## Versiones conservadas

- `ManoTerapia_dashboard_v1_BACKUP.html`: referencia V1 funcional aportada por el usuario.
- `ManoTerapia_dashboard_v2_respaldo_anterior.html`: instantánea V2 intermedia conservada.
- `ManoTerapia_dashboard_v2.html`: versión vigente con identidad académica, banner centrado, gestos representativos y animaciones discretas.
- `CHANGELOG.md`: evolución y límites de la verificación.

Estas instantáneas documentan estados recuperables; no reconstruyen commits históricos que nunca existieron.

## Límites del prototipo

La mano esclava no tiene medición de posición en esta versión. Los gestos pistolita y dedo medio requieren validación mecánica y calibración física; corazón permanece deshabilitado. Las rutinas son demostraciones del prototipo, no protocolos clínicos.

Los datos de sesiones permanecen en el navegador. Exportar CSV para conservarlos; no incluir datos personales de participantes en el repositorio.

## Forma de trabajar

Registrar cada cambio terminado con su descripción, pruebas y limitaciones. Conservar versiones verificadas antes de modificar comportamiento o firmware. Un repositorio por proyecto facilita su seguimiento futuro.

Este repositorio es privado. No se ha otorgado licencia de redistribución.

## Verificación

Con Node.js instalado, ejecutar desde la raíz: `node tests/verify.cjs`. Las pruebas usan señales simuladas y no sustituyen la prueba física del prototipo.
