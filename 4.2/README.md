# Práctica 4.2-P8 – Encuesta "¿Compras local o global?"

**Asignatura:** Desarrollo Sustentable (ACD-0908) · **Carrera:** Ingeniería en Sistemas Computacionales
**Unidad 4:** Escenario económico · **Tema 4.2:** Economía global vs economía local y PIB
**Institución:** Instituto Tecnológico de Mazatlán
**Equipo:** _[número y nombres]_ · **Profesor:** _[nombre]_ · **Fecha:** _[fecha]_

> Los campos entre `[ ]` se llenan con los datos reales de su encuesta (marcados con ▶).

---

## Actividad 1. Investigación previa

### 1. Economía local vs. economía global

La **economía local** es el conjunto de actividades de producción, comercio y consumo que ocurren dentro de una comunidad o región y cuyo dinero circula principalmente en ella. La **economía global** es la red de intercambio de bienes, servicios, capital e información entre países, impulsada por la globalización, las cadenas de suministro internacionales y el comercio electrónico. La diferencia clave es hacia dónde fluye el dinero y qué tan lejos ocurre la producción.

Ejemplos en Mazatlán:

| Economía local | Economía global |
|---|---|
| Pescadores y vendedores de pescado y camarón del Mercado Pino Suárez o del muelle; el dinero se queda en familias de la ciudad. | Cruceros internacionales, cadenas hoteleras extranjeras y compras en apps como Temu, Shein o Amazon, donde el pago sale del país o va a corporativos internacionales. |
| Tienda de abarrotes de la colonia y tianguis de fin de semana. | Supermercados o cadenas internacionales con productos importados. |

### 2. PIB y diferencia de aportación

El **Producto Interno Bruto (PIB)** es el valor total de los bienes y servicios finales producidos dentro de un país en un periodo (normalmente un año). Se calcula por gasto como PIB = C + I + G + (X − M): consumo, inversión, gasto del gobierno y exportaciones menos importaciones.

Una compra local aporta al PIB nacional: el producto se genera aquí, paga sueldos, renta, impuestos y proveedores locales, y el vendedor suele volver a gastar en la misma comunidad (efecto multiplicador). Una compra en una plataforma extranjera cuenta como **importación (M)**, que se resta del PIB; la producción, el empleo y la mayor parte de la ganancia quedan en otro país. Solo se queda aquí una parte pequeña (por ejemplo, paquetería o impuestos).

### 3. OMC y T-MEC

- **OMC (Organización Mundial del Comercio):** organismo internacional con sede en Ginebra, que establece reglas del comercio entre países, resuelve disputas y promueve la reducción de aranceles y barreras. México es miembro desde 1995. Influye porque las reglas comunes permiten que lleguen a México productos de muchos países con aranceles previsibles.
- **T-MEC (Tratado entre México, Estados Unidos y Canadá):** acuerdo comercial vigente desde el 1 de julio de 2020, que sustituyó al TLCAN. Establece reglas de origen (por ejemplo, para el sector automotriz), libre comercio de la mayoría de los productos de la región, y normas laborales y ambientales. Influye en que muchos productos (autos, electrónicos, alimentos) lleguen a México desde Norteamérica con aranceles bajos o nulos, y en que productos mexicanos se exporten con facilidad.

> *Verifiquen y amplíen con fuentes oficiales (OMC, Secretaría de Economía, INEGI) y cítenlas aquí:* _[fuentes]_

---

## Actividad 2. Preparar la hoja

**Paso 1.** Se creó el archivo de Google Sheets **Encuesta_Equipo#** con una pestaña llamada **Respuestas** y estos encabezados en la fila 1:

| A | B | C | D | E | F | G |
|---|---|---|---|---|---|---|
| Fecha | Comida | Ropa | Apps | Criterio | Origen | Edad |

▶ *Captura de pantalla: [insertar imagen]*

## Actividad 3. Las preguntas

| Campo | Pregunta | Opciones |
|---|---|---|
| comida | ¿Dónde compras la mayor parte de tu comida? | Mercado o tianguis / Tienda de barrio / Supermercado / En línea |
| ropa | ¿Dónde compras tu ropa? | Negocio local / Tienda departamental / App internacional / Segunda mano |
| apps | ¿Con qué frecuencia compras en apps internacionales? | Nunca / Una vez al mes / Varias veces al mes / Cada semana |
| criterio | ¿Qué pesa más al comprar? | Precio / Calidad / Cercanía / Apoyar lo local / Marca |
| origen | ¿Sabes de dónde viene lo que compras? | Sí / A veces / No |
| edad | Rango de edad | Menos de 18 / 18 a 29 / 30 a 49 / 50 o más |

## Actividad 4. Crear el webhook

