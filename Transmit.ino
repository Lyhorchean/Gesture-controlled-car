#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9
#define ENA 5
#define ENB 4
int _speed = 255;
MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
struct MyData {
  byte X;
  byte Y;
};

MyData data;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  pinMode(LED_BUILTIN, OUTPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}
//char text = 'N';
void loop()
{


  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 0, 255 ); // X axis data
  data.Y = map(ay, -17000, 17000, 0, 255);  // Y axis data
  //delay(500);
  Serial.print("Axis X = ");
  Serial.print(data.X);
  Serial.print("  ");
  Serial.print("Axis Y = ");
  Serial.println(data.Y);
  if (data.Y < 80) { //gesture : forward
    Serial.println("gesture 1");
    text='R';
    radio.write(&text, sizeof(text));
  }
  if (data.Y > 145) {//gesture : backward
    text='L';
    Serial.println("gesture 2");
    radio.write(&text, sizeof(text));

  }
  if (data.X > 155) {//gesture : left
    text='B';
    Serial.println("gesture 3");
    radio.write(&text, sizeof(text)); 

  }
  if (data.X < 80) {//gesture : right
    text='T';
    Serial.println("gesture 4");
    radio.write(&text, sizeof(text));

  }
  if (data.X > 100 && data.X < 170 && data.Y > 80 && data.Y < 130) { //gesture : little bit down or stop
    text='S';
    Serial.println("gesture 5");
    radio.write(&text, sizeof(text));
  }

}
