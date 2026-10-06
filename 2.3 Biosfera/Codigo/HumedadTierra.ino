const int PIN_SENSOR = A0;   // Señal del sensor
const int LED_PIN    = 13;   // LED integrado (alerta de riego)

// Umbral: ajusta según las lecturas que veas en el Monitor Serie
// En la mayoría de sensores: lectura ALTA = tierra SECA, lectura BAJA = tierra HÚMEDA
const int UMBRAL_HUMEDAD = 400; 

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("=== Monitor de humedad del suelo ===");
}

void loop() {
  int lectura = analogRead(PIN_SENSOR);

  // Mapeo invertido: a mayor lectura (más seco), menor porcentaje de humedad
  int porcentaje = map(lectura, 0, 1023, 100, 0); 
  porcentaje = constrain(porcentaje, 0, 100);

  Serial.print("Lectura: ");
  Serial.print(lectura);
  Serial.print("  |  Humedad: ");
  Serial.print(porcentaje);
  Serial.print("%  |  Estado: ");

  // Si la lectura supera el umbral -> TIERRA SECA -> ENCIENDE LED
  if (lectura > UMBRAL_HUMEDAD) {
    Serial.println("TIERRA SECA -> Se recomienda regar");
    digitalWrite(LED_PIN, HIGH); // LED Encendido
  } 
  // Si la lectura está por debajo del umbral -> TIERRA HÚMEDA -> APAGA LED
  else {
    Serial.println("TIERRA HUMEDA -> No necesita riego");
    digitalWrite(LED_PIN, LOW);  // LED Apagado
  }

  delay(1000);
}
