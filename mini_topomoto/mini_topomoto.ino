//controllo 2 motori DC da 3,5 volt
/**
Semplice robot che avanza per un numero casuale di secondi in avanti.
Al timeout (casuale), il robot si ferma, ruota in una delle due direzioni per un tempo
casuale e poi avanza.
Ci sono due pulsanti che intercettano il contatto con un ostacolo; quando di riceve 
l'impulso da almeno un pulsante, il robot si ferma, indietreggia, e avanza in una direzione casuale.

*/

const int pinStopA = 2;
const int pinStopB = 3;
const int pinMtSx = 11;
const int pinMtDx = 10;
const int pinCtrlASx = 13;
const int pinCtrlBSx = 12;
const int pinCtrlADx = 8;
const int pinCtrlBDx = 7;

boolean stop = false;

char fase; //A: avanti - I: indietro - S: stop - R: ruota 

const long indietroTimeout = 1500; // 1,5 secondi
const long stopTimeout = 1000; // 1 secondo 
long ruotaTimeout = 0; 

long stopTimer = 0;
long indietroTimer = 0;
long ruotaTimer = 0;

int speedSx = 0;
int speedDx = 0;

void setup() {
  Serial.begin(9600);  
  
  pinMode(pinStopA, INPUT_PULLUP);
  pinMode(pinStopB, INPUT_PULLUP);
  pinMode(pinCtrlASx, OUTPUT);
  pinMode(pinCtrlBSx, OUTPUT);
  pinMode(pinCtrlADx, OUTPUT);
  pinMode(pinCtrlBDx, OUTPUT);

  //imposto direzione avanti
  avanti();
  fase = 'A';
  speedSx = 255;
  speedDx = 255;

  stopTimer = 0;
  indietroTimer = 0;
  ruotaTimer = 0;
}

void loop() {
  Serial.print("\tstopTimer: " + String(stopTimer));
  Serial.print("\tindietroTimer: " + String(indietroTimer));
  Serial.print("\truotaTimer: " + String(ruotaTimer));
  Serial.print("\tspeedSx: " + String(speedSx));
  Serial.println("\tspeedDx: " + String(speedDx));

  
  //se almeno uno dei due pulsanti è "schiacciato" il robot si deve fermare!
  stop = digitalRead(pinStopA) == LOW || digitalRead(pinStopB) == LOW;
  if(stop && stopTimer == 0){
    fase = 'S';
    stopTimer = millis(); //inizio la fase di stop
    speedSx = 0;
    speedDx = 0;
  }


  switch (fase) {
    case 'S':
      Serial.println("STOP!");
      
      if(millis() - stopTimer >= stopTimeout){//tempo di stop scaduto!
        stopTimer = 0;
        indietroTimer = millis();
        indietro();
        fase = 'I';
        speedSx = 123;
        speedDx = 123;
      }
      break;
    case 'I':
      Serial.println("INDIETRO!");
      if(millis() - indietroTimer >= indietroTimeout){
        indietroTimer = 0;
        ruotaTimeout = random(2000, 4001); //timeout casuale da 2 a 4 secondi
        ruotaTimer = millis();
        ruota();
        fase = 'R';
        speedSx = 123;
        speedDx = 123;
      }
      break;
    case 'R':
      Serial.println("RUOTA!");
      if(millis() - ruotaTimer >= ruotaTimeout){
        ruotaTimer = 0;
        avanti();
        fase = 'A';
        speedSx = 255;
        speedDx = 255;
      }
      break;
    case 'A':
      Serial.println("AVANTI!");
      speedSx = 255;
      speedDx = 255;
      avanti();
  }


  analogWrite(pinMtSx, speedSx);  
  analogWrite(pinMtDx, speedDx);



/*
  if(stop) { //&& timer == 0){
    Serial.println("STOP!");
    stopTimer = millis(); //inizio la fase di stop
    speedSx = 0;
    speedDx = 0;      
  }else if(millis() - stopTimer >= stopTimeout){//tempo di stop scaduto!
    Serial.println("INDIETRO!");
    stopTimer = 0;
    indietroTimer = millis();
    indietro();
    speedSx = 123;
    speedDx = 123;
  }else if(millis() - indietroTimer >= indietroTimeout){
    Serial.println("RUOTA!");
    indietroTimer = 0;
    ruotaTimeout = random(0, 4001); //timeout casuale da 0 a 4 secondi
    ruotaTimer = millis();
    ruota();
    speedSx = 123;
    speedDx = 123;
  }else if(millis() - ruotaTimer >= ruotaTimeout){
    ruotaTimer = 0;
    avanti();
    speedSx = 255;
    speedDx = 255;
  }

  analogWrite(pinMtSx, speedSx);  
  analogWrite(pinMtDx, speedDx);  
  */
}

void avanti(){
  digitalWrite(pinCtrlASx, HIGH);
  digitalWrite(pinCtrlBSx, LOW);
  digitalWrite(pinCtrlADx, HIGH);
  digitalWrite(pinCtrlBDx, LOW);
}

void indietro(){
  digitalWrite(pinCtrlASx, LOW);
  digitalWrite(pinCtrlBSx, HIGH);
  digitalWrite(pinCtrlADx, LOW);
  digitalWrite(pinCtrlBDx, HIGH);
}

void ruota(){
  digitalWrite(pinCtrlASx, LOW);
  digitalWrite(pinCtrlBSx, HIGH);
  digitalWrite(pinCtrlADx, HIGH);
  digitalWrite(pinCtrlBDx, LOW);
}


