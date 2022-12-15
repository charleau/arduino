/*
    Programme de départ pour boiter CRiBoks        
    debounce des boutons software
*/

//-----------------------DÉCLARATIONS DES PORTS UTILISÉS ET DES #INCLUDE-----------------------\\

int enter = A0;
int up = A1;
int down = A2;        // BOUTONs (= EST LE PORT ARDUINO PERMANENT)
int back = A3;
int next = A4;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


//----------------------------DÉCLARATION DES VARIABLES----------------------------\\

int etatenter = 0;
int etatup = 0;
int etatdown = 0;
int etatback = 0;
int etatnext = 0;

bool is_ready = false;
float v_logiciel = 0.0;

//-----------------------DÉCLARATION DE L'UTILISATION DES PINS-----------------------\\

void setup() {
  Serial.begin(9600);

  pinMode(enter, INPUT);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(back, INPUT);
  pinMode(next, INPUT);

//-----------------------------AFFICHAGE DE DÉPART DU LCD----------------------------\\

  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("   CRiBoks V2   ");
  lcd.setCursor(0,1);
  lcd.print(" Charles Ricard ");
  delay(5000);
  
}

//------------------------------DÉPART BOUCLE PROGRAMME------------------------------\\

void loop() {
   if(is_ready == false){
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
    lcd.setCursor(0,1);
    lcd.print("[####          ]");
    delay(150);
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
    lcd.setCursor(0,1);
    lcd.print("[------OK------]");
    delay(1500);
    lcd.clear();
while(1){                                   // À retirer
    delay(1000);
    lcd.setCursor(0,0);
    lcd.print(" PROG           ");
    delay(700);
    lcd.setCursor(0,0);
    lcd.print(" PROG NOT       ");
    delay(700);
    lcd.setCursor(0,0);
    lcd.print(" PROG NOT FOUND ");
    delay(700);
    lcd.setCursor(0,1);
    lcd.print("  Version ");
    lcd.print(v_logiciel);
    lcd.print("   ");
    delay(3500);
    lcd.setCursor(0,0);
    lcd.print("      NOT FOUND ");
    delay(300);
    lcd.setCursor(0,0);
    lcd.print("          FOUND ");
    delay(300);
    lcd.setCursor(0,0);
    lcd.print("                ");
    delay(300);
    lcd.clear();
    delay(500);
}                                             // À retirer
    is_ready = true;
  }
}    // end void loop()
