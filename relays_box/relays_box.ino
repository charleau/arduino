/**
 * Relay box Version 2
 * 
 **/


/*------------------ Déclaration des pins utilisées ------------------*/
const int relay1 = 2;
const int relay2 = 3;
const int relay3 = 4;
const int relay4 = 5;
const int relay5 = 6;
const int relay6 = 7;
const int relay7 = 8;
const int relay8 = 9;
const int     IR = 10;
const int anaSound = A0;
const int digSound = 11;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

#include <IRremote.h>
IRrecv irrecv(IR);     
decode_results results;;

#include "RTClib.h"
RTC_DS1307 rtc;

/*------------------ Déclaration des variables utilisées ------------------*/
        int r1 = 0;
        int r2 = 0;
        int r3 = 0;
        int r4 = 0;
        int r5 = 0;
        int r6 = 0;
        int r7 = 0;
        int r8 = 0;

 int threshold = 7;
int soundValue = 0;
                    
        bool reverse = false;
bool isSoundReactive = false;

  int setYear = 2023;
 int setMonth = 6;
   int setDay = 15;
  int setHour = 0;
int setMinute = 0;
char daysWeek[7][3] = {"Dim", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam"};
bool rtcOK = false;

float   speedLCD = 0;  //only to print speedDelay/1000 on LCD
float speedDelay = 50; //speed is in milliseconds
int        prgNb = 0;
byte relaysPower = 1;

/*----- Variables timer -----*/
unsigned long   currentTime = 0;
unsigned long  previousTime = 0;
unsigned long    previousIR = 0;
unsigned long previousSound = 0;
             int soundDelay = 15;
                int IRDelay = 50;

int irValue;

/*----- Caractère plein pour LCD -----*/
byte fullCase[8]={B11111, B11111, B11111, B11111,
                  B11111, B11111, B11111, B11111,};


/*--------------------------- Setup du Arduino ---------------------------*/
void setup() {
  Serial.begin(115200);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
  pinMode(relay8, OUTPUT);
  pinMode(IR    ,  INPUT);
  pinMode(anaSound, INPUT);
  
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  digitalWrite(relay8, HIGH);

  lcd.init();
  lcd.backlight();

  lcd.createChar(1, fullCase);

  irrecv.enableIRIn();
  decode_results results;

  if(!rtc.begin()){
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("     RTC error!     ");
    while (1);
  }
  //rtcSetting();
}

/*------------------------------------- Programme principal ----------------------------------*/
void loop() {
  speedLCD = speedDelay / 1000;
  
  soundReact();
  timer();
  relayTask();
  lcdTask();
  irReceiver();
  
}

/*------------------------------ Fonction de réaction au son -----------------------------*/

void soundReact(){
    soundValue = analogRead(anaSound);
    soundValue = abs(soundValue - (110 + threshold));
/*
    Serial.print("X:");
    Serial.println(soundValue);
*/
  if(isSoundReactive){
    if(soundValue > 6){
      progTask();
    }
  }
}

/*-------------------------------------- Fonction Timer --------------------------------------*/
void timer(){
  currentTime = millis();

  if(!isSoundReactive){
    if(currentTime - previousTime >= speedDelay){
      previousTime = currentTime;
      progTask();
    }
  }
}

/*------------------------------ Gestion des différents programmes -----------------------------*/
void progTask(){
  
  switch(prgNb){
    
    case 0:
      lcd.setCursor(6,2);
      lcd.print("All off         ");
      relaysPower = 0;
    break;

    case 1:
      lcd.setCursor(6,2);
      lcd.print("All on         ");
      relaysPower = -1;
      for(int i = 2; i < 10; i++){
        digitalWrite(i, LOW);
      }
    break;
    
    case 2:
      lcd.setCursor(6,2);
      lcd.print("balayage 1->8  ");
      
      if(relaysPower >= 8){
      relaysPower = 1;
      }
      else{
        relaysPower++;
      }      
    break;

    
    case 3:
      lcd.setCursor(6,2);
      lcd.print("balayage 1<-8    ");
      
      if(relaysPower <= 1){
      relaysPower = 8;      
      }
      else{
        relaysPower--;
      }      
    break;

    
    case 4:
      lcd.setCursor(6,2);
      lcd.print("clign 1-4<->5-8     ");
    
      if(relaysPower == 11){
        relaysPower = 10;
      }
      else{
        relaysPower = 11;
       } 
    break;

    case 5:
      lcd.setCursor(6,2);
      lcd.print("balayage 1<->8     ");
      if(reverse){
        if(relaysPower >= 8){
        reverse =!reverse;
        }
        else{
          relaysPower++;
        } 
      }
      else{
        if(relaysPower <= 1){
        reverse =!reverse;      
        }
        else{
          relaysPower--;
        } 
      }
    break;
  }
}

/*--------------------------- Fonction de gestion de la manette IR ---------------------------*/
void irReceiver(){
/*
                flèche droite == -15811
                flèche gauche == 8925
                  flèche haut == -28561
                   flèche bas == -8161
                        power == -23971
                         stop == -7651
                            EQ== -26521
                            0 == 26775
                            8 == 19125
                            9 == 21165
*/
  if(currentTime - previousIR >= IRDelay){
    previousIR = currentTime;
    if (irrecv.decode(&results)){
      irValue = results.value;
      Serial.println(irValue);

      switch(irValue){
        case -23971:
            prgNb = 1;
        break;
        
        case -7651:
            prgNb = 0;
        break;
        
        case -15811:
          if(prgNb < 5 && prgNb >= 1){
            prgNb++;
          }
        break;
        
        case 8925:
          if(prgNb > 2 && prgNb <= 5){
            prgNb--;
          }
        break;

        case -28561:
          speedDelay = speedDelay + 50;
        break;

        case -8161:
          if(speedDelay > 50){
            speedDelay = speedDelay - 50;
          }
        break;
        
        case -26521:
          isSoundReactive = !isSoundReactive;
        break;

        case 19125:
          adjustThreshold();
        break;
      }
    }
  }
  irrecv.resume();
}

/*------------------------------ Ajustement du threshold -----------------------------*/

void adjustThreshold(){
  lcd.clear();
  while(irValue != 765){
      if (irrecv.decode(&results)){
        irValue = results.value;
        if(irValue == -28561){ threshold++; }
        if(irValue == -8161){ threshold--; }
      }
      irrecv.resume();
      lcd.setCursor(0, 2);
      lcd.print("Sensibility : ");
      lcd.print(threshold);
      lcd.print("        ");
    }
    irrecv.resume();
    irValue = 0;
    lcd.clear();
}

/*------------------------------ Gestion de l'allumage des relais -----------------------------*/
void relayTask(){
  switch(relaysPower){

    case -1: break;
    
    case 0:
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, HIGH);
      digitalWrite(relay5, HIGH);
      digitalWrite(relay6, HIGH);
      digitalWrite(relay7, HIGH);
      digitalWrite(relay8, HIGH); 
    break;    


    case 1:
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, HIGH);
      digitalWrite(relay5, HIGH);
      digitalWrite(relay6, HIGH);
      digitalWrite(relay7, HIGH);
      digitalWrite(relay8, HIGH);      
    break;
    case 2:
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, LOW);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, HIGH);
      digitalWrite(relay5, HIGH);
      digitalWrite(relay6, HIGH);
      digitalWrite(relay7, HIGH);
      digitalWrite(relay8, HIGH);
    break;
    case 3:
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, LOW);
      digitalWrite(relay4, HIGH);
      digitalWrite(relay5, HIGH);
      digitalWrite(relay6, HIGH);
      digitalWrite(relay7, HIGH);
      digitalWrite(relay8, HIGH);
    break;
    case 4:
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, LOW);
      digitalWrite(relay5, HIGH);
      digitalWrite(relay6, HIGH);
      digitalWrite(relay7, HIGH);
      digitalWrite(relay8, HIGH);
    break;
    case 5:
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, HIGH);
      digitalWrite(relay5, LOW);
      digitalWrite(relay6, HIGH);
      digitalWrite(relay7, HIGH);
      digitalWrite(relay8, HIGH);
    break;
    case 6:
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, HIGH);
      digitalWrite(relay5, HIGH);
      digitalWrite(relay6, LOW);
      digitalWrite(relay7, HIGH);
      digitalWrite(relay8, HIGH);
    break;
    case 7:
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, HIGH);
      digitalWrite(relay5, HIGH);
      digitalWrite(relay6, HIGH);
      digitalWrite(relay7, LOW);
      digitalWrite(relay8, HIGH);
    break;
    case 8:
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, HIGH);
      digitalWrite(relay5, HIGH);
      digitalWrite(relay6, HIGH);
      digitalWrite(relay7, HIGH);
      digitalWrite(relay8, LOW);
    break;



    case 10:
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, HIGH);
      digitalWrite(relay5, LOW);
      digitalWrite(relay6, LOW);
      digitalWrite(relay7, LOW);
      digitalWrite(relay8, LOW);      
    break;
    case 11 :
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, LOW);
      digitalWrite(relay3, LOW);
      digitalWrite(relay4, LOW);
      digitalWrite(relay5, HIGH);
      digitalWrite(relay6, HIGH);
      digitalWrite(relay7, HIGH);
      digitalWrite(relay8, HIGH);      
    break;  
  }
}

