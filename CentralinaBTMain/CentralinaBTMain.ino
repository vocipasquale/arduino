#include <RTClib.h>

#include <RTClib.h>

#include <SoftwareSerial.h>
#include <RTClib.h>
#include <Wire.h>
//#include <EEPROM.h>

/*
 * pin output:
 * - output 1: PIN9
 * - output 2: PIN10
 * - output 3: PIN11
 * - output 4: PIN12
 * 
 * pin RTC:
 * - SCL: A5
 * - SDA: A4
 * 
 */

SoftwareSerial BTApp(2,3); // (RX,TX)
DS1307 rtc;

String input = "";

//definizione strutture logiche
typedef struct{
  uint8_t hour = (uint8_t)0;
  uint8_t minute = (uint8_t)0;
}Time;

typedef struct{
  Time start;
  Time stop;
  bool status=false;
  bool enabled=false;
}Alarm;

const int NUM_ALARM = 6;
//const int UART = 38400;

typedef struct{
  String name=""; //10 char
  int pin;
  bool status; //false = off   
  //int numAlarmEnabled = 0;
  Alarm alarms[NUM_ALARM];
}Output;

const int NUM_OUTPUT = 4;
Output outputs[NUM_OUTPUT];

const int NAME_LENGTH = 10;

String GET_TIME = "GT"; //"GET_TIME";
String GET_GENERAL_STATUS = "GS"; //"GET_GENERAL_STATUS";
String GET_STATUS_1 = "G1"; //"GET_STATUS_1";
String GET_STATUS_2 = "G2"; //"GET_STATUS_2";
String GET_STATUS_3 = "G3"; //"GET_STATUS_3";
String GET_STATUS_4 = "G4"; //"GET_STATUS_4";
String SET_TIME = "ST"; //"SET_TIME";
String SET_STATUS_1 = "S1"; //"SET_STATUS_1";
String SET_STATUS_2 = "S2"; //"SET_STATUS_2";
String SET_STATUS_3 = "S3"; //"SET_STATUS_3";
String SET_STATUS_4 = "S4"; //"SET_STATUS_4";
String RESET_1 = "R1";
String RESET_2 = "R2";
String RESET_3 = "R3";
String RESET_4 = "R4";

int inputInt = 0;

void setup() {
  Serial.begin(38400);
  
  //initialize bluetooth client
  BTApp.begin(38400);  

  delay(500);
  Serial.println("ready...");

  //initialize RTC
  rtc.begin();
  Wire.begin();  
  //if(!rtc.isrunning()) {
  //  Serial.println("RTC NOT run!");
  //  rtc.adjust(DateTime(__DATE__, __TIME__));
  //}else{
  // Serial.println(getTime());
  //} 

 //initializa outputs
 Output output1;
 setOutputName(&output1, "Output 1");
 output1.pin = 9;
 pinMode(9, OUTPUT);
 outputOff(&output1);
  
 Output output2;
 setOutputName(&output2, "Output 2");
 output2.pin = 10;
 pinMode(10, OUTPUT);
 outputOff(&output2);
  
 Output output3;
 setOutputName(&output3, "Output 3");
 output3.pin = 11;
 pinMode(11, OUTPUT);
 outputOff(&output3);

 Output output4; 
 setOutputName(&output4, "Output 4"); 
 output4.pin = 12;
 pinMode(12, OUTPUT);
 outputOff(&output4);
 
 //array output
 outputs[0] = output1;
 outputs[1] = output2;
 outputs[2] = output3;
 outputs[3] = output4; 
}

