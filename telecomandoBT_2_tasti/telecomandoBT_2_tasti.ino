
#include <SoftwareSerial.h>

#define __BAUD 38400

// HC-05:
// TXD -> Arduino D10
// RXD <- Arduino D11 tramite partitore
SoftwareSerial bluetooth(10, 11);

const byte PIN_A = 2;
const byte PIN_B = 3;

const unsigned long DEBOUNCE_MS = 25;
const unsigned long MIN_PRESS_MS = 500;
const unsigned long MAX_PRESS_MS = 1000;

struct Pulsante {
  byte pin;
  bool letturaPrecedente;
  bool statoStabile;
  unsigned long ultimoCambio;
  unsigned long inizioPressione;
};

Pulsante A = {PIN_A, HIGH, HIGH, 0, 0};
Pulsante B = {PIN_B, HIGH, HIGH, 0, 0};

void controllaPulsante(Pulsante &p, char comando) {
  unsigned long adesso = millis();
  bool lettura = digitalRead(p.pin);

  // Rileva un cambiamento del segnale grezzo
  if (lettura != p.letturaPrecedente) {
    p.letturaPrecedente = lettura;
    p.ultimoCambio = adesso;
  }

  // Accetta il nuovo stato solo dopo l'antirimbalzo
  if ((adesso - p.ultimoCambio >= DEBOUNCE_MS) &&
      (lettura != p.statoStabile)) {

    p.statoStabile = lettura;

    if (p.statoStabile == LOW) {
      // Inizio della pressione stabile
      p.inizioPressione = adesso;
    } else {
      // Rilascio: calcola la durata
      unsigned long durata =
          adesso - p.inizioPressione;

      if (durata >= MIN_PRESS_MS &&
          durata <= MAX_PRESS_MS) {

        //bluetooth.print("CMD:");
        bluetooth.println(comando);

        Serial.print("Inviato: ");
        Serial.println(comando);
      } else {
        Serial.print("Pressione ignorata: ");
        Serial.print(durata);
        Serial.println(" ms");
      }
    }
  }
}

void setup() {
  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);

  Serial.begin(__BAUD);
  bluetooth.begin(__BAUD);

  Serial.println("Telecomando Bluetooth pronto");
}

void loop() {
  controllaPulsante(A, 'A');
  controllaPulsante(B, 'B');
}
