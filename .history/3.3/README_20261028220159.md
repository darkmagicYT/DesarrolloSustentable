# Clasificador de residuos por foto: Bot de Telegram y Make

## Descripción

Se realizó una práctica en la que se construyó un bot de Telegram y una automatización en Make para clasificar residuos. El usuario envía al bot la foto de un residuo; Make descarga la imagen, un Make AI Agent con visión la analiza y regresa una respuesta en texto plano con qué es el residuo, su material, su clasificación (orgánico, inorgánico reciclable, inorgánico no reciclable o manejo especial o peligroso), si se recicla, en qué contenedor va, su tiempo aproximado de degradación y un consejo para reducirlo o reutilizarlo.

Flujo: Telegram (Watch Updates) → Telegram (Download a File) → Make AI Agent con visión → Telegram (Send a Text Message or a Reply)

## Objetivos de aprendizaje

- Identificar el impacto de los residuos que se generan en la vida diaria.
- Construir sin programar un clasificador de residuos con IA conectado a un bot de Telegram.
- Evaluar la precisión de la IA comparando sus respuestas con fuentes oficiales.

## Material utilizado

- Celular con Telegram y cámara
- Telegram (BotFather)
- Make (plan Pro del curso, Make's AI Provider)
- Computadora con navegador
- 10 residuos distintos de la casa o del campus para fotografiar

## Diagrama

![Diagrama](Imagenes/Diagrama.png)

## Código

- [Blueprint del escenario de Make](Codigo/Clasificador_Residuos_Equipo#.blueprint.json)

## Video del funcionamiento

[Ver video en YouTube](URL_DEL_VIDEO)

[Ver carpeta donde se guarda el link a YouTube](Video/README.md)

## Evidencia

### Foto 1 (Escenario en Make)

![Escenario](Imagenes/Diagrama.png)

### Foto 2 (Conversación con el bot en Telegram)

![Telegram](Imagenes/Telegram.png)

### Foto 3 (Créditos consumidos en el historial del escenario)

![Creditos](Imagenes/Creditos.png)

### Fotos de los materiales a los que se tomaron foto

[Fotos](Imagenes/)

## Conclusiones

La práctica nos permitió conocer el impacto de los residuos que generamos y cómo se puede conectar un bot de Telegram con una automatización en Make y un agente de IA con visión que clasifica residuos a partir de una foto. También vimos la importancia de comparar lo que responde la IA contra fuentes confiables.

## Resultados

[Resultados.pdf](Resultados/Resultados.pdf)