void loop() {
/*
 * Comandi AT
AT -> Testa la connessione all’interfaccia AT
AT + reset -> Resetta il nostro componente
AT + version -> Comunica la versione del firmware
AT + orgl -> Riporta le impostazioni correnti alle predefinite
AT + addr -> Il dispositivo ci comunica il proprio indirizzo
AT + name -> Domandiamo o impostiamo il nome del dispositivo
AT + rname -> Domandiamo il nome di un dispositivo bluetooth a cui siamo collegati (remoto)
AT + role -> Domandiamo o impostiamo il ruolo del dispositivo (1=Master / 0=Slave)
AT + class -> Domandiamo o impostiamo la classe del dispositivo ( Classe of Device CoD)
AT + iac -> Domandiamo o impostiamo le richieste del codice di accesso
AT + inqm -> Domandiamo o impostiamo le richieste della modalità di accesso
AT + pswd -> Domandiamo la password o ne impostiamo l’associazione
AT + uart -> Domandiamo i parametri UART o li reimpostiamo
AT + cmode -> Domandiamo la modalità di connessione o la impostiamo
AT + bind -> Domandiamo o impostiamo l’associazione all’indirizzo del bluetooth
AT + polar -> Domandiamo o impostiamo la polarità di output del LED
AT + pio -> Impostiamo o resettiamo un pin di Input/Output (I/O) utente
AT + mpio -> Impostiamo o resettiamo più pin di I/O utente
AT + mpio? -> Domandiamo l’I/O di un pin utente
AT + ipscan -> Domandiamo o impostiamo i parametri di scansione
AT + sniff -> Domandiamo o impostiamo i parametri di risparmio energetico SNIFF
AT + senm -> Domandiamo o impostiamo i modi di sicurezza e crittografia
AT + rmsad -> Elimina un dispositivo autenticato dalla lista
AT + fsad -> Trova un dispositivo dalla lista dei dispositivi autenticati
AT + adcn -> Domandiamo il numero totale dei dispositivi dalla lista dei dispositivi autenticati
AT + mrad -> Domandiamo quale è il dispositivo autenticato utilizzato più di recente
AT + state -> Domandiamo lo stato corrente del dispositivo
AT + init -> Inizializziamo il profilo SPP (ricerca)
AT + inq -> Domandiamo quale sia il dispositivo individuabile più vicino
AT + inqc -> Cancelliamo la ricerca dei dispositivi individuabili
AT + pair -> Associazione al dispositivo
AT + link -> Connessione ad un dispositivo remoto
AT + disc -> Disconnessione da un dispositivo remoto
AT + ensniff -> Entriamo in modalità risparmio energetico
AT + exsniff -> Usciamo dalla modalità di risparmio energetico
*/

/*
  if(BTApp.available() > 0){
    Serial.println(BTApp.readStringUntil('#'));
  }
  
 if(Serial.available()){
   BTApp.write(Serial.read());
 }
 */
  
    // controllo sullo stato degli allarmi
    checkAlarms(rtc.now());
    
    if(BTApp.available()){
      input = BTApp.readStringUntil('#');
      Serial.println(input);
    
    if(input.equals(GET_TIME)){
      Serial.println(getTime());
      BTApp.print(getTime());
    }

    if(input.equals(GET_GENERAL_STATUS)){
      Serial.println(getGeneralStatus());
        BTApp.print(getGeneralStatus());
    }
    
    if(input.equals(GET_STATUS_1)){
      Serial.println(getStatusOutput(1));
      BTApp.print(getStatusOutput(1));
    }

    if(input.equals(GET_STATUS_2)){
      Serial.println(getStatusOutput(2));
      BTApp.print(getStatusOutput(2));
    }

    if(input.equals(GET_STATUS_3)){
      Serial.println(getStatusOutput(3));
      BTApp.print(getStatusOutput(3));
    }

    if(input.equals(GET_STATUS_4)){
      Serial.println(getStatusOutput(4));
      BTApp.print(getStatusOutput(4));
    }

    if(input.startsWith(SET_TIME)){
      Serial.println(input);
      setTime(input.substring(SET_TIME.length()));
    }

    if(input.startsWith(SET_STATUS_1)){
      Serial.println(input.length());
      //log(input.substring(SET_STATUS_1.length()+2));
      setStatusOutuput(1, input.substring(SET_STATUS_1.length()+2));
    }

    if(input.startsWith(SET_STATUS_2)){
      Serial.println(input);
      //log(input.substring(SET_STATUS_2.length()+2));
      setStatusOutuput(2, input.substring(SET_STATUS_2.length()+2));
    }

    if(input.startsWith(SET_STATUS_3)){
      Serial.println(input);
      //log(input.substring(SET_STATUS_3.length()+2));
      setStatusOutuput(3, input.substring(SET_STATUS_3.length()+2));
    }

    if(input.startsWith(SET_STATUS_4)){
      Serial.println(input);
      //log(input.substring(SET_STATUS_4.length()+2));
      setStatusOutuput(4, input.substring(SET_STATUS_4.length()+2));
    }

    if(input.equals(RESET_1)){
      Serial.println(input);
      resetOutuput(&outputs[0]);
    }

    if(input.equals(RESET_2)){
      Serial.println(input);
      resetOutuput(&outputs[1]);
    }

    if(input.equals(RESET_3)){
      Serial.println(input);
      resetOutuput(&outputs[2]);
    }

    if(input.equals(RESET_4)){
      Serial.println(input);
      resetOutuput(&outputs[3]);
    }
  }

  delay(200);//da rivedere...
}


