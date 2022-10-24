#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(57600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

double vel = 0;
float currAcc = 1000;
int counter = 0;

void loop() {
  mpu6050.update();

  /*
  Serial.print(mpu6050.getAngleX(), 1);
  Serial.print("\t");
  Serial.print(mpu6050.getAngleY(), 1);
  Serial.print("\t");
  Serial.print(mpu6050.getAngleZ(), 1);
  Serial.print("\t");
  */
  
  float accX = (mpu6050.getAccX() + sin(radians(mpu6050.getAngleY()))) * 100;
  float accY = (mpu6050.getAccY() - sin(radians(mpu6050.getAngleX()))) * 100;
  float accZ = (mpu6050.getAccZ() + 1 - cos(radians(mpu6050.getAngleX())) - cos(radians(mpu6050.getAngleY()))) * 100;
  /*
  Serial.print(accX, 1);
  Serial.print("\t");
  Serial.print(accY, 1);
  Serial.print("\t");
  Serial.print(accZ, 1);
  Serial.print("\t");

  Serial.print(100);
  Serial.print("\t");
  Serial.print(-100);
  */
  
  if(accZ > 30){
    if(accZ >= currAcc){
      vel+= accZ/100;
    }
    else{
      counter ++;      
      if(counter > 10){
        Serial.print(vel);
        Serial.println();
        counter = 0;
        vel = 0;
      }
    }
  }

  currAcc = accZ;

  /*
  Serial.print("\t");
  Serial.print(vel);

  Serial.print("\t");
  Serial.print(mpu6050.getAccZ()*100, 1);

  Serial.println();
  */
}