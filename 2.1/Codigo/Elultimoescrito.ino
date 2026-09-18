#include <EEPROM.h>
#include "Arduino_LED_Matrix.h"

// ==================================================
// MATRIZ LED INTEGRADA DEL UNO R4 WIFI
// ==================================================

ArduinoLEDMatrix matrix;


// ==================================================
// LOS 10 LEDs EXTERNOS
// PINES 4 AL 13
// ==================================================

const int primerPin = 4;
const int ultimoPin = 13;


// ==================================================
// EEPROM
// ==================================================

const int direccionEEPROM = 0;

int secuencia;


// ==================================================
// SETUP
// ==================================================

void setup() {
  // ------------------------------------------
  // Configurar los 10 LEDs
  // ------------------------------------------
  for (int pin = primerPin; pin <= ultimoPin; pin++) {

    pinMode(pin, OUTPUT);

    digitalWrite(pin, LOW);
  }

  // ------------------------------------------
  // Iniciar matriz integrada
  // ------------------------------------------

  matrix.begin();

  matrix.clear();


  // ------------------------------------------
  // Leer secuencia anterior
  // ------------------------------------------

  secuencia = EEPROM.read(direccionEEPROM);

  // ------------------------------------------
  // Comprobar valor válido
  // ------------------------------------------

  if (secuencia > 2) {

    secuencia = 0;
  }

  // ------------------------------------------
  // Cambiar a la siguiente secuencia
  // ------------------------------------------

  secuencia++;

  if (secuencia > 2) {

    secuencia = 0;
  }

  // ------------------------------------------
  // Guardar nueva secuencia
  // ------------------------------------------

  EEPROM.update(direccionEEPROM, secuencia);
}


// ==================================================
// LOOP
// ==================================================

void loop() {

  // ==========================================
  // SECUENCIA 1
  // PARES Y NONES
  // ==========================================

  if (secuencia == 0) {

    secuenciaParesNones();
  }


  // ==========================================
  // SECUENCIA 2
  // OLEAJE
  // ==========================================

  else if (secuencia == 1) {

    secuenciaOleaje();
  }


  // ==========================================
  // SECUENCIA 3
  // CUENTA REGRESIVA + BOOM
  // ==========================================

  else {

    secuenciaBoom();
  }
}


// ==================================================
// SECUENCIA 1
// PARES → NONES
// ==================================================

void secuenciaParesNones() {

  // ------------------------------------------
  // PARES
  // 4, 6, 8, 10, 12
  // ------------------------------------------

  apagarTodos();

  for (int pin = 4; pin <= 13; pin += 2) {

    digitalWrite(pin, HIGH);
  }

  delay(1000);


  // ------------------------------------------
  // NONES
  // 5, 7, 9, 11, 13
  // ------------------------------------------

  apagarTodos();

  for (int pin = 5; pin <= 13; pin += 2) {

    digitalWrite(pin, HIGH);
  }

  delay(1000);
}


// ==================================================
// SECUENCIA 2
// TODOS → 4→13 → 13→4
// ==================================================

void secuenciaOleaje() {

  // ------------------------------------------
  // TODOS ENCENDIDOS
  // ------------------------------------------

  for (int pin = primerPin; pin <= ultimoPin; pin++) {

    digitalWrite(pin, HIGH);
  }

  delay(1000);


  // ------------------------------------------
  // OLEAJE 4 → 13
  // ------------------------------------------

  for (int pin = primerPin; pin <= ultimoPin; pin++) {

    apagarTodos();

    digitalWrite(pin, HIGH);

    delay(150);
  }


  // ------------------------------------------
  // OLEAJE 13 → 4
  // ------------------------------------------

  for (int pin = ultimoPin; pin >= primerPin; pin--) {

    apagarTodos();

    digitalWrite(pin, HIGH);

    delay(150);
  }
}


// ==================================================
// SECUENCIA 3
// 10 SEGUNDOS + BOOM
// ==================================================

void secuenciaBoom() {

  // ------------------------------------------
  // Limpiar matriz
  // ------------------------------------------

  matrix.clear();


  // ------------------------------------------
  // Encender los 10 LEDs
  // ------------------------------------------

  for (int pin = primerPin; pin <= ultimoPin; pin++) {

    digitalWrite(pin, HIGH);
  }


  // ------------------------------------------
  // CUENTA REGRESIVA
  // ------------------------------------------

  for (int segundo = 10; segundo >= 1; segundo--) {

    mostrarNumero(segundo);


    // ----------------------------------------
    // Apagar un LED por segundo
    //
    // 10 → pin 4
    // 9  → pin 5
    // 8  → pin 6
    // ...
    // 1  → pin 13
    // ----------------------------------------

    int led = primerPin + (10 - segundo);

    digitalWrite(led, LOW);

    delay(1000);
  }


  // ------------------------------------------
  // Todos apagados
  // ------------------------------------------

  apagarTodos();

  matrix.clear();

  delay(300);


  // ------------------------------------------
  // BOOM
  // ------------------------------------------

  mostrarBOOM();


  delay(3000);

  matrix.clear();

  delay(1000);
}


// ==================================================
// APAGAR TODOS LOS LEDs
// ==================================================

void apagarTodos() {

  for (int pin = primerPin; pin <= ultimoPin; pin++) {

    digitalWrite(pin, LOW);
  }
}


// ==================================================
// MOSTRAR NÚMERO
// ==================================================
//
// La matriz del UNO R4 WiFi es 12 columnas x 8 filas.
// Aquí usamos 12x8.
//

