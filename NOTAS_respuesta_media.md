# Respuesta intermedia

El usuario probó la respuesta suave y solicita un poco más de velocidad, sin volver al seguimiento directo anterior.

Esta variante cambia únicamente PASO_MANUAL_GRADOS de 3 a 4 respecto de ManoTerapia_ESP32_respuesta_suave.ino. Aumenta el límite de cambio por iteración durante espejo, rutinas y práctica; no define una velocidad física constante del servo.

Conserva filtro, calibración, pines corregidos, antirrebote, rampa de demostración automática, activación inicial y protocolo. La versión suave permanece disponible para comparar.

Pruebas simuladas de seguimiento y conservación de parámetros superadas. Pendiente compilar y probar en el ESP32. Comprobar primero lecturas con servos desactivados y después el seguimiento con movimientos lentos.