#include <LiquidCrystal.h>
const int rs = 3, en = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int rled = 9;
const int vled = 8;
int etat = 0;
const int bouton = A0;
const int bouton2 = A1;
int boutonstatus = 0;
int bouton2status = 12;
int metaltouch = 10;
int metaltouchanal = A2;
int touchstate;
int buzzer = 11;
int analogval;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(rled, OUTPUT);
  pinMode(vled, OUTPUT);
  pinMode(bouton, INPUT);
  pinMode(bouton2, INPUT);
  pinMode(metaltouch, INPUT);
  pinMode(buzzer, OUTPUT);
}
void loop() {
  delay(2000);
  noTone(buzzer);
  boutonstatus = digitalRead(bouton);
  lcd.setCursor(0,0);
  lcd.print("Etat alarme :");

  if(boutonstatus == LOW){
    lcd.setCursor(0,1);
    lcd.print("Desactive");
    digitalWrite(rled, LOW);
    digitalWrite(vled, HIGH);
  }
  if(boutonstatus == HIGH){
    lcd.setCursor(0,1);
    lcd.print("Active   ");
    digitalWrite(vled, LOW);
    digitalWrite(rled, HIGH);
    do{
      bouton2status = digitalRead(bouton2);
      touchstate = digitalRead(metaltouch);
      if(touchstate == LOW){
        tone(buzzer, 1000);
      }
      analogval = analogRead(metaltouchanal);
      Serial.println(analogval);
    }while(bouton2status != HIGH);
  }
}
