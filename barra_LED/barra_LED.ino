  int r = 0;
  int g = 0;
  int b = 0;
  int min = 0;
  int max = 255;

  void setup() {
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);    
  }

  void loop() {
    /*
    for(int i = 0; i < 256; i++){
      rgb(255-i, i, 0); //dal rosso al verde
      delay(10);
    }

    for(int i = 0; i < 256; i++){
      rgb(0, 255-i, i); //dal verde al blu
      delay(10);
    }
    

    for(int i = 0; i < 256; i++){
      rgb(i, 0, 255-i); //dal blu al rosso
      delay(10);
    }
    */

    for(int i = 0; i < 256; i++){
      rgb(255-i, 0, i); //dal rosso al verde
      delay(20);
    }

    
    for(int i = 0; i < 256; i++){
      rgb(i, 0, 255-i); //dal rosso al verde
      delay(20);
    }

  }

  void rgb(int r, int g, int b){
    analogWrite(11, r);
    analogWrite(9, g);
    analogWrite(10, b);
  }

  void checkRGB(){
    red(5, 50, false, true);
    green(5, 50, false, true);
    blue(5, 50, false, true);

  }

  void check(){
    on(1, 500, true);
    on(2, 500, true);
    on(3, 500, true);
    on(4, 500, true);
    on(5, 500, true);
    on(6, 500, true);
    on(7, 500, true);
    on(8, 500, true);
    
    //delay(500);
    
    on(8, 500, true); 
    on(7, 500, true);
    on(6, 500, true);
    on(5, 500, true);
    on(4, 500, true);
    on(3, 500, true);
    on(2, 500, true);
    on(1, 500, true);

  }

  void on(int pin, long sleep, boolean offPin){
    digitalWrite(pin, HIGH);
    delay(sleep);
    if(offPin){
      off(pin);
    }
  }

  void off(int pin){
    digitalWrite(pin, LOW);
  }

  void red(int incr, long sleep, boolean rebound, boolean offPin){
    boolean c = true; 
    int i = 0;
    while(c){
      //Serial.print("r = ");
      //Serial.println(r);
            
      analogWrite(11, i);
      
      i = i + incr;
      
      if(i == max) {
        if(rebound){
          incr = (incr) * (-1);
        }else if(offPin){
          analogWrite(11, 0);
          c = false;
        }
      }else{
        c = i >= min && i <= max;
      }

      delay(sleep);
    }
      
    }


  void green(int incr, long sleep, boolean rebound, boolean offPin){
    boolean c = true; 
    int i = 0;
    while(c){
      //Serial.print("r = ");
      //Serial.println(r);
            
      analogWrite(9, i);
      
      i = i + incr;
      
      if(i == max) {
        if(rebound){
          incr = (incr) * (-1);
        }else if(offPin){
          analogWrite(9, 0);
          c = false;
        }
      }else{
        c = i >= min && i <= max;
      }

      delay(sleep);
    }
  }

  void blue(int incr, long sleep, boolean rebound, boolean offPin){
    boolean c = true; 
    int i = 0;
    while(c){
      //Serial.print("r = ");
      //Serial.println(r);
            
      analogWrite(10, i);
      
      i = i + incr;
      
      if(i == max) {
        if(rebound){
          incr = (incr) * (-1);
        }else if(offPin){
          analogWrite(10, 0);
          c = false;
        }
      }else{
        c = i >= min && i <= max;
      }

      delay(sleep);
    }
  }