**Paso 2.** Se creó el escenario **Encuesta_Equipo#** en Make, con el módulo **Webhooks → Custom webhook**. URL copiada: `[pegar URL, no compartir públicamente]`

## Actividad 5. Generar la página con IA

Se usó el prompt de la práctica en una IA generativa (versión gratuita) y se guardó el resultado como **index.html** (adjunto). La URL del webhook se pegó en la constante `WEBHOOK_URL`.

**Paso 3.** En Make se presionó *Run once*, se llenó la encuesta y se envió una respuesta. El webhook detectó los siete campos: accion, comida, ropa, apps, criterio, origen, edad. ▶ *Captura: [insertar imagen]*

## Actividad 6. Ruta 1: guardar cada respuesta

- **Paso 4.** Después del webhook se agregó **Flow Control → Router**.
- **Paso 5.** En la primera ruta: **Google Sheets → Add a Row**, archivo Encuesta_Equipo#, pestaña Respuestas. Fecha = `{{formatDate(now; "DD/MM/YYYY HH:mm")}}`; Comida, Ropa, Apps, Criterio, Origen y Edad mapeados desde los campos del webhook.
- **Paso 6.** **Webhooks → Webhook Response**: Status `200`; Body `Respuesta registrada. Gracias por participar.`; Headers `Content-Type = text/plain; charset=utf-8` y `Access-Control-Allow-Origin = *`.
- **Paso 7.** Filtro de la ruta 1 (llave inglesa de la flecha, **después** de agregar los módulos): `accion` *Equal to* `respuesta`.

▶ *Captura de la ruta 1: [insertar imagen]*

## Actividad 7. Ruta 2: generar el reporte con IA

- **Paso 8.** **Google Sheets → Search Rows**, misma hoja y pestaña, *Maximum number of returned rows* = `200`.
- **Paso 9.** **Tools → Text aggregator**, Source Module: Search Rows. Text: `{{Comida}} | {{Ropa}} | {{Apps}} | {{Criterio}} | {{Origen}} | {{Edad}}` (se usa para que la IA se ejecute una sola vez y no gaste créditos por cada respuesta).
- **Paso 10.** **Make AI Agent**, Connection: *Make's AI Provider*. Input: `Respuestas de la encuesta (comida | ropa | apps | criterio | origen | edad):` seguido del texto del agregador (mapeado desde el panel). Instructions: el texto de la práctica, copiado completo.
- **Paso 11.** **Webhooks → Webhook Response**: Status `200`, Body = respuesta del AI Agent, mismos dos headers.
- **Paso 12.** Filtro de la ruta 2: `accion` *Equal to* `reporte`. Se guardó y activó el escenario con *Immediately as data arrives*.

▶ *Captura del escenario completo: [insertar imagen]*

## Actividad 8. Aplicar y verificar

**Paso 13.** index.html se subió al repositorio de prácticas y se publicó con GitHub Pages. URL: `[https://usuario.github.io/repositorio/]`. Se aplicó la encuesta a **20 personas** desde la página publicada. ▶ *Captura de la hoja con 20 filas.*

**Paso 14.** Reporte generado por la IA (pegar tal cual):

```
[pegar aquí el resultado del botón "Generar reporte"]
```

**Paso 15.** Verificación con COUNTIF en una celda libre de la hoja (ejemplos):

| Pregunta | Opción | Fórmula |
|---|---|---|
| Comida | Mercado o tianguis | `=COUNTIF(Respuestas!B:B; "Mercado o tianguis") / COUNTA(Respuestas!B2:B)` |
| Comida | Supermercado | `=COUNTIF(Respuestas!B:B; "Supermercado") / COUNTA(Respuestas!B2:B)` |
| Ropa | App internacional | `=COUNTIF(Respuestas!C:C; "App internacional") / COUNTA(Respuestas!C2:C)` |
| Apps | Nunca | `=COUNTIF(Respuestas!D:D; "Nunca") / COUNTA(Respuestas!D2:D)` |

(Si su Sheets está en configuración regional de México/EE. UU., use coma en lugar de punto y coma. Formato de celda: porcentaje.)

**Paso 16.** Comparación (llenar con sus datos):

| Pregunta / opción | % Sheets (COUNTIF) | % IA | ¿Coincide? |
|---|---|---|---|
| Comida – Mercado o tianguis | ▶ | ▶ | ▶ |
| Comida – Supermercado | ▶ | ▶ | ▶ |
| Ropa – App internacional | ▶ | ▶ | ▶ |
| Apps – Nunca | ▶ | ▶ | ▶ |

---

## Preguntas del informe

> Plantillas de respuesta con ≥5 renglones. Sustituyan los ▶ por sus resultados reales y ajusten el sentido si sus datos dicen otra cosa.

