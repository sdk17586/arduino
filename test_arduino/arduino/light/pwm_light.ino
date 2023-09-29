int LED=13;

void setup() {
pinMode(LED, OUTPUT);
}

void loop() {
analogWrite(LED,255);
delay(1000);
analogWrite(LED,0);
delay(1000);      
}