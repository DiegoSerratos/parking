/*****************************************************************************************
*      DESCRIPCIÓN DE LA LIBRERÍA: El objetivo de esta librería es generar tiempos de    *
*       espera de ejecución sin la implementación de la función "delay()".               *
******************************************************************************************/
#ifndef parking_h
#define parking_h

#include "RTC.h"
#include "MicroSD.h"
//#include "MicroSD.h"
#include "MQTT.h"
#include "RFID.h"
//#include "RFID2.h"
#include "hall.h"


#include <ArduinoJson.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


#define TIEMPO1 1000     // Constante para indicar 1 segundo (1000 ms).
#define TIEMPO2 2000     // Constante para indicar 2 segundos (2000 ms).
#define TIEMPO3 3000     // Constante para indicar 3 segundos (3000 ms).
#define TIEMPO4 4000     // Constante para indicar 4 segundos (4000 ms).
#define TIEMPO5 5000     // Constante para indicar 5 segundos (5000 ms).
#define TIEMPO6 6000     // Constante para indicar 6 segundos (6000 ms).
#define TIEMPO7 7000     // Constante para indicar 7 segundos (7000 ms).
#define TIEMPO8 8000     // Constante para indicar 8 segundos (8000 ms).

MQTT mqtt;
MicroSD MSD;
DS1307_RTC RTC;
LiquidCrystal_I2C lcd(0x27, 16, 2);
lector entrada;
//lector_2 salida;
hall HALL;
String hora;
String fecha;
String SalidaString = "";
//const int ledVerdePin = 14;
//const int ledRojoPin = 12;
// Definir el pin del sensor Hall
//const int hallPin = 32;

class millis_parking {

  public:
    uint64_t tiempo_anterior1 = 0,   // Contador de tiempo que tendrá múltiplos de TIEMPO1.
             tiempo_anterior2 = 0,   // Contador de tiempo que tendrá múltiplos de TIEMPO2.
             tiempo_anterior3 = 0,   // Contador de tiempo que tendrá múltiplos de TIEMPO3.
             tiempo_anterior4 = 0,   // Contador de tiempo que tendrá múltiplos de TIEMPO4.
             tiempo_anterior5 = 0,   // Contador de tiempo que tendrá múltiplos de TIEMPO5.
             tiempo_anterior6 = 0,   // Contador de tiempo que tendrá múltiplos de TIEMPO6.
             tiempo_anterior7 = 0,   // Contador de tiempo que tendrá múltiplos de TIEMPO7.
             tiempo_anterior8 = 0,   // Contador de tiempo que tendrá múltiplos de TIEMPO8.
             tiempo_actual = 0;      // Contador de tiempo que tendrá múltiplos de TIEMPO.
    
  public:

    void rtc ( void );            // Función que ejecuta una acción cada segundo.
    void microsd ( void );            // Función que ejecuta una acción cada dos segundos.
    void lcdi2c ( void );            // Función que ejecuta una acción cada tres segundos.
    void json ( void );
    void mqtt (void);
    void rfid ( void );            // Función que ejecuta una acción cada segundo.
    void rfid_2 ( void );
    void hall ( void );            // Función que ejecuta una acción cada tres segundos.
    void actualizar_tareas (void );  // Función que actualiza el conteo obtenido de la función "millis()".
 
};

/*
   Al arranque del sistema la variable "tiempo_anterior1" tendrá el valor de 0, 
   cuando "tiempo_actual" sea igual a "TIEMPO1" es decir cuando hayan pasado
   1000 ms, "tiempo_anterior" tomará el valor de "tiempo_actual", para que la
   diferencia entre ellos siempre se cumpla cuando pase el tiempo asignado en "TIEMPO1".
*/

/*~~~~~~~~~~~~~~~~~~~~~~~~ rfid - Función que se ejecuta cada TIEMPO1 ( 1 SEGUNDOS ) ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_parking :: rfid ( void ) {

  if ( ( tiempo_actual - tiempo_anterior1 ) >= TIEMPO1 ){

      Serial.println( "1.Rfid Entrada Activo" );
      entrada.validacion();
      tiempo_anterior1 = tiempo_actual;

  }
  
}

/*~~~~~~~~~~~~~~~~~~~~~~~~ hall - Función que se ejecuta cada TIEMPO8 ( 8 SEGUNDOS ) ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_parking :: hall ( void ) {

  if ( ( tiempo_actual - tiempo_anterior2 ) >= TIEMPO2 ){

     Serial.println ( "2.- Sensot hall" );
     HALL.espacio();
     tiempo_anterior2 = tiempo_actual;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~ rtc - Función que se ejecuta cada TIEMPO3 ( 3 SEGUNDO) ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_parking :: rtc ( void ) {
  if ( ( tiempo_actual - tiempo_anterior3 ) >= TIEMPO3 ){
    
    Serial.println ( "3.- Ejecutando RTC" );
    
    tiempo_anterior3 = tiempo_actual;
    RTC.get_time ( );               /* Actualizar fecha y hora en formato RAW */
    RTC.show_time ( );              /* Dar formato y mostrar por consola serial */
    delay ( 1000 ); 

  }

}

