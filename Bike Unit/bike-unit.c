#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
Smart Helmet For Safe Driving Using Sensors
Electronics And Telecommunication, VJTI Page 42
static const int RXPin = 4, TXPin = 5; // GPIO 4=D2(conneect Tx of GPS) and GPIO
5=D1(Connect Rx of GPS
static const uint32_t GPSBaud = 9600; //if Baud rate 9600 didn't work in your case then use
4800
TinyGPSPlus gps; // The TinyGPS++ object
WidgetMap myMap(V0); // V0 for virtual pin of Map Widget
SoftwareSerial ss(RXPin, TXPin); // The serial connection to the GPS device
BlynkTimer timer;
float spd; //Variable to store the speed
float sats; //Variable to store no. of satellites response
String bearing; //Variable to store orientation or direction of GPS
char auth[] = "UAqUlps8WH9lQSvhuR5WZVyqcXOEMPBu"; //Your Project
authentication key
char ssid[] = "12345678"; // Name of your network (HotSpot or Router
name)
char pass[] = "12345678"; // Corresponding Password
//unsigned int move_index; // moving index, to be used later
unsigned int move_index = 1; // fixed location for now

const int xpin = A0;
#define echoPin D0
#define trigPin D3
long duration;
int distance;
void setup()
{
 Serial.begin(9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(D8,OUTPUT);
 pinMode(D4,OUTPUT);
 Serial.println();
 ss.begin(GPSBaud);
 Blynk.begin(auth, ssid, pass);
 timer.setInterval(5000L, checkGPS); // every 5s check if GPS is connected, only really needs to
be done once
 Serial.println("Hello SUJIT ");
}
void checkGPS(){
 if (gps.charsProcessed() < 10)
 {
 Serial.println(F("No GPS detected: check wiring."));
 Blynk.virtualWrite(V4, "GPS ERROR"); // Value Display widget on V4 if GPS not
detected
 }
}
void loop()
{
 if (Serial.available()){
 char k = Serial.read();
 Serial.println(k);
 if(k=='B'){
 digitalWrite(D4,1);
 }
 else{
 digitalWrite(D4,0);
 }
 }

digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distance = duration * 0.034 / 2;
 Serial.println(distance);
 delay(100);
 if (distance<50){
 digitalWrite(D8,1);
 }
 else{
 digitalWrite(D8,0);
 }
 while (ss.available() > 0)
 {
 // sketch displays information every time a new sentence is correctly encoded.
 if (gps.encode(ss.read()))
 displayInfo();
 }
 Blynk.run();
 timer.run();
}

void displayInfo()
{

 if (gps.location.isValid() )
 {
 float latitude = (gps.location.lat()); //Storing the Lat. and Lon.
 float longitude = (gps.location.lng());
 Blynk.virtualWrite(V1, String(latitude, 6));
 Blynk.virtualWrite(V2, String(longitude, 6));
 myMap.location(move_index, latitude, longitude, "GPS_Location");
 int x = analogRead(xpin);
 delay(1);
 float zero_G = 512.0;
 float scale = 102.3;
 float Xaxis = (((float)x - 331.5)/65.5*9.8);
 //Serial.println(Xaxis);
if(Xaxis>35){
 Blynk.notify("Accident Happened! \n I Need Help.....");
 Serial.print("Accident Detected");
 }
 else if(Xaxis<15){
 Blynk.notify("Accident Happened! \n I Need Help.....");
 Serial.print("Accident Detected");
 }
 else{
 Serial.print("Safe");
 }
 }
 Serial.println();
}