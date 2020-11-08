#include<Wire.h>

int XVal, YVal;
int setting = 1;
int incomingByte = 0;
const int axisX = A0;
const int axisY = A1;
const int buzzer = 11;
const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void setup(){
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  pinMode(axisX, INPUT);
  pinMode(axisY, INPUT);
}

void loop() {
  noTone(buzzer);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  XVal = analogRead(axisX);
  YVal = analogRead(axisY);

  if (setting == 0) {
    Serial.print(XVal);
    Serial.print(',')
    Serial.println(YVal);
  }

  if (setting == 1) {
    Serial.print(AcX);
    Serial.print(',');
    Serial.println(AcY);
  }

  if (Serial.available() > 0){
    incomingByte = Serial.read();
  }

  if (incomingByte == 'E'){
    tone(buzzer, 1000); // Send 1KHz sound signal...
    incomingByte = 0;
  }




  delay(300);
}