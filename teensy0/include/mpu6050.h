//mpu6050 kadai roboken
#include<Arduino.h>
#include<Wire.h>

#define MPU6050_ADDRESS 0x68
#define MPU6050_PWR_MGMT_1 0x6B
#define MPU6050_GYRO 0x1B 
#define MPU6050_ACCl 0x1C 
#define MPU6050_FILTER 0x1A 

int xAccl,yAccl,zAccl;
int xGyro,yGyro,zGyro;

void mpu6050_init(){
    
    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(MPU6050_PWR_MGMT_1);
    Wire.write(0x00);
    Wire.endTransmission();
    
    Wire.endTransmission(MPU6050_ADDRESS);
    Wire.write(MPU6050_GYRO);//serect renge register
    Wire.write(0x00);//±250°/s 
    Wire.endTransmission();

    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(MPU6050_ACCl);//serect renge register
    Wire.write(0x00);//±2go
    Wire.endTransmission();

    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(MPU6050_FILTER);//low pass filter
    Wire.write(0x00);//44 Hz
    Wire.endTransmission();



}
void mpu6050_getdata(){
    int16_t ax,ay,az;
    int16_t gx,gy,gz;
    int16_t temp;

    Wire.beginTransmission(0x68);
    Wire.write(0x3B);
    Wire.endTransmission();
    Wire.requestFrom(0x68,14);

    while(Wire.available()<14);
    
    ax=Wire.read()<<8|Wire.read();
    ay=Wire.read()<<8|Wire.read();
    az=Wire.read()<<8|Wire.read();
    temp=Wire.read()<<8|Wire.read();
    gx=Wire.read()<<8|Wire.read();
    gy=Wire.read()<<8|Wire.read();
    gz=Wire.read()<<8|Wire.read();

    xAccl=((ax-1797)/16374.0);
    yAccl=((ay+1319)/16374.0);
    zAccl=((az+16378)/16374.0);

    xGyro=((gx+38)/121.0);
    yGyro=((gy+23)/121.0);
    zGyro=((gz-9)/121.0);



    //Serial.println(xGyro);

}



