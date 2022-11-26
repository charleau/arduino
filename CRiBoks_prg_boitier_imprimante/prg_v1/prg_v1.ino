 


//-----------------------DÉCLARATIONS DES PORTS UTILISÉS ET DES #INCLUDE-----------------------\\

int enter = A0;
int up = A1;
int down = A2;        // BOUTONs (= EST LE PORT ARDUINO PERMANENT)
int back = A3;
int next = A4;
int limit_door = A5;

int lumiere = 9;  //relais
int fans = 10;    //relais
int temp_capt = 8;  // signal | 5v | gnd
int buzzer = 11;

#include <LiquidCrystal.h>                                    // LCD SCREEN
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include <DHT.h>
#define DHTPIN 8                                              // capteur de température
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//----------------------------DÉCLARATION DES VARIABLES----------------------------\\

int etatenter = 0;
int etatup = 0;
int etatdown = 0;
int etatback = 0;
int etatnext = 0;
int etatlimit_door = 0;

int etatfans = 1;
int etatled = 1;

int temp_auto_mode = 0;
int choix_etat_fans = 0;
int choix_menu = 0;
int set_temp = 25;
int choix_time = 0;
int t_max = 0;
int nb_erreur = 0;
bool temp_auto = false;
bool mode_nuit = false;
bool saison = false;
bool erreur = false;

int temperature;
int humidite;

//-----------------------DÉCLARATION DE L'UTILISATION DES PINS-----------------------\\

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(enter, INPUT);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(back, INPUT);
  pinMode(next, INPUT);
  pinMode(limit_door, INPUT);
  pinMode(temp_capt, INPUT);
  pinMode(lumiere, OUTPUT);
  pinMode(fans, OUTPUT);
  pinMode(buzzer, OUTPUT);

//-----------------------------AFFICHAGE DE DÉPART DU LCD----------------------------\\

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("CRiBoks V5.3");
  lcd.setCursor(2,1);
  lcd.print("Printer Box");
  delay(5000);
  
}

//-----------------------FONCTION BOUTONS BOITIER-----------------------\\

void boutons(void) {

                
  digitalWrite(enter, HIGH);
  digitalWrite(up, HIGH);
  digitalWrite(down, HIGH);
  digitalWrite(back, HIGH);
  digitalWrite(next, HIGH);
  digitalWrite(limit_door, HIGH);
                                    // DEFINITIONS BOUTONS BOITIER
  etatenter = digitalRead(enter);
  etatup = digitalRead(up);
  etatdown = digitalRead(down);
  etatback = digitalRead(back);
  etatnext = digitalRead(next);
  etatlimit_door = digitalRead(limit_door);
  
                                       // boutons sur boitier
    if(etatnext == LOW){
      
      etatnext = 0;
      delay(200);
    }                         //  
    if(etatback == LOW){
      
      etatback = 0;
      delay(200);
    }
    if(etatdown == LOW){
      if(choix_menu > 0){
        choix_menu = choix_menu - 1;
        etatdown = 0;
        delay(200);
      }
      else{
        choix_menu = 5;
        etatdown = 0;
        delay(200);
      }
    }                                   // Choix du menu
    if(etatup == LOW){
      if(choix_menu < 5){
        choix_menu = choix_menu + 1;
        etatup = 0;
        delay(200);
      }
      else{
        choix_menu = 0;
        etatup = 0;
        delay(200);
      }
    }
    if(etatenter == LOW){
      etatenter = 0;
      delay(200);
    }
}


//-----------------------FONCTION AFFICHAGE ÉCRAN LCD 16X2-----------------------\\

