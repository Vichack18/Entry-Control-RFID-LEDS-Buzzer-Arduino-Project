#include <MFRC522.h>
#include <SPI.h>

#define RST_PIN 9 // pin reset en el pin numero 9 //
#define SS_PIN 10 // donde lo conectamos //

MFRC522 mfrc522 (SS_PIN, RST_PIN);

byte LecturaUID[4];
byte usuario1[4] = {0x79, 0xA2, 0x7C, 0x9C}; // Corresponde al codigo de la tarjeta 
byte usuario2[4] = {0x5A, 0xC4, 0xF3, 0x3F}; // Llavero 1
byte usuario3[4] = {0x26, 0x19, 0xA7, 0xAC}; // Llavero 2
byte usuario4[4] = {0x32, 0x77, 0xCD, 0x83}; // Llavero 3

boolean estadov=false;
boolean estador=false:
boolean estadoa=false;

int ledv=4;
int ledr=2;
int leda=3;
int buzzer =5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  SPI.begin ();
  mfrc522.PCD_Init();
  Serial.println("Ingrese tarjeta");
  pinMode (ledv , OUTPUT);
  pinMode (ledr , OUTPUT);
  pinMode (leda , OUTPUT);
  pinMode (buzzer , OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
    if (! mfrc522.PICC_IsNewCardPresent()){  // si lee una tarjeta, nos va a dar un valor verdadero, si no, seguira return hasta que si sea //
      return;
    }
    if (! mfrc522.PICC_ReadCardSerial()){
      return;
    }

    Serial.print("UID:  ");

    for(byte i=0; i<mfrc522.uid.size; i++){
      if (mfrc522.uid.uidByte[i]<0x10){
        Serial.print(" 0");
      }
      else {
        Serial.print(" ");
      }
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      LecturaUID[i]= mfrc522.uid.uidByte[i];
    }

    Serial.println("");

    if(comparaUID(LecturaUID, usuario1)){
      tone(buzzer, 1000, 2000);
    }

    if(comparaUID(LecturaUID, usuario2)){
      if (estadov==false){
        digitalWrite(ledv, HIGH);
        estadov=!estadov;
      }
      else {
        digitalWrite(ledv, LOW);
        estadov=!estadov;
      }
    }
    if(comparaUID(LecturaUID, usuario3)){
      if (estadoa==false){
        digitalWrite(leda, HIGH);
        estadoa=!estadoa;
      }
      else {
        digitalWrite(leda, LOW);
        estadoa=!estadoa;
      }
    }
    if(comparaUID(LecturaUID, usuario4)){
      if (estador==false){
        digitalWrite(ledr, HIGH);
        estador=!estador;
      }
      else {
        digitalWrite(ledr, LOW);
        estador=!estador;
      }
    }

    delay(1000); // lee cada un segundo los datos de una tarjeta que se apoye // Si dejamos apoyado todo el tiempo estara en un bucle el programa
}

boolean comparaUID(byte lectura[], byte usuario[]){
  for (byte i=0;i<mfrc522.uid.size;i++){
    if(lectura[i]!= usuario[i]){
      return(false); // que nos devuelva un falso, es decir, la tarjeta que pongamos no tendra acceso
    }
    return (true);
  }
}