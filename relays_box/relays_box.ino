#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

const int relay1 = 2;
const int relay2 = 3;
const int relay3 = 4;
const int relay4 = 5;
const int relay5 = 6;
const int relay6 = 7;
const int relay7 = 8;
const int relay8 = 9;
const int     IR = 10;

int r1 = 0;
int r2 = 0;
int r3 = 0;
int r4 = 0;
int r5 = 0;
int r6 = 0;
int r7 = 0;
int r8 = 0;
bool reverse = false;

float   speedLCD = 0;  //only to print speedDelay/1000 on LCD
float speedDelay = 50; //speed is in milliseconds
int        prgNb = 0;
byte relaysPower = 1;

unsigned long  currentTime = 0;
unsigned long previousTime = 0;
unsigned long   previousIR = 0;

int IRDelay = 50;

int irValue;
#include <IRremote.h>
IRrecv irrecv(IR);     
decode_results results;;

byte fullCase[8]={B11111, B11111, B11111, B11111,
                  B11111, B11111, B11111, B11111,};

void setup() {
  Serial.begin(9600);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
  pinMode(relay8, OUTPUT);
  pinMode(IR    ,  INPUT);
  
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
}

void loop() {
  speedLCD = speedDelay / 1000;
  
  timer();
  relayTask();
  lcdTask();
  irReceiver();
}

void timer(){
  currentTime = millis();

  if(currentTime - previousTime >= speedDelay){
    previousTime = currentTime;
    progTask();
  }
}



void irReceiver(){
/*
                flèche droite == -15811
                flèche gauche == 8925
                flèche haut == -28561
                flèche bas == -8161
                power == -23971
                stop == -7651
                EQ == -26521
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
      }
    }
  }
  irrecv.resume();
}


void progTask(){
  
  switch(prgNb){
    
    case 0:
      lcd.setCursor(0,2);
      lcd.print("Nom: All off         ");
      relaysPower = 0;
    break;

    case 1:
      lcd.setCursor(0,2);
      lcd.print("Nom: All on         ");
      relaysPower = -1;
      for(int i = 2; i < 10; i++){
        digitalWrite(i, LOW);
      }
    break;
    
    case 2:
      lcd.setCursor(0,2);
      lcd.print("Nom: balayage 1->8  ");
      
      if(relaysPower >= 8){
      relaysPower = 1;
      }
      else{
        relaysPower++;
      }      
    break;

    
    case 3:
      lcd.setCursor(0,2);
      lcd.print("Nom: balayage 1<-8 ");
      
      if(relaysPower <= 1){
      relaysPower = 8;      
      }
      else{
        relaysPower--;
      }      
    break;

    
    case 4:
      lcd.setCursor(0,2);
      lcd.print("Nom: clign 1-4<->5-8 ");
    
      if(relaysPower == 11){
        relaysPower = 10;
      }
      else{
        relaysPower = 11;
       } 
    break;

    case 5:
      lcd.setCursor(0,2);
      lcd.print("Nom: balayage 1<->8 ");
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





void lcdTask(){
  
  lcd.setCursor(0,0);
  lcd.print("delais : ");
  lcd.print(speedLCD);
  lcd.print("s");
  
  lcd.setCursor(0,1);
  lcd.print("Prog : #");
  lcd.print(prgNb);
  lcd.print("   ");

  r1 = !digitalRead(relay1);
  r2 = !digitalRead(relay2);
  r3 = !digitalRead(relay3);
  r4 = !digitalRead(relay4);
  r5 = !digitalRead(relay5);
  r6 = !digitalRead(relay6);
  r7 = !digitalRead(relay7);
  r8 = !digitalRead(relay8);

  
  lcd.setCursor(4,3);
  lcd.print("1>");
  lcd.setCursor(14,3);
  lcd.print("<8");

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
