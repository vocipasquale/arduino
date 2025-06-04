const int onOffM1 = 9;
const int controlPin1M1 = 3;
const int controlPin2M1 = 2;

const int onOffM2 = 10;
const int controlPin1M2 = 5;
const int controlPin2M2 = 4;

void setup() {

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
  //STOP per 2 secondi
  digitalWrite(onOffM1, LOW);
  digitalWrite(controlPin1M1, LOW);
  digitalWrite(controlPin2M1, LOW);
  digitalWrite(onOffM2, LOW);
  digitalWrite(controlPin1M2, LOW);
  digitalWrite(controlPin2M2, LOW);
  delay(2000);
  
  //ACCESO in una direzione per 2 secondi
  digitalWrite(onOffM1, HIGH);
  digitalWrite(controlPin1M1, HIGH);
  digitalWrite(controlPin2M1, LOW);
  digitalWrite(onOffM2, HIGH);
  digitalWrite(controlPin1M2, HIGH);
  digitalWrite(controlPin2M2, LOW);
  delay(2000);

  //STOP per 2 secondi
  digitalWrite(onOffM1, LOW);
  digitalWrite(controlPin1M1, LOW);
  digitalWrite(controlPin2M1, LOW);
  digitalWrite(onOffM2, LOW);
  digitalWrite(controlPin1M2, LOW);
  digitalWrite(controlPin2M2, LOW);
  delay(2000);

  //ACCESO in nell'altra direzione per 2 secondi
  digitalWrite(onOffM1, HIGH);
  digitalWrite(controlPin1M1, LOW);
  digitalWrite(controlPin2M1, HIGH);
  digitalWrite(onOffM2, HIGH);
  digitalWrite(controlPin1M2, LOW);
  digitalWrite(controlPin2M2, HIGH);
  delay(2000);

  //STOP per 2 secondi
  digitalWrite(onOffM1, LOW);
  digitalWrite(controlPin1M1, LOW);
  digitalWrite(controlPin2M1, LOW);
  digitalWrite(onOffM2, LOW);
  digitalWrite(controlPin1M2, LOW);
  digitalWrite(controlPin2M2, LOW);
  delay(2000);

  //RUOTA in una direzione per 2 secondi
  digitalWrite(onOffM1, HIGH);
  digitalWrite(controlPin1M1, LOW);
  digitalWrite(controlPin2M1, HIGH);
  digitalWrite(onOffM2, HIGH);
  digitalWrite(controlPin1M2, HIGH);
  digitalWrite(controlPin2M2, LOW);
  delay(2000);

  //STOP per 2 secondi
  digitalWrite(onOffM1, LOW);
  digitalWrite(controlPin1M1, LOW);
  digitalWrite(controlPin2M1, LOW);
  digitalWrite(onOffM2, LOW);
  digitalWrite(controlPin1M2, LOW);
  digitalWrite(controlPin2M2, LOW);
  delay(2000);

  //RUOTA in una direzione per 2 secondi
  digitalWrite(onOffM1, HIGH);
  digitalWrite(controlPin1M1, HIGH);
  digitalWrite(controlPin2M1, LOW);
  digitalWrite(onOffM2, HIGH);
  digitalWrite(controlPin1M2, LOW);
  digitalWrite(controlPin2M2, HIGH);
  delay(2000);

}
