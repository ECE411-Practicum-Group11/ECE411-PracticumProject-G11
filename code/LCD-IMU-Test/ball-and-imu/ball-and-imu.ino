#include <LiquidCrystal.h>

#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

#define GRAVITY 0.1
#define PERIOD 50 // Time between frames in milliseconds

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Initializing variables
int lcdpos = 0;
float ballpos = 0;
float gravity = GRAVITY;
float ballspeed = 1;
unsigned long currTime = 0;

double vel = 0;
int counter = 0;
int isAccel = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(57600);

  Wire.begin();
  Wire.setWireTimeout(3000, true); //timeout value in uSec
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  currTime = millis();
}

void loop() {

  // Advance animation after the desired time has elapsed
  if((millis() - currTime) >= PERIOD){
    currTime = millis();
    animation();
  }

  mpu6050.update();

  float accX = (mpu6050.getAccX() + sin(radians(mpu6050.getAngleY()))) * 100;
  float accY = (mpu6050.getAccY() - sin(radians(mpu6050.getAngleX()))) * 100;
  float accZ = (mpu6050.getAccZ() + 1 - cos(radians(mpu6050.getAngleX())) - cos(radians(mpu6050.getAngleY()))) * 100;
  Serial.print(accX,1);
  Serial.print("\t");
  Serial.print(vel,1);
  Serial.print("\t");
  Serial.print(400);
  Serial.print("\t");
  Serial.print(-400);
  Serial.println();

  // Jump when motion sensor is shooketh
  if(accX > 30){
    vel+= accX/10;
    isAccel = 1;
  }else{
    if(isAccel){
      counter++;
    }  
  }
  if(counter > 2){
    if(ballspeed < 0){
      ballspeed = 0;
    }
    ballspeed += vel/300;
    counter = 0;
    vel = 0;
    isAccel = 0;
  }

}


void animation(){
  // Update ball position and velocity
  ballspeed -= gravity;
  ballpos += ballspeed;

  // Bounce when height reaches 0
  if(ballpos <= 0){
    ballpos = 0;
    ballspeed *= -0.8; // Ball bounces with friction
  }

  // Debug logs
  //Serial.println("");
  //Serial.print(ballspeed);
  //Serial.print(", ");
  //Serial.print(ballpos);
  
  lcdpos = floor(ballpos);
  //Serial.print(", ");
  //Serial.print(lcdpos);

  // Draw ball when within screen bounds
  lcd.clear();
  lcd.setCursor(lcdpos, 0);
  if((lcdpos >= 0) && (lcdpos < 16)){
    lcd.print("O");
  }
}