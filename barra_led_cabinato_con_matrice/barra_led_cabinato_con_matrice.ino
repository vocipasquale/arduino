  // mappa led {pin, stato} (stato -> 0: spento 1: acceso)
    int led[6][2] = {
      {2, 0},
      {3, 0},
      {4, 0},
      {5, 0},
      {6, 0},
      {7, 0},
    };

    int pinRgbRosso = 11;
    int pinRgbBlu = 10;

    int index = 0;
    int onOffTime = 10; //millisecondi
    int clockEvent = 500; //millisecondi: ogni clock succede qualcosa... 
    

    char cC = 0;  //assume: 0 (rosso); 1 (blu)
    unsigned long startTimeCommon = millis();
    unsigned long startTimeRGB = 0;
    unsigned long  startTimeLED = 0;


    void setup() {
      Serial.begin(9600);

      //inizializzazione dei tempi
      startTimeRGB = startTimeCommon;
      startTimeLED = startTimeCommon;

      pinMode(led[0][0], OUTPUT);
      pinMode(led[1][0], OUTPUT);
      pinMode(led[2][0], OUTPUT);
      pinMode(led[3][0], OUTPUT);
      pinMode(led[4][0], OUTPUT);
      pinMode(led[5][0], OUTPUT);
    }

    void loop() {

      //accende spegne il led RGB
      startTimeRGB = rgb(onOffTime);
      
      //gestione effetti sui LED
      int m = millis() - startTimeLED;

      //Serial.print("m: ");
      //Serial.println(m);

      if(m >= 0 & m < clockEvent){ //1° clock
        led[0][1] = HIGH;
        led[1][1] = HIGH;
        led[2][1] = HIGH;
        led[3][1] = HIGH;
        led[4][1] = HIGH;
        led[5][1] = HIGH;
      } else if(m >= clockEvent & m < clockEvent * 2){ //2° clock
        led[0][1] = LOW;
        led[1][1] = LOW;
        led[2][1] = LOW;
        led[3][1] = LOW;
        led[4][1] = LOW;
        led[5][1] = LOW;
      }else if(m >= clockEvent * 2 & m < clockEvent * 3){ //3° clock
        led[0][1] = HIGH;
        led[1][1] = HIGH;
        led[2][1] = HIGH;
        led[3][1] = HIGH;
        led[4][1] = HIGH;
        led[5][1] = HIGH;
      } else if(m >= clockEvent * 3 & m < clockEvent * 4){ //4° clock
        led[0][1] = LOW;
        led[1][1] = LOW;
        led[2][1] = LOW;
        led[3][1] = LOW;
        led[4][1] = LOW;
        led[5][1] = LOW;
      } else if(m >= clockEvent * 4 & m < clockEvent * 5){ //5° clock
        led[0][1] = HIGH;
        led[1][1] = LOW;
        led[2][1] = LOW;
        led[3][1] = LOW;
        led[4][1] = LOW;
        led[5][1] = LOW;
      } else if(m >= clockEvent * 5 & m < clockEvent * 6){ //6° clock
        led[0][1] = LOW;
        led[1][1] = HIGH;
        led[2][1] = LOW;
        led[3][1] = LOW;
        led[4][1] = LOW;
        led[5][1] = LOW;
      } else if(m >= clockEvent * 6 & m < clockEvent * 7){ //7° clock
        led[0][1] = LOW;
        led[1][1] = LOW;
        led[2][1] = HIGH;
        led[3][1] = LOW;
        led[4][1] = LOW;
        led[5][1] = LOW;
      } else if(m >= clockEvent * 7 & m < clockEvent * 8){ //8° clock
        led[0][1] = LOW;
        led[1][1] = LOW;
        led[2][1] = LOW;
        led[3][1] = HIGH;
        led[4][1] = LOW;
        led[5][1] = LOW;
      } else if(m >= clockEvent * 8 & m < clockEvent * 9){ //9° clock
        led[0][1] = LOW;
        led[1][1] = LOW;
        led[2][1] = LOW;
        led[3][1] = LOW;
        led[4][1] = HIGH;
        led[5][1] = LOW;
      } else if(m >= clockEvent * 9 & m < clockEvent * 10){ //10° clock
        led[0][1] = LOW;
        led[1][1] = LOW;
        led[2][1] = LOW;
        led[3][1] = LOW;
        led[4][1] = LOW;
        led[5][1] = HIGH;
      } else if(m >= clockEvent * 10 & m < clockEvent * 11){ //11° clock
        led[0][1] = LOW;
        led[1][1] = LOW;
        led[2][1] = LOW;
        led[3][1] = LOW;
        led[4][1] = LOW;
        led[5][1] = LOW;
      }  else if(m >= clockEvent * 11 & m < clockEvent * 12){ //13° clock
        led[0][1] = LOW;
        led[1][1] = LOW;
        led[2][1] = LOW;
        led[3][1] = LOW;
        led[4][1] = LOW;
        led[5][1] = HIGH;
      } else if(m >= clockEvent * 12 & m < clockEvent * 13){ //13° clock
        led[0][1] = LOW;
        led[1][1] = LOW;
        led[2][1] = LOW;
        led[3][1] = LOW;
        led[4][1] = HIGH;
        led[5][1] = LOW;
      } else if(m >= clockEvent * 13 & m < clockEvent * 14){ //13° clock
        led[0][1] = LOW;
        led[1][1] = LOW;
        led[2][1] = LOW;
        led[3][1] = HIGH;
        led[4][1] = LOW;
        led[5][1] = LOW;
      } else if(m >= clockEvent * 14 & m < clockEvent * 15){ //13° clock
        led[0][1] = LOW;
        led[1][1] = LOW;
        led[2][1] = HIGH;
        led[3][1] = LOW;
        led[4][1] = LOW;
        led[5][1] = LOW;
      } else if(m >= clockEvent * 15 & m < clockEvent * 16){ //13° clock
        led[0][1] = LOW;
        led[1][1] = HIGH;
        led[2][1] = LOW;
        led[3][1] = LOW;
        led[4][1] = LOW;
        led[5][1] = LOW;
      } else if(m >= clockEvent * 16 & m < clockEvent * 17){ //13° clock
        led[0][1] = HIGH;
        led[1][1] = LOW;
        led[2][1] = LOW;
        led[3][1] = LOW;
        led[4][1] = LOW;
        led[5][1] = LOW;
      } else if(m >= clockEvent * 17 & m < clockEvent * 18){ //13° clock
        led[0][1] = LOW;
        led[1][1] = LOW;
        led[2][1] = LOW;
        led[3][1] = LOW;
        led[4][1] = LOW;
        led[5][1] = LOW;
      } 

      onOffLED();

      if(m >= clockEvent * 18){
        startTimeLED = millis();//riavvia il timer...  
      }
      
    }

    void onOffLED(){
      digitalWrite(led[0][0], led[0][1]);
      digitalWrite(led[1][0], led[1][1]);
      digitalWrite(led[2][0], led[2][1]);
      digitalWrite(led[3][0], led[3][1]);
      digitalWrite(led[4][0], led[4][1]);
      digitalWrite(led[5][0], led[5][1]);
    }
    

    /**
      accende e spegne il led RGB con un tempo di accensione e spegnimento predefinito
      
      restituisce il valore di millis() per far capire "da fuori" che il contatore del tempo 
      deve essere reimpostato
    */
    unsigned long rgb(int onOffTime){
      
      if (millis() - startTimeRGB >= onOffTime) {//temporizzazione, 

        if (cC == 0 and index < 256) {  //...verso il rosso
          writeRGB(index, 0, 255 - index);
        }

        if (cC == 1 and index < 256) {  //...verso il blu
          writeRGB(255 - index, 0, index);
        }

        if (cC == 0 and index == 256) {  //...commuta sul blu
          cC = 1;
          index = 0;
        }

        if (cC == 1 and index == 256) {  //...commuta sul rosso
          cC = 0;
          index = 0;
        }

        index++;     
        return millis(); // Reset del timer
      }
    }
     

    void writeRGB(int r, int g, int b) {
      analogWrite(11, r);
      analogWrite(10, b);
    }
