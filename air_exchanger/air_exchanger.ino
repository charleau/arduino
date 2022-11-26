 // PRG V4.73 correction :
 // Ajustement de l'ouverture en mode auto
 // Ajout d'un mode test système
 // Ajout de fonction [allumer tout]
 // Ajout de fonction [éteindre tout]


//-----------------------DÉCLARATIONS DES PORTS UTILISÉS ET DES #INCLUDE-----------------------\\

int enter = A0;
int up = A1;
int down = A2;      // BOUTONs (= EST LE PORT ARDUINO PERMANENT)
int back = A3;
int next = A4;

int temp_capt = 8;  // DHT11  --> signal | 5v | gnd
int fan_out = 9;    // relais
int fan_in = 10;    // relais
int valve = 11;     // servo-motor SG90 --> brun=grd | rouge=5vdc | jaune=signal
int fans_volt = 12; // relais
int irremote = 13;    // Récepteur Infra-Rouge


#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 7, d7 = 6;         // LCD SCREEN
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//#include "Accents.h"


#include <DHT.h>
#define DHTPIN 8                                                  // capteur de température
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


#include <Servo.h>
Servo servo_valve;


int irvalue;
#include <IRremote.h>
IRrecv irrecv(irremote);     
decode_results results;;

//----------------------------DÉCLARATION DES VARIABLES----------------------------\\

int etatenter = 1;
int etatup = 1;
int etatdown = 1;             // Etat des boutons
int etatback = 1;
int etatnext = 1;
bool is_ready = false;
bool is_a_test = false;
int ouverture = 100;
int etat_fan_in = 0;
int etat_fan_out = 0;
int vitesse_fans = 0;
bool auto_ventil = false;
int temp_voulue = 25;
int angle = 180;
int choix_menu = 1;
int temperature = 0;
int humidite = 0;

float v_logiciel = 4.73;


//-----------------------DÉCLARATION DE L'UTILISATION DES PINS-----------------------\\

void setup() {
  Serial.begin(9600);
  dht.begin();
  irrecv.enableIRIn();
  decode_results results;

  pinMode(enter, INPUT);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(back, INPUT);                   // INPUT MODE
  pinMode(next, INPUT);
  pinMode(temp_capt, INPUT);
  
  
  pinMode(fan_in, OUTPUT);
  pinMode(fan_out, OUTPUT);               // OUTPUT MODE
  pinMode(valve, OUTPUT);
  pinMode(fans_volt, OUTPUT);

  servo_valve.attach(11);


//-----------------------------AFFICHAGE DE DÉPART DU LCD----------------------------\\

  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("   CRiBoks V2   ");
  lcd.setCursor(0,1);
  lcd.print(" Charles Ricard ");
  delay(5000);
  
}

void power_off(){
  ouverture = 100;
  etat_fan_in = 0;
  etat_fan_out = 0;
  vitesse_fans = 0;
  auto_ventil = false;
  digitalWrite(fans_volt, LOW);
  digitalWrite(fan_in, LOW);
  digitalWrite(fan_out, LOW);
  servo_valve.write(180);
}

void power_on(){
  ouverture = 0;
  etat_fan_in = 1;
  etat_fan_out = 1;
  vitesse_fans = 1;
  auto_ventil = false;
  digitalWrite(fan_in, HIGH);
  delay(100);
  digitalWrite(fans_volt, HIGH);
  digitalWrite(fan_out, HIGH);
  servo_valve.write(0);
}


//------------------------------FONCTION BOUTONS BOITIER------------------------------\\

