const int relay1 = 2;
const int relay2 = 3;
const int relay3 = 4;
const int relay4 = 5;
const int relay5 = 6;
const int relay6 = 7;
const int relay7 = 8;
const int relay8 = 9;

int speedDelay = 1000;           //speed is in milliseconds
int prgNb = 0;

unsigned long currentTime = 0;
unsigned long previousTime = 0;

void setup() {
  

}

void loop() {
  timer();

  switch(prgNb){
    case 0:

    break;
  }
}

void timer(){
  currentTime = millis();

  if(currentTime - previousTime >= speedDelay){
    previousTime = currentTime;
    
  }
}