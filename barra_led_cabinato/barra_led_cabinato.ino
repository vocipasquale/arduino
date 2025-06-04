    struct LED {
      int pin;
      int stato;
    };

    LED led_1;
    LED led_2;
    LED led_3;
    LED led_4;
    LED led_5;
    LED led_6;
    //LED led_7;
    //LED led_8;

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

      led_1.pin = 2;
      led_2.pin = 3;
      led_3.pin = 4;
      led_4.pin = 5;
      led_5.pin = 6;
      led_6.pin = 7;
      //led_7.pin = 8;
      //led_8.pin = 8;

      led_1.stato = LOW;
      led_2.stato = LOW;
      led_3.stato = LOW;
      led_4.stato = LOW;
      led_5.stato = LOW;
      led_6.stato = LOW;
      //led_7.stato = LOW;
     // led_8.stato = LOW;

      pinMode(led_1.pin, OUTPUT);
      pinMode(led_2.pin, OUTPUT);
      pinMode(led_3.pin, OUTPUT);
      pinMode(led_4.pin, OUTPUT);
      pinMode(led_5.pin, OUTPUT);
      pinMode(led_6.pin, OUTPUT);
      //pinMode(led_7.pin, OUTPUT);
     // pinMode(led_8.pin, OUTPUT);
    }

    void loop() {

      //accende spegne il led RGB
      startTimeRGB = rgb(onOffTime);
      
      //gestione effetti sui LED
      int m = millis() - startTimeLED;

      //Serial.print("m: ");
      //Serial.println(m);

      if(m >= 0 & m < clockEvent){ //1° clock
        led_1.stato = HIGH;
        led_2.stato = HIGH;
        led_3.stato = HIGH;
        led_4.stato = HIGH;
        led_5.stato = HIGH;
        led_6.stato = HIGH;
     //   led_7.stato = HIGH;
     //   led_8.stato = HIGH;
      } else if(m >= clockEvent & m < clockEvent * 2){ //2° clock
        led_1.stato = LOW;
        led_2.stato = LOW;
        led_3.stato = LOW;
        led_4.stato = LOW;
        led_5.stato = LOW;
        led_6.stato = LOW;
     //   led_7.stato = LOW;
     //   led_8.stato = LOW;
      }else if(m >= clockEvent * 2 & m < clockEvent * 3){ //3° clock
        led_1.stato = HIGH;
        led_2.stato = HIGH;
        led_3.stato = HIGH;
        led_4.stato = HIGH;
        led_5.stato = HIGH;
        led_6.stato = HIGH;
     //   led_7.stato = HIGH;
     //   led_8.stato = HIGH;
      } else if(m >= clockEvent * 3 & m < clockEvent * 4){ //4° clock
        led_1.stato = LOW;
        led_2.stato = LOW;
        led_3.stato = LOW;
        led_4.stato = LOW;
        led_5.stato = LOW;
        led_6.stato = LOW;
     //   led_7.stato = LOW;
     //   led_8.stato = LOW;
      } else if(m >= clockEvent * 4 & m < clockEvent * 5){ //5° clock
        led_1.stato = HIGH;
        led_2.stato = LOW;
        led_3.stato = LOW;
        led_4.stato = LOW;
        led_5.stato = LOW;
        led_6.stato = LOW;
     //   led_7.stato = LOW;
     //   led_8.stato = LOW;
      } else if(m >= clockEvent * 5 & m < clockEvent * 6){ //6° clock
        led_1.stato = LOW;
        led_2.stato = HIGH;
        led_3.stato = LOW;
        led_4.stato = LOW;
        led_5.stato = LOW;
        led_6.stato = LOW;
     //   led_7.stato = LOW;
     //   led_8.stato = LOW;
      } else if(m >= clockEvent * 6 & m < clockEvent * 7){ //7° clock
        led_1.stato = LOW;
        led_2.stato = LOW;
        led_3.stato = HIGH;
        led_4.stato = LOW;
        led_5.stato = LOW;
        led_6.stato = LOW;
     //   led_7.stato = LOW;
     //   led_8.stato = LOW;
      } else if(m >= clockEvent * 7 & m < clockEvent * 8){ //8° clock
        led_1.stato = LOW;
        led_2.stato = LOW;
        led_3.stato = LOW;
        led_4.stato = HIGH;
        led_5.stato = LOW;
        led_6.stato = LOW;
     //   led_7.stato = LOW;
     //   led_8.stato = LOW;
      } else if(m >= clockEvent * 8 & m < clockEvent * 9){ //9° clock
        led_1.stato = LOW;
        led_2.stato = LOW;
        led_3.stato = LOW;
        led_4.stato = LOW;
        led_5.stato = HIGH;
        led_6.stato = LOW;
     //   led_7.stato = LOW;
     //   led_8.stato = LOW;
      } else if(m >= clockEvent * 9 & m < clockEvent * 10){ //10° clock
        led_1.stato = LOW;
        led_2.stato = LOW;
        led_3.stato = LOW;
        led_4.stato = LOW;
        led_5.stato = LOW;
        led_6.stato = HIGH;
     //   led_7.stato = LOW;
      //  led_8.stato = LOW;
      } else if(m >= clockEvent * 10 & m < clockEvent * 11){ //11° clock
        led_1.stato = LOW;
        led_2.stato = LOW;
        led_3.stato = LOW;
        led_4.stato = LOW;
        led_5.stato = LOW;
        led_6.stato = LOW;
      //  led_7.stato = HIGH;
      //  led_8.stato = LOW;
      }  else if(m >= clockEvent * 11 & m < clockEvent * 12){ //13° clock
        led_1.stato = LOW;
        led_2.stato = LOW;
        led_3.stato = LOW;
        led_4.stato = LOW;
        led_5.stato = LOW;
        led_6.stato = HIGH;
      //  led_7.stato = LOW;
      //  led_8.stato = LOW;
      } else if(m >= clockEvent * 12 & m < clockEvent * 13){ //13° clock
        led_1.stato = LOW;
        led_2.stato = LOW;
        led_3.stato = LOW;
        led_4.stato = LOW;
        led_5.stato = HIGH;
        led_6.stato = LOW;
      //  led_7.stato = LOW;
      //  led_8.stato = LOW;
      } else if(m >= clockEvent * 13 & m < clockEvent * 14){ //13° clock
        led_1.stato = LOW;
        led_2.stato = LOW;
        led_3.stato = LOW;
        led_4.stato = HIGH;
        led_5.stato = LOW;
        led_6.stato = LOW;
      //  led_7.stato = LOW;
      //  led_8.stato = LOW;
      } else if(m >= clockEvent * 14 & m < clockEvent * 15){ //13° clock
        led_1.stato = LOW;
        led_2.stato = LOW;
        led_3.stato = HIGH;
        led_4.stato = LOW;
        led_5.stato = LOW;
        led_6.stato = LOW;
      //  led_7.stato = LOW;
      //  led_8.stato = LOW;
      } else if(m >= clockEvent * 15 & m < clockEvent * 16){ //13° clock
        led_1.stato = LOW;
        led_2.stato = HIGH;
        led_3.stato = LOW;
        led_4.stato = LOW;
        led_5.stato = LOW;
        led_6.stato = LOW;
      //  led_7.stato = LOW;
      //  led_8.stato = LOW;
      } else if(m >= clockEvent * 16 & m < clockEvent * 17){ //13° clock
        led_1.stato = HIGH;
        led_2.stato = LOW;
        led_3.stato = LOW;
        led_4.stato = LOW;
        led_5.stato = LOW;
        led_6.stato = LOW;
      //  led_7.stato = LOW;
      //  led_8.stato = LOW;
      } else if(m >= clockEvent * 17 & m < clockEvent * 18){ //13° clock
        led_1.stato = LOW;
        led_2.stato = LOW;
        led_3.stato = LOW;
        led_4.stato = LOW;
        led_5.stato = LOW;
        led_6.stato = LOW;
      //  led_7.stato = LOW;
      //  led_8.stato = LOW;
      } 

      onOffLED();

      if(m >= clockEvent * 20){
        startTimeLED = millis();//riavvia il timer...  
      }
      
    }

    void onOffLED(){
      digitalWrite(led_1.pin, led_1.stato);
      digitalWrite(led_2.pin, led_2.stato);
      digitalWrite(led_3.pin, led_3.stato);
      digitalWrite(led_4.pin, led_4.stato);
      digitalWrite(led_5.pin, led_5.stato);
      digitalWrite(led_6.pin, led_6.stato);
    //  digitalWrite(led_7.pin, led_7.stato);
    //  digitalWrite(led_8.pin, led_8.stato);
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