void boutons(void) {

                //flèche droite == -15811
                //flèche gauche == 8925
                //flèche haut == -28561
                //flèche bas == -8161
                //power == -23971
                //stop == -7651
                //EQ == -26521

  if (irrecv.decode(&results)){
    irvalue = results.value;
    Serial.println(irvalue);

    if(irvalue == -23971){
      power_on();
    }
    if(irvalue == -7651){
      power_off();
    }

    if(irvalue == -15811){
      if(auto_ventil == true){
        if(choix_menu < 7){
          choix_menu = choix_menu + 1;
        }
        else{
          choix_menu = 0;
        }
      }                                         // NEXT
      else{
        if(choix_menu < 6){
          choix_menu = choix_menu + 1;
        }
        else{
          choix_menu = 0;
        }
      }
    }                         //  choix programme (flèches)
    if(irvalue == 8925){
      if(choix_menu > 0){
        choix_menu = choix_menu - 1;
      }                                         // BACK
      else{
        if(auto_ventil == true){
        choix_menu = 7;
        }
        else{
          choix_menu = 6;
        }
      }
    }

    if(irvalue == -28561){
      if(choix_menu == 2){
        if(ouverture <= 95){
          ouverture += 5;
        }
        else{
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(" TRAPPE  FERMEE ");
          lcd.setCursor(0,1);
          lcd.print("   AU MAXIMUM   ");
          delay(3000);
          lcd.clear();
        }
      }
      if(choix_menu == 3){
        etat_fan_in = 1;
      }
      if(choix_menu == 4){
        etat_fan_out = 1;
      }
      if(choix_menu == 5){
        vitesse_fans = 1;
      }
      if(choix_menu == 6){
        auto_ventil = true;
      }
      if(choix_menu == 7){
        if(temp_voulue < 30){
              temp_voulue++;
            }
            else{
              lcd.setCursor(0,0);
              lcd.print(" Temp. maximale ");
              lcd.setCursor(0,1);
              lcd.print("    ATTEINTE    ");
              delay(3000);
            }
      }
    }

    
    if(irvalue == -8161){
      if(choix_menu == 2){
        if(ouverture >= 5){
            ouverture -= 5;
        }
        else{
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(" TRAPPE OUVERTE ");
          lcd.setCursor(0,1);
          lcd.print("   AU MAXIMUM   ");
          delay(3000);
          lcd.clear();
        }
      }
      if(choix_menu == 3){
        etat_fan_in = 0;
      }
      if(choix_menu == 4){
        etat_fan_out = 0;
      }
      if(choix_menu == 5){
        vitesse_fans = 0;
      }
      if(choix_menu == 6){
        auto_ventil = false;
      }
      if(choix_menu == 7){
        if(temp_voulue > 15){
              temp_voulue--;
            }
            else{
              lcd.setCursor(0,0);
              lcd.print(" Temp. minimale ");
              lcd.setCursor(0,1);
              lcd.print("    ATTEINTE    ");
              delay(3000);
            }
      }
    }

    
    irrecv.resume();
  }

                
  digitalWrite(enter, HIGH);
  digitalWrite(up, HIGH);
  digitalWrite(down, HIGH);               // Envoies de 5vdc sur les boutons
  digitalWrite(back, HIGH);
  digitalWrite(next, HIGH);
                                    
  etatenter = digitalRead(enter);
  etatup = digitalRead(up);
  etatdown = digitalRead(down);           // Lecture de l'état des boutons
  etatback = digitalRead(back);
  etatnext = digitalRead(next);


  
    if(etatdown == LOW){
      etatdown = 0;                             // DOWN
      delay(200);
    }

    
    if(etatup == LOW){
      etatup = 0;                             // UP
      delay(200);
    }

    
    if(etatback == LOW){
      if(choix_menu > 0){
        choix_menu = choix_menu - 1;
        etatback = 0;
        delay(200);
      }                                         // BACK
      else{
        if(auto_ventil == true){
        choix_menu = 7;
        etatback = 0;
        delay(200);
        }
        else{
          choix_menu = 6;
          etatback = 0;
          delay(200);
        }
      }
    }

    
    if(etatnext == LOW){
      if(auto_ventil == true){
        if(choix_menu < 7){
          choix_menu = choix_menu + 1;
          etatnext = 0;
          delay(200);
        }
        else{
          choix_menu = 0;
          etatnext = 0;
          delay(200);
        }
      }                                         // NEXT
      else{
        if(choix_menu < 6){
          choix_menu = choix_menu + 1;
          etatnext = 0;
          delay(200);
        }
        else{
          choix_menu = 0;
          etatnext = 0;
          delay(200);
        }
      }
    }

    
    if(etatenter == LOW){
      etatenter = 0;                            // ENTER
      delay(200);
    }

    

    if((etatenter == LOW && etatdown == LOW && etatnext == LOW) || irvalue == -26521){ 
      is_a_test = true;
    }
}


//-----------------------------FONCTION MENU ÉCRAN LCD 16X2---------------------------\\

