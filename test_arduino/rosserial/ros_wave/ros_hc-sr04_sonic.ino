#include <ros.h>
#include <std_msgs/Float32.h>

#define ULTRASONIC_PIN_2_TX 16
#define ULTRASONIC_PIN_2_RX 17
#define ULTRASONIC_PIN_1_TX 18
#define ULTRASONIC_PIN_1_RX 19

ros::NodeHandle nh;


std_msgs::Float32 distance_msg;
std_msgs::Float32 distance_msg2;

ros::Publisher distance_pub("/mcu/sonic/front", &distance_msg);
ros::Publisher distance_pub2("/mcu/sonic/rear", &distance_msg2);


void setup()
{

  pinMode(ULTRASONIC_PIN_2_TX, OUTPUT);
  pinMode(ULTRASONIC_PIN_2_RX, INPUT);
  
  pinMode(ULTRASONIC_PIN_1_TX, OUTPUT);
  pinMode(ULTRASONIC_PIN_1_RX, INPUT);
  Serial.begin(9600);

  nh.initNode();
  nh.advertise(distance_pub);
  nh.advertise(distance_pub2);

}

void loop() {
  ultrasonic(distance_pub, ULTRASONIC_PIN_2_TX, ULTRASONIC_PIN_2_RX, "front");
  ultrasonic(distance_pub2, ULTRASONIC_PIN_1_TX,ULTRASONIC_PIN_1_RX, "rear");
  nh.spinOnce();

}



void ultrasonic(ros::Publisher &pub, int trigPin, int echoPin, const char* prefix) {
  long duration;
  float distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.017) / 100;


  if (distance >= 0.2 && distance <= 1.5) {
      distance_msg.data = distance;
      Serial.print(prefix);
      Serial.print(" distance=");
      Serial.println(distance);
      pub.publish(&distance_msg);
  } else if (distance > 1.5) {
      Serial.print(prefix);
      Serial.print(" distance=");
      Serial.println("999");
      distance_msg.data = 999.0; 
      pub.publish(&distance_msg);
  } else if (distance < 0.2) {
      Serial.print(prefix);
      Serial.print(" distance=");
      Serial.println("-999");
      distance_msg.data = -999.0; 
      pub.publish(&distance_msg);
  }
}