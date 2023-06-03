#include "parking.h"       /* Librería propia para controlar las tareas. */
  millis_parking pkg;      /* Instancia de la clase. */
void setup ( void ) {
  
  Serial.begin ( 115200 );     /* Configuración BaudRate a 115200 bits por segundo */
  Serial.println ( F ( "Ha iniciado el sistema" ) ); /*Se almacena en memoria flash*/
  RTC.RTC_init ( );
  MSD.MicroSD_init( );
  
  lcd.init();
  lcd.backlight();
  SPI.begin();
  //mfrc522.PCD_Init();
  //mfrc522_2.PCD_Init();
  servo1.attach(pinServo1); // Pin donde está conectado el servo
  //pinMode(pinBuzzer, OUTPUT);
 // servo2.attach(pinServo2); // Pin donde está conectado el servo
  mqtt.setup_WiFi (  );         /* Configura lo necesario para conectarse a una red WiFi */ 
  mqtt.set_MQTT_server (  );    /* Establece la dirección del Broker MQTT a utilizar */
  mqtt.set_MQTT_callback (  );  /* Se configura la obtención de la información como suscriptor */
  pinMode(ledVerdePin, OUTPUT);
  pinMode(ledRojoPin, OUTPUT);
  // Configurar el pin del sensor Hall como entrada
  pinMode(hallPin, INPUT);

}

void loop ( void ) {
  delay(10);
  mqtt.reconnect_MQTT ();
  pkg.actualizar_tareas ( );
  pkg.rtc ( );
  pkg.microsd ( );
  pkg.lcdi2c ( );
  pkg.json ( );
  pkg.mqtt();
 // pkg.rfid ( );
  pkg.hall ( );
  
}