void menu(){
  switch(choix_menu){
    case 0:
      lcd.setCursor(0,0);
      lcd.print(" Air  Exchanger ");
      lcd.setCursor(0,1);
      lcd.print("  Version ");
      lcd.print(v_logiciel);
      lcd.print("   ");
    break;
    
    case 1:                                                         // AFFICHAGE 1 --> Température et humidité actuelle
        lcd.setCursor(0,0);
        lcd.print("Temperature: ");
        lcd.print(temperature);
        lcd.print("C");
        lcd.setCursor(0,1);
        lcd.print(" ");
        lcd.print(humidite);
        lcd.print("%");
        lcd.print(" d'humidite ");
    break;

    case 2:                                                         // AFFICHAGE 2 --> Ouverture manuelle de la trappe
      if(etatup == 0){
        if(ouverture <= 95){
          ouverture += 5;
          etatup = 1;
        }
        else{
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(" TRAPPE  FERMEE ");
          lcd.setCursor(0,1);
          lcd.print("   AU MAXIMUM   ");
          delay(3000);
          lcd.clear();
        }
      }
      if(etatdown == 0){
        if(ouverture >= 5){
            ouverture -= 5;
            etatdown = 1;
        }
        else{
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(" TRAPPE OUVERTE ");
          lcd.setCursor(0,1);
          lcd.print("   AU MAXIMUM   ");
          delay(3000);
          lcd.clear();
        }
      }
    
      if(ouverture < 100 && ouverture > 9){
        lcd.setCursor(0,0);
        lcd.print("Trappe  aeration");
        lcd.setCursor(0,1);
        lcd.print(" Fermee  a ");
        lcd.print(ouverture);
        lcd.print(" % ");
      }
      else if(ouverture < 10){
        lcd.setCursor(0,0);
        lcd.print("Trappe  aeration");
        lcd.setCursor(0,1);
        lcd.print(" Fermee  a ");
        lcd.print(ouverture);
        lcd.print(" %  ");
      }
      else if(ouverture == 100){
        lcd.setCursor(0,0);
        lcd.print("Trappe  aeration");
        lcd.setCursor(0,1);
        lcd.print(" Fermee  a ");
        lcd.print(ouverture);
        lcd.print(" %");
      }

      angle = ((ouverture * 180) / 100);
      servo_valve.write(angle);
    break;

    case 3:                                                         // AFFICHAGE 3 --> Fan d'entrée
      if(etat_fan_in == 1){
        lcd.setCursor(0,0);
        lcd.print("Fan  entree  air");
        lcd.setCursor(0,1);
        lcd.print("   > ACTIVE <   ");

        digitalWrite(fan_in, HIGH);
        etat_fan_in = 1;
        
        if(etatdown == 0){
          etat_fan_in = 0;
          etatdown = 1;
        }
      }
      else if(etat_fan_in == 0){
        lcd.setCursor(0,0);
        lcd.print("Fan  entree  air");
        lcd.setCursor(0,1);
        lcd.print("  > INACTIVE <  ");
        digitalWrite(fan_in, LOW);
        etat_fan_in = 0;

        if(etatup == 0){
          etat_fan_in = 1;
          etatup = 1;
        }
      }
    break;

    case 4:                                                         // AFFICHAGE 4 --> Fan de sortie
      if(etat_fan_out == 1){
        lcd.setCursor(0,0);
        lcd.print("Fan  sortie  air");
        lcd.setCursor(0,1);
        lcd.print("   > ACTIVE <   ");
        digitalWrite(fan_out, HIGH);
        etat_fan_out = 1;

        if(etatdown == 0){
          etat_fan_out = 0;
          etatdown = 1;
        }
      }
      else if(etat_fan_out == 0){
        lcd.setCursor(0,0);
        lcd.print("Fan  sortie  air");
        lcd.setCursor(0,1);
        lcd.print("  > INACTIVE <  ");
        digitalWrite(fan_out, LOW);
        etat_fan_out = 0;

        if(etatup == 0){
          etat_fan_out = 1;
          etatup = 1;
        }
      }
    break;

    case 5:
      if(vitesse_fans == 0){
        lcd.setCursor(0,0);
        lcd.print("Vitesse des fans");
        lcd.setCursor(0,1);
        lcd.print("    > DEMI <    ");
        digitalWrite(fans_volt, LOW);

        if(etatup == 0){
          vitesse_fans = 1;
          etatup = 1;
        }
      }
      else if(vitesse_fans == 1){
        lcd.setCursor(0,0);
        lcd.print("Vitesse des fans");
        lcd.setCursor(0,1);
        lcd.print("    > FULL <    ");
        digitalWrite(fans_volt, HIGH);

        if(etatdown == 0){
          vitesse_fans = 0;
          etatdown = 1;
        }
      }
    break;

    case 6:   
      if(auto_ventil == false){
        lcd.setCursor(0,0);
        lcd.print("Type d'aeration ");
        lcd.setCursor(0,1);
        lcd.print("  > MANUELLE <  ");

        if(etatup == 0){
          auto_ventil = true;
          etatup = 1;
        }
      }
      else if(auto_ventil == true){
        lcd.setCursor(0,0);
        lcd.print("Type d'aeration ");
        lcd.setCursor(0,1);
        lcd.print("    > AUTO <    ");
        if(etatdown == 0){
          auto_ventil = false;
          etatdown = 1;
        }
      }
    break;
    
    case 7:

        if(etatup == 0){
          if(temp_voulue < 30){
            temp_voulue++;
            etatup = 1;
          }
          else{
            lcd.setCursor(0,0);
            lcd.print(" Temp. maximale ");
            lcd.setCursor(0,1);
            lcd.print("    ATTEINTE    ");
            delay(3000);
          }
        }
        if(etatdown == 0){
          if(temp_voulue > 15){
            temp_voulue--;
            etatdown = 1;
          }
          else{
            lcd.setCursor(0,0);
            lcd.print(" Temp. minimale ");
            lcd.setCursor(0,1);
            lcd.print("    ATTEINTE    ");
            delay(3000);
          }
        }
    
      lcd.setCursor(0,0);
      lcd.print(" Temp. voulue : ");
      lcd.setCursor(0,1);
      lcd.print("    > ");
      lcd.print(temp_voulue);
      lcd.print(" C <    ");
    break;
  } // end switch
} // end void

