//controllo 2 motori DC da 3,5 volt
/**
in questa versione la direzione del motore è sempre la stessa e per variare
la velocità di rotazione uso in input un trimmer che pilota
un'uscita PWM. Per fermare il motore si usa sempre il trimmer.
*/


//input del trimmer
const int trmInputSx = A0;
const int trmInputDx = A1;

const int mtSx = 11;
const int mtDx = 10;

int speedMtSx = 0;
int speedMtDx = 0;


void setup() {
  Serial.begin(9600);  
   
}

void loop() {
  speedMtSx = analogRead(trmInputSx)/4;
  speedMtDx = analogRead(trmInputDx)/4;

  analogWrite(mtSx, speedMtSx);
  analogWrite(mtDx, speedMtDx);


}
