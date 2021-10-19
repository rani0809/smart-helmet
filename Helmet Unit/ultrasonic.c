const int trigPin = 2; //D4
const int echoPin = 0; //D3
long duration; int distance;
void setup()
{
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
Serial.begin(9600);
}
void loop()
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
Smart Helmet For Safe Driving Using Sensors
Electronics And Telecommunication, VJTI Page 40
digitalWrite(trigPin,HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
Serial.print("Distance: ");
Serial.println(distance);delay(2000);
}