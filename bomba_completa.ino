#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,21,20);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int seg = 30;
int mins = 0;
int hor = 0;
int cont;
int inputByte = 0;        // Caracter ASCII introducido por el teclado
String    txt = "";       // Variable con el texto a imprimir
byte      c1, c2;         // Contadores
String    msg = "123";    // Clave a teclear

void setup()
{
  Serial.begin(9600);  // Abre puerto serie, transferencia 9600 bps
  Serial.println("###############################################");
  Serial.println("###### SOFTWARE PARA DESACTIVAR BOMBAS  #######");
  Serial.println("####  Ingrese la PASSWORD CORRECTAMENTE    ####");
  Serial.println("####     solo dispone de 3 INTENTOS        ####");
  Serial.println("###############################################");
  lcd.init();
  lcd.backlight();
      
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  lcd.init();
  lcd.backlight();
  delay(100);
}


void loop()
{
  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("BOMBA ACTIVADA");
  lcd.setCursor(5,1);
  lcd.print(hor);
  lcd.print(":");
  lcd.print(mins);
  lcd.print(":");
  lcd.print(seg);
  seg--;
  if (seg < 0){
    seg=59;
    mins--;
    if (mins < 0){
      mins=59;
      hor = hor - 1;
    }
  }
  if (hor == 0){
    if (mins == 0){
     if(seg == 0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("BOOM!!!");
    digitalWrite(13,HIGH);
    digitalWrite(12,HIGH);
    digitalWrite(11,HIGH);

    fin();
    
      }}}
  

  if (Serial.available() > 0) { 
      
      delay(5);                     // Da tiempo a leer el buffer de entrada
      if (txt=="") c2=c1=0;         // iguala contadores
 
      inputByte = Serial.read();    // lee byte entrante:
      txt = txt + char(inputByte);  // va completando el texto
      c1++; 
 
  } // FIN captura caracter de entrada 
 
c2++; 
 
  if ((txt != "") && (c1 != c2)) {
     if (txt == msg) {              // Comprueba si es la palabra buscada
        bombaDesactivada();
        
        
     }else{
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("Pass ERrOr!!!!");
        digitalWrite(12, HIGH);
        digitalWrite(11, LOW);
        delay(1000);
     }
     txt = "";                     // inicializa variable para nueva captura
      
  }
  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
  digitalWrite(11,LOW);

  delay(1000);
  digitalWrite(13,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(11,HIGH);
  
  
}
void bombaDesactivada(){
   Serial.println("BOMBA DESACTIVADA!!!");
   Serial.println(txt);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("BOMBA");
   lcd.setCursor(0,1);
   lcd.print("DESACTIVADA!!!");
   digitalWrite(13, LOW);
   digitalWrite(11, HIGH);
   digitalWrite(12, LOW);
   delay(1000);
   fin();
 }

void fin(){
  fin();
}
