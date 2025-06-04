#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal.h>


//#ifdef __AVR__
//  #include <avr/power.h>
//#endif

#define PIN 7
#define NUM_LEDS 40


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

int i = 0;
int r = 0;
int g = 0;
int b = 0;
int d = 1; // 1 --> avanti; -1 --> indietro
char c = 'r'; // r, g, b
boolean avanti = true;
const int maxVal = 64;

void setup()
{
  pinMode(PIN, OUTPUT);
  strip.begin();  
  Serial.begin(9600); 

  
}

void loop()
{
 
  
  /*
  for(int b=0; b<=maxVal; b++){
    for(int g=0; g<=maxVal; g++){
      for(int r=0; r<=maxVal; r++){
        for(int i=0; i<=NUM_LEDS; i++){
         // Serial.print("r: "+String(r));
         // Serial.print("\tg: "+String(g));
         // Serial.println("\tb: "+String(b));
         // Serial.println("\ti: "+String(i));
  
          strip.setPixelColor(i, strip.Color(r, g, b));
          //delay(2);
        }
        strip.show();
      }
    }
  }
*/

/*
  if(avanti){
    if(r<=maxVal){
      r++;
    }else if(g<=maxVal){
      g++;
    }
    else if(b<=maxVal){
      b++;
    }else{
      avanti=false; //indietro
      r=maxVal;
      g=maxVal;
      b=maxVal;
    }    
  }
  else{ //indietro
    if(r>0){
      r--;
    }else if(g>0){
      g--;
    }else if(b>0){
      b--;
    }else{// r,g,b < 0
      avanti=true;
      r=0;
      g=0;
      b=0;
    }
  }

  Serial.print("r: "+String(r));
  Serial.print("\tg: "+String(g));
  Serial.println("\tb: "+String(b));

  for(int i=0; i<=NUM_LEDS; i++){
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();  
*/


  for(int i=0; i<NUM_LEDS; i++){
    if(i%2==0){
      strip.setPixelColor(i, strip.Color(20, 20, 0));
    }else{
      strip.setPixelColor(i, strip.Color(0, 20, 0));
    }
  }
  strip.show(); 

}


