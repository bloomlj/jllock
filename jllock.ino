/*
 * Write personal data of a MIFARE RFID card using a RFID-RC522 reader
 * Uses MFRC522 - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT. 
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 * Hardware required:
 * Arduino
 * PCD (Proximity Coupling Device): NXP MFRC522 Contactless Reader IC
 * PICC (Proximity Integrated Circuit Card): A card or tag using the ISO 14443A interface, eg Mifare or NTAG203.
 * The reader can be found on eBay for around 5 dollars. Search for "mf-rc522" on ebay.com. 
 */

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

#define ENABLE_STEPER 6
#define SETP 5
#define DIR 4


MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
char charreceive;


void setup() {
       pinMode(7, OUTPUT);
      pinMode(ENABLE_STEPER,OUTPUT); // Enable 
      pinMode(SETP,OUTPUT); // Step 
      pinMode(DIR,OUTPUT); // Dir 
      digitalWrite(ENABLE_STEPER,LOW); // Set Enable low 
      
        Serial.begin(4800);        // Initialize serial communications with the PC
        SPI.begin();               // Init SPI bus
        mfrc522.PCD_Init();        // Init MFRC522 card
//        Serial.println(F("Write personal data on a MIFARE PICC "));



}

void loop() {
   
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  while(1)
 {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())  return;

   // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())  return;
        
//        Serial.print(F("Card UID:"));    //Dump UID
   String rfidcode = "";     
   for (byte i = 0; i < mfrc522.uid.size; i++)
     {
//      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
 //     Serial.print(mfrc522.uid.uidByte[i]);  
        //Serial.print(mfrc522.uid.uidByte[i], HEX);
        rfidcode+= String(mfrc522.uid.uidByte[i],HEX);
        //delay(2000);
         
    } 

      Serial.print(rfidcode);

      delay(2000);
        charreceive=char(Serial.read());
        while(Serial.available() == 0)
          {;
          }
        charreceive=char(Serial.read());
        delay(2);  
        if(charreceive=='Y')
          {
            digitalWrite(7, HIGH);   // turn the LED on (HIGH is the voltage level)
            delay(1000);              // wait for a second
            digitalWrite(7, LOW);    // turn the LED off by making the voltage LOW
            delay(1000);              // wait for a second

            // open the door
            
            int x;
            digitalWrite(DIR,HIGH); // Set Dir high
            for(x = 0; x < 90; x++) // Loop 200 times 
            { 
                digitalWrite(SETP,HIGH); // Output high 
                delayMicroseconds(500); // Wait 1/2 a ms 
                digitalWrite(SETP,LOW); // Output low 
                delayMicroseconds(500); // Wait 1/2 a ms 
            } 
            
            delay(3000); // pause one second
            
            digitalWrite(DIR,LOW); // Set Dir low
            for(x = 0; x < 90; x++) // Loop 2000 times 
            { 
              digitalWrite(SETP,HIGH); // Output high 
              delayMicroseconds(500); // Wait 1/2 a ms 
              digitalWrite(SETP,LOW); // Output low 
              delayMicroseconds(500); // Wait 1/2 a ms 
            } 
            delay(1000); // pause one second 


          }
//        
//        if(charreceive=='N')
//          {
//          Serial.println(F("NO"));
//          }
//        if(charreceive=='E')
//          {
//          Serial.println(F("ERROR")); 
//          }    

 }               

}
