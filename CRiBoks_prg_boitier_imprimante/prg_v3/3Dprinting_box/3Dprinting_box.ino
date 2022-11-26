/*
  Version 7.73
 
 * Ajout d'un deuxième boitier à contrôler :
 * {  
 *    deuxième DHT11
 *    deuxième limit switch pour nouvelle porte
 *    deuxième relais de lumière
 *    deuxième relais de ventilation
 * }
 
 * Changement de LCD vers LCD I2C 16x2
 * Remplacement des delay par une fonction avec [millis()]
 * Ajout de deux tonalités différentes du BUZZER lors d'erreur avec un des boitiers afin de les différencier
 * Ajustement de la fonction d'ouverture des portes
 * Ajout de [round()] pour les températures afin de réduire les décliques sans arrêt des relais
 * Ajout d'une fonction d'allumage automatique des lumières selon la température réglée

 */



#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <DHT.h>
#define DHTUp_pin 7
#define DHTUp_type DHT11
#define DHTDown_pin 9
#define DHTDown_type DHT11
DHT DHTUp(DHTUp_pin, DHTUp_type);
DHT DHTDown(DHTDown_pin, DHTDown_type);

//--------------------------DÉCLARATION DES PORTS UTILISÉS-------------------------\\

const int lightDown = 2;
const int ventilDown= 3;
const int lightUp = 4;
const int ventilUp = 5;
const int doorUp = 6;
const int DHTUp_capt = 7;
const int doorDown = 8;
const int DHTDown_capt = 9;
const int buzzer = 10;

const int enter = A0;
const int up = A2;
const int down = A1;        // BOUTONs (= EST LE PORT ARDUINO PERMANENT)
const int back = A3;
const int next = 11;

//----------------------------DÉCLARATION DES VARIABLES----------------------------\\

float v_logiciel = 7.73;

int enterPressed = 0;
int upPressed = 0;
int downPressed = 0;
int etatDoorUp = 0;
int etatDoorDown = 0;
int backPressed = 0;
int nextPressed = 0;
int doorUpPressed = 0;
int doorDownPressed = 0;

int tempUp;
int humUp;
int tempDown;
int humDown;

int setTempUp = 30;
int setTempDown = 30;
int t_maxUp = 0;
int t_maxDown = 0;

int nbErrUp = 0;
int nbErrDown = 0;

int menuState = -3;
int menuStateSave;

bool isVentilUp = false;
bool isVentilDown = false;
bool isLightUp = false;
bool isLightDown = false;
bool isErrUp = false;
bool isErrDown = false;

bool isReady = false;

bool setingsSaved = false;

bool isVentilUpSaved = false;
bool isVentilDownSaved = false;
bool isLightUpSaved = false;
bool isLightDownSaved = false;
bool isLightAuto = false;

bool alarm = false;

long cT = 0;
int buttonsDelay = 250;
long buttonsPrevious = 0;

int alarmUpDelay = 250;
long alarmUpPrevious = 0;

int alarmDownDelay = 500;
long alarmDownPrevious = 0;

//----------------------ASSIGNATION DE L'UTILISATION DES PORTS----------------------\\

