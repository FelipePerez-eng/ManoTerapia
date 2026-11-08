# Estado de recuperación del ERC · 8 de noviembre de 2026

Se volvió a ejecutar KiCad 10 sobre hardware/kicad/Placa.kicad_sch, con formato JSON y severidad completa. La consola informa:

```text
Se encontraron 28 violaciones
Informe ERC guardado en .../work/ERC_2026-11-08.json
```

Sin embargo, el archivo de destino permaneció con el contenido de prueba `{}` (3 bytes), sin resultados ERC. También se registraron errores de acceso a HKCU\Software\kicad-cli, bloqueo de Placa.kicad_pro y creación de Placa.kicad_prl. Se solicitaron y concedieron permisos de escritura sobre el destino y la copia KiCad, pero el informe siguió sin escribirse. Por tanto no se entrega ese JSON como un informe válido.

Se intentó además cargar la copia del esquema desde el editor gráfico de KiCad, sin conseguir completar la apertura con los controles disponibles. No se obtuvo una captura de las incidencias. El conteo de consola no basta para clasificarlas ni para atribuirles los saltos.

Para obtener el detalle en KiCad: abrir Placa.kicad_pro y el editor de esquemas; utilizar Inspeccionar → Comprobador de reglas eléctricas; ejecutar la comprobación y guardar el informe o enviar capturas de la lista. La revisión del DRC de la PCB continúa pendiente. No se han eliminado marcadores ni cambiado conexiones para ocultar resultados.