/*------------------------------------- DS1307 RTC ------------------------------------*/

void rtcTask(){
  
}

/*--------------------------------- Affichage du LCD ----------------------------------*/
void lcdTask(){

  DateTime now = rtc.now();
  
  lcd.setCursor(0,0);
  lcd.print("delais : ");
  if(!isSoundReactive){
    lcd.print(speedLCD);
    lcd.print("s         ");
  }
  else{
    lcd.print("Sound react");    
  }
  
  lcd.setCursor(0,1);
  lcd.print("Prog : #");
  lcd.print(prgNb);
  lcd.print("            ");
  lcd.setCursor(15,1);
  if(now.hour() < 10){ lcd.print("0"); }
  lcd.print(now.hour());
  lcd.print(":");
  if(now.minute() < 10){ lcd.print("0"); }
  lcd.print(now.minute());
  lcd.print(" ");

  lcd.setCursor(0,2);
  lcd.print("Nom:");

  r1 = !digitalRead(relay1);
  r2 = !digitalRead(relay2);
  r3 = !digitalRead(relay3);
  r4 = !digitalRead(relay4);
  r5 = !digitalRead(relay5);
  r6 = !digitalRead(relay6);
  r7 = !digitalRead(relay7);
  r8 = !digitalRead(relay8);

  
  lcd.setCursor(0,3);
  lcd.print("    1>");
  lcd.setCursor(14,3);
  lcd.print("<8    ");

  if(r1){
    lcd.setCursor((4+relay1),3);
    lcd.write(1);
  }
  else{
    lcd.setCursor((4+relay1),3);
    lcd.print(" ");
  }
  if(r2){
    lcd.setCursor((4+relay2),3);
    lcd.write(1);
  }
  else{
    lcd.setCursor((4+relay2),3);
    lcd.print(" ");
  }
  if(r3){
    lcd.setCursor((4+relay3),3);
    lcd.write(1);
  }
  else{
    lcd.setCursor((4+relay3),3);
    lcd.print(" ");
  }
  if(r4){
    lcd.setCursor((4+relay4),3);
    lcd.write(1);
  }
  else{
    lcd.setCursor((4+relay4),3);
    lcd.print(" ");
  }
  if(r5){
    lcd.setCursor((4+relay5),3);
    lcd.write(1);
  }
  else{
    lcd.setCursor((4+relay5),3);
    lcd.print(" ");
  }
  if(r6){
    lcd.setCursor((4+relay6),3);
    lcd.write(1);
  }
  else{
    lcd.setCursor((4+relay6),3);
    lcd.print(" ");
  }
  if(r7){
    lcd.setCursor((4+relay7),3);
    lcd.write(1);
  }
  else{
    lcd.setCursor((4+relay7),3);
    lcd.print(" ");
  }
  if(r8){
    lcd.setCursor((4+relay8),3);
    lcd.write(1);
  }
  else{
    lcd.setCursor((4+relay8),3);
    lcd.print(" ");
  }
  
}

