#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;

const int CAMERA_LED = 2;

void camera_messageCb(const std_msgs::String& msg) {

  if (strcmp(msg.data, "light off") == 0) {
    digitalWrite(CAMERA_LED, LOW);
  } else {
    digitalWrite(CAMERA_LED, HIGH);
  }
 
}

ros::Subscriber<std_msgs::String> sub("/mcu/camera_light", &camera_messageCb);

void setup() {
  pinMode(CAMERA_LED, OUTPUT); 

  Serial.begin(9600);
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
}