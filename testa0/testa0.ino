// By HORIZON LAB.

#include "Wire.h"
const int MPU=0x68;   // The code for the mpu-6050 is from Arduino User JohnChi
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int addressA = 2; //S0
int addressB = 3; //S1
int addressC = 4; //S2
//int addressD = 5; //S3


void setup() 
{                
  Wire.begin(); // wake up I2C bus
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(115200);
  pinMode(addressA, OUTPUT);  //S0
  pinMode(addressB, OUTPUT);  //S1
  pinMode(addressC, OUTPUT);  //S2  
 // pinMode(addressD, OUTPUT);  //S4  
}


void loop() 
{
  Serial.println("------------LOOP1------------");
  // First IMU: Check the table for channel 0 (1=HIGH, 0=LOW)
  digitalWrite(addressA, LOW);
  digitalWrite(addressB, LOW);
  digitalWrite(addressC, LOW);
 /// digitalWrite(addressD, LOW);
  read_imus();
  delay(15);
 
  Serial.println("------------LOOP2------------");
  // First IMU: Check the table for channel 0 (1=HIGH, 0=LOW)
 digitalWrite(addressA, LOW);
 digitalWrite(addressB, LOW);
  digitalWrite(addressC,HIGH);
  //digitalWrite(addressD, HIGH);
  read_imus();
  delay(15);
  // Second IMU: Check the table for channel 1 (1=HIGH, 0=LOW)
    Serial.println("------------LOOP3------------");
  // First IMU: Check the table for channel 0 (1=HIGH, 0=LOW)
 digitalWrite(addressA, LOW);
 digitalWrite(addressB, HIGH);
  digitalWrite(addressC,LOW);
  //digitalWrite(addressD, HIGH);
  read_imus();
  delay(15);
//

}

void read_imus()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  delay(10);
}


