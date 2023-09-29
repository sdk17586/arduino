#include <SoftwareSerial.h>
#include <ros.h>
#include <std_msgs/Float32.h>


ros::NodeHandle nh;

SoftwareSerial mySerial(11, 10);
unsigned char data[4] = {};
float distance;

std_msgs::Float32 distance_msg;

ros::Publisher distance_pub("/mcu/distance", &distance_msg);

void setup()
{
  Serial.begin(57600);
  mySerial.begin(9600);

  nh.initNode();
  nh.advertise(distance_pub);
  nh.advertise(status_pub);
}

void loop()
{
  do {
    for (int i = 0; i < 4; i++) {
      data[i] = mySerial.read();
    }
  } while (mySerial.read() == 0xff);

  mySerial.flush();

  if (data[0] == 0xff) {
    int sum;
    sum = (data[0] + data[1] + data[2]) & 0x00FF;
    if (sum == data[3]) 
    {
      distance = (data[1] << 8) + data[2];
      if(distance>30)
      {
      Serial.print("distance=");
      Serial.print(distance/1000);
      Serial.println("m");
      distance_msg.data = distance / 1000;
      distance_pub.publish(&distance_msg);
      } 
      else 
      {
        distance_msg.data = 0;
        distance_pub.publish(&distance_msg);
      }
    } else 
    { Serial.println("ERROR");
    }
  }

  nh.spinOnce();
  delay(100);
}
