int set0 = 2;
int set1 = 3;
int set2 = 4;
int set3 = 5;
int set4 = 6;
int set5 = 7;
int set6 = 8;           // Brancher les relais lumières gauches (set7 à set0)  (= est le port du Arduino)
int set7 = 9;           // Brancher les relais lumières droites (set8 à set13)  (= est le port du Arduino)
int set8 = 10;          // Brancher le IRRECEIVER sur port A2 et 5 volt.
int set9 = 11;
int set10 = 12;
int set11 = 13;
int set12 = A0;
int set13 = A1;
int irremote = A2;

int irvalue;
#include <IRremote.h>
IRrecv irrecv(irremote);     
decode_results results;  

int delais;               // Variable délais entre changement de relais (contrôlé par "void manette")
int noprog;               // Variable numéro de programme (contrôlé par "void manette")

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
  pinMode(set8, OUTPUT);
  pinMode(set9, OUTPUT);
  pinMode(set10, OUTPUT);
  pinMode(set11, OUTPUT);
  pinMode(set12, OUTPUT);
  pinMode(set13, OUTPUT);

  irrecv.enableIRIn();
  noprog = -2000;         // assignation d'une valeur de départ à la variable "noprog"
  delais = 165;           // assignation d'une valeur de départ à la variable "delais"

}



