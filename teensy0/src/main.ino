#include<Arduino.h>
#include<bmx055.h>
#include<MadgwickAHRS.h>

Madgwick filter;
int v;
int theta;
int m[4];
double roll,pitch,yaw;

void setup(){
    Wire.begin();
    Serial.begin(115200);
    BMX055_Init();
    filter.begin(100);
    delay(300);
}

void loop(){
    BMX055_Accl();
    BMX055_Gyro();
    BMX055_Mag();
    
    filter.updateIMU(xGyro,yGyro,zGyro,xAccl,yAccl,zAccl); 
    roll=filter.getRoll();
    pitch=filter.getPitch();
    yaw=filter.getYaw();

    Serial.println(xAccl);
    
    m[0]=v*cos(M_PI/2+theta)-v*sin(M_PI/2+theta);
    m[1]=-v*cos(M_PI/2-theta)-v*sin(M_PI/2-theta);
    m[2]=-v*cos(M_PI/2+theta)+v*sin(M_PI/2+theta);
    m[3]=v*cos(M_PI/2-theta)+v*sin(M_PI/2-theta);
}

