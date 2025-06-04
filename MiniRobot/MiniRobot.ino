#include <SoftwareSerial.h>

#define __BAUD 38400

// Pin per il modulo Bluetooth
SoftwareSerial BTSerial(6, 7); // RX, TX

const int onOffM1 = 9;
const int controlPin1M1 = 3;
const int controlPin2M1 = 2;

const int onOffM2 = 10;
const int controlPin1M2 = 5;
const int controlPin2M2 = 4;

void setup() {
  Serial.begin(__BAUD);
  BTSerial.begin(__BAUD);

  pinMode(controlPin1M1, OUTPUT);
  pinMode(controlPin2M1, OUTPUT);
  pinMode(onOffM1, OUTPUT);
  digitalWrite(onOffM1, LOW);

  pinMode(controlPin1M2, OUTPUT);
  pinMode(controlPin2M2, OUTPUT);
  pinMode(onOffM2, OUTPUT);
  digitalWrite(onOffM2, LOW);
}

void loop() {
  if(BTSerial.available()){
    // Leggi i dati in arrivo
    String data = BTSerial.readStringUntil('\n');
    // Visualizza i dati sul monitor seriale
    Serial.println("Ricevuto: " + data);
    
    switch (data){
      case "AVANTI":
        avanti();
        break;
      case "INDIETRO":
        indietro();
        break;
      case "SX":
        sinistra();
        break;
      case "DX":
        dx();
        break;
      default:
        stop();
    }
  }else{
    stop();
  }

  delay(10);
  
  /*
  stop();
  delay(2000);

  avanti();
  delay(2000);

  stop();
  delay(2000);  

  indietro();
  delay(2000);

  stop();
  delay(2000);

  dx();
  delay(2000);

  stop();
  delay(2000);
  
  sx();
  delay(2000);
*/
}

void avanti(){
  digitalWrite(onOffM1, HIGH);
  digitalWrite(controlPin1M1, LOW);
  digitalWrite(controlPin2M1, HIGH);
  digitalWrite(onOffM2, HIGH);
  digitalWrite(controlPin1M2, HIGH);
  digitalWrite(controlPin2M2, LOW);
}

void indietro(){
  digitalWrite(onOffM1, HIGH);
  digitalWrite(controlPin1M1, HIGH);
  digitalWrite(controlPin2M1, LOW);
  digitalWrite(onOffM2, HIGH);
  digitalWrite(controlPin1M2, LOW);
  digitalWrite(controlPin2M2, HIGH);
}


void sx(){
  digitalWrite(onOffM1, HIGH);
  digitalWrite(controlPin1M1, HIGH);
  digitalWrite(controlPin2M1, LOW);
  digitalWrite(onOffM2, HIGH);
  digitalWrite(controlPin1M2, HIGH);
  digitalWrite(controlPin2M2, LOW);
}


void dx(){
  digitalWrite(onOffM1, HIGH);
  digitalWrite(controlPin1M1, LOW);
  digitalWrite(controlPin2M1, HIGH);
  digitalWrite(onOffM2, HIGH);
  digitalWrite(controlPin1M2, LOW);
  digitalWrite(controlPin2M2, HIGH);
}

void stop(){
  digitalWrite(onOffM1, LOW);
  digitalWrite(controlPin1M1, LOW);
  digitalWrite(controlPin2M1, LOW);
  digitalWrite(onOffM2, LOW);
  digitalWrite(controlPin1M2, LOW);
  digitalWrite(controlPin2M2, LOW);
}