void mostrarNumero(int numero) {

  // Limpiar
  matrix.clear();


  // ------------------------------------------
  // Dígitos 0-9
  // ------------------------------------------

  const uint8_t numeros[10][8] = {

    // 0
    {
      0b00111100,
      0b01100110,
      0b11000011,
      0b11000011,
      0b11000011,
      0b11000011,
      0b01100110,
      0b00111100
    },

    // 1
    {
      0b00011000,
      0b00111000,
      0b00011000,
      0b00011000,
      0b00011000,
      0b00011000,
      0b01111110,
      0b00000000
    },

    // 2
    {
      0b00111100,
      0b01100110,
      0b00000110,
      0b00001100,
      0b00011000,
      0b00110000,
      0b01111110,
      0b00000000
    },

    // 3
    {
      0b00111100,
      0b01100110,
      0b00000110,
      0b00011100,
      0b00000110,
      0b00000110,
      0b01100110,
      0b00111100
    },

    // 4
    {
      0b00001100,
      0b00011100,
      0b00101100,
      0b01001100,
      0b01111110,
      0b00001100,
      0b00001100,
      0b00000000
    },

    // 5
    {
      0b01111110,
      0b01100000,
      0b01100000,
      0b01111100,
      0b00000110,
      0b00000110,
      0b01100110,
      0b00111100
    },

    // 6
    {
      0b00111100,
      0b01100110,
      0b01100000,
      0b01111100,
      0b01100110,
      0b01100110,
      0b01100110,
      0b00111100
    },

    // 7
    {
      0b01111110,
      0b00000110,
      0b00001100,
      0b00011000,
      0b00110000,
      0b00110000,
      0b00110000,
      0b00000000
    },

    // 8
    {
      0b00111100,
      0b01100110,
      0b01100110,
      0b00111100,
      0b01100110,
      0b01100110,
      0b01100110,
      0b00111100
    },

    // 9
    {
      0b00111100,
      0b01100110,
      0b01100110,
      0b00111110,
      0b00000110,
      0b00000110,
      0b01100110,
      0b00111100
    }
  };


  // ------------------------------------------
  // Para 1-9
  // ------------------------------------------

  if (numero >= 1 && numero <= 9) {

    uint32_t frame[3] = {0, 0, 0};

    // Copiar el dibujo de 8x8
    for (int fila = 0; fila < 8; fila++) {

      uint8_t filaDatos = numeros[numero][fila];

      for (int columna = 0; columna < 8; columna++) {

        if (filaDatos & (1 << (7 - columna))) {

          int posicion = fila * 12 + columna + 2;

          if (posicion < 96) {

            int bloque = posicion / 32;

            int bit = 31 - (posicion % 32);

            frame[bloque] |= ((uint32_t)1 << bit);
          }
        }
      }
    }

    matrix.loadFrame(frame);
  }


  // ------------------------------------------
  // Para 10
  // ------------------------------------------

  else if (numero == 10) {

    uint32_t frame[3] = {0, 0, 0};


    // Dígito 1
    for (int fila = 0; fila < 8; fila++) {

      uint8_t datos = numeros[1][fila];

      for (int columna = 0; columna < 4; columna++) {

        if (datos & (1 << (7 - columna))) {

          int posicion = fila * 12 + columna;

          int bloque = posicion / 32;

          int bit = 31 - (posicion % 32);

          frame[bloque] |= ((uint32_t)1 << bit);
        }
      }
    }


    // Dígito 0
    for (int fila = 0; fila < 8; fila++) {

      uint8_t datos = numeros[0][fila];

      for (int columna = 0; columna < 8; columna++) {

        if (datos & (1 << (7 - columna))) {

          int posicion = fila * 12 + columna + 5;

          if (posicion < 96) {

            int bloque = posicion / 32;

            int bit = 31 - (posicion % 32);

            frame[bloque] |= ((uint32_t)1 << bit);
          }
        }
      }
    }


    matrix.loadFrame(frame);
  }
}


// ==================================================
// MOSTRAR BOOM
// ==================================================

void mostrarBOOM() {

  // ------------------------------------------
  // B
  // ------------------------------------------

  const uint8_t B[8] = {

    0b11111100,
    0b11000110,
    0b11000110,
    0b11111100,
    0b11000110,
    0b11000110,
    0b11111100,
    0b00000000
  };


  // ------------------------------------------
  // O
  // ------------------------------------------

  const uint8_t O[8] = {

    0b00111100,
    0b01100110,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11000011,
    0b01100110,
    0b00111100
  };


  // ------------------------------------------
  // M
  // ------------------------------------------

  const uint8_t M[8] = {

    0b11000011,
    0b11100111,
    0b11111111,
    0b11011011,
    0b11000011,
    0b11000011,
    0b11000011,
    0b00000000
  };


  // ------------------------------------------
  // B
  // ------------------------------------------

  mostrarLetra(B);

  delay(400);


  // ------------------------------------------
  // O
  // ------------------------------------------

  mostrarLetra(O);

  delay(400);


  // ------------------------------------------
  // O
  // ------------------------------------------

  mostrarLetra(O);

  delay(400);


  // ------------------------------------------
  // M
  // ------------------------------------------

  mostrarLetra(M);

  delay(700);
}


// ==================================================
// MOSTRAR UNA LETRA
// ==================================================

void mostrarLetra(const uint8_t letra[8]) {

  uint32_t frame[3] = {
    0,
    0,
    0
  };


  for (int fila = 0; fila < 8; fila++) {

    for (int columna = 0; columna < 8; columna++) {

      if (letra[fila] & (1 << (7 - columna))) {

        int posicion = fila * 12 + columna + 2;


        if (posicion < 96) {

          int bloque = posicion / 32;

          int bit = 31 - (posicion % 32);

          frame[bloque] |= ((uint32_t)1 << bit);
        }
      }
    }
  }


  matrix.loadFrame(frame);
}