# Estilos de vida entre generaciones: Página web y Make

## Descripción

Se realizó una práctica en la que se construyó una página web llamada "Estilos de vida entre generaciones" y una automatización en Make. Se entrevistó a tres personas (un abuelo o abuela, un padre o madre y un amigo o amiga de la misma edad) con las mismas 8 preguntas sobre sus hábitos de consumo (comida, ropa, electrónicos, transporte, basura, desechables, agua y qué consideran necesario para vivir bien). En la página se capturan la edad y las respuestas de cada persona y se presiona "Comparar respuestas"; la página envía los tres textos a un webhook de Make, un Make AI Agent analiza únicamente lo que dicen las respuestas y regresa una respuesta en texto plano con la comparación por tema, un análisis y tres conclusiones.

Flujo: Página web → Make (Webhooks → Make AI Agent → Webhook Response) → Página web

## Objetivos de aprendizaje

- Distinguir los estilos de vida y de consumo de tres generaciones del entorno familiar o de la comunidad.
- Construir sin programar una página web conectada a Make e IA que compare las respuestas de las entrevistas.
- Formular conclusiones propias sobre la sustentabilidad de esos hábitos, analizando con criterio lo que propone la IA.

## Material utilizado

- Computadora con navegador
- Make (plan Pro del curso, Make's AI Provider)
- IA generativa (versión gratuita) para generar la página
- GitHub y GitHub Pages
- Tres personas entrevistadas: un abuelo o abuela, un padre o madre y un amigo o amiga de su edad (solo se registró la edad, sin nombres ni otros datos personales)

## Diagrama

![Diagrama](Imagenes/Diagrama.png)

## Código

- [index.html (página web)](Codigo/index.html)
- [Blueprint del escenario de Make](Codigo/Generaciones.blueprint.json)

Página publicada: [https://darkmagicyt.github.io/DesarrolloSustentable/3.4/Codigo/index.html](https://darkmagicyt.github.io/DesarrolloSustentable/3.4/Codigo/index.html)

## Video del funcionamiento

[Ver video en YouTube](https://youtu.be/FZxh08Vyo1E)

[Ver carpeta donde se guarda el link a YouTube](Video/README.md)

## Evidencia

### Foto 1 (Escenario en Make)

![Escenario](Imagenes/Diagrama.png)

### Foto 2 (Página web publicada)

![Pagina](Imagenes/Pagina.png)

### Foto 3 (Entrevistas capturadas en la página)

![Entrevistas](Imagenes/Entrevistas.png)

### Foto 4 (Análisis generado por la IA)

![Analisis](Imagenes/Analisis.png)

## Conclusiones

La práctica nos permitió conocer cómo han cambiado los estilos de vida y de consumo entre tres generaciones y cómo se puede conectar una página web con una automatización en Make y un agente de IA que compara únicamente lo que dicen las entrevistas. También vimos la importancia de leer el análisis de la IA con criterio propio, marcando con qué conclusiones estamos de acuerdo y con cuáles no.

## Resultados

[Resultados.pdf](Resultados/Resultados.pdf)