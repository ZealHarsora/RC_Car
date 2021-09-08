#include<Wire.h>

#define MPU_I2C 0b110100//104 decimal

struct AxisValues{
  float X;
  float Y;
  float Z;
};

AxisValues accel_Raw;
AxisValues gyro_Raw;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 Wire.begin();
 setupMPU();
}

void setupMPU() {
  Wire.beginTransmission(MPU_I2C);
  Wire.write(0x6B);
  Wire.write(0b00000000);
  Wire.endTransmission();
  //Gyroscope configuration
  Wire.beginTransmission(MPU_I2C);
  Wire.write(0X1B);
  Wire.write(0b00000000);
  Wire.endTransmission();
  //Accelerameter Configuration
  Wire.beginTransmission(MPU_I2C);
  Wire.write(0X1C);
  Wire.write(0b00000000);
  Wire.endTransmission();
  
}

void loop() {
  // put your main code here, to run repeatedly:
recordAccelRegisters();
recordGyroRegisters();
}

void recordAccelRegisters(){
  //0x3B -> 0x40
  Wire.beginTransmission(MPU_I2C);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(MPU_I2C, 6);
  while(Wire.available()<6)
  accel_Raw.X= Wire.read()<<8 | Wire.read() ;
  accel_Raw.Y= Wire.read()<<8 | Wire.read();
  accel_Raw.Z= Wire.read()<<8 | Wire.read();
}

void recordGyroRegisters() {
   //0x43 -> 0x48
  Wire.beginTransmission(MPU_I2C);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(MPU_I2C, 6);
  while(Wire.available()<6);
  gyro_Raw.X= Wire.read()<<8 | Wire.read() ;
  gyro_Raw.Y= Wire.read()<<8 | Wire.read();
  gyro_Raw.Z= Wire.read()<<8 | Wire.read();
}
void logData(){
  Serial.print("Accel X: ");
  Serial.print(accel_Raw.X);
  Serial.print("Accel X: ");
  Serial.print(accel_Raw.Y);
  Serial.print("Accel X: ");
  Serial.print(accel_Raw.Z);
  Serial.print("-------Gyro X: ");
  Serial.print(gyro_Raw.X);
  Serial.print(";Gyro Y: ");
  Serial.print(gyro_Raw.Y);
  Serial.print(";Gyro Z: ");
  Serial.print(gyro_Raw.Z);
  
}
