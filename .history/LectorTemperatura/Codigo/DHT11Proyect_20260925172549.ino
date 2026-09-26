#include <WiFiS3.h>
#include <WiFiSSLClient.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Mega_2.4G_9887"; // debe ser red de 2.4 GHz
const char* password = "9FXbZRuD";
const char* host = "hook.us2.make.com"; // ajusta segun tu zona de Make
const char* webhookPath = "/t40wbzqiixrba4jvotcds2z8bok9xjmb"; // parte despues del dominio

const int ledPin = 13;
const int ledParpadeoPin = 12; // LED que parpadea cuando la temperatura vuelve a la normalidad
const float UMBRAL_TEMP = 27.40; // grados Celsius

bool estadoCaliente = false;
float ultimaTemp = 25.30;
float ultimaHumedad = 65;
unsigned long ultimaLectura = 0;
const unsigned long INTERVALO_LECTURA = 2000;

// --- Control del parpadeo no bloqueante ---
bool parpadeoActivo = false;
bool estadoLedParpadeo = false;
unsigned long ultimoCambioParpadeo = 0;
const unsigned long INTERVALO_PARPADEO = 500; // ms entre cada cambio de estado del LED

WiFiServer server(80);
WiFiSSLClient client;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(ledPin, OUTPUT);
  pinMode(ledParpadeoPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(ledParpadeoPin, LOW);

  Serial.print("Conectando a Wi-Fi");
  
  // Iniciar la conexión
  WiFi.begin(ssid, password);

  // Esperar hasta estar conectado Y tener una IP válida asignada por el router
  while (WiFi.status() != WL_CONNECTED || WiFi.localIP() == IPAddress(0, 0, 0, 0)) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n¡Conexión exitosa!");
  Serial.print("Servidor listo en: http://");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  if (millis() - ultimaLectura >= INTERVALO_LECTURA) {
    ultimaLectura = millis();
    leerYEvaluar();
  }

  manejarParpadeo();

  WiFiClient webClient = server.available();
  if (webClient) {
    while (webClient.connected() && webClient.available()) {
      char c = webClient.read();
      if (c == '\n') break;
    }
    enviarPagina(webClient);
    webClient.stop();
  }
}

void leerYEvaluar() {
  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();

  if (isnan(humedad) || isnan(temperatura)) {
    Serial.println("Error al leer el sensor DHT11");
    return;
  }

  ultimaTemp = temperatura;
  ultimaHumedad = humedad;
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" *C");

  bool estaCalienteAhora = (temperatura >= UMBRAL_TEMP);
  digitalWrite(ledPin, estaCalienteAhora ? HIGH : LOW);

  if (estaCalienteAhora && !estadoCaliente) {
    // Pasó de normal a caliente: apaga el parpadeo si estaba activo
    enviarAlertaMake(temperatura);
    parpadeoActivo = false;
    digitalWrite(ledParpadeoPin, LOW);
  } else if (!estaCalienteAhora && estadoCaliente) {
    // Pasó de caliente a normal: activa el parpadeo de aviso
    parpadeoActivo = true;
  }

  estadoCaliente = estaCalienteAhora;
}

void manejarParpadeo() {
  if (!parpadeoActivo) return;

  unsigned long ahora = millis();
  if (ahora - ultimoCambioParpadeo >= INTERVALO_PARPADEO) {
    ultimoCambioParpadeo = ahora;
    estadoLedParpadeo = !estadoLedParpadeo;
    digitalWrite(ledParpadeoPin, estadoLedParpadeo ? HIGH : LOW);
  }
}

void enviarPagina(WiFiClient &webClient) {
  webClient.println("HTTP/1.1 200 OK");
  webClient.println("Content-Type: text/html");
  webClient.println("Connection: close");
  webClient.println();
  webClient.println("<!DOCTYPE html><html><head>");
  webClient.println("<meta name='viewport' content=");
  webClient.println("'width=device-width, initial-scale=1'>");
  webClient.println("<meta http-equiv='refresh' content='5'>");
  webClient.println("<style>");
  webClient.println("body{font-family:sans-serif;text-align:center;}");
  webClient.println("body{margin-top:50px;}");
  webClient.println("h1{font-size:28px;}");
  webClient.println(".valor{font-size:48px;font-weight:bold;}");
  webClient.println("</style></head><body>");
  webClient.println("<h1>Monitor del cuarto</h1>");
  webClient.print("<p>Temperatura</p><p class='valor'>");
  webClient.print(ultimaTemp);
  webClient.println(" &deg;C</p>");
  webClient.print("<p>Humedad</p><p class='valor'>");
  webClient.print(ultimaHumedad);
  webClient.println(" %</p>");
  webClient.print("<p>Estado: <b>");
  webClient.print(estadoCaliente ? "CALIENTE (LED encendido)" : "Normal");
  webClient.println("</b></p>");
  webClient.println("</body></html>");
}

void enviarAlertaMake(float temp) {
  if (client.connect(host, 443)) {
    String jsonPayload = "{\"temperatura\":" + String(temp) + "}";
    client.println("POST " + String(webhookPath) + " HTTP/1.1");
    client.println("Host: " + String(host));
    client.println("Content-Type: application/json");
    client.println("Content-Length: " + String(jsonPayload.length()));
    client.println("Connection: close");
    client.println();
    client.println(jsonPayload);
    Serial.println("Alerta enviada a Make");
  } else {
    Serial.println("Fallo la conexion al webhook");
  }
  client.stop();
}