#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
#define RELAY 4 

MFRC522 rfid(SS_PIN, RST_PIN); 
String konten="";
void setup() { 
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init(); 
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);
  Serial.println(F("Program Kunci By Ilham Akbar"));
}
 
void loop() {
  delay(500);
  if ( ! rfid.PICC_IsNewCardPresent() || ! rfid.PICC_ReadCardSerial()) return;
  Serial.println(F("Kode UID RFID : "));
  printHex(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();
  //Tambahkan UID RFID dibawah Sini
  if(konten.substring(1)=="67 B4 B4 60"
    || konten.substring(1)=="04 75 41 C2 A6 56 80"
    || konten.substring(1)=="04 70 8B 2A 07 2B 80"
    //|| konten.substring(1)=="0F 5D 8B DC"
  
  ){
    bukaPintu();
  }else{
    Serial.print(F("PICC type: "));
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
    Serial.println(rfid.PICC_GetTypeName(piccType));
  }
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

void bukaPintu(){
  digitalWrite(RELAY, LOW);
  delay(7000);
  digitalWrite(RELAY, HIGH);
}

void printHex(byte *buffer, byte bufferSize) {
  konten = "";
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
    konten.concat(String(buffer[i] < 0x10 ? " 0" : " "));
    konten.concat(String(buffer[i], HEX));
  }
  konten.toUpperCase();
}
