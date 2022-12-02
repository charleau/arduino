const int relay1 = 2;
const int relay2 = 3;
const int relay3 = 4;
const int relay4 = 5;
const int relay5 = 6;
const int relay6 = 7;
const int relay7 = 8;
const int relay8 = 9;

int speedDelay = 2000;           //speed is in milliseconds
int prgNb = 0;

byte relaysPower = 0;

unsigned long currentTime = 0;
unsigned long previousTime = 0;

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

}

void loop() {
  timer();
  relayTask();
  //Serial.println(0b10110);
}

void timer(){
  currentTime = millis();

  if(currentTime - previousTime >= speedDelay){
    previousTime = currentTime;
    relaysPower = relaysPower * 2;
  }
}

void progTask(){
  switch(prgNb){
    case 0:

    break;
  }
}

void relayTask(){
  
      for(int i = 0; i < 10; i++){
        digitalWrite(i, HIGH);
      }
      
  switch(relaysPower){
    case 0b0:                                   // ALL OFF
      for(int i = 0; i < 10; i++){
        digitalWrite(i, HIGH);
      }
    break;
    case 0b1:
      digitalWrite(relay1, LOW);      
    break;
    case 0b10:
      digitalWrite(relay2, LOW);
    break;
    case 0b100:
      digitalWrite(relay3, LOW);
    break;
    case 0b1000:
      digitalWrite(relay4, LOW);
    break;
    case 0b10000:
      digitalWrite(relay5, LOW);
    break;
    case 0b100000:
      digitalWrite(relay6, LOW);
    break;
    case 0b1000000:
      digitalWrite(relay7, LOW);
    break;
    case 0b10000000:
      digitalWrite(relay8, LOW);
    break;
  }
}