void auto_temp(){

  if(temperature <= temp_voulue){
    digitalWrite(fans_volt, LOW);
    vitesse_fans = 0;
    digitalWrite(fan_in, LOW);
    etat_fan_in = 0;
    digitalWrite(fan_out, LOW);
    etat_fan_out = 0;
    ouverture = 100;
  }
  
  if(temperature == (temp_voulue + 1)){
    digitalWrite(fan_in, HIGH);
    etat_fan_in = 1;
    delay(100);
    digitalWrite(fans_volt, LOW);
    vitesse_fans = 0;
    digitalWrite(fan_out, HIGH);
    etat_fan_out = 1;
    ouverture = 50;
  }

  if(temperature >= (temp_voulue +2)){
    digitalWrite(fan_in, HIGH);
    etat_fan_in = 1;
    delay(100);
    digitalWrite(fans_volt, HIGH);
    vitesse_fans = 1;
    digitalWrite(fan_out, HIGH);
    etat_fan_out = 1;
    ouverture = 0;
  }
  angle = ((ouverture * 180) / 100);
  servo_valve.write(angle);
}



void loop() {
  if(is_ready == false || is_a_test == true){
    servo_valve.write(90);

  if(is_a_test == false){
    lcd.setCursor(0,0);
    lcd.print(" INITIALISATION ");
  }
  else{
    lcd.setCursor(0,0);
    lcd.print("  SYSTEM  TEST  ");
  }
    lcd.setCursor(0,1);
    lcd.print("[#             ]");
    delay(150);
   servo_valve.write(0);
    lcd.setCursor(0,1);
    lcd.print("[##            ]");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[###           ]");
    delay(150);
   digitalWrite(fan_in, HIGH);
   digitalWrite(fan_out, HIGH);
    lcd.setCursor(0,1);
    lcd.print("[####          ]");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[#####         ]");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[######        ]");
    delay(150);
  if(is_a_test == true){delay(2350);}
    lcd.setCursor(0,1);
    lcd.print("[#######       ]");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[########      ]");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[#########     ]");
   digitalWrite(fans_volt, HIGH);
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[##########    ]");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[###########   ]");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[############  ]");
    delay(150);
    if(is_a_test == true){delay(2350);}
    lcd.setCursor(0,1);
    lcd.print("[############# ]");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("[##############]");
    delay(400);
    lcd.setCursor(0,1);
    lcd.print("[              ]");
   servo_valve.write(angle);
    delay(450);
    power_off();
    delay(450);
    lcd.setCursor(0,1);
    lcd.print("[------OK------]");
    delay(1500);
    lcd.clear();
    delay(1000);
  if(is_a_test == false){
    lcd.setCursor(0,0);
    lcd.print(" Air            ");
    delay(700);
    lcd.setCursor(0,0);
    lcd.print(" Air  Exchanger ");
    delay(700);
    lcd.setCursor(0,1);
    lcd.print("  Version ");
    lcd.print(v_logiciel);
    lcd.print("   ");
    delay(3500);
    lcd.setCursor(0,0);
    lcd.print("      Exchanger ");
    delay(300);
    lcd.setCursor(0,0);
    lcd.print("                ");
    delay(300);
    lcd.clear();
    delay(500);
  }
    is_ready = true;
    is_a_test = false;
  }
  
  temperature = dht.readTemperature();
  humidite = dht.readHumidity();
  boutons();
  menu();

  if(auto_ventil == true){
    auto_temp();
  }
}
