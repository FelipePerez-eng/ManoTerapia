# ManoTerapia · sistema visual vigente

## Alcance

Dashboard académico en `outputs/ManoTerapia_dashboard_v2.html`. Estética clara, blanca y azul, orientada a operar y explicar el prototipo durante la muestra. Conservar identidad institucional y comportamiento documentados en PRODUCT.md.

## Composición

Cabecera con marca, integrantes y conexión; navegación superior única y persistente. Banner completo centrado, con ancho máximo de 660 px. Portada con título y explicación centrados, seguida de una secuencia de preparación, actividad y registro, sin repetir enlaces de navegación.

Las vistas operativas usan encabezados alineados a la izquierda, datos agrupados y controles identificables. La biblioteca muestra cuatro columnas en pantalla amplia, tres en tamaño intermedio y dos en móvil; una columna en pantallas muy estrechas. Las tarjetas señalan el gesto seleccionado mediante color y borde, además del estado aria-pressed del botón.

## Estilo

Fondo #f4f7fa, texto #17334e, texto secundario #50657a, azul de acción #1258a0 y azul profundo #173f67. Tipografía de sistema Segoe UI para conservar el archivo autónomo. Radios de 12–14 px y separación generosa entre grupos. Sombras reservadas para la navegación persistente; superficies de contenido delimitadas por bordes. Emojis representativos en gestos y rutinas por preferencia explícita del usuario.

## Interacción y movimiento

Entrada breve al cambiar de vista, transición de barras de progreso y elevación discreta de tarjetas de gestos al pasar el puntero. Sin animaciones continuas ni simulación de actividad del hardware. Respeta prefers-reduced-motion. Foco de teclado visible, botones de al menos 42 px y navegación desplazable en pantallas pequeñas.

## Verificación y límites

Pruebas de sintaxis y comportamiento simulado superadas tras el refinamiento. No se pudo realizar inspección visual: la política del navegador bloqueó observar la URL file local. No afirmar verificación visual ni prueba con ESP32 físico hasta realizarlas.