void manette() {                              // Fonction de contrôle pour la manette IR avec récepteur IR

                //flèche droite == -15811
                //flèche gauche == 8925
                //flèche haut == -28561
                //flèche bas == -8161
                //power == -23971
                //stop == -7651
  
  if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            
            if(irvalue == -15811){
              noprog = noprog+1;
            }                         //  choix programme (flèches)
            if(irvalue == 8925){
            noprog = noprog-1;
            }


            if(delais > 15){
              if(irvalue == -28561){
                delais = delais-50;
              }                         // réglage delais (vitesse)
            }
            if(irvalue == -8161){
              delais = delais+50;
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
}




void loop() {

    manette();
    switch(noprog){



                                    // PROG -2000 ( ALL OFF / POWER OFF)
      case -2000 : {
        while(noprog != -1){
          digitalWrite(set0, LOW);
          digitalWrite(set1, LOW);
          digitalWrite(set2, LOW);
          digitalWrite(set3, LOW);
          digitalWrite(set4, LOW);
          digitalWrite(set5, LOW);
          digitalWrite(set6, LOW);
          digitalWrite(set7, LOW);
          digitalWrite(set8, LOW);
          digitalWrite(set9, LOW);
          digitalWrite(set10, LOW);
          digitalWrite(set11, LOW);
          digitalWrite(set12, LOW);
          digitalWrite(set13, LOW);
          manette();
        }
      }


      
                                        //PROG -1 (Tout Allumé / POWER ON)
      case -1 : {
        while(noprog == -1){
          digitalWrite(set0, HIGH);
          digitalWrite(set1, HIGH);
          digitalWrite(set2, HIGH);
          digitalWrite(set3, HIGH);
          digitalWrite(set4, HIGH);
          digitalWrite(set5, HIGH);
          digitalWrite(set6, HIGH);
          digitalWrite(set7, HIGH);
          digitalWrite(set8, HIGH);
          digitalWrite(set9, HIGH);
          digitalWrite(set10, HIGH);
          digitalWrite(set11, HIGH);
          digitalWrite(set12, HIGH);
          digitalWrite(set13, HIGH);
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
        digitalWrite(set8, LOW);
        digitalWrite(set9, LOW);
        digitalWrite(set10, LOW);
        digitalWrite(set11, LOW);
        digitalWrite(set12, LOW);
        digitalWrite(set13, LOW);
        manette();
      }
    
    
    
                                        //PROG 0 (Balayage Simple gauche-droite)
      case 0 : {
        while(noprog == 0){
          
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
          digitalWrite(set8, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set8, LOW);
          digitalWrite(set9, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set9, LOW);
          digitalWrite(set10, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set10, LOW);
          digitalWrite(set11, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set11, LOW);
          digitalWrite(set12, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set12, LOW);
          digitalWrite(set13, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set13, LOW);
          
        } // end while
      }   // end case 0

      

                                             //PROG 1 (Balayage Double côtés-centre-côtés)
      case 1 : {      
        while(noprog == 1){
          
          manette();
          
          digitalWrite(set0, HIGH);
          digitalWrite(set13, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set0, LOW);
          digitalWrite(set13, LOW);
          digitalWrite(set1, HIGH);
          digitalWrite(set12, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set1, LOW);
          digitalWrite(set12, LOW);
          digitalWrite(set2, HIGH);
          digitalWrite(set11, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set2, LOW);
          digitalWrite(set11, LOW);
          digitalWrite(set3, HIGH);
          digitalWrite(set10, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set3, LOW);
          digitalWrite(set10, LOW);
          digitalWrite(set4, HIGH);
          digitalWrite(set9, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set4, LOW);
          digitalWrite(set9, LOW);
          digitalWrite(set5, HIGH);
          digitalWrite(set8, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set5, LOW);
          digitalWrite(set8, LOW);
          digitalWrite(set6, HIGH);
          digitalWrite(set7, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set6, LOW);
          digitalWrite(set7, LOW);
          digitalWrite(set5, HIGH);
          digitalWrite(set8, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set5, LOW);
          digitalWrite(set8, LOW);
          digitalWrite(set4, HIGH);
          digitalWrite(set9, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set4, LOW);
          digitalWrite(set9, LOW);
          digitalWrite(set3, HIGH);
          digitalWrite(set10, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set3, LOW);
          digitalWrite(set10, LOW);
          digitalWrite(set2, HIGH);
          digitalWrite(set11, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set2, LOW);
          digitalWrite(set11, LOW);
          digitalWrite(set1, HIGH);
          digitalWrite(set12, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set1, LOW);
          digitalWrite(set12, LOW);

          manette();
          
         } //while
      }    // case 1


                                            // PROG 2 (All ON balayage gauche-droite 1 led off)
      case 2 : {
        while(noprog == 2){
          digitalWrite(set0, HIGH);
          digitalWrite(set1, HIGH);
          digitalWrite(set2, HIGH);
          digitalWrite(set3, HIGH);
          digitalWrite(set4, HIGH);
          digitalWrite(set5, HIGH);
          digitalWrite(set6, HIGH);
          digitalWrite(set7, HIGH);
          digitalWrite(set8, HIGH);
          digitalWrite(set9, HIGH);
          digitalWrite(set10, HIGH);
          digitalWrite(set11, HIGH);
          digitalWrite(set12, HIGH);
          digitalWrite(set13, HIGH);
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
          digitalWrite(set8, LOW);
          delay(delais);

          manette();

          digitalWrite(set8, HIGH);
          digitalWrite(set9, LOW);
          delay(delais);

          manette();
          
          digitalWrite(set9, HIGH);
          digitalWrite(set10, LOW);
          delay(delais);

          manette();
          
          digitalWrite(set10, HIGH);
          digitalWrite(set11, LOW);
          delay(delais);

          manette();
          
          digitalWrite(set11, HIGH);
          digitalWrite(set12, LOW);
          delay(delais);

          manette();
          
          digitalWrite(set12, HIGH);
          digitalWrite(set13, LOW);
          delay(delais);
          
          manette();

          digitalWrite(set13, HIGH);
          digitalWrite(set12, LOW);
          delay(delais);

          manette();

          digitalWrite(set12, HIGH);
          digitalWrite(set11, LOW);
          delay(delais);

          manette();

          digitalWrite(set11, HIGH);
          digitalWrite(set10, LOW);
          delay(delais);

          manette();

          digitalWrite(set10, HIGH);
          digitalWrite(set9, LOW);
          delay(delais);

          manette();

          digitalWrite(set9, HIGH);
          digitalWrite(set8, LOW);
          delay(delais);

          manette();

          digitalWrite(set8, HIGH);
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
        digitalWrite(set8, LOW);
        digitalWrite(set9, LOW);
        digitalWrite(set10, LOW);
        digitalWrite(set11, LOW);
        digitalWrite(set12, LOW);
        digitalWrite(set13, LOW);
        manette();
      }   // end case 2


                                        // PROG 3 (Balayage double centre-côtés / côtés-centre full)
      case 3 : {
        while(noprog == 3){
          
          manette();
          
          digitalWrite(set0, HIGH);
          digitalWrite(set1, HIGH);
          digitalWrite(set2, HIGH);
          digitalWrite(set3, HIGH);
          digitalWrite(set4, HIGH);
          digitalWrite(set5, HIGH);
          digitalWrite(set6, HIGH);
          digitalWrite(set7, HIGH);
          digitalWrite(set8, HIGH);
          digitalWrite(set9, HIGH);
          digitalWrite(set10, HIGH);
          digitalWrite(set11, HIGH);
          digitalWrite(set12, HIGH);
          digitalWrite(set13, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set0, LOW);
          digitalWrite(set13, LOW);
          digitalWrite(set1, HIGH);
          digitalWrite(set12, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set1, LOW);
          digitalWrite(set12, LOW);
          digitalWrite(set2, HIGH);
          digitalWrite(set11, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set2, LOW);
          digitalWrite(set11, LOW);
          digitalWrite(set3, HIGH);
          digitalWrite(set10, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set3, LOW);
          digitalWrite(set10, LOW);
          digitalWrite(set4, HIGH);
          digitalWrite(set9, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set4, LOW);
          digitalWrite(set9, LOW);
          digitalWrite(set5, HIGH);
          digitalWrite(set8, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set5, LOW);
          digitalWrite(set8, LOW);
          digitalWrite(set6, HIGH);
          digitalWrite(set7, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set6, LOW);
          digitalWrite(set7, LOW);
          digitalWrite(set5, HIGH);
          digitalWrite(set8, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set5, LOW);
          digitalWrite(set8, LOW);
          digitalWrite(set4, HIGH);
          digitalWrite(set9, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set4, LOW);
          digitalWrite(set9, LOW);
          digitalWrite(set3, HIGH);
          digitalWrite(set10, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set3, LOW);
          digitalWrite(set10, LOW);
          digitalWrite(set2, HIGH);
          digitalWrite(set11, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set2, LOW);
          digitalWrite(set11, LOW);
          digitalWrite(set1, HIGH);
          digitalWrite(set12, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set1, LOW);
          digitalWrite(set12, LOW);

          manette();
          
        } // end while
      }   // end case 3


                                            // PROG 4  (Balayage doouble allumé centre-côtés)
      case 4 : {
        while(noprog == 4){
          
          manette();
          
          digitalWrite(set0, HIGH);
          digitalWrite(set1, HIGH);
          digitalWrite(set2, HIGH);
          digitalWrite(set3, HIGH);
          digitalWrite(set4, HIGH);
          digitalWrite(set5, HIGH);
          digitalWrite(set6, HIGH);
          digitalWrite(set7, HIGH);
          digitalWrite(set8, HIGH);
          digitalWrite(set9, HIGH);
          digitalWrite(set10, HIGH);
          digitalWrite(set11, HIGH);
          digitalWrite(set12, HIGH);
          digitalWrite(set13, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set0, LOW);
          digitalWrite(set13, LOW);
          delay(delais);
          
          manette();
          
          digitalWrite(set1, LOW);
          digitalWrite(set12, LOW);
          delay(delais);
          
          manette();
          
          digitalWrite(set2, LOW);
          digitalWrite(set11, LOW);
          delay(delais);
          
          manette();
          
          digitalWrite(set3, LOW);
          digitalWrite(set10, LOW);
          delay(delais);

          manette();
          
          digitalWrite(set4, LOW);
          digitalWrite(set9, LOW);
          delay(delais);

          manette();
          
          digitalWrite(set5, LOW);
          digitalWrite(set8, LOW);
          delay(delais);
          
          manette();

          digitalWrite(set6, LOW);
          digitalWrite(set7, LOW);
          delay(delais);

          manette();

          digitalWrite(set6, HIGH);
          digitalWrite(set7, HIGH);
          delay(delais);
          
          manette();
          digitalWrite(set5, HIGH);
          digitalWrite(set8, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set4, HIGH);
          digitalWrite(set9, HIGH);
          delay(delais);
          
          manette();

          digitalWrite(set3, HIGH);
          digitalWrite(set10, HIGH);
          delay(delais);
          
          manette();

          digitalWrite(set2, HIGH);
          digitalWrite(set11, HIGH);
          delay(delais);
          
          manette();

          digitalWrite(set1, HIGH);
          digitalWrite(set12, HIGH);
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
        digitalWrite(set8, LOW);
        digitalWrite(set9, LOW);
        digitalWrite(set10, LOW);
        digitalWrite(set11, LOW);
        digitalWrite(set12, LOW);
        digitalWrite(set13, LOW);
        manette();
      }   // end case 4


                                      // PROG 5 (balayage simple gauche-droite-gauche)
      case 5 : {
        while(noprog == 5){
          
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
          digitalWrite(set8, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set8, LOW);
          digitalWrite(set9, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set9, LOW);
          digitalWrite(set10, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set10, LOW);
          digitalWrite(set11, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set11, LOW);
          digitalWrite(set12, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set12, LOW);
          digitalWrite(set13, HIGH);
          delay(delais);
          
          manette();
          
          digitalWrite(set13, LOW);
          digitalWrite(set12, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set12, LOW);
          digitalWrite(set11, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set11, LOW);
          digitalWrite(set10, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set10, LOW);
          digitalWrite(set9, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set9, LOW);
          digitalWrite(set8, HIGH);
          delay(delais);

          manette();
          
          digitalWrite(set8, LOW);
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
