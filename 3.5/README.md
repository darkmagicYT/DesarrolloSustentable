# Noticias climáticas del día: Página web y Make

## Descripción

Se realizó una práctica en la que se construyó una página web llamada "Noticias climáticas del día" y una automatización en Make. En la página el usuario elige uno de seis temas ambientales y presiona "Ver noticias"; la página envía el tema a un webhook de Make, que busca las cinco noticias más recientes en Google News mediante un feed RSS, las junta en un solo texto, un Make AI Agent las resume y regresa una respuesta en texto plano con un resumen del día, las noticias con su enlace a la fuente y una acción concreta que un estudiante puede realizar.

Flujo: Página web → Make (Webhooks → RSS → Text aggregator → Make AI Agent → Webhook Response) → Página web

Temas elegidos: cambio climático, huracanes Pacífico mexicano, deforestación México, reciclaje, autos eléctricos México y sequía Sinaloa.

## Objetivos de aprendizaje

- Construir sin programar una herramienta de difusión ambiental que obtenga noticias recientes mediante RSS, las resuma con IA y las muestre en una página web.
- Verificar que los resúmenes generados por la IA sean fieles a sus fuentes.

## Material utilizado

- Computadora con navegador
- Make (plan Pro del curso, conexión Make's AI Provider)
- IA generativa para generar la página
- GitHub y GitHub Pages

## Resultados Act9

![Resultados](Imagenes/Resultados.png)

## Diagrama

![Diagrama](Imagenes/Diagrama.png)

## Código

- [index.html (página web)](Codigo/index.html)
- [Blueprint del escenario de Make](Codigo/Noticias_Climaticas.blueprint.json)

Página publicada: [[https://darkmagicyt.github.io/DesarrolloSustentable/3.5/Codigo/index.html](https://darkmagicyt.github.io/DesarrolloSustentable/3.5/Codigo/index.html)]

## Video del funcionamiento

[Carpeta](Video/README.md)
[[enlace del video](https://youtu.be/0t2_hKdPLUc)]

## Evidencia

### Foto 1 (Escenario en Make)

![Escenario](Imagenes/Diagrama.png)

### Foto 2 (Página web publicada)

![Pagina](Imagenes/Pagina.png)

### Foto 3 (Prueba de los temas desde la página publicada)

![Temas](Imagenes/Temas.png)

### Foto 4 (Creditos)

![Creditos](Imagenes/Creditos.png)

## Conclusiones

La práctica permitió construir una herramienta de difusión ambiental sin programar el procesamiento de la información. A su vez comprobamos que la informacion fuera veridica y concordara con la informacion de google news conociedo de antemano que la IA puede comenter errores de estructuracion por falta de contexto. Se reforzo el conocimiento sobre como conectar webhook a una pagina web, se logro conectar la pagina de google news a make para obtener la informacion buscada.
