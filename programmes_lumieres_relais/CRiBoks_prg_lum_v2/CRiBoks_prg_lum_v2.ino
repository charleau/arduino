int set0 = 0;
int set1 = 1;
int set2 = 8;
int set3 = 9;
int set4 = 10;
int set5 = 11;
int set6 = 12;           // Brancher les relais lumières gauches (set7 à set0)  (= est le port du Arduino)
int set7 = 13;           // Brancher les relais lumières droites (set8 à set13)  (= est le port du Arduino)

int irremote = A5;
int enter = A0;
int up = A1;
int down = A2;
int back = A3;
int next = A4;

int irvalue;
#include <IRremote.h>
IRrecv irrecv(irremote);     
decode_results results;

#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned long temps;
unsigned long previousMillis;
float delais;               // Variable délais entre changement de relais (contrôlé par "void manette")
int noprog;               // Variable numéro de programme (contrôlé par "void manette")


int etatenter = 0;
int etatup = 0;
int etatdown = 0;
int etatback = 0;
int etatnext = 0;



void setup() {
  Serial.begin(9600);
  pinMode(set0, OUTPUT);
  pinMode(set1, OUTPUT);
  pinMode(set2, OUTPUT);
  pinMode(set3, OUTPUT);
  pinMode(set4, OUTPUT);
  pinMode(set5, OUTPUT);
  pinMode(set6, OUTPUT);
  pinMode(set7, OUTPUT);

  pinMode(enter, INPUT);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(back, INPUT);
  pinMode(next, INPUT);

  lcd.begin(16, 2);
  lcd.setCursor(2,0);
  lcd.print("CRiBoks V3.1");
  lcd.setCursor(0,1);
  lcd.print("**SYSTEM ERROR**");

  delay(5000);
  
  irrecv.enableIRIn();
  noprog = -2000;         // assignation d'une valeur de départ à la variable "noprog"
  delais = 1000;           // assignation d'une valeur de départ à la variable "delais"

}



void manette() {                              // Fonction de contrôle pour la manette IR avec récepteur IR

                //flèche droite == -15811
                //flèche gauche == 8925
                //flèche haut == -28561
                //flèche bas == -8161
                //power == -23971
                //stop == -7651
  digitalWrite(enter, HIGH);
  digitalWrite(up, HIGH);
  digitalWrite(down, HIGH);
  digitalWrite(back, HIGH);
  digitalWrite(next, HIGH);
  
  etatenter = digitalRead(enter);
  etatup = digitalRead(up);
  etatdown = digitalRead(down);
  etatback = digitalRead(back);
  etatnext = digitalRead(next);
  
  if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            
            if(irvalue == -15811){
              noprog = noprog+1;
            }                         //  choix programme (flèches)
            if(irvalue == 8925){
            noprog = noprog-1;
            }


            if(delais > 500){
              if(irvalue == -28561){
                delais = delais-500;
              }                         // réglage delais (vitesse)
            }
            if(irvalue == -8161){
              delais = delais+500;
            }


            if(irvalue == -7651){
              noprog = -2000;
            }                         // power on / power off
            if(irvalue == -23971){
              noprog = -1;
            }


            if(irvalue == 26775){
              noprog = 0;
            }
            if(irvalue == 12495){
              noprog = 1;
            }
            if(irvalue == 6375){
              noprog = 2;
            }
            if(irvalue == 31365){
              noprog = 3;
            }
            if(irvalue == 4335){
              noprog = 4;             // numéros programme direct
            }
            if(irvalue == 14535){
              noprog = 5;
            }
            if(irvalue == 23205){
              noprog = 6;
            }
            if(irvalue == 17085){
              noprog = 7;
            }
            if(irvalue == 19125){
              noprog = 8;
            }
            if(irvalue == 21165){
              noprog = 9;
            }
            
          irrecv.resume();
          }
          else{
            if(etatnext == LOW){
              noprog = noprog+1;
              etatnext = 0;
              delay(200);
            }                         //  choix programme (flèches)
            if(etatback == LOW){
               noprog = noprog-1;
               etatback = 0;
               delay(200);
            }


            if(delais > 500){
              if(etatdown == LOW){
                delais = delais-500;
                etatdown = 0;
                delay(200);
              }                         // réglage delais (vitesse)
            }
            if(etatup == LOW){
              delais = delais+500;
              etatup = 0;
              delay(200);
            }
            if(etatenter == LOW){
              if(noprog == -2000){
                noprog = -1;
                delay(200);
              }
              else{
                noprog = -2000;
                delay(200);
              }
            }
            
          }
}


