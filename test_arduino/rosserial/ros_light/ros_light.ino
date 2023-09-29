#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;

const int LED_PIN = 13;

void messageCb(const std_msgs::String& msg) {

  if (strcmp(msg.data, "light off") == 0) {
    digitalWrite(LED_PIN, LOW);
  } else {
    digitalWrite(LED_PIN, HIGH);
  }
 
}

ros::Subscriber<std_msgs::String> sub("/mcu/light", &messageCb);

void setup() {
  pinMode(LED_PIN, OUTPUT); 

  Serial.begin(9600);
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
}

// rostopic pub -1 /mcu/light std_msgs/String "data: 'light on'"
// rostopic pub -1 /mcu/light std_msgs/String "data: 'light off'"

// rostopic pub -1 /mcu/camera_light std_msgs/String "data: 'light on'"