**1. ¿El consumo de su comunidad es más local o más global? ¿En qué productos se nota más?**

Según la encuesta aplicada a 20 personas, el consumo de nuestra comunidad es más ▶ (local/global). En comida, el ▶ % compra en mercado, tianguis o tienda de barrio y el ▶ % en supermercado o en línea. En ropa, el ▶ % compra en negocios locales o de segunda mano, mientras que el ▶ % usa tiendas departamentales o apps internacionales. Lo global se nota más en ▶ (por ejemplo, ropa y artículos de bajo precio por apps), y lo local en ▶ (por ejemplo, alimentos frescos como pescado, frutas y verduras). El criterio que más pesa es ▶ (precio/calidad/cercanía/apoyar lo local/marca), lo que explica este patrón. Por edad, el grupo de ▶ compra más en apps internacionales que el de ▶.

**2. ¿Qué efecto tiene en el PIB y en el empleo de Mazatlán que las personas compren en apps internacionales?**

Cada compra en una app extranjera cuenta como importación, que resta al PIB, porque el valor se genera fuera del país. El dinero sale de la economía de Mazatlán y no paga sueldos, rentas ni proveedores de la ciudad, lo que reduce el efecto multiplicador del consumo local. Esto puede disminuir las ventas de comercios pequeños, que son una fuente importante de empleo en la ciudad, y con ello las horas de trabajo y la creación de nuevos puestos. También se pierde recaudación local y estatal ligada al comercio establecido. Aun así, estas apps ofrecen precios bajos y variedad, por lo que la solución no es prohibirlas sino equilibrar el consumo. En nuestra encuesta, el ▶ % compra al menos una vez al mes en apps internacionales, lo que muestra un flujo de dinero hacia afuera de ▶ (bajo/medio/alto) alcance.

**3. ¿Qué impacto ambiental tiene el transporte y el empaque de lo que se compra en línea desde otro país?**

Un producto comprado en el extranjero viaja miles de kilómetros por barco, avión y camión, y cada tramo consume combustible y emite CO₂. Los envíos individuales y pequeños son menos eficientes que el transporte de mercancía a granel para una tienda, y el envío aéreo urgente emite mucho más por kilo que el marítimo. Además, cada paquete usa cajas, bolsas de plástico, relleno y cinta que suelen desecharse de inmediato, generando residuos difíciles de reciclar. Las devoluciones y reenvíos multiplican la huella. Comprar local acorta la cadena, reduce el transporte y permite usar menos empaque (envases reutilizables, bolsas propias). Además, el ▶ % de los encuestados no sabe o solo a veces sabe de dónde viene lo que compra, por lo que no ve este impacto.

**4. ¿Coincidieron los porcentajes de la IA con los de Sheets? ¿Qué aprendieron sobre verificar a la IA?**

Al comparar ▶ preguntas, los porcentajes de la IA ▶ (coincidieron / difirieron en ▶ puntos en ▶). Esto se comprobó con fórmulas COUNTIF sobre las 20 respuestas, que son exactas y repetibles. Aprendimos que una IA de lenguaje puede redactar muy bien un reporte y aun así equivocarse al contar o redondear, y que por eso su resultado debe tratarse como un borrador, no como una verdad. Verificar con una fuente determinista (la hoja de cálculo) es parte del trabajo profesional cuando se automatiza un análisis. También aprendimos que las instrucciones claras (usar únicamente los datos, formato fijo) y el Text aggregator mejoran la calidad y reducen el gasto de créditos. Si hubo diferencias, la corrección correcta es siempre la de Sheets.

**5. ¿Qué acción concreta propondrían para impulsar el consumo local en su colonia?**

Proponemos organizar un **mercadito local mensual** en un parque o calle de la colonia, con productores, pescadores y negocios de barrio, anunciado en grupos de WhatsApp y redes vecinales. Se pediría a los comercios aceptar pagos por transferencia o QR para competir en comodidad con las apps. Se haría un directorio digital sencillo (mapa o lista) de negocios de la colonia con sus productos y horarios, que puede construirse con las mismas herramientas de esta práctica (Sheets y GitHub Pages). Para reducir empaques, se invitaría a llevar bolsas y envases propios, con un pequeño descuento. La meta sería que al menos ▶ de cada 10 vecinos compre una vez al mes en un negocio local; se mediría con una nueva encuesta en 3 meses.

---

## Conclusión general

▶ *(3–5 renglones: qué aprendieron sobre el consumo de su comunidad, el uso de Make y la verificación de la IA.)*

## Evidencias

- Archivo `index.html` y URL de GitHub Pages.
- Capturas: hoja con 20 respuestas, escenario de Make, reporte de la IA, fórmulas COUNTIF.