void setOutputName(Output *output, String name){
  //log("set output name, ricevuto: '"+name+"'");
  int diff = NAME_LENGTH - name.length();

  if(diff > 0){//parametro di lunghezza minore: devo fill-are
    for(int f=0;f<diff; f++){
      name.concat(" ");
    }
  }else if(diff < 0){//parametro di lunghezza eccessisa: devo troncare
   name = name.substring(0, NAME_LENGTH);
  }
  output->name = name;
 Serial.print("set output name: '");
 Serial.print(output->name);
 Serial.println("'");
     
}

/**
 * return hhmm
 */
String getTime(){
  DateTime now = rtc.now();
  String t = convertIntToString(now.hour());
  String m = convertIntToString(now.minute());
  t.concat(m);
  return t;  
}

/**
 * restituisce lo stato corrente di tutti gli output e relativo nome.
 * p.e (58 char):
 * 0400Output 1    01Output 2    01Output 3    00Output 4    
 * 
 * 04: 4 output
 * 00: spento output 1
 * 01: acceso Output 2
 * 01: acceso Output 3
 * 00: spento output 4 
 */
String getGeneralStatus(){
  String result = "";

  //numero di outputs
  result.concat(convertIntToString(NUM_OUTPUT));
 
  //sato e nome di ogni output
  for(int o=0; o<NUM_OUTPUT; o++){
     //stato
     result.concat(getStatusOnOff(o+1));
    
     //nome
     result.concat(outputs[o].name);
    // log("output name "+String(o+1)+": "+outputs[o].name);
  }
  //log(result);
  return result;
}

/**
 * modifica il time del RTC
 * con il valore del parmetro
 */
void setTime(String timeStr){
  if(checkHH(timeStr.substring(0,2).toInt()) && checkMI(timeStr.substring(2).toInt())){
    //data e ora definite manualmente
    DateTime customDate = 
      DateTime(rtc.now().year(), 
      rtc.now().month(), 
      rtc.now().day(), 
      (uint8_t)(timeStr.substring(0,2)).toInt(), 
      (uint8_t)(timeStr.substring(2)).toInt(), 
      (uint8_t)(0));
    Serial.print(timeStr.substring(0,2));
    Serial.print(":");
    Serial.println(timeStr.substring(2));
    
    rtc.adjust(customDate);
  }
}

bool checkMI(int minuti){
  return minuti >= 0 && minuti <= 59 ;
}

bool checkHH(int ora){
  return ora>=0 && ora<=23;
}
/*
 * accende il pin specificato
 */
