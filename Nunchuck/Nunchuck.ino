#include <Wire.h>
#include <WiiChuck.h>

// Crea un oggetto Accessory 
Accessory nunchuck;

int preX;
int preY;
int x;
int y;
int outX;
int outY;
int bC;
int bZ;
int sens; //sensibilità dell'input

void setup() {
  //pinMode(A4, INPUT_PULLUP); // Abilita la pull-up interna su A4
  //pinMode(A5, INPUT_PULLUP); // Abilita la pull-up interna su A5
  
  // Avvia la comunicazione seriale per vedere i dati sul monitor seriale
  Serial.begin(9600);

  // Inizializza il nunchuck
  nunchuck.type = NUNCHUCK;
  nunchuck.begin();
  
  //Serial.println("nunchuck ready!");
  preX = 9999;
  preY = 9999;
  x = 0;
  y = 0;
  bC = 0;
  bZ = 0;
  sens = 1;
}

void loop() {
  
  nunchuck.readData();

  // Leggi e stampa i valori dell'accelerometro
  x = nunchuck.getAccelX(); //[0,1024]
  //Serial.print("X: ");
  //Serial.print(x);
  //Serial.print(" ");
  
  y = nunchuck.getAccelY(); //[0,1024] 
  //Serial.print("Y: ");
  //Serial.print(y);
  //Serial.print(" ");


  x = readInput(x, preX, sens);
  y = readInput(y, preY, sens);
  
  //invio x...
  Serial.print(x - preX); // < 0 verso sinistra; > 0 verso destra
  Serial.print(" ");
  preX = x;

  //invio y...
  Serial.print(y - preY); // < 0 verso il basso; > 0 verso l'alto
  Serial.print(" ");
  preY = y;

  

  // Leggi e stampa lo stato dei pulsanti C e Z
  Serial.print(nunchuck.getButtonC());
  Serial.print(" ");
  Serial.println(nunchuck.getButtonZ());

  // Aspetta un breve intervallo
  delay(50);
}

//"rilegge" l'input tenendo conto delle possibili oscillazioni
//rispetto al precedente valore di input
int readInput(int input, int preVal, int s){
  
  if(preVal == 9999){//prima chiamata al 
    return input;
  }
  
  if(abs(abs(input) - abs(preVal)) > s){// è la sensibilità dell'input
    return input;
  }
    
  return preVal;
}

