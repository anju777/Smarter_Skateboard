#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial HM10(2, 3); // RX = 2, TX = 1

// https://bluerobotics.com/learn/guide-for-controlling-the-basic-esc-with-a-potentiometer/#:~:text=Connecting%20the%20ESC&text=Connect%20the%20white%20signal%20wire,ESC%20to%20your%20power%20source.
#define ESC_PIN 9; // signal pin for the ESC
Servo esc;

char appData;  
String inData = "";
int speed = 100; // TODO: tune

void setup() {
  // set up bluetooth module
  Serial.begin(9600);
  Serial.println("HM10 serial started at 9600");
  HM10.begin(9600); // set HM10 serial at 9600 baud rate
  pinMode(13, OUTPUT); // onboard LED
  digitalWrite(13, LOW); // switch OFF LED

  //set up servo
  esc.attach(ESC_PIN);
  esc.writeMicroseconds(1500); // send "stop" signal to ESC. Also necessary to arm the ESC. servo.write(0)?? https://forum.arduino.cc/t/arduino-and-esc-and-motor/563422/8
  delay(7000); // delay to allow the ESC to recognize the stopped signal.
}

void loop() {
    HM10.listen();  // listen the HM10 port
    while (HM10.available() > 0) {   // if HM10 sends something then read
      appData = HM10.read();
      inData = String(appData);  // save the data in string format
      Serial.write(appData);

      if (appData == ' ') {
        fwd();
      }
      else if (appData == 'q') {
        rev();
      }
      else {
        brake();
      }
    }
}

void fwd() {
  esc.write(speed);
}

void rev() {
  esc.write(-speed);
}

void brake() {
  esc.write(90);
}