void outputOn(Output *output){
  digitalWrite(output->pin, LOW);
  output->status=true;
}

/*
 * spegne il pin specificato
 */
void outputOff(Output *output){
  digitalWrite(output->pin, HIGH);
  output->status=false;
}

/*
 * restituisce lo stato, il nome e gli allarmi 
 * dell'uscita indicata nel parametro, p.e:
 * 0106100010301100113012001230130013301400143015001530:Output 1
 * 
 */
String getStatusOutput(int i){
  String result = "";

  //posizione 0-1: stato on/off
  result.concat(getStatusOnOff(i));
  
  //posizione 2-3: numero intervalli (sempre 6 in questa versione)
  result.concat(convertIntToString(NUM_ALARM));

  //posizione 4-52: elenco allarmi
  for(int a=0; a<NUM_ALARM; a++){
      result.concat(alarmToString(&outputs[i-1].alarms[a]));
  }

  //posizione 53: ":"
  result.concat(":");

  //posizione 54-66: name
  result.concat(outputs[i-1].name);

  return result;
}

/**
 * reimposta gli intervalli degli allarmi dell'uscita
 * indicata come parametro; cambia anche il nome dell'uscita.
 * esempio di statusOutput:
 * 100010301100113012001230130013301400143015001530:Name_XXX
 */
void setStatusOutuput(int o, String statusOutput){
  Alarm alarms[NUM_ALARM];
  alarms[0] = stringToAlarm(statusOutput.substring(0,8));
  alarms[1] = stringToAlarm(statusOutput.substring(8,16));
  alarms[2] = stringToAlarm(statusOutput.substring(16,24));
  alarms[3] = stringToAlarm(statusOutput.substring(24,32));
  alarms[4] = stringToAlarm(statusOutput.substring(32,40));
  alarms[5] = stringToAlarm(statusOutput.substring(40,48));
     
  for(int a=0; a<NUM_ALARM; a++){
   if(alarms[a].enabled){ //formalmente corretto: posso cambiare quello salvato
   // log("set alarm "+String(o)+": new value [start: "+String(alarms[a].start.hour)+":"+String(alarms[a].start.minute)+"]");
   // log("set alarm "+String(o)+": new value [stop: "+String(alarms[a].stop.hour)+":"+String(alarms[a].stop.minute)+"]");
    outputs[o-1].alarms[a].start.hour = alarms[a].start.hour; //(uint8_t) 11;//
    outputs[o-1].alarms[a].start.minute = alarms[a].start.minute; //(uint8_t) 59; //
    outputs[o-1].alarms[a].stop.hour = alarms[a].stop.hour; //(uint8_t) 23; //
    outputs[o-1].alarms[a].stop.minute = alarms[a].stop.minute; //(uint8_t) 59; //   
    outputs[o-1].alarms[a].enabled = true;
  }
 }

  //set name
  String newName = statusOutput.substring(statusOutput.lastIndexOf(":")+1);
  setOutputName(&outputs[o-1],newName);
}

