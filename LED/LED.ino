int r = 0;
int g = 0;
int b = 0;
int min = 0;
int max = 255;
int i = 0;
//int d = 1;
boolean t = true;

void setup() {
  Serial.begin(9600);
  //red(5, 0);
  //blue(5, 0);
  green(5, 0);
}

void loop() {
  
 
}


void red(int incr, long sleep){
  while(t){
    Serial.print("r = ");
    Serial.println(r);
    
    r = i;    
    analogWrite(11, r);
    
    i = i + incr;
    if(i == max) {
      incr = -1;       
    }else if(i == min){
      incr = 1;
    }

    t = i >= min && i <= max;
    delay(sleep);
  }
}

void green(int incr, long sleep){
  while(t){
    Serial.print("g = ");
    Serial.println(g);
    
    g = i;    
    analogWrite(9, g);
    
    i = i + incr;
    if(i == max) {
      incr = -1;       
    }else if(i == min){
      incr = 1;
    }

    t = i >= min && i <= max;
    delay(sleep);
  }
}

void blue(int incr, long sleep){
  while(t){
    Serial.print("b = ");
    Serial.println(b);
    
    b = i;    
    analogWrite(10, b);
    
    i = i + incr;
    if(i == max) {
      incr = -1;       
    }else if(i == min){
      incr = 1;
    }

    t = i >= min && i <= max;
    delay(sleep);
  }
}