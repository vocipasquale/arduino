// ***************************************************************
// controllo 1 motore DC da 24 volt 75 watt con un driver BTS7960
// ******************* FRENATA RIGENERATIVA **********************
// ***************************************************************

/**
per variare la velocità di rotazione uso in input un potenziometro lineare

VALORI= [0, 1023];
0 --> fermo
1023 --> max

per gestire la frenata generativa

NOTA 2:
implementare illuminazione STOP: quando Y diminuisce

*/

const int SPEED_MAX = 255;
const int SPEED_MAX_RETRO = 60;

//input del joystick
const uint8_t pot = A0;

const int pinEn = 12; //pin abilita/disabilita motore
const int pinAv = 11; //pin Avanti (PWM) motore
const int pinIn = 10; //pin Indietro (PWM) motore
const int pinPWM1 = 7; //pin abilita/disabilita relè 
const int pinDsPWM2 = 6; //pin Avanti (PWM) motore Sx
const int pinDsBatt1 = 5; //pin Indietro (PWM) motore Sx
const int pinDsBatt2 = 4; //pin Indietro (PWM) motore Sx

const int pinRetro = 2; //pin retromarcia
int speed = 0;


void setup() {
  Serial.begin(9600);  
  
  pinMode(pinRetro, INPUT);
  pinMode(pinEnDx, OUTPUT);
  pinMode(pinAvDx, OUTPUT);
  pinMode(pinInDx, OUTPUT);
//  pinMode(pinEnSx, OUTPUT);
//  pinMode(pinAvSx, OUTPUT);
//  pinMode(pinInSx, OUTPUT);

}

void loop() {
  //int speedSx = 0;
  //int speedDx = 0;
  boolean retro = (digitalRead(pinRetro) == LOW); //interruttore per abilitare la retromarcia
  int spCurr = analogRead(pot)/4;

  ////////////////////////////////////////////
  //accensione led STOP se spCurr < speed !
  ////////////////////////////////////////////

  speed = spCurr;
   
  if(retro){
    indietro(speed);
  }else{
    avanti(speed);
  }

  delay(200);
}


void avanti(int sp){
  if(sp == 0){
    //frenata rigenerativa
    //...
  }else{
    analogWrite(pinAvDx, sp);
    analogWrite(pinInDx, 0);
  }
  
}

void indietro(int sp){
  analogWrite(pinInDx, sp);
  analogWrite(pinAvDx, 0);
}

 
}
