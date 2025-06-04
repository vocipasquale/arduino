//controllo 2 motori DC da 3,5 volt
/**
in questa versione la direzione del motore è sempre la stessa e per variare
la velocità di rotazione uso in input un trimmer che pilota
un'uscita PWM. Per fermare il motore si usa sempre il trimmer.
Uso due trimmer per simulare un joystick (cloche):
 - uno per l'asse X e uno per l'asse Y

*/


//input del trimmer
const int pinX = A0;
const int pinY = A1;

const int pinMtSx = 11;
const int pinMtDx = 10;

int x = 0; // asse X --> direzione
int y = 0; // asse Y --> velocità

int speedSx = 0;
int speedDx = 0;

long timer = 0;


void setup() {
  Serial.begin(9600);  
   timer = millis();
}

void loop() {
  x = analogRead(pinX)/4; 
  y = analogRead(pinY)/4; 

  if(x <= 125){ //direzione: SX-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //speedSx= y * (x/127); //x==0 --> motore di sx spento; x==123 --> entrambe i motori accesi 
    speedSx = map(x, 0, 125, 0, 255);
    speedDx = y; //motore dx sempre acceso con velocità y
    
  }else{ // direzione DX
    speedSx = y; //motore sx sempre acceso con velocità y 
    speedDx = map(x, 126, 255, 255, 0);  //x==0 --> motore di sx spento; x==123 --> entrambe i motori accesi 
  }
  
  Serial.print("X: " + String(x));
  Serial.print("\tY: " + String(y));
  Serial.print("\tspeedSx: " + String(speedSx));
  Serial.println("\tspeedDx: " + String(speedDx));

  analogWrite(pinMtSx, speedSx);  
  analogWrite(pinMtDx, speedDx);  
  
  delay(100);

}
