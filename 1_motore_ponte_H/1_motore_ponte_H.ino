//controllo un motore RS445 24 V 75 W
/**
in questa versione la direzione del motore è sempre la stessa e per variare
la velocità di rotazione uso in input un trimmer che pilota
un'uscita PWM. Per fermare il motore si usa sempre il trimmer.
*/

//pin per gestire il senso di rotazione
const int pinDir1 = 2;
const int pinDir2 = 7;

//input del trimmer
const int trmInput = A0;
const int pwmOut = 3;

int speed = 0;


void setup() {
  Serial.begin(9600);  

  pinMode(pinDir1, OUTPUT);
  pinMode(pinDir2, OUTPUT);

  //in questa versione un solo senso di rotazione
  digitalWrite(pinDir1, HIGH);
  digitalWrite(pinDir2, LOW);

  
}

void loop() {
  speed = analogRead(trmInput)/4;
  
  Serial.print("speed: ");
  Serial.println(speed);

  analogWrite(pwmOut, speed);

}
