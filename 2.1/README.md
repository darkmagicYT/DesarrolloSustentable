
# Secuencias de LEDs con Arduino UNO R4 WiFi (Matriz LED + EEPROM)

## Descripción

Este proyecto controla 10 LEDs externos (conectados en los pines digitales 4 al 13) junto con la matriz LED integrada del Arduino UNO R4 WiFi para ejecutar tres secuencias distintas de forma rotativa. Cada vez que la placa se reinicia, el programa lee de la memoria EEPROM la última secuencia ejecutada, avanza a la siguiente y la guarda, de modo que en cada arranque se muestra una animación diferente:

1. **Pares y Nones**: enciende alternadamente los LEDs de pines pares (4, 6, 8, 10, 12) y luego los de pines nones (5, 7, 9, 11, 13).
2. **Oleaje**: enciende todos los LEDs, y después realiza un barrido de izquierda a derecha (4→13) y de derecha a izquierda (13→4).
3. **Cuenta regresiva + BOOM**: realiza una cuenta regresiva del 10 al 1 mostrando cada número en la matriz LED integrada mientras apaga un LED externo por segundo, y al finalizar despliega la palabra "BOOM" letra por letra en la matriz.

## Objetivos de aprendizaje

Programar en Arduino el control secuencial de múltiples salidas digitales (10 LEDs) combinado con el uso de la matriz LED integrada del UNO R4 WiFi para representar números y texto mediante frames binarios, y aplicar la memoria EEPROM para conservar y rotar el estado de ejecución entre reinicios de la placa.

## Material utilizado

- Arduino UNO R4 WiFi (con matriz LED integrada de 12x8)
- Protoboard
- 10 LEDs
- 10 Resistencias 220 ohms
- Cables Dupont

## Diagrama del circuito


## Código

[Codigo/Elultimoescrito.ino](enlace-al-repositorio)

## Video del funcionamiento

[Ver video en YouTube](enlace-al-video)

## Evidencias de armado

_(Pendiente: agregar aquí fotografías del circuito armado en la protoboard)_

## Reporte

[Resultados/Resultados.pdf](enlace-al-reporte)

## Conclusiones

La práctica permitió reforzar el manejo de múltiples salidas digitales de forma simultánea (10 LEDs), el uso de bucles `for` para generar patrones de encendido y apagado, y el manejo de la matriz LED integrada del UNO R4 WiFi mediante la construcción manual de frames de 96 bits (3 bloques de 32 bits) para representar dígitos y letras. Asimismo, se comprendió el uso práctico de la memoria EEPROM para persistir un estado (la secuencia actual) entre reinicios de la placa, incluyendo la validación de rangos para evitar lecturas de valores corruptos o fuera de rango. Esto resalta la importancia de planear la lógica de temporización (`delay()`) y el direccionamiento de bits al trabajar con matrices LED de bajo nivel.

## Resultados

[Resultados/Resultados.pdf](enlace-al-reporte)

Documento con la descripción de la práctica, objetivos y procedimientos realizados.

- Reporte técnico (PDF)
- Datos adicionales (si aplica)
- Diagramas adicionales