void ecran(){
  lcd.clear();
  if(choix_menu != 4){
    lcd.setCursor(0,0);
    lcd.print("Tmp:");                                    // LCD print temp and hum
    lcd.print(temperature);
    lcd.print("C");
    lcd.setCursor(9,0);
    lcd.print("Hum:");
    lcd.print(humidite);
    lcd.print("%");
  }


    
      if(choix_menu == 0){
        if(choix_etat_fans == 0){
          lcd.setCursor(0,1);
          //lcd.print("> Etat fans: OFF");
          lcd.print("> ventil: OFF  <");
          delay(100);                                       // menu sur fans -- etat off
          
          temp_auto = false;
          
          if(etatnext == 0){
            if(choix_etat_fans < 2){
              choix_etat_fans++; 
            }
            etatnext = 1;
          }
          if(etatback == 0){
            if(choix_etat_fans > 0){
              choix_etat_fans--;
            }
            etatback = 1;
          }
        }

        
        if(choix_etat_fans == 1){
          lcd.setCursor(0,1);
          //lcd.print("> Etat fans: ON ");
          lcd.print("> ventil:  ON  <");
          delay(100);                                       // menu sur fans -- etat on

          temp_auto = false;
          
          if(etatnext == 0){
            if(choix_etat_fans < 2){
              choix_etat_fans++; 
            }
            etatnext = 1;
          }
          if(etatback == 0){
            if(choix_etat_fans > 0){
              choix_etat_fans--;
            }
            etatback = 1;
          }
        }

        
        if(choix_etat_fans == 2){
          lcd.setCursor(0,1);
          //lcd.print("> Etat fans:AUTO");
          lcd.print("> ventil: AUTO <");
          delay(100);                                       // menu sur fans -- etat AUTO

          temp_auto = true;
  
          if(etatnext == 0){
            if(choix_etat_fans < 2){
              choix_etat_fans++; 
            }
            etatnext = 1;
          }
          if(etatback == 0){
            if(choix_etat_fans > 0){
              choix_etat_fans--;
            }
            etatback = 1;
          }
        }
      }



      

      if(choix_menu == 2){
        if(etatled == 0){
          lcd.setCursor(0,1);
          //lcd.print("> Etat led: OFF ");
          lcd.print("> lumiere: OFF <");
          delay(100);                                       // menu sur LED -- etat off
          if(etatenter == 0){
            etatled = 1;
            etatenter = 1;
          }
        }
        if(etatled == 1){
          lcd.setCursor(0,1);
          //lcd.print("> Etat led: ON ");
          lcd.print("> lumiere:  ON <");
          delay(100);                                       // menu sur LED -- etat on
          if(etatenter == 0){
            etatled = 0;
            etatenter = 1;
          }
        }
      }




      if(choix_menu == 1){
          lcd.setCursor(0,1);
          lcd.print(">MAX temp : ");
          lcd.print(set_temp);
          lcd.print("C<");
          delay(100);                                       // menu sur set temp
          if(etatnext == 0){
            set_temp++;
            etatnext = 1;
          }
          if(etatback == 0){
            set_temp--;
            etatback = 1;
          }
      }

      if(choix_menu == 3){
        if(choix_time == 0){
          lcd.setCursor(0,1);                                  // menu sur set time
          lcd.print(">  time:  DAY  <");
          delay(100);
          mode_nuit = false;
          if(etatenter == 0){
            choix_time = 1;
            etatenter = 1;
          }
        }
          if(choix_time == 1){
            lcd.setCursor(0,1);
            lcd.print(">  time: NIGHT <");
            delay(100);
            mode_nuit = true;
            if(etatenter == 0){
              choix_time = 0;
              etatenter = 1;
            }
          }
        }


      if(choix_menu == 4){
        lcd.setCursor(0,0);
        lcd.print("    JOURNAL    ");
        lcd.setCursor(0,1);
        lcd.print("n_err:");
        lcd.print(nb_erreur);
        lcd.print(" T_MX:");
        lcd.print(t_max);
        delay(100);
        if(etatenter == 0){
          nb_erreur = 0;
          t_max = 0;
          etatenter = 1;
        }
      }

      if(choix_menu == 5){
        lcd.setCursor(0,0);
        lcd.print("Printer BOX v5.3");
        lcd.setCursor(0,1);
        lcd.print(" Charles Ricard ");
        delay(100);
      }
      

      if(etatlimit_door == 1){
        while(etatlimit_door != 0){
          boutons();
          lcd.setCursor(0,0);
          lcd.print(">PORTE OUVERTE!<");
          lcd.setCursor(0,1);                                     // ouverture de porte
          lcd.print("lum:ON  fans:OFF");
          digitalWrite(lumiere, HIGH);
          digitalWrite(fans, LOW);
        }
      }
}

      void auto_vent(){
        if(temp_auto == true){
          
          if(temperature <= set_temp){
            etatfans = 0;
            digitalWrite(fans, LOW);
            erreur = false;
              //lcd.setCursor(0,0);
              //lcd.print("> AUTO VENTIL: <");
              //lcd.setCursor(0,1);
              //lcd.print(">   ARRET...   <");
              //delay(2000);
          }
          if(temperature > set_temp){
            etatfans = 1;
            digitalWrite(fans, HIGH);
              //lcd.setCursor(0,0);
              //lcd.print("> AUTO VENTIL: <");
              //lcd.setCursor(0,1);
              //lcd.print("> DEMARRAGE... <");
              //delay(2000);
          }
          if(temperature > set_temp + 2){
            if(mode_nuit == false){
              tone(buzzer, 2000);
            }
            while((temperature > set_temp + 2) && (etatenter == HIGH)){
              digitalWrite(fans, HIGH);
              digitalWrite(lumiere, LOW);

              lcd.setCursor(0,0);
              lcd.print("!! WATCH  OUT !!");
              lcd.setCursor(0,1);
              lcd.print(">> TO HI TEMP <<");
              delay(2000);
              temperature = dht.readTemperature();
              if(t_max < temperature){
                t_max = temperature;
              }
              etatenter = digitalRead(enter);
            }
            etatenter = 1;
            if(erreur == false){
              nb_erreur++;
              erreur = true;
            }
          }
          noTone(buzzer);
        }
      }



//------------------------------DÉPART BOUCLE PROGRAMME------------------------------\\

void loop() {
    temperature = dht.readTemperature();
    if(t_max < temperature){
      t_max = temperature;
    }
    humidite = dht.readHumidity();
    ecran();
    if(choix_etat_fans == 0){
      digitalWrite(fans, LOW);
    }
    if(choix_etat_fans == 1){
      digitalWrite(fans, HIGH);
    }
    if(etatled == 0){
      digitalWrite(lumiere, LOW);
    }
    if(etatled == 1){
      digitalWrite(lumiere, HIGH);
    }
    boutons();
    auto_vent();

   
}    // end void loop()