void ecran(){
//  lcd.clear();
//  if(noprog == -2000){
//    lcd.setCursor(0,0);
//    lcd.print("PROGRAMME : OFF");
//  }
//  else if(noprog == -1){
//    lcd.setCursor(0,0);
//    lcd.print("PROGRAMME : ALL");
//  }
//  else{
//    lcd.setCursor(0,0);
//    lcd.print("PROGRAMME : ");
//    lcd.print(noprog);
//  }
//  lcd.setCursor(0,1);
//  lcd.print("DELAIS (s) : ");
//  lcd.print(delais/1000);
}


void timer(){
  temps = millis();
  if( temps - previousMillis >= delais){
    previousMillis = temps;
  }
}


void loop() {

    manette();
    switch(noprog){



                                    // PROG -2000 ( ALL OFF / POWER OFF)
      case -2000 : {
        while(noprog != -1){
          delay(100);
          ecran();
          digitalWrite(set0, LOW);
          digitalWrite(set1, LOW);
          digitalWrite(set2, LOW);
          digitalWrite(set3, LOW);
          digitalWrite(set4, LOW);
          digitalWrite(set5, LOW);
          digitalWrite(set6, LOW);
          digitalWrite(set7, LOW);
          manette();
        }
      }


      
                                        //PROG -1 (Tout Allumé / POWER ON)
      case -1 : {
        while(noprog == -1){
          delay(100);
          ecran();
          digitalWrite(set0, HIGH);
          digitalWrite(set1, HIGH);
          digitalWrite(set2, HIGH);
          digitalWrite(set3, HIGH);
          digitalWrite(set4, HIGH);
          digitalWrite(set5, HIGH);
          digitalWrite(set6, HIGH);
          digitalWrite(set7, HIGH);

          manette();
        }
        digitalWrite(set0, LOW);
        digitalWrite(set1, LOW);
        digitalWrite(set2, LOW);
        digitalWrite(set3, LOW);
        digitalWrite(set4, LOW);
        digitalWrite(set5, LOW);
        digitalWrite(set6, LOW);
        digitalWrite(set7, LOW);

        manette();
      }
    
    
    
                                        //PROG 0 (Balayage Simple gauche-droite)
      case 0 : {
        while(noprog == 0){
          ecran();
          
          manette();
          
          digitalWrite(set0, HIGH);
          timer();
          
          manette();
          
          digitalWrite(set0, LOW);
          digitalWrite(set1, HIGH);
          timer();
          
          manette();
          
          digitalWrite(set1, LOW);
          digitalWrite(set2, HIGH);
          timer();
          
          manette();
          
          digitalWrite(set2, LOW);
          digitalWrite(set3, HIGH);
          timer();
          
          manette();
          
          digitalWrite(set3, LOW);
          digitalWrite(set4, HIGH);
          timer();
          
          manette();
          
          digitalWrite(set4, LOW);
          digitalWrite(set5, HIGH);
          timer();
          
          manette();
          
          digitalWrite(set5, LOW);
          digitalWrite(set6, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set6, LOW);
          digitalWrite(set7, HIGH);
          timer();
          
          manette();
          
          digitalWrite(set7, LOW);
          timer();
          
        } // end while
      }   // end case 0

      

                                             //PROG 1 (Balayage Double côtés-centre-côtés)
      case 1 : {      
        while(noprog == 1){
          ecran();
          
          manette();
          
          digitalWrite(set0, HIGH);
          digitalWrite(set7, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set0, LOW);
          digitalWrite(set7, LOW);
          digitalWrite(set1, HIGH);
          digitalWrite(set6, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set1, LOW);
          digitalWrite(set6, LOW);
          digitalWrite(set2, HIGH);
          digitalWrite(set5, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set2, LOW);
          digitalWrite(set5, LOW);
          digitalWrite(set3, HIGH);
          digitalWrite(set4, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set3, LOW);
          digitalWrite(set4, LOW);
          digitalWrite(set2, HIGH);
          digitalWrite(set5, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set2, LOW);
          digitalWrite(set3, LOW);
          digitalWrite(set1, HIGH);
          digitalWrite(set5, HIGH);
          delay(delais);

          manette();

          digitalWrite(set1, LOW);
          digitalWrite(set2, LOW);
          digitalWrite(set0, HIGH);
          digitalWrite(set5, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set0, LOW);
          digitalWrite(set1, LOW);
          digitalWrite(set2, HIGH);
          digitalWrite(set5, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set2, LOW);
          digitalWrite(set5, LOW);

          manette();
          
         } //while
      }    // case 1


                                            // PROG 2 (All ON balayage gauche-droite 1 led off)
      case 2 : {
        while(noprog == 2){
          ecran();
          
          digitalWrite(set0, HIGH);
          digitalWrite(set1, HIGH);
          digitalWrite(set2, HIGH);
          digitalWrite(set3, HIGH);
          digitalWrite(set4, HIGH);
          digitalWrite(set5, HIGH);
          digitalWrite(set6, HIGH);
          digitalWrite(set7, HIGH);
          delay(delais);
          
          manette();

          digitalWrite(set0, LOW);
          delay(delais);

          manette();
          
          digitalWrite(set0, HIGH);
          digitalWrite(set1, LOW);
          delay(delais);

          manette();
          
          digitalWrite(set1, HIGH);
          digitalWrite(set2, LOW);
          delay(delais);

          manette();
          
          digitalWrite(set2, HIGH);
          digitalWrite(set3, LOW);
          delay(delais);

          manette();
          
          digitalWrite(set3, HIGH);
          digitalWrite(set4, LOW);
          delay(delais);

          manette();
          
          digitalWrite(set4, HIGH);
          digitalWrite(set5, LOW);
          delay(delais);

          manette();
          
          digitalWrite(set5, HIGH);
          digitalWrite(set6, LOW);
          delay(delais);

          manette();
          
          digitalWrite(set6, HIGH);
          digitalWrite(set7, LOW);
          delay(delais);

          manette();
          
          digitalWrite(set7, HIGH);
          digitalWrite(set6, LOW);
          delay(delais);

          manette();

          digitalWrite(set6, HIGH);
          digitalWrite(set5, LOW);
          delay(delais);

          manette();

          digitalWrite(set5, HIGH);
          digitalWrite(set4, LOW);
          delay(delais);

          manette();

          digitalWrite(set4, HIGH);
          digitalWrite(set3, LOW);
          delay(delais);

          manette();

          digitalWrite(set3, HIGH);
          digitalWrite(set2, LOW);
          delay(delais);

          manette();

          digitalWrite(set2, HIGH);
          digitalWrite(set1, LOW);
          delay(delais);

          manette();

          digitalWrite(set1, HIGH);
         
          manette();

        } // end while
        digitalWrite(set0, LOW);
        digitalWrite(set1, LOW);
        digitalWrite(set2, LOW);
        digitalWrite(set3, LOW);
        digitalWrite(set4, LOW);
        digitalWrite(set5, LOW);
        digitalWrite(set6, LOW);
        digitalWrite(set7, LOW);
        manette();
      }   // end case 2


                                        // PROG 3 (Balayage double centre-côtés / côtés-centre full)
      case 3 : {
        while(noprog == 3){
          ecran();
          manette();
          
          digitalWrite(set0, HIGH);
          digitalWrite(set1, HIGH);
          digitalWrite(set2, HIGH);
          digitalWrite(set3, HIGH);
          digitalWrite(set4, HIGH);
          digitalWrite(set5, HIGH);
          digitalWrite(set6, HIGH);
          digitalWrite(set7, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set0, LOW);
          digitalWrite(set7, LOW);
          digitalWrite(set1, HIGH);
          digitalWrite(set6, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set1, LOW);
          digitalWrite(set6, LOW);
          digitalWrite(set2, HIGH);
          digitalWrite(set5, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set2, LOW);
          digitalWrite(set5, LOW);
          digitalWrite(set3, HIGH);
          digitalWrite(set4, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set3, LOW);
          digitalWrite(set4, LOW);
          digitalWrite(set2, HIGH);
          digitalWrite(set5, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set4, LOW);
          digitalWrite(set3, LOW);
          digitalWrite(set5, HIGH);
          digitalWrite(set4, HIGH);
          delay(delais);

          manette();
          
        } // end while
      }   // end case 3


                                            // PROG 4  (Balayage doouble allumé centre-côtés)
      case 4 : {
        while(noprog == 4){
          ecran();
          manette();
          
          digitalWrite(set0, HIGH);
          digitalWrite(set1, HIGH);
          digitalWrite(set2, HIGH);
          digitalWrite(set3, HIGH);
          digitalWrite(set4, HIGH);
          digitalWrite(set5, HIGH);
          digitalWrite(set6, HIGH);
          digitalWrite(set7, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set0, LOW);
          digitalWrite(set7, LOW);
          delay(delais);
          
          manette();
          
          digitalWrite(set1, LOW);
          digitalWrite(set6, LOW);
          delay(delais);
          
          manette();
          
          digitalWrite(set2, LOW);
          digitalWrite(set5, LOW);
          delay(delais);
          
          manette();
          
          digitalWrite(set3, LOW);
          digitalWrite(set4, LOW);
          delay(delais);

          manette();

          digitalWrite(set4, HIGH);
          digitalWrite(set3, HIGH);
          delay(delais);
          
          manette();
          digitalWrite(set5, HIGH);
          digitalWrite(set2, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set6, HIGH);
          digitalWrite(set1, HIGH);
          delay(delais);
          
          manette();

          digitalWrite(set7, HIGH);
          digitalWrite(set0, HIGH);
          delay(delais);

          manette();
          
        } // end while
        digitalWrite(set0, LOW);
        digitalWrite(set1, LOW);
        digitalWrite(set2, LOW);
        digitalWrite(set3, LOW);
        digitalWrite(set4, LOW);
        digitalWrite(set5, LOW);
        digitalWrite(set6, LOW);
        digitalWrite(set7, LOW);

        manette();
      }   // end case 4


                                      // PROG 5 (balayage simple gauche-droite-gauche)
      case 5 : {
        while(noprog == 5){
          ecran();
          manette();
          
          digitalWrite(set0, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set0, LOW);
          digitalWrite(set1, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set1, LOW);
          digitalWrite(set2, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set2, LOW);
          digitalWrite(set3, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set3, LOW);
          digitalWrite(set4, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set4, LOW);
          digitalWrite(set5, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set5, LOW);
          digitalWrite(set6, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set6, LOW);
          digitalWrite(set7, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set7, LOW);
          digitalWrite(set6, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set6, LOW);
          digitalWrite(set5, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set5, LOW);
          digitalWrite(set4, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set4, LOW);
          digitalWrite(set3, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set3, LOW);
          digitalWrite(set2, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set2, LOW);
          digitalWrite(set1, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set1, LOW);
          
        } // end while
      }   // end case 5
      
   } // end switch(noprog)
}    // end void loop()
