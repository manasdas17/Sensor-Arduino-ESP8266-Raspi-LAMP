#include <DHT.h>
#include <floatToString.h>

//Definicion de variables necesarias para conectar a la //red Wi-Fi
#define SSID        "MyWiFi01" //Debido a bug en ESP66 el nombre de la red no puede contener espacios y debe tener al menos un numero
#define PASS        "Mypass"
#define TARGET_IP   "192.168.1.100"
#define TARGET_PORT 80
#define GET_T "GET /habitacion1/t1.php?valor="
#define GET_H "GET /habitacion1/h1.php?valor="
#define http_final " HTTP/1.1"
#define host "Host: alistecasa.no-ip.org"

#define DHTPIN 3 //define el nº de pin del sensor
#define DHTTYPE DHT22 //define el tipo de sensor
DHT dht(DHTPIN, DHTTYPE); //crea una instancia del sensor

int comillas = 34; //numero del caracter ASCII de las comillas
int car = 13;
int lef = 10;
int incomingByte=0; //variable en la que se va a guardar byte recibido

char temp1[10];
char temp2[10];

String temperatura;
String humedad;

void setup()
{
  Serial.begin(9600); //Se inicializa el UART
  Serial.setTimeout(5000);
  delay(1000); //Espera 1 segundo
  Serial.print("AT+RST"); //Resetea el modulo
  retornocarro();
  delay(2000);
  
  Serial.print("AT+CWMODE=1");
  retornocarro();
  
  //Se escriben por el puerto serie los comandos necesarios para iniciar la conexion
  Serial.print("AT+CWJAP=");
  Serial.write(comillas);
  Serial.print(SSID);
  Serial.write(comillas);
  Serial.print(",");
  Serial.write(comillas);
  Serial.print(PASS);
  Serial.write(comillas);
  retornocarro();
  recepcion();

	//Testea si la conexion se realizo correctamente
  Serial.print("AT+CWJAP?");
  retornocarro();
  recepcion();

  //Establece conexion con el servidor
  Serial.print("AT+CIPSTART=");
  Serial.write(comillas);
  Serial.print("TCP");
  Serial.write(comillas);
  Serial.print(",");
  Serial.write(comillas);
  Serial.print(TARGET_IP);
  Serial.write(comillas);
  Serial.print(",");
  Serial.print(TARGET_PORT);
  retornocarro();
  recepcion();
  delay(2000);

  Serial.print("AT+CIPMODE=1");
  retornocarro();

  dht.begin(); //inicializa el sensor

}


void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(0);
  String cadena3; 

  cadena3 = host;

 floatToString(temp1, t, 2);
 floatToString(temp2, h, 2);

 //Se envia la temperatura en primer lugar...
 String cadena1 =GET_T+String(temp1)+http_final;
 conexion_servidor();
 //--- cadena...
 delay(500);
 Serial.print(cadena1);
 Serial.write(car);
 Serial.write(lef);
 Serial.print(cadena3);
 retornocarro();
 
 delay(500);
 Serial.print("AT+CIPCLOSE");
 retornocarro();
 
 delay(500);
 String cadena2 =GET_H+String(temp2)+http_final;
 conexion_servidor();
 delay(500);
 Serial.print(cadena2);
 Serial.write(car);
 Serial.write(lef);
 Serial.print(cadena3);
 retornocarro();
 
 delay(500);
 Serial.print("AT+CIPCLOSE");
 retornocarro();
 
 
 delay(5000);
}

void conexion_servidor()
{
  //Establece conexion con el servidor
  Serial.print("AT+CIPSTART=");
  Serial.write(comillas);
  Serial.print("TCP");
  Serial.write(comillas);
  Serial.print(",");
  Serial.write(comillas);
  Serial.print(TARGET_IP);
  Serial.write(comillas);
  Serial.print(",");
  Serial.print(TARGET_PORT);
  retornocarro();
  recepcion();
  delay(2000); 
}

void recepcion()
{
  delay(500);
  while (Serial.available() >0) 
  {
    incomingByte = Serial.read();
  }
}

void retornocarro()
{
  Serial.write(car);
  Serial.write(lef);
  Serial.write(car);
  Serial.write(lef);
}
