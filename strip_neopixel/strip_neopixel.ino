#include <Adafruit_NeoPixel.h>

#define PIN 7
#define NUM_LEDS 48

struct RGB{
  int r;
  int g;
  int b;
};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

RGB rgbStrip[NUM_LEDS];

int speed = 50; //millisecondi
unsigned long timer;

//prima animazione
int valoreCorrente = 0;
int direzione = 1; //1: 0 -> 255; -1: 255 -> 0


void setup()
{
  pinMode(PIN, OUTPUT);
  strip.begin();
  
  randomSeed(A0);//randomSeed(millis()); da considerare nel caso reale
  
  for(int p=0; p<NUM_LEDS; p++){
    rgbStrip[p].r=random(0,256);  
    rgbStrip[p].g=random(0,256);
    rgbStrip[p].b=random(0,256);
  }
  
  for(int p=0; p<NUM_LEDS; p++){
  	strip.setPixelColor(p, strip.Color(rgbStrip[p].r, rgbStrip[p].g, rgbStrip[p].b));
  }
    
  strip.show();
  delay(1000);
  clearStrip();
  timer = millis();
  
}

void loop()
{
  //prima animazione
  primaAnimazione();
  
}


void clearStrip(){
  //SPENTO
  for(int r=0; r<NUM_LEDS; r++){
  	strip.setPixelColor(0, strip.Color(0, 0, 0));
  }
  strip.show();  
}


//tutti i led della striscia pulsano da 
//spento ad un colore (a rotazione da 0,0,0 a 255,255,255)
void primaAnimazione(){
  int step = 15;
  unsigned long m = millis();
  int timeOut = m - timer;
  
  if(true){//timeOut>=speed){//se è stato raggiunto il time-out
    
    if(valoreCorrente <= 0){
      direzione = 1; 
      valoreCorrente=5;
    }else if(valoreCorrente >= 255){
      direzione = -1;  
      valoreCorrente=255;
    }
    
    valoreCorrente+=step*direzione;
    
    
    //for(int p=0; p<NUM_LEDS; p++){
    //	rgbStrip[p].r=val;  
    //	rgbStrip[p].g=val;
    //	rgbStrip[p].b=val;
  	//}
  
  	for(int p=0; p<NUM_LEDS; p++){
  		strip.setPixelColor(p, strip.Color(valoreCorrente, valoreCorrente, valoreCorrente));
  	}	
    strip.show();
  
  	timer = millis(); //reset timer
  }   
  
}