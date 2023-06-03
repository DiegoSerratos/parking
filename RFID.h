#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#define SS_PIN 4
#define RST_PIN 27
#define pinServo1 14
//#define pinBuzzer  27
MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo servo1;

  
class lector {
   public:
    void validacion ( void );      
    void accesoEntrada();
    void buzzer();
};

void lector :: validacion(void)
{
      
    if (!mfrc522.PICC_IsNewCardPresent()) {
      return;
    }

    if (!mfrc522.PICC_ReadCardSerial()) {
      Serial.print("No hay comunicacion");
      return;
    }

    Serial.print("UID tag: ");
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message: ");
    content.toUpperCase();

    if (content.substring(1) == "43 87 13 BA" ||
        content.substring(1) == "75 4D 14 53" ||
        content.substring(1) == "83 AD FC AC" ||
        content.substring(1) == "9D 37 7B 25") {
            Serial.println("Acceso Autorizado1");
            accesoEntrada();
            Serial.println("Servo1");
    } else {
        Serial.println("Acceso Denegado");
        //buzzer();        
    }
    mfrc522.PICC_HaltA(); // Poner en espera a la tarjeta para evitar lecturas repetidas
    delay(1000);          // Esperar antes de leer la siguiente tarjeta
}
void lector :: accesoEntrada(){
      Serial.print("Funcion");                
      //Movemos el servo a 0 grados
      servo1.write(0);
      //Esperamos 1.5 segundos
      delay(1500);
      //Movemos el servo a 180 grados
      servo1.write(90);
      //Esperamos 1.5 segundos
      delay(1500);
      Serial.print("Termino1"); 
    }

/*void lector :: buzzer(){
     tone(pinBuzzer,200);
     delay(2000);
     noTone(pinBuzzer);
     delay(1000);
  }*/
