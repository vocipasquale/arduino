#include <SoftwareSerial.h>

SoftwareSerial BTSerial(6,7); //RX: pin 6 - TX: pin 7

#define __BAUD 38400

void setup(){
  Serial.begin(__BAUD);
  BTSerial.begin(__BAUD);
  delay(1500);

}

void loop(){
  if(BTSerial.available()){
    Serial.write((BTSerial.read()));
  }

  if(Serial.available()){
    BTSerial.write(Serial.read());
  }
}