/*~~~~~~~~~~~~~~~~~~~~~~~~ mqtt - Función que se ejecuta cada TIEMPO4 ( 4 SEGUNDOS ) ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_parking :: mqtt ( void ) {

  if ( ( tiempo_actual - tiempo_anterior4 ) >= TIEMPO4 ){
    // Obtener la hora del RTC
    SalidaString="";
    DynamicJsonDocument JSON ( 1024 );  
    RTC.get_time();
    //Asignar a varibles la hora y fecha
    fecha= RTC.fecha_ ( );              
    hora=RTC.time_();
     Serial.println ( "4.- MQTT" );
     JSON["Fecha"]=fecha;
     JSON["Hora"]=hora;
     JsonObject actuador  = JSON.createNestedObject("Actuadores");
     
    serializeJsonPretty( JSON, SalidaString );
    
    
    client.publish( TXTOPIC, SalidaString.c_str());
    Serial.println(SalidaString);
    tiempo_anterior4 = tiempo_actual;
  }
  
}

/*~~~~~~~~~~~~~~~~~~~~~~~~ lcdi2c - Función que se ejecuta cada TIEMPO5 ( 5 SEGUNDOS ) ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_parking :: lcdi2c ( void ) {

  if ( ( tiempo_actual - tiempo_anterior5 ) >= TIEMPO5 ){

     Serial.println ( "5.- Ejecutando Pantalla LCD" );
     

    //lcd.backlight();
    // Obtener la hora del RTC
    RTC.get_time();
    //Asignar a varibles la hora y fecha
    fecha= RTC.fecha_ ( );              
    hora=RTC.time_();
    
    // Mostrar la hora en el LCD
    lcd.setCursor(0, 0);
    lcd.print("Hora: ");
    lcd.print(hora);
    lcd.setCursor(0, 1);
    lcd.print("Fecha: ");
    lcd.print(fecha);
    tiempo_anterior5 = tiempo_actual;
  }
  
}

/*~~~~~~~~~~~~~~~~~~~~~~~~ json - Función que se ejecuta cada TIEMPO6 ( 6 SEGUNDOS ) ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_parking :: json ( void ) {

  if ( ( tiempo_actual - tiempo_anterior6 ) >= TIEMPO6 ){
    Serial.println( "6.- json" ); 
  /*  RTC.get_time();
    fecha= RTC.fecha_ ( );              
    hora=RTC.time_();
    JsonObject FyH  = JSON.createNestedObject("FyH");
    FyH [ "fecha: "] = fecha;
    FyH [ "hora: "] = hora;
    serializeJsonPretty( JSON, SalidaString );
    Serial.println(SalidaString); 
    client.publish( TXTOPIC, SalidaString.c_str());*/
    tiempo_anterior6 = tiempo_actual;
  }
  
}

/*~~~~~~~~~~~~~~~~~~~~~~~~ microsd - Función que se ejecuta cada TIEMPO7  ( 7 SEGUNDOS ) ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_parking :: microsd ( void ) {
  if ( ( tiempo_actual - tiempo_anterior7 ) >= TIEMPO7 ){

     Serial.println ( "7.- Ejecutando Micro SD" );
     tiempo_anterior2 = tiempo_actual;
     delay ( 2000 ); // this speeds up the simulation
      MSD.SaveFile (SalidaString);                     
      MSD.ReadFile ( );
      MicroSD_File.println (  );
     Serial.println ( "7.1.-Guardado en MicroSD" );
     tiempo_anterior7 = tiempo_actual;

  }
}




/*~~~~~~~~~~~~~~~~~~~~~~~~ actualizar_tareas - Función que actualiza el contador de "millis()" ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_parking :: actualizar_tareas ( void ) {

  tiempo_actual = millis( );

}

#endif
