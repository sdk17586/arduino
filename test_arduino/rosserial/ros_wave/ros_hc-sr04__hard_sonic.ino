#include <ros.h>
#include <std_msgs/Float32.h>
//TX1:송신 RX1:수신
#define ULTRASONIC_PIN_1_TX 18
#define ULTRASONIC_PIN_1_RX 19

unsigned char data[4] = {};
float distance;


std_msgs::Float32 distance_msg;
std_msgs::Float32 distance_msg2;


ros::Publisher distance_pub("/mcu/sonic/front", &distance_msg);

ros::Publisher distance_pub2("/mcu/sonic/back", &distance_msg2);

void setup() {
  Serial.begin(57600);   
  Serial1.begin(9600);
  
  nh.initNode();
  nh.advertise(distance_pub);
  nh.advertise(distance_pub2);  
}

void loop() {
  if (Serial1.available() >= 4) {
    for (int i = 0; i < 4; i++) {
      data[i] = Serial1.read();
    } 
    while (Serial1.read() == 0xff);

    Serial1.flush();

    if (data[0] == 0xff) {
    int sum = (data[0] + data[1] + data[2]) & 0x00FF;

    if (sum == data[3]) {
      distance = (data[1] << 8) + data[2];
      if (distance > 30) {
        Serial.print("distance=");
        Serial.print(distance / 1000);
        Serial.println("m");
        distance_msg.data = distance / 1000;
        distance_pub.publish(&distance_msg);
      } else {
        distance_msg.data = 0;
        distance_pub.publish(&distance_msg);
      }
    } else {
      Serial.println("ERROR");
    }
   }
  }
}
