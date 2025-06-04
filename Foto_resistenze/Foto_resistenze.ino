const int sxSensor = A0;
const int avSensor = A1;
const int dxSensor = A2;

int sxOffset = 0;
int avOffset = 0;
int dxOffset = 0;

int sxValue = 0;
int avValue = 0;
int dxValue = 0;


void setup() {
  Serial.begin(9600);
  /* a parità di luce le tre fotoresistenze 
  hanno una variazione di resistenza molto diversa tra loro,
  provo a ricostruire un valore proporzionale e lineare 
  dando per scontato che il valore massimo restituito 
  in tutti e tre i casi è sempre 1023
  */
  
  sxOffset = analogRead(sxSensor);
  delay(5);

  avOffset = analogRead(avSensor);
  delay(5);

  dxOffset = analogRead(dxSensor); 
  delay(5);
}

void loop() {
  sxValue = map(analogRead(sxSensor), sxOffset, 1023, 1, 10);
  delay(5);

  avValue = map(analogRead(avSensor), avOffset, 1023, 1, 10);
  delay(5);

  dxValue = map(analogRead(dxSensor), dxOffset, 1023, 1, 10); 
  delay(5);

  Serial.print("sx: ");
  Serial.println(sxValue);

  Serial.print("av: ");
  Serial.println(avValue);

  Serial.print("dx: ");
  Serial.println(dxValue);

  analizza(sxValue, avValue, dxValue);
  delay(1000);

}


void analizza(int sx, int av, int dx){
  char maggiore;
  int valore = 0;

  if (sx > av && sx > dx) {
    maggiore = 's';
    valore = sx;
  } else if (av > sx && av > dx) {
    maggiore = 'a';
    valore = av;
  } else {
    maggiore = 'd';
    valore = dx;
  }

  Serial.print("maggiore: ");
  Serial.print(maggiore);
  Serial.print(" ");
  Serial.println(valore);
  
}