void setup() {
  Serial.begin(9600);
  DHTUp.begin();
  DHTDown.begin();

  pinMode(enter, INPUT);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(back, INPUT);
  pinMode(next, INPUT);
  pinMode(doorUp, INPUT);
  pinMode(doorDown, INPUT);

  pinMode(DHTUp_capt, INPUT);
  pinMode(DHTDown_capt, INPUT);

  pinMode(lightDown, OUTPUT);
  pinMode(ventilDown, OUTPUT);
  pinMode(lightUp, OUTPUT);
  pinMode(ventilUp, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(lightDown, LOW);
  digitalWrite(ventilDown, HIGH);
  digitalWrite(lightUp, LOW);
  digitalWrite(ventilUp, HIGH);
  digitalWrite(doorUp, HIGH);
  digitalWrite(ventilDown, HIGH);

//-----------------------------AFFICHAGE DE DÉPART DU LCD----------------------------\\

  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("   CRiBoks V3   ");
  lcd.setCursor(0,1);
  lcd.print(" Charles Ricard ");
  delay(3000);
}

//------------------------------DÉPART BOUCLE PROGRAMME------------------------------\\

void loop() {

  cT = millis();

  boutons();
  menu(tempUp, tempDown);
  
  tempUp = DHTUp.readTemperature();
  humUp = DHTUp.readHumidity();
  
  tempDown = DHTDown.readTemperature();
  humDown = DHTDown.readHumidity();

  if(isLightAuto){
    if(tempUp >= setTempUp){
      isLightUp = true;
    }
    else{
      isLightUp = false;
    }
    if(tempDown >= setTempDown){
      isLightDown = true;
    }
    else{
      isLightDown = false;
    }
  }

  if(t_maxUp < tempUp){
    t_maxUp = tempUp;
  }
  if(t_maxDown < tempDown){
    t_maxDown = tempDown;
  }

  if(isVentilUp){ digitalWrite(ventilUp, LOW); } else{ digitalWrite(ventilUp, HIGH); }
  if(isVentilDown){ digitalWrite(ventilDown, LOW); } else{ digitalWrite(ventilDown, HIGH); }
  if(isLightUp){ digitalWrite(lightUp, LOW); } else{ digitalWrite(lightUp, HIGH); }
  if(isLightDown){ digitalWrite(lightDown, LOW); } else{ digitalWrite(lightDown, HIGH); }
  
   autoVentilUp();
   autoVentilDown();
}

//------------------------------FONCTION BOUTONS BOITIER-----------------------------\\

void boutons() {

  digitalWrite(enter, HIGH);
  digitalWrite(up, HIGH);
  digitalWrite(down, HIGH);
  digitalWrite(back, HIGH);
  digitalWrite(next, HIGH);
  digitalWrite(doorUp, HIGH);
  digitalWrite(doorDown, HIGH);

  if(cT - buttonsPrevious >= buttonsDelay){
    buttonsPrevious = cT;

    enterPressed = !digitalRead(enter);
    upPressed = digitalRead(up);
    downPressed = digitalRead(down);
    backPressed = digitalRead(back);
    nextPressed = digitalRead(next);
    doorUpPressed = digitalRead(doorUp);
    doorDownPressed = digitalRead(doorDown);

    if(nextPressed == 1){
      if(menuState < 6){
        menuState = menuState + 1;
      }
      else{
        menuState = -3;
      }
      nextPressed = 0;
    }
  
    if(backPressed == 1){
      if(menuState > -3){
        menuState = menuState - 1;
      }
      else{
        menuState = 6;
      }
      backPressed = 0;
    }
  }
  
  if(setingsSaved == false){
      isLightUpSaved = isLightUp;
      isLightDownSaved = isLightDown;
      menuStateSave = menuState;
      setingsSaved = true;
    }
    
  if(doorDownPressed == LOW){
    menuState = 8;
    isLightDown = true;
  }
  else if(doorUpPressed == LOW){
    menuState = 9;
    isLightUp = true;
  }
  else if(doorDownPressed == LOW && doorUpPressed == LOW){
    menuState = 7;
  }
  else{
    menuState = menuStateSave;
    setingsSaved = false;
  }
}

//----------------------------MENU AFFICHAGE LCD 16x2 I2C----------------------------\\

void menu(int tempUp, int tempDown){
  
  if(menuState == -3){
    lcd.setCursor(0,0);
    lcd.print("UP   T:");
    lcd.print(tempUp);
    lcd.print("C H:");
    lcd.print(humUp);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("DOWN T:");
    lcd.print(tempDown);
    lcd.print("C H:");
    lcd.print(humDown);
    lcd.print("%");
  }

  if(menuState == -2){
    lcd.setCursor(0,0);
    lcd.print("   LIGHT MODE   ");
    if(isLightAuto){
      lcd.setCursor(0,1);
      lcd.print(">State:  AUTO  <");
    }
    else{
      lcd.setCursor(0,1);
      lcd.print(">State: MANUAL <");
    }
    if(enterPressed){
        isLightAuto = !isLightAuto;
    }
    enterPressed = 0;
  }

  if(menuState == -1){
    lcd.setCursor(0,0);
    lcd.print("  LIGHT BOX UP  ");
    if(isLightUp){
      lcd.setCursor(0,1);
      lcd.print(">  State:  ON  <");
    }
    else{
      lcd.setCursor(0,1);
      lcd.print(">  State:  OFF <");
    }
    if(enterPressed){
        isLightUp = !isLightUp;
    }
    enterPressed = 0;
  }

  if(menuState == 0){
    lcd.setCursor(0,0);
    lcd.print(" LIGHT BOX DOWN ");
    if(isLightDown){
      lcd.setCursor(0,1);
      lcd.print(">  State:  ON  <");
    }
    else{
      lcd.setCursor(0,1);
      lcd.print(">  State:  OFF <");
    }
    if(enterPressed){
        isLightDown = !isLightDown;
    }
    enterPressed = 0;
  }

  if(menuState == 1){
    lcd.setCursor(0,0);
    lcd.print("Boitier du HAUT ");
    lcd.setCursor(0,1);
    lcd.print(">SET temp : ");
    lcd.print(setTempUp);
    lcd.print("C<");
    if(upPressed == 1){
      if(setTempUp < 75){
        setTempUp++;
      }
      else{
        lcd.setCursor(0,0);
        lcd.print(" Temp. maximale ");
        lcd.setCursor(0,1);
        lcd.print("    ATTEINTE    ");
        delay(2000);
      }
      upPressed = 0;
    }
    if(downPressed == 1){
      if(setTempUp > 20){ 
        setTempUp--;
      }
      else{
        lcd.setCursor(0,0);
        lcd.print(" Temp. minimale ");
        lcd.setCursor(0,1);
        lcd.print("    ATTEINTE    ");
        delay(2000);
      }
      downPressed = 0;
    }
  }

  if(menuState == 2){
    lcd.setCursor(0,0);
    lcd.print("Boitier du BAS  ");
    lcd.setCursor(0,1);
    lcd.print(">SET temp : ");
    lcd.print(setTempDown);
    lcd.print("C<");
    if(upPressed == 1){
      if(setTempDown < 75){
        setTempDown++;
      }
      else{
        lcd.setCursor(0,0);
        lcd.print(" Temp. maximale ");
        lcd.setCursor(0,1);
        lcd.print("    ATTEINTE    ");
        delay(2000);
      }
      upPressed = 0;
    }
    if(downPressed == 1){
      if(setTempDown > 20){ 
        setTempDown--;
      }
      else{
        lcd.setCursor(0,0);
        lcd.print(" Temp. minimale ");
        lcd.setCursor(0,1);
        lcd.print("    ATTEINTE    ");
        delay(2000);
      }
      downPressed = 0;
    }
  }

  if(menuState == 3){
    lcd.setCursor(0,0);
    lcd.print("                ");
    if(alarm){
      lcd.setCursor(0,1);
      lcd.print(">  time:  DAY  <");
    }
    else{
      lcd.setCursor(0,1);
      lcd.print(">  time: NIGHT <");
    }
    if(enterPressed){
        alarm = !alarm;
    }
    enterPressed = 0;
  }

  if(menuState == 4){
    lcd.setCursor(0,0);
    lcd.print(" JOURNAL BOX UP ");
    lcd.setCursor(0,1);
    lcd.print("NbErr:");
    lcd.print(nbErrUp);
    lcd.print("  TMax:");
    lcd.print(t_maxUp);
    if(enterPressed == 1){
      nbErrUp = 0;
      t_maxUp = 0;
      enterPressed = 0;
    }
  }

  if(menuState == 5){
    lcd.setCursor(0,0);
    lcd.print("JOURNAL BOX DOWN");
    lcd.setCursor(0,1);
    lcd.print("NbErr:");
    lcd.print(nbErrDown);
    lcd.print("  TMax:");
    lcd.print(t_maxDown);
    if(enterPressed){
      nbErrDown = 0;
      t_maxDown = 0;
      enterPressed = 0;
    }
  }

  if(menuState == 6){
    lcd.setCursor(0,0);
    lcd.print(" 3D Printer BOX ");
    lcd.setCursor(0,1);
    lcd.print("  Version ");
    lcd.print(v_logiciel);
    lcd.print("   ");
  }

  if(menuState == 7){
    lcd.setCursor(0,0);
    lcd.print(">TWO DOORS OPEN<");
    lcd.setCursor(0,1);
    lcd.print("lum:ON  vent:OFF");
  }
  
  if(menuState == 8){
    lcd.setCursor(0,0);
    lcd.print(">DOWN DOOR OPEN<");
    lcd.setCursor(0,1);
    lcd.print("lum:ON  vent:OFF");
  }
  
  if(menuState == 9){
    lcd.setCursor(0,0);
    lcd.print("> UP DOOR OPEN <");
    lcd.setCursor(0,1);
    lcd.print("lum:ON  vent:OFF");
  }
}

//----------------------------VENTILATION AUTOMATIQUE UP-----------------------------\\

void autoVentilUp(){
    if(tempUp <= setTempUp){
      isVentilUp = false;
      isErrUp = false;
    }
    if(tempUp > setTempUp){
      isVentilUp = true;
      isErrUp = false;
    }
    if(tempUp > setTempUp + 3){
        if(alarm){
          tone(buzzer, 1800);
          if(cT- alarmUpPrevious >= alarmUpDelay){
            alarmUpPrevious = cT;
            noTone(buzzer);
          }
        }
        else{
          noTone(buzzer);
        }
        tempUp = DHTUp.readTemperature();
        if(t_maxUp < tempUp){
          t_maxUp = tempUp;
        }
        if(!isErrUp){
          nbErrUp++;
          isErrUp = true;
        }
    }
}

//---------------------------VENTILATION AUTOMATIQUE DOWN----------------------------\\

void autoVentilDown(){
    if(tempDown <= setTempDown){
      isVentilDown = false;
      isErrDown = false;
    }
    if(tempDown > setTempDown){
      isVentilDown = true;
      isErrDown = false;
    }
    if(tempDown > setTempDown + 3){
      if(alarm){
        tone(buzzer, 1500);
        if(cT- alarmDownPrevious >= alarmDownDelay){
          alarmDownPrevious = cT;
          tone(buzzer, 1800);
        }
     }
     else{
      noTone(buzzer);
     }
      tempDown = DHTDown.readTemperature();
      if(t_maxDown < tempDown){
        t_maxDown = tempDown;
      }
      if(!isErrDown){
        nbErrDown++;
        isErrDown = true;
      }
    }
}