/**
 * restituisce una sottostriga
 
  *char substr(char c[],int start, int lenght){
     for(int i=0; i
  }
*/
    /** converte una string in formato hhmihhmi in un alarm,   
     *  se la string non è formalmente corretta restitusce 
     *  un alarn con enabled == false
     */
    Alarm stringToAlarm(String alarmString){
      Serial.print("stringToAlarm, ricevuto input: ");
      Serial.println(alarmString); 
      
      Alarm result;
      result.enabled = false;
      
      Time start = stringToTime(alarmString.substring(0,4));
      Time stop = stringToTime(alarmString.substring(4));

      //log("stringToAlarm, convertito start: "+String(start.hour)+String(start.minute));
      //log("stringToAlarm, convertito stop: "+String(stop.hour)+String(stop.minute));
      
      if( (start.hour == 0 && start.minute == 0)
          || (stop.hour == 0 && stop.minute == 0)
       ){
        result.enabled = false;   
        Serial.println("stringToAlarm: alarm non definito!"); 
        return result;     
      }

      result.start = start;
      result.stop = stop;
      result.enabled = true;   
            
      return result;
    }

   
  /**
   * converte una string in formato hhmi
   * in un'istanza di Time, restituisce time = "0000" in caso di errore
   * 
   */
  Time stringToTime(String timeString){
    //log("1 stringToTime: "+timeString);
    Time time;
    String hh = timeString.substring(0,2);
    String mi = timeString.substring(2);    
      
    if( !checkHH(hh.toInt()) || !checkMI(mi.toInt())){     
     hh = "00";
     mi = "00";
    }
     
    time.hour = (uint8_t)hh.toInt();
    time.minute = (uint8_t)mi.toInt();
   // log("2 stringToTime: "+String(time.hour)+String(time.minute));
    
    return time;           
  }

  

/**
 * restituisce l'allarme nel formato hhmihhmi,
 * p.e.: 10001030
 */
 String alarmToString(Alarm *alarm){
  String result = "00000000";
  if(alarm->enabled){
    result = "";
    result.concat(convertIntToString(alarm->start.hour));
    result.concat(convertIntToString(alarm->start.minute));
    result.concat(convertIntToString(alarm->stop.hour));
    result.concat(convertIntToString(alarm->stop.minute));
  }
  return result;
 }
 
/**
 * restituisce 00 se Off, 01 se On
 */
String getStatusOnOff(int i){
  if(outputs[i-1].status){
    return "01";
  }else {
    return "00";
  }
}

String convertIntToString(int i){
  String result = "";
  if(i <= 9){
    result.concat("0");
  }
  result.concat(String(i));
  return result;
}

void resetOutuput(Output *o){
  if(o->status){//se è acceso in questo momento...
    outputOff(o);//...lo spengo
    Serial.print("Off output ");
    Serial.print(o->name);
    Serial.print(" status: ");
    Serial.println(o->status);
  }
  
  for(int a=0; a<NUM_ALARM; a++){
    o->alarms[a].start.hour=(uint8_t)0;
    o->alarms[a].start.minute=(uint8_t)0;
    o->alarms[a].stop.hour=(uint8_t)0;
    o->alarms[a].stop.minute=(uint8_t)0;
    o->alarms[a].status = false;
    o->alarms[a].enabled = false;
    Serial.print("reset alarms ");
    Serial.print(String(a+1));
    Serial.println(" output "+o->name);
  }
}

void checkAlarms(DateTime now){
 for(int o = 0; o<NUM_OUTPUT; o++){
// log("check output "+String(o+1)+"... ");
   for(int a=0; a<NUM_ALARM; a++){
      if(outputs[o].alarms[a].enabled){
        //log("alarm enabled Output"+String(o+1)+" alarm "+String(a));
        //log("output "+outputs[o].name+" status: "+String(outputs[o].status));
      if(outputs[o].alarms[a].status==false){
        //non è attivo, cioè lo "start" non è ancora stato raggiunto
        //log("output "+outputs[o].name+" spento! ");
        if(outputs[o].alarms[a].start.hour == now.hour()
          &&  outputs[o].alarms[a].start.minute == now.minute()){
            //log("accendo output "+String(o+1));
              outputOn(&outputs[o]);
              outputs[o].alarms[a].status = true;
          }       
        }else{
           //log("output "+outputs[o].name+" acceso! ");
          //è attivo, cioè lo start è stato raggiunto, bisogna controllare lo stop
          if(outputs[o].alarms[a].stop.hour == now.hour()
            &&  outputs[o].alarms[a].stop.minute == now.minute()){
              //log("spengo output "+String(o+1));
              outputOff(&outputs[o]);
              outputs[o].alarms[a].status = false;
          }
        }
      }
   
   }
  }
}
