 // PRG V2 corrections :
 // Rafraichissement de l'écran lcd
 // Correction des délais
 // Ajout de limites de température maximum et minimum pour le mode auto
 // Ajout de séquence de démarrage avec vérification du fonctionnement des composantes


//-----------------------DÉCLARATIONS DES PORTS UTILISÉS ET DES #INCLUDE-----------------------\\

int enter = A0;
int up = A1;
int down = A2;        // BOUTONs (= EST LE PORT ARDUINO PERMANENT)
int back = A3;
int next = 11;
/*int limit_door = A5;

int lumiere = 9;  //relais
int fans = 10;    //relais
int temp_capt = 8;  // signal | 5v | gnd
int buzzer = 11;
*/
#include <LiquidCrystal_I2C.h>                                    // LCD SCREEN
LiquidCrystal_I2C lcd(0x27, 16, 2);
/*
#include <DHT.h>
#define DHTPIN 8                                              // capteur de température
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);*/

//----------------------------DÉCLARATION DES VARIABLES----------------------------\\

bool lum_ok = false;
bool fans_ok = false;
bool temp_ok = false;
bool is_ready = false;

float v_logiciel = 5.63;

int etatenter = 1;
int etatup = 1;
int etatdown = 1;
int etatback = 1;
int etatnext = 1;
int etatlimit_door = 0;

int etatfans = 0;
int etatled = 0;

int temp_auto_mode = 0;
int choix_etat_fans = 0;
int choix_menu = 0;
int set_temp = 25;
int choix_time = 0;
int t_max = 0;
int nb_erreur = 0;
bool temp_auto = false;
bool mode_nuit = false;
bool erreur = false;

int temperature;
int humidite;

//-----------------------DÉCLARATION DE L'UTILISATION DES PINS-----------------------\\

void setup() {
  Serial.begin(9600);
 // dht.begin();

 /* pinMode(enter, INPUT);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(back, INPUT);
  pinMode(next, INPUT);
  pinMode(limit_door, INPUT);
  pinMode(temp_capt, INPUT);
  pinMode(lumiere, OUTPUT);
  pinMode(fans, OUTPUT);
  pinMode(buzzer, OUTPUT);
*/
//-----------------------------AFFICHAGE DE DÉPART DU LCD----------------------------\\
//----------------------------MENU AFFICHAGE LCD 16x2 I2C----------------------------\\
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("   CRiBoks V2   ");
  lcd.setCursor(0,1);
  lcd.print(" Charles Ricard ");
  delay(5000);

  lcd.init();
  lcd.backlight();
  
}

//-----------------------FONCTION BOUTONS BOITIER-----------------------\\

