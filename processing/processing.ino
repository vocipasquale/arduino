int val;
int inputPin = 0;                // Set the input to analog in pin 0

void setup() {
  Serial.begin(9600);            // Start serial communication at 9600 bps
}

void loop() {
  val = analogRead(inputPin);  // Read analog input pin, put in range 0 to 255
  Serial.write(val/4); //map(val, 0, 1023, 0, 255));             // Send the value
  //Serial.println(map(val, 0, 1023, 0, 255));
  delay(100);                    // Wait 100ms for next reading
}