//controllo 2 motori DC da 24 volt 75 watt
/**
per variare la velocità di rotazione uso in input un joystick
che pilota due uscite PWM (motore Sx e motore Dx).

L'asse Y del joystick rappresenta la velocità:
- AVANTI: da 127 a 255
- INDIETRO: da 126 a 0 (solo se interruttore specifico è HIGH)
- STOP: 127

L'asse X del joystick rappresenta la direzione:
- SINISTRA: da 0 a 126
- DESTRA: da 128 a 255
- DRITTO: 127

Per fermare i motori si usa sempre il joystick (Y = 127).


NOTA:
implementare illuminazione STOP: quando Y diminuisce


*/


//input del joystick
const int pinX = A0;
const int pinY = A1;

const int pinMtSx = 11; //PWM motore Sx
const int pinMtDx = 10; //PWM motore Dx
const int pinCtrlASx = 13; //control A motore SX
const int pinCtrlBSx = 12; //control B motore SX
const int pinCtrlADx = 8; //control A motore DX
const int pinCtrlBDx = 7; //control B motore DX
const int pinRetro = 2;


int x = 0; // asse X --> direzione
int y = 0; // asse Y --> velocità
int x0; //valore "zero" dell'asse X (quando il joystick non è toccato)
int y0; //valore "zero" dell'asse Y (quando il joystick non è toccato)
int toll = 5; // tolleranza delle misure


void setup() {
  Serial.begin(9600);  
  
  pinMode(pinRetro, INPUT);
  pinMode(pinCtrlASx, OUTPUT);
  pinMode(pinCtrlBSx, OUTPUT);
  pinMode(pinCtrlADx, OUTPUT);
  pinMode(pinCtrlBDx, OUTPUT);

  initXY();
}

void loop() {
  int speedSx = 0;
  int speedDx = 0;
  boolean retro = (digitalRead(pinRetro) == HIGH); //interruttore per abilitare la retromarcia

  x = map(analogRead(pinX), 0, 1023, 0, 255); ///4; 
  y = map(analogRead(pinY), 0, 1023, 0, 255); ///4; 
  
  //Serial.print("X: " + String(x));
  //Serial.println("\tY: " + String(y));


//il joistik tutto giù da 255, tutto su da 0
//l'asse Y va da 255 (tutto giù) a 0 (tutto su)  
 // y = 255 -y;

//se retro disabilitata: disabilito il joistick indietro
  if(!retro){
    avanti();
    if(y < (y0 - toll)){
      y = 0;
    }else if (y > (y0 + toll)){
      y = map(y, y0, 255, 1, 255);
    }else if (y > (y0 - toll) && y < (y0 + toll)){
      y = 0;
    }  
  }

//se retro abilitata: disabilito il joistick avanti
  if(retro){
    indietro();
    if(y >= (y0 + toll)){
      y = 0;
    }else if (y < (y0 - toll)){
      y = map(y, y0, 0, 1, 60);
    } else if (y > (y0 - toll) && y < (y0 + toll)){
      y = 0;
    }  
  }

 //////////////////////////////////////////// 

  if(x < (x0 - toll)){ //direzione: SX-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //speedSx= y * (x/127); //x==0 --> motore di sx spento; x==123 --> entrambe i motori accesi 
    speedSx = map(x, 0, 125, 0, 255);
    speedDx = y; //motore dx sempre acceso con velocità y
    
  }else if(x >(x0 + toll)){ // direzione DX
    speedSx = y; //motore sx sempre acceso con velocità y 
    speedDx = map(x, 126, 255, 255, 0);  //x==0 --> motore di sx spento; x==123 --> entrambe i motori accesi 
  }else if(x > (x0 - toll) && x < (x0 + toll)){
    speedSx = y;
    speedDx = y;
  }
  
  Serial.print("X: " + String(x));
  Serial.print("\tY: " + String(y));
  Serial.print("\tX0: " + String(x0));
  Serial.print("\tY0: " + String(y0));
  Serial.print("\tretro: " + String(retro));
  Serial.print("\tspeedSx: " + String(speedSx));
  Serial.println("\tspeedDx: " + String(speedDx));  
  
  analogWrite(pinMtSx, speedSx);  
  analogWrite(pinMtDx, speedDx);    
  delay(200);


}

void initXY(){
  //x0 = analogRead(pinX)/4;
  //y0 = analogRead(pinY)/4;
  
  x0 = map(analogRead(pinX), 0, 1023, 0, 255); 
  y0 = map(analogRead(pinY), 0, 1023, 0, 255);
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