#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#define SS_PIN 26
#define RST_PIN 27
#define pinServo2 25
MFRC522 mfrc522_2(SS_PIN, RST_PIN);
Servo servo2;
  
class lector_2 {
   public:
    void validacion_2 ( void );  
    void accesoSalida();  
};

void lector_2 :: validacion_2 (void)
{
    if (!mfrc522_2.PICC_IsNewCardPresent()) {
      return;
    }

    if (!mfrc522_2.PICC_ReadCardSerial()) {
      Serial.print("No hay comunicacion");
      return;
    }

    Serial.print("UID tag: ");
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522_2.uid.size; i++) {
      Serial.print(mfrc522_2.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522_2.uid.uidByte[i], HEX);
      content.concat(String(mfrc522_2.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522_2.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message: ");
    content.toUpperCase();

    if (content.substring(1) == "43 87 13 BA" ||
        content.substring(1) == "75 4D 14 53" ||
        content.substring(1) == "83 AD FC AC" ||
        content.substring(1) == "9D 37 7B 25") {
            Serial.println("Acceso Autorizado2");
            accesoSalida();
            Serial.println("Servo2");
    } else {
        Serial.println("Acceso Denegado");
        delay(3000);
    }
    mfrc522_2.PICC_HaltA(); // Poner en espera a la tarjeta para evitar lecturas repetidas
    delay(1000);          // Esperar antes de leer la siguiente tarjeta
}

  void lector_2 :: accesoSalida(){
    Serial.print("Funcion");                
    //Movemos el servo a 0 grados
    servo2.write(0);
    //Esperamos 1.5 segundos
    delay(1500);
    //Movemos el servo a 180 grados
    servo2.write(90);
    //Esperamos 1.5 segundos
    delay(1500);
    Serial.print("Termino2"); 
  }
