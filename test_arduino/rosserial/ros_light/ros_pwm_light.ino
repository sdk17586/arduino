#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;

int LED=13;

void messageCb(const std_msgs::Int32& msg) {
    int pwm = msg.data; 
    analogWrite(LED, pwm);
}

ros::Subscriber<std_msgs::Int32> sub("/mcu/led_pwm", &messageCb);

void setup() {

  pinMode(LED, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
}

// rostopic pub -1 /mcu/pwm std_msgs/Int32 "data: 255"
