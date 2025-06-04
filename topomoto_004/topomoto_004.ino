//controllo 2 motori DC da 24 volt 75 watt con due driver BTS7960

/**
per variare la velocità di rotazione uso in input un joystick
che pilota due uscite PWM (motore Sx e motore Dx).

L'asse Y del joystick rappresenta la velocità:
- AVANTI: da 127 a 255
- INDIETRO: da 126 a 0 (solo se interruttore specifico è HIGH)
- STOP: 127
(leg. nota seguente)

L'asse X del joystick rappresenta la direzione:
- SINISTRA: da 0 a 126
- DESTRA: da 128 a 255
- DRITTO: 127

Per fermare i motori si usa sempre il joystick (Y = 127).


NOTA:
il joistik tutto giù restituisce 255, tutto su restituisce 0
l'asse Y va da 255 (tutto giù) a 0 (tutto su)

NOTA 2:
implementare illuminazione STOP: quando Y diminuisce


*/

const int SPEED_MAX = 255;
const int SPEED_MAX_RETRO = 60;

//input del joystick
const int pinX = A0;
const int pinY = A1;

const int pinEnDx = 12; //pin abilita motore Dx
const int pinAvDx = 11; //pin Avanti (PWM) motore Dx
const int pinInDx = 10; //pin Indietro (PWM) motore Dx

const int pinEnSx = 7; //pin abilita motore Sx
const int pinAvSx = 6; //pin Avanti (PWM) motore Sx
const int pinInSx = 5; //pin Indietro (PWM) motore Sx

const int pinRetro = 2; //pin retromarcia

int x = 0; // asse X --> direzione
int y = 0; // asse Y --> velocità
int x0; //valore "zero" dell'asse X (quando il joystick non è toccato)
int y0; //valore "zero" dell'asse Y (quando il joystick non è toccato)
int toll = 5; // tolleranza delle misure

int speed[2] = {0, 0}; // speed[0] -> speedSx; speed[1] -> speedDx

void setup() {
  Serial.begin(9600);  
  
  pinMode(pinRetro, INPUT);
  pinMode(pinEnDx, OUTPUT);
  pinMode(pinAvDx, OUTPUT);
  pinMode(pinInDx, OUTPUT);
  pinMode(pinEnSx, OUTPUT);
  pinMode(pinAvSx, OUTPUT);
  pinMode(pinInSx, OUTPUT);

  initXY();
}

void loop() {
  //int speedSx = 0;
  //int speedDx = 0;
  boolean retro = (digitalRead(pinRetro) == LOW); //interruttore per abilitare la retromarcia

  x = map(analogRead(pinX), 0, 1023, 0, 255); ///4; 
  y = map(analogRead(pinY), 0, 1023, 0, 255); ///4; 
  
  //Serial.print("X: " + String(x));
  //Serial.println("\tY: " + String(y));

//il joistik tutto giù da 255, tutto su da 0
//l'asse Y va da 255 (tutto giù) a 0 (tutto su)  
  y = 255 -y;

  setSpeedMotors(retro);

  Serial.print("X: " + String(x));
  Serial.print("\tY: " + String(y));
  Serial.print("\tX0: " + String(x0));
  Serial.print("\tY0: " + String(y0));
  Serial.print("\tretro: " + String(retro));
  Serial.print("\tspeedSx: " + String(speed[0]));
  Serial.println("\tspeedDx: " + String(speed[1]));  
  
  if(retro){
    indietro(speed[0], speed[1]);
  }else{
    avanti(speed[0], speed[1]);
  }
  
  delay(200);
}

void initXY(){
  x0 = map(analogRead(pinX), 0, 1023, 0, 255); 
  y0 = map(analogRead(pinY), 0, 1023, 0, 255);

//il joystick tutto giù da 255, tutto su da 0
//l'asse Y va da 255 (tutto giù) a 0 (tutto su)  
  y0 = 255 - y0;

}

void avanti(int spSx, int spDx){
  analogWrite(pinAvSx, spSx);
  analogWrite(pinInSx, 0);

  analogWrite(pinAvDx, spDx);
  analogWrite(pinInDx, 0);
}

void indietro(int spSx, int spDx){
  analogWrite(pinInSx, spSx);
  analogWrite(pinAvSx, 0);

  analogWrite(pinInDx, spDx);
  analogWrite(pinAvDx, 0);
}

void setSpeedMotors(boolean retro){
  int sp = 0;

  if(retro){
    if(y < (y0 - toll)){
      sp = map(y, y0, 0, 1, SPEED_MAX_RETRO);
    }
  }else{
    if(y > (y0 + toll)){
      sp = map(y, y0, 255, 1, SPEED_MAX);
    }  
  }  

  if(x < (x0 - toll)){ //direzione: SX-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    speed[0] = map(x, x0, 0, sp, 0);
    speed[1] = sp;    
  }else if(x >(x0 + toll)){ // direzione DX
    speed[0] = sp; 
    speed[1] = map(x, x0, 255, sp, 0); 
  }else if(x > (x0 - toll) && x < (x0 + toll)){
    speed[0] = sp;
    speed[1] = sp;
  } 
  
    
  /*
  
  //se retro disabilitata: disabilito il joistick indietro
  if(!retro){
    Serial.println("avanti!");
    if(y < y0){ //(y0 - toll)){
      y = 0;
    }else if (y > y0){ //(y0 + toll)){
      y = map(y, y0, 255, 1, SPEED_MAX);
    }else if (y > (y0 - toll) && y < (y0 + toll)){
      y = 0;
    }  
  } else{ //se retro abilitata: disabilito il joistick avanti
    Serial.println("retro!");
    if(y >= (y0 + toll)){
      y = 0;
    }else if (y < (y0 - toll)){
      y = map(y, y0, 0, 1, SPEED_MAX_RETRO);
    } else if (y > (y0 - toll) && y < (y0 + toll)){
      y = 0;
    }  
  }

 //////  DIREZIONE  ///////// 

  if(x < (x0 - toll)){ //direzione: SX-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    speed[0] = map(x, x0, 0, SPEED_MAX, 0);
    speed[1] = y; //motore dx sempre acceso con velocità y    
  }else if(x >(x0 + toll)){ // direzione DX
    speed[0] = y; //motore sx sempre acceso con velocità y 
    speed[1] = map(x, x0, 255, SPEED_MAX, 0); 
  }else if(x > (x0 - toll) && x < (x0 + toll)){
    speed[0] = y;
    speed[1] = y;
  }
  
  */

}
