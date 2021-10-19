void setup() {
 // put your setup code here, to run once:
Serial.begin(9600);
pinMode(2,INPUT_PULLUP);
}
void loop() {
 // put your main code here, to run repeatedly:
int t = digitalRead(2);
if (t==1){
Serial.print("A");
}
else{
 Serial.print("B");
}
delay(1000);
}