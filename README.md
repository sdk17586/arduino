# rdv_mcu
이 패키지는 조명led, 네온led, 초음파 센서 2개, camera_tower_led 를 한번에 제어하는 아두이노 패키지입니다.
# RUN
     roslaunch rdv_mcu mcu.launch

## Dependency

This project depends on the following libraries:

- [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)

To install this library, open Arduino IDE, go to `Sketch > Include Library > Manage Libraries`, search for `Adafruit_NeoPixel`, and install it.

## Ultura_sonic_sensor_name
![KakaoTalk_20230928_131940722_01](https://github.com/rendezvue/rdv_amr_mcu/assets/122353362/8bb3ae20-558e-450a-9199-d3021ed2deaf)
name : hcsr04p
![KakaoTalk_20230928_131940722](https://github.com/rendezvue/rdv_amr_mcu/assets/122353362/04e89fce-85de-4362-8076-55ffc3d3f47e)
name : a02yyuw


![arduino_pin_map](https://github.com/rendezvue/rdv_amr_mcu/assets/122353362/709f1cc8-9cfe-4526-b53d-d41379ad60cd)



          
| Device        | Pin | Connection  |
|---------------|-----|-------------|
| 조명 LED      | 13  | -           |
| -             | GND | 모터드라이브 GND |
| 네온 LED      | 12  | -           |
| -             | VCC | 5V          |
| -             | GND | GND         |
| 초음파 센서1  | -   | -           |
| -             | VCC | 5V          |
| -             | GND | GND         |
| Trig(blue)    | TX  | 16          |
| echo(green)   | RX  | 17          |
| 초음파 센서2  | -   | -           |
| -             | VCC | 5V          |
| -             | GND | GND         |
| Trig(blue)    | TX  | 18          |
| echo(green)   | RX  | 19          |
| camera LED    | 2  | -           |
| -             | GND | 모터드라이브 GND |
