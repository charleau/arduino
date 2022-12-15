/*
    Programme de départ pour boiter CRiBoks        
    debounce des boutons software
*/

//-----------------------DÉCLARATIONS DES PORTS UTILISÉS ET DES #INCLUDE-----------------------\\

const int enter = A0;
const int up = A1;
const int down = A2;        // BOUTONs (= EST LE PORT ARDUINO PERMANENT)
const int back = A3;
const int next = A5;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


//----------------------------DÉCLARATION DES VARIABLES----------------------------\\

bool etatEnter = false;
bool etatUp = false;
bool etatDown = false;
bool etatBack = false;
bool etatNext = false;

bool pushedEnter = false;
bool pushedUp = false;
bool pushedDown = false;
bool pushedBack = false;
bool pushedNext = false;

bool is_ready = false;
float v_logiciel = 0.0;

//-----------------------DÉCLARATION DE L'UTILISATION DES PINS-----------------------\\

void setup() {
  Serial.begin(9600);

  pinMode(enter, INPUT);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(back, INPUT);
  pinMode(next, INPUT);

  digitalWrite(enter, HIGH);
  digitalWrite(up, HIGH);
  digitalWrite(down, HIGH);
  digitalWrite(back, HIGH);
  digitalWrite(next, HIGH);

//-----------------------------AFFICHAGE DE DÉPART DU LCD----------------------------\\

  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("   CRiBoks V2   ");
  lcd.setCursor(0,1);
  lcd.print(" Charles Ricard ");
  delay(5000);
  
}

//----------------------------FONCTION GESTION DES BOUTONS---------------------------\\

void boutons(){

  etatEnter = !digitalRead(enter);
  etatUp = !digitalRead(up);
  etatDown = !digitalRead(down);
  etatBack = !digitalRead(back);
  etatNext = !digitalRead(next);

  if(etatEnter){pushedEnter = true;}
  if(etatUp){pushedUp = true;}
  if(etatDown){pushedDown = true;}
  if(etatBack){pushedBack = true;}
  if(etatNext){pushedNext = true;}
}

//------------------------------DÉPART BOUCLE PROGRAMME------------------------------\\

void loop() {

  boutons();
    lcd.print(pushedEnter);
    lcd.print(pushedUp);
    lcd.print(pushedDown);
    lcd.print(pushedBack);
    lcd.print(pushedNext);
    lcd.clear();
    
}    // end void loop()