void rtcSetting(){

  /*
            enter == 765
                0 == 26775
                9 == 21165
      flèche haut == -28561
       flèche bas == -8161
  */
  
  DateTime now = rtc.now();
  
  lcd.setCursor(0, 0);
  lcd.print("RTC setting correct?");
  lcd.setCursor(0, 1);
  lcd.print(daysWeek[now.dayOfTheWeek()]);
  lcd.setCursor(3, 1);
  lcd.print(" ");
  lcd.print(now.day());
  lcd.print("-");
  lcd.print(now.month());
  lcd.print("-");
  lcd.print(now.year());
  lcd.print(" ");
  if(now.hour() < 10){ lcd.print("0"); }
  lcd.print(now.hour());
  lcd.print(":");
  if(now.minute() < 10){ lcd.print("0"); }
  lcd.print(now.minute());
  lcd.setCursor(0, 3);
  lcd.print("0 for OK  | 9 if not");

  while(irValue != 26775 && irValue != 21165){
    delay(10);
    if (irrecv.decode(&results)){
      irValue = results.value;
      if(irValue == 26775){rtcOK = true;}
    }
    irrecv.resume();
  }

  if(!rtcOK){
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("      SET DATE      ");
/*-------------SET THE DAY-------------*/
    while(irValue != 765){
      if (irrecv.decode(&results)){
        irValue = results.value;
        if(irValue == -28561 && setDay < 31){ setDay++; }
        if(irValue == -8161 && setDay > 1){ setDay--; }
      }
      irrecv.resume();
      lcd.setCursor(0, 2);
      lcd.print("      Day : ");
      lcd.print(setDay);
      lcd.print("        ");
    }
    irrecv.resume();
    irValue = 0;

/*-------------SET THE MONTH-------------*/
    while(irValue != 765){
      if (irrecv.decode(&results)){
        irValue = results.value;
        if(irValue == -28561 && setMonth < 12){ setMonth++; }
        if(irValue == -8161 && setMonth > 1){ setMonth--; }
      }
      irrecv.resume();
      lcd.setCursor(0, 2);
      lcd.print("    Month : ");
      lcd.print(setMonth);
      lcd.print("        ");
    }
    irrecv.resume();
    irValue = 0;

/*-------------SET THE YEAR-------------*/
    while(irValue != 765){
      if (irrecv.decode(&results)){
        irValue = results.value;
        if(irValue == -28561){ setYear++; }
        if(irValue == -8161 && setYear > 2022){ setYear--; }
      }
      irrecv.resume();
      lcd.setCursor(0, 2);
      lcd.print("     Year : ");
      lcd.print(setYear);
      lcd.print("        ");
    }
    irrecv.resume();
    irValue = 0;

    lcd.setCursor(0, 0);
    lcd.print("      SET TIME      ");

/*-------------SET THE HOUR-------------*/
    while(irValue != 765){
      if (irrecv.decode(&results)){
        irValue = results.value;
        if(irValue == -28561 && setHour < 23){ setHour++; }
        if(irValue == -8161 && setHour > 0){ setHour--; }
      }
      irrecv.resume();
      lcd.setCursor(0, 2);
      lcd.print("     Hour : ");
      lcd.print(setHour);
      lcd.print("        ");
    }
    irrecv.resume();
    irValue = 0;

/*-------------SET THE MINUTE-------------*/
    while(irValue != 765){
      if (irrecv.decode(&results)){
        irValue = results.value;
        if(irValue == -28561 && setMinute < 59){ setMinute++; }
        if(irValue == -8161 && setMinute > 0){ setMinute--; }
      }
      irrecv.resume();
      lcd.setCursor(0, 2);
      lcd.print("   Minute : ");
      lcd.print(setMinute);
      lcd.print("        ");
    }
    irrecv.resume();
    irValue = 0;

    rtc.adjust(DateTime(setYear, setMonth, setDay, setHour, setMinute, 0));
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("   Settings  have   ");
    lcd.print("    been  saved!    ");
    delay(3000);
    lcd.clear();
    
  }
  
}
