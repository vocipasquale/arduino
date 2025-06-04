#include <SoftwareSerial.h>

#define __BAUD 38400

// Pin per il modulo Bluetooth
SoftwareSerial BTSerial(6, 7); // RX, TX



void setup() {
  Serial.begin(__BAUD);
  BTSerial.begin(__BAUD);
  
  
}

void loop() {
  if(BTSerial.available()){
    Serial.write((BTSerial.read()));
  }

  if(Serial.available()){
    BTSerial.write(Serial.read());
  }
}