void boutons(void) {

                
  digitalWrite(enter, HIGH);
  digitalWrite(up, HIGH);
  digitalWrite(down, HIGH);
  digitalWrite(back, HIGH);
  digitalWrite(next, HIGH);
  /*digitalWrite(limit_door, HIGH);*/
                                    // DEFINITIONS BOUTONS BOITIER
  etatenter = digitalRead(enter);
  etatup = digitalRead(up);
  etatdown = digitalRead(down);
  etatback = digitalRead(back);
  etatnext = digitalRead(next);
  /*etatlimit_door = digitalRead(limit_door);*/
  
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
  if((choix_menu == 0) || (choix_menu == 1) || (choix_menu == 2) || (choix_menu == 3) || (choix_menu == 1)){
    lcd.setCursor(0,0);
    lcd.print("Tmp:");                                    // LCD print temp and hum
    lcd.print(temperature);
    lcd.print("C");
    lcd.print("  Hum:");
    lcd.print(humidite);
    lcd.print("%");
  }


    
      if(choix_menu == 0){
        if(choix_etat_fans == 0){
          lcd.setCursor(0,1);
          lcd.print("> ventil: OFF  <");                                       // menu sur fans -- etat off
          
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
          lcd.print("> ventil:  ON  <");                                       // menu sur fans -- etat on

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
          lcd.print("> ventil: AUTO <");                                       // menu sur fans -- etat AUTO

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
          lcd.print("> lumiere: OFF <");                                     // menu sur LED -- etat off
          if(etatenter == 0){
            etatled = 1;
            etatenter = 1;
          }
        }
        if(etatled == 1){
          lcd.setCursor(0,1);
          lcd.print("> lumiere:  ON <");                                     // menu sur LED -- etat on
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
          lcd.print("C<");                                       // menu sur set temp
          if(etatnext == 0){
            if(set_temp < 75){
              set_temp++;
            }
            else{
              lcd.setCursor(0,0);
              lcd.print(" Temp. maximale ");
              lcd.setCursor(0,1);
              lcd.print("    ATTEINTE    ");
              delay(2000);
            }
            etatnext = 1;
          }
          if(etatback == 0){
            if(set_temp > 20){ 
              set_temp--;
            }
            else{
              lcd.setCursor(0,0);
              lcd.print(" Temp. minimale ");
              lcd.setCursor(0,1);
              lcd.print("    ATTEINTE    ");
              delay(2000);
            }
            etatback = 1;
          }
      }

      if(choix_menu == 3){
        if(choix_time == 0){
          lcd.setCursor(0,1);                                  // menu sur set time
          lcd.print(">  time:  DAY  <");
          mode_nuit = false;
          if(etatenter == 0){
            choix_time = 1;
            etatenter = 1;
          }
        }
          if(choix_time == 1){
            lcd.setCursor(0,1);
            lcd.print(">  time: NIGHT <");
            mode_nuit = true;
            if(etatenter == 0){
              choix_time = 0;
              etatenter = 1;
            }
          }
        }


      if(choix_menu == 4){
        lcd.setCursor(0,0);
        lcd.print("    JOURNAL     ");
        lcd.setCursor(0,1);
        lcd.print("NbErr:");
        lcd.print(nb_erreur);
        lcd.print("  TMax:");
        lcd.print(t_max);
        if(etatenter == 0){
          nb_erreur = 0;
          t_max = 0;
          etatenter = 1;
        }
      }

      if(choix_menu == 5){
        lcd.setCursor(0,0);
        lcd.print(" 3D Printer BOX ");
        lcd.setCursor(0,1);
        lcd.print("  Version ");
        lcd.print(v_logiciel);
        lcd.print("   ");
      }
      

  /*    if(etatlimit_door == 1){
        while(etatlimit_door != 0){
          boutons();
          lcd.setCursor(0,0);
          lcd.print(">PORTE OUVERTE!<");
          lcd.setCursor(0,1);                                     // ouverture de porte
          lcd.print("lum:ON  fans:OFF");
          digitalWrite(lumiere, HIGH);
          digitalWrite(fans, LOW);
        }
      }*/
}

      void auto_vent(){
          if(temperature <= set_temp){
            etatfans = 0;
         //   digitalWrite(fans, LOW);
            erreur = false;
          }
          if(temperature > set_temp){
            etatfans = 1;
         //   digitalWrite(fans, HIGH);
          }
          if(temperature > set_temp + 2){
            if(mode_nuit == false){
         //     tone(buzzer, 2000);
            }
            while((temperature > set_temp + 2) && (etatenter == HIGH)){
           //   digitalWrite(fans, HIGH);
            //  digitalWrite(lumiere, LOW);

              lcd.setCursor(0,0);
              lcd.print("!! WATCH  OUT !!");
              lcd.setCursor(0,1);
              lcd.print(">> TO HI TEMP <<");
           //   temperature = dht.readTemperature();
              if(t_max < temperature){
                t_max = temperature;
              }
              etatenter = digitalRead(enter);
              if(erreur == false){
                nb_erreur++;
                erreur = true;
              }
            }
            etatenter = 1;
          }
        //  noTone(buzzer);
          erreur = false;
      }



//------------------------------DÉPART BOUCLE PROGRAMME------------------------------\\

void loop() {
/*if(is_ready == false){
    lcd.setCursor(0,0);
    lcd.print(" INITIALISATION ");
    lcd.setCursor(0,1);
    lcd.print("[#             ]");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[##            ]");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[###           ]");
    delay(150);
    
    digitalWrite(lumiere, HIGH);
    lcd.setCursor(0,1);
    lcd.print("[####          ]");
    delay(150);
    while(etatenter != 0 && etatnext != 0){
      boutons();
      lcd.setCursor(0,0);
      lcd.print("Lumiere allumee?");
      lcd.setCursor(0,1);
      lcd.print("  Enter for OK  ");
      delay(1000);
      lcd.setCursor(0,1);
      lcd.print(" Next if NOT OK ");
      boutons();
      delay(1000);
    }
    if(etatenter == 0){
      lum_ok = true;
      digitalWrite(lumiere, LOW);
      etatenter = 1;
    }
    if(etatnext == 0){
      etatnext = 1;
    }
    
    lcd.setCursor(0,0);
    lcd.print(" INITIALISATION ");
    lcd.setCursor(0,1);
    lcd.print("[#####         ]");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[######        ]");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[#######       ]");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[########      ]");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[#########     ]");
    delay(150);

    digitalWrite(fans, HIGH);
    while(etatenter != 0 && etatnext != 0){
      boutons();
      lcd.setCursor(0,0);
      lcd.print("ventilation ok ?");
      lcd.setCursor(0,1);
      lcd.print("  Enter for OK  ");
      delay(1000);
      lcd.setCursor(0,1);
      lcd.print(" Next if NOT OK ");
      boutons();
      delay(1000);
    }
    if(etatenter == 0){
      fans_ok = true;
      digitalWrite(fans, LOW);
      etatenter = 1;
    }
    if(etatnext == 0){
      etatnext = 1;
    }

    lcd.setCursor(0,0);
    lcd.print(" INITIALISATION ");
    lcd.setCursor(0,1);
    lcd.print("[##########    ]");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[###########   ]");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[############  ]");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[############# ]");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[##############]");
    delay(400);
    lcd.setCursor(0,1);
    lcd.print("[              ]");
    delay(700);
    temperature = dht.readTemperature();
    if (temperature != 0){
      temp_ok = true;
    }
    if(temp_ok == true && fans_ok == true && lum_ok == true){
      lcd.setCursor(0,1);
      lcd.print("[--systeme-ok--]");
      delay(1500);
    }
    else{
      while(1){
        lcd.setCursor(0,0);
        lcd.print("SYSTEME  FAILURE");
        lcd.setCursor(0,1);
        lcd.print("reboot or check ");
        delay(2000);
        lcd.setCursor(0,1);
        lcd.print(" bad connection ");
        delay(2000);
        if(temp_ok == false){
          lcd.setCursor(0,1);
          lcd.print(" for DHT11 capt.");
          delay(2000);
        }
        if(fans_ok == false){
          lcd.setCursor(0,1);
          lcd.print(" for fans relay.");
          delay(2000);
        }
        if(lum_ok == false){
          lcd.setCursor(0,1);
          lcd.print(" for leds relay.");
          delay(2000);
        }
      }
    }
    lcd.clear();
    delay(1000);
    lcd.setCursor(0,0);
    lcd.print(" 3D             ");
    delay(700);
    lcd.setCursor(0,0);
    lcd.print(" 3D Printer     ");
    delay(700);
    lcd.setCursor(0,0);
    lcd.print(" 3D Printer BOX ");
    delay(700);
    lcd.setCursor(0,1);
    lcd.print("  Version ");
    lcd.print(v_logiciel);
    lcd.print("   ");
    delay(3500);
    lcd.setCursor(0,0);
    lcd.print("    Printer BOX ");
    delay(300);
    lcd.setCursor(0,0);
    lcd.print("            BOX ");
    delay(300);
    lcd.setCursor(0,0);
    lcd.print("                ");
    delay(300);
    lcd.clear();
    delay(500);
    is_ready = true;
  }*/
    //temperature = dht.readTemperature();
    if(t_max < temperature){
      t_max = temperature;
    }
   // humidite = dht.readHumidity();
    ecran();
    if(choix_etat_fans == 0){
 //     digitalWrite(fans, LOW);
    }
    if(choix_etat_fans == 1){
  //    digitalWrite(fans, HIGH);
    }
    if(etatled == 0){
   //   digitalWrite(lumiere, LOW);
    }
    if(etatled == 1){
      
   //   digitalWrite(lumiere, HIGH);
    }
    boutons();

    if(temp_auto == true){
      auto_vent();
    }

   
}    // end void loop()
