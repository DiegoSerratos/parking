  // Definir los pines de los LEDs
const int ledVerdePin = 12;
const int ledRojoPin = 13;
// Definir el pin del sensor Hall
const int hallPin = 32;

class hall {
   public:
    void espacio ( void );   
};

void hall :: espacio (void){
        // Leer el valor del sensor Hall
  int hallValue = digitalRead(hallPin);
  
  // Verificar si se detecta un imán
  if (hallValue == 1) {
    // Imán detectado
    digitalWrite(ledVerdePin, LOW);   // Apagar el LED verde
    digitalWrite(ledRojoPin, HIGH);  // Encender el LED rojo
    Serial.println("Imán NO detectado: LED Rojo encendido");
  } else {
    // No se detecta un imán
    digitalWrite(ledVerdePin, HIGH);  // Encender el LED verde
    digitalWrite(ledRojoPin, LOW);   // Apagar el LED rojo
    Serial.println("Imán detectado: LED Verde encendido");
  }
  
  // Esperar un breve periodo de tiempo
  delay(500);

}
