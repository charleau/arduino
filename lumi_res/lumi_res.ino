int set0 = 2;
int set1 = 3;
int set2 = 4;
int set3 = 5;
int set4 = 6;
int set5 = 7;
int set6 = 8;
int set7 = 9;
int set8 = 10;
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

int delais;
int noprog;

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
  noprog = -1;
  delais = 150;

}

void loop() {

  if (irrecv.decode(&results)){
    irvalue = results.value;
    Serial.println(irvalue);      

    if(irvalue == -15811){
      noprog = noprog+1;
    }
    if(irvalue == 8925){
      noprog = noprog-1;
    }
  irrecv.resume();
  }
  if (irrecv.decode(&results)){
    irvalue = results.value;
    Serial.println(irvalue);      

    if(irvalue == -28561){
      delais = delais+50;
    }
    if(irvalue == -8161){
      delais = delais-50;
    }
  irrecv.resume();
  }



  
    switch(noprog){


      
  //PROG -1 (Tout Allumé)
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
        if (irrecv.decode(&results)){
          irvalue = results.value;
          Serial.println(irvalue);      
      
          if(irvalue == -15811){
            noprog = noprog+1;
          }
          if(irvalue == 8925){
            noprog = noprog-1;
          }
          irrecv.resume();
          }
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);      
        
            if(irvalue == -28561){
              delais = delais+50;
            }
            if(irvalue == -8161){
              delais = delais-50;
            }
            irrecv.resume();
            }
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
      if (irrecv.decode(&results)){
        irvalue = results.value;
        Serial.println(irvalue);      
    
        if(irvalue == -15811){
          noprog = noprog+1;
        }
        if(irvalue == 8925){
          noprog = noprog-1;
        }
        irrecv.resume();
        }
    }
    if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);      
        
            if(irvalue == -28561){
              delais = delais+50;
            }
            if(irvalue == -8161){
              delais = delais-50;
            }
            irrecv.resume();
            }
    
    
    
    
    
    
    //PROG 1 (Balayage Simple gauche-droite)
      case 0 : {
        while(noprog == 0){

          
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
          }
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);      
        
            if(irvalue == -28561){
              delais = delais+150;
            }
            if(irvalue == -8161){
              delais = delais-150;
            }
          irrecv.resume();
          }

          
          digitalWrite(set0, HIGH);
          delay(delais);

          
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);      
        
            if(irvalue == -28561){
              delais = delais+50;
            }
            if(irvalue == -8161){
              delais = delais-50;
            }
          irrecv.resume();
          }
          
          
          digitalWrite(set0, LOW);
          digitalWrite(set1, HIGH);
          delay(delais);

          
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);      
        
            if(irvalue == -28561){
              delais = delais+50;
            }
            if(irvalue == -8161){
              delais = delais-50;
            }
          irrecv.resume();
          }

          
          digitalWrite(set1, LOW);
          digitalWrite(set2, HIGH);
          delay(delais);

          
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);      
        
            if(irvalue == -28561){
              delais = delais+50;
            }
            if(irvalue == -8161){
              delais = delais-50;
            }
          irrecv.resume();
          }

          
          digitalWrite(set2, LOW);
          digitalWrite(set3, HIGH);
          delay(delais);

          
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);      
        
            if(irvalue == -28561){
              delais = delais+50;
            }
            if(irvalue == -8161){
              delais = delais-50;
            }
          irrecv.resume();
          }

          
          digitalWrite(set3, LOW);
          digitalWrite(set4, HIGH);
          delay(delais);

          
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);      
        
            if(irvalue == -28561){
              delais = delais+50;
            }
            if(irvalue == -8161){
              delais = delais-50;
            }
          irrecv.resume();
          }

          
          digitalWrite(set4, LOW);
          digitalWrite(set5, HIGH);
          delay(delais);

          
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);      
        
            if(irvalue == -28561){
              delais = delais+50;
            }
            if(irvalue == -8161){
              delais = delais-50;
            }
          irrecv.resume();
          }

          
          digitalWrite(set5, LOW);
          digitalWrite(set6, HIGH);
          delay(delais);

          
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);      
        
            if(irvalue == -28561){
              delais = delais+50;
            }
            if(irvalue == -8161){
              delais = delais-50;
            }
          irrecv.resume();
          }

          
          digitalWrite(set6, LOW);
          digitalWrite(set7, HIGH);
          delay(delais);

          
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);      
        
            if(irvalue == -28561){
              delais = delais+50;
            }
            if(irvalue == -8161){
              delais = delais-50;
            }
          irrecv.resume();
          }

          
          digitalWrite(set7, LOW);
          digitalWrite(set8, HIGH);
          delay(delais);

          
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);      
        
            if(irvalue == -28561){
              delais = delais+50;
            }
            if(irvalue == -8161){
              delais = delais-50;
            }
          irrecv.resume();
          }

          
          digitalWrite(set8, LOW);
          digitalWrite(set9, HIGH);
          delay(delais);

          
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);      
        
            if(irvalue == -28561){
              delais = delais+50;
            }
            if(irvalue == -8161){
              delais = delais-50;
            }
          irrecv.resume();
          }

          
          digitalWrite(set9, LOW);
          digitalWrite(set10, HIGH);
          delay(delais);

          
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);      
        
            if(irvalue == -28561){
              delais = delais+50;
            }
            if(irvalue == -8161){
              delais = delais-50;
            }
          irrecv.resume();
          }

          
          digitalWrite(set10, LOW);
          digitalWrite(set11, HIGH);
          delay(delais);

          
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);      
        
            if(irvalue == -28561){
              delais = delais+50;
            }
            if(irvalue == -8161){
              delais = delais-50;
            }
          irrecv.resume();
          }

          
          digitalWrite(set11, LOW);
          digitalWrite(set12, HIGH);
          delay(delais);

          
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);      
        
            if(irvalue == -28561){
              delais = delais+50;
            }
            if(irvalue == -8161){
              delais = delais-50;
            }
          irrecv.resume();
          }

          
          digitalWrite(set12, LOW);
          digitalWrite(set13, HIGH);
          delay(delais);

          
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);      
        
            if(irvalue == -28561){
              delais = delais+50;
            }
            if(irvalue == -8161){
              delais = delais-50;
            }
          irrecv.resume();
          }

          
          digitalWrite(set13, LOW);
        }
      }
      break;

      

    //PROG 2 (Balayage Double côtés-centre-côtés)
      case 1 : {      
        while(noprog == 1){
          digitalWrite(set0, HIGH);
          digitalWrite(set13, HIGH);
          delay(delais);
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          digitalWrite(set0, LOW);
          digitalWrite(set13, LOW);
          digitalWrite(set1, HIGH);
          digitalWrite(set12, HIGH);
          delay(delais);
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          digitalWrite(set1, LOW);
          digitalWrite(set12, LOW);
          digitalWrite(set2, HIGH);
          digitalWrite(set11, HIGH);
          delay(delais);
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          digitalWrite(set2, LOW);
          digitalWrite(set11, LOW);
          digitalWrite(set3, HIGH);
          digitalWrite(set10, HIGH);
          delay(delais);
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          digitalWrite(set3, LOW);
          digitalWrite(set10, LOW);
          digitalWrite(set4, HIGH);
          digitalWrite(set9, HIGH);
          delay(delais);
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          digitalWrite(set4, LOW);
          digitalWrite(set9, LOW);
          digitalWrite(set5, HIGH);
          digitalWrite(set8, HIGH);
          delay(delais);
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          digitalWrite(set5, LOW);
          digitalWrite(set8, LOW);
          digitalWrite(set6, HIGH);
          digitalWrite(set7, HIGH);
          delay(delais);
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          digitalWrite(set6, LOW);
          digitalWrite(set7, LOW);
          digitalWrite(set5, HIGH);
          digitalWrite(set8, HIGH);
          delay(delais);
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          digitalWrite(set5, LOW);
          digitalWrite(set8, LOW);
          digitalWrite(set4, HIGH);
          digitalWrite(set9, HIGH);
          delay(delais);
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          digitalWrite(set4, LOW);
          digitalWrite(set9, LOW);
          digitalWrite(set3, HIGH);
          digitalWrite(set10, HIGH);
          delay(delais);
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          digitalWrite(set3, LOW);
          digitalWrite(set10, LOW);
          digitalWrite(set2, HIGH);
          digitalWrite(set11, HIGH);
          delay(delais);
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          digitalWrite(set2, LOW);
          digitalWrite(set11, LOW);
          digitalWrite(set1, HIGH);
          digitalWrite(set12, HIGH);
          delay(delais);
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
          }
          digitalWrite(set1, LOW);
          digitalWrite(set12, LOW);
          if (irrecv.decode(&results)){
            irvalue = results.value;
            Serial.println(irvalue);
            if(irvalue == -15811){
              noprog = noprog+1;
            }
            if(irvalue == 8925){
            noprog = noprog-1;
            }
            irrecv.resume();
        }
      }
    }
    break;




    
    if (irrecv.decode(&results)){
        irvalue = results.value;
        Serial.println(irvalue);
        if(irvalue == -15811){
          noprog = noprog+1;
        }
        if(irvalue == 8925){
        noprog = noprog-1;
        }
      }
    }
  }
