#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define IN1 6
#define IN2 5
#define IN3 4
#define IN4 3
#define ENA 10
#define ENB 9
int _speed = 255;

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
    pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}
char text = ' ';
void loop() {
  if (radio.available()) {

    radio.read(&text, sizeof(text));
    Serial.println(text);
    if(text=='B'){
      Forward();
    }
    if(text=='T'){
      Backward();
    }
    if(text=='R'){
      Right();
    }
    if(text=='L'){
      Left();
    }
    if(text=='S'){
      _stop();
    }
  }
}
void Forward() { 
  
 digitalWrite(IN1, 1); 
 digitalWrite(IN2, 0); 
 digitalWrite(IN3, 1); 
 digitalWrite(IN4, 0); 
 analogWrite(ENA, _speed); 
 analogWrite(ENB, _speed); 
}
void Backward()
{
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  analogWrite(ENA, _speed);
  analogWrite(ENB, _speed);
} 
void Right() { 
 digitalWrite(IN1, 0); 
 digitalWrite(IN2, 1); 
 digitalWrite(IN3, 1); 
 digitalWrite(IN4, 0); 
 analogWrite(ENA, _speed); 
 analogWrite(ENB, _speed);
}
void Left() { 
 digitalWrite(IN1, 1); 
 digitalWrite(IN2, 0); 
 digitalWrite(IN3, 0);
 digitalWrite(IN4, 1); 
 analogWrite(ENA, _speed); 
 analogWrite(ENB, _speed);

 }
 void _stop()
{
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  
}
