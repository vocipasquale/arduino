const int SPEED_MAX = 255;
const int SPEED_MAX_RETRO = 60;

const int pinEDx = 12;
const int pinADx = 11;
const int pinIDx = 10;
const int pinRetro = 2;

//input del joystick
//const int pinX = A0;
const int pinY = A1;

//int x = 0; // asse X --> direzione
int y = 0; // asse Y --> velocità
//int x0; //valore "zero" dell'asse X (quando il joystick non è toccato)
int y0; //valore "zero" dell'asse Y (quando il joystick non è toccato)
int toll = 5; // tolleranza delle misure
int yPre = 0;



void setup() {
  Serial.begin(9600);  
  
  pinMode(pinRetro, INPUT);
  pinMode(pinADx, OUTPUT);
  pinMode(pinIDx, OUTPUT);
  pinMode(pinEDx, OUTPUT);

  y0 = analogRead(pinY)/4;
  digitalWrite(pinEDx, HIGH);
}


void loop() {
  boolean retro = (digitalRead(pinRetro) == HIGH); //interruttore per abilitare la retromarcia

  y = analogRead(pinY)/4; 
  
//il joistik tutto giù da 255, tutto su da 0
//l'asse Y va da 255 (tutto giù) a 0 (tutto su)  
  y = 255 -y;


  //se retro disabilitata: disabilito il joistick indietro
  if(!retro){
    Serial.println("avanti!");
    if(y < (y0 - toll)){
      y = 0;
    }else if (y > (y0 + toll)){
      y = map(y, y0, 255, 1, 255);
    }else if (y > (y0 - toll) && y < (y0 + toll)){
      y = 0;
    }
    
    if(y<yPre-toll){
      digitalWrite(pinEDx, LOW);
    } else{
      avanti(y); 
    }
  }else{
    Serial.println("retro!");
    if(y >= (y0 + toll)){
      y = 0;
    }else if (y < (y0 - toll)){
      y = map(y, y0, 0, 1, 60);
    } else if (y > (y0 - toll) && y < (y0 + toll)){
      y = 0;
    } 

    if(y<yPre-toll){
      digitalWrite(pinEDx, LOW);
    } else{
      indietro(y);
    }

  }
  yPre = y;
  Serial.println("y: "+String(y));

}




/*
void loop() {

  for(int v=0; v<256; v++){
    avanti(v);
    Serial.println(v);
    delay(50);
  }

  delay(5000);

  for(int v=0; v<256; v++){
    indietro(v);
    Serial.println(v);
    delay(50);
  }

  delay(5000);

}
*/


void avanti(int speed){
  if(speed > SPEED_MAX){
    speed = SPEED_MAX;
  }

  digitalWrite(pinEDx, HIGH);
  analogWrite(pinADx, speed);  
  analogWrite(pinIDx, 0); 
}

void indietro(int speed){
  if(speed > SPEED_MAX_RETRO){
    speed = SPEED_MAX_RETRO;
  }
  
  digitalWrite(pinEDx, HIGH);
  analogWrite(pinADx, 0);  
  analogWrite(pinIDx, speed); 
}