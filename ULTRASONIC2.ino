//Μετρητής αποστάσεων και συσκευή μέτρησης της ταχύτητας του ήχου μέσω υπερήχων//
//Εξωτερικές βιβλιοθήκες 
#include <LiquidCrystal.h>

//Σύνδεση πομποδέκτη υπέρηχων
int send = 13;
int receive = 12;
//Σύνδεση περιφερειακών συσκευών
#define BUTTON 6 
#define INDLED 13
#define NOTE 8

int Csound=340 ;


int l = 255;
//Σύνδεση οθόνης υγρών κρυστάλλων
LiquidCrystal lcd(11,10,9,2,3,4,5);

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode( send, OUTPUT );
  pinMode( receive, INPUT );
  pinMode(INDLED, OUTPUT);
  
  Serial.begin( 115200 );
  Serial.println( "device ok");
  
  
  lcd.begin(16, 2); 
}
 
void loop() {

  
// Κουμπί επαναφοράς
while(digitalRead(BUTTON) == LOW) {            
  analogWrite(INDLED, 0);  
  lcd.clear();
  analogWrite(NOTE, 0);
}                             
  
analogWrite(INDLED, l);  

//Ανάγνωση αισθητήρα απόστασης
digitalWrite(send, LOW);			
digitalWrite(send, HIGH);	
delayMicroseconds( 10 );
digitalWrite(send, LOW);

//Αναγωγή σε μετρήσιμες ποσότητες
 
long duration = pulseIn(receive, HIGH);
 long r = (Csound/100) * duration / 2;		
float distance = r / 100;


//Έξοδος σε LCD και SerialPort

lcd.setCursor(0, 0);
lcd.print("time: ");
lcd.print(duration/2);
lcd.print(" us    ");
Serial.println( duration/2);

lcd.setCursor(0, 1);

 
if( duration > 38000 ) {lcd.println("Beyond Limits "); analogWrite(NOTE, l);delay (100);analogWrite(NOTE, 0);}		
else { lcd.print("dist: ");Serial.println( "dist: "); lcd.print(distance);Serial.println( distance); lcd.println(" cm    ");Serial.println( c);}
 
//Ρυθμός ανανέωσης οθόνης LCD
delay( 1000 );					
}
