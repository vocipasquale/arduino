#include <Wire.h>
#include <WiiChuck.h>

// Crea un oggetto Accessory 
Accessory nunchuck;

int oX;
int oY;
int sens;

void setup() {
  pinMode(2, INPUT); // Abilita la pull-up interna su A4
  
  // Avvia la comunicazione seriale per vedere i dati sul monitor seriale
  Serial.begin(9600);

  // Inizializza il nunchuck
  nunchuck.type = NUNCHUCK;
  nunchuck.begin();
  
  oX = 131; //default
  oY = 132; //default
  sens = 5;
}

void loop() {
  
  nunchuck.readData();

  if(digitalRead(2) == HIGH){
    oX = nunchuck.getJoyX(); //imposto il valore di riferimento di X quando il joystick non è mosso
    oY = nunchuck.getJoyY(); //imposto il valore di riferimento di Y quando il joystick non è mosso
  }

  // Leggi e stampa i valori dell'accelerometro
  //Serial.print("X: ");
  Serial.print(getOutput(oX, nunchuck.getJoyX(), sens));
  Serial.print(" ");
    
  //Serial.print("Y: ");
  Serial.print((-1) * getOutput(oY, nunchuck.getJoyY(), sens));
  Serial.print(" ");


  // Leggi e stampa lo stato dei pulsanti C e Z
  Serial.print(nunchuck.getButtonC());
  Serial.print(" ");
  Serial.println(nunchuck.getButtonZ());

  // Aspetta un breve intervallo
  delay(10);
}

int getOutput(int o, int val, int s){
  
  if(val > (o + s)){
    return 1;
  }

  if(val < (o - s)){
    return -1;
  }

  return 0; //sono nell'origine (o +- s)

}


