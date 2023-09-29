//TX1, RX1에 아두이노 핀 꼽기
unsigned char data[4] = {};
float distance;

void setup() {
  Serial.begin(57600);  
  Serial1.begin(9600);  
}

void loop() {
  if (Serial1.available() >= 4) {
    for (int i = 0; i < 4; i++) {
      data[i] = Serial1.read();
    } while (Serial1.read() == 0xff);

    Serial1.flush();

    if (data[0] == 0xff) {
    int sum = (data[0] + data[1] + data[2]) & 0x00FF;

    if (sum == data[3]) {
      distance = (data[1] << 8) + data[2];
      if (distance > 30) {
        Serial.print("distance=");
        Serial.print(distance / 10);
        Serial.println("cm");

      } else {
        Serial.println("Below the lower limit");
      }
    } else {
      Serial.println("ERROR");
    }
  }
  }
}
