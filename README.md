# parking
Este proyecto fue realizado por alumnos de la facultadad de TEMATICA colima (UCOL), de la carrera Ing. en Tecnologias de Internet.
Este proyecto fue relaizado en sexto semestre de la carrera en la materia de Sistemas Embebidos para Internet de las Cosas.

#EXPLICACION DE LOS DOCUMENTOS
En el repositiorio se subieron varios archivos el funcionamiento en general del proyecto es emplementado por tareas "millis()" el archivo principal 
donde se ejecutan todos los archivos .h es el archivo con extencion .ino (parking.ino) hay un achivo intermediario llamado parking.h el cual recibe 
las tareas y organiza por tiempos de ejcucion, aqui mismo se declaran las clases que son incluidas en el archivo principal. Por otra parte estan 
los archivos en general, los cuales contienen todo el codigo necesario para que el proyecto funcione, todo esto se separo por archivos  .h y se 
incluyeron al intermediario, toda esta implementacion fue por medio de clases, y se incluyeron como librerias a los archivos principales. 

#FUNCIONAMIENTO DEL PROYECTO
Elaboramos una maqueta la cual representaba a un estacionamiento inteligente, esta tenia acceso controlado la cual se realizava por medio de placas
RFID RC522, estas atorizan la entrada a llaves de acceso autorizaadas, posteriormente cuando el acceso es correcto manda una señal al servo para
que este pueda avanzar, en el display marca la hora exacta ya que esta la controlamos por medio de un RTC DS1307, tambien se incluye un lector de 
microSD que guarda las interacciones de los servomotores y el acceso de las personas, esta se guarda en formato JSON y a su vez es subido a un 
servidor MQTT, la aplicacion instalada en la PC es MQTT Explorer, esta puede ser intalada desde la tienda microsoft. Por ultimo los lugares son 
controlados visualmente con dos leds los cuales marcan 2 colores, ocupado(verde), desocupado(rojo), esto es controlado por sensores hall, estos
sensores son activados por capos magneticos, por lo que debajo de cada vehiculo utilizado incorporamos unos pequeños imanes. 
