// selfbalancing robot.v1;
#include <stdio.h>
#include <Wire.h>
const int MPU_ADD = 0x68;
float intialspeed = 15;
float intialangle = 40.5;
// 550rpm => 100PWM
// create degree to pwm signal
// create pwm to rpm
int gyro_x, gyro_y, gyro_z;
float rotx, roty, rotz;

void setup()
{
    // put your setup code here, to run once:
    Wire.begin(); // begin 12C communication protocol
    Serial.begin(6900);
    Wire.beginTransmission(MPU_ADD);
    Wire.write(MPU_ADD);
    Wire.write(0);
    Wire.endTransmission(true);
}
float degree_to_pwm(float degree)
{
    return (degree / 18.0) + 2.5;
}
float pwm_to_rpm(float pwm)
{
    return (pwm * 550) / 100;
}
void calcu_rot()
{
    // using plus.minus 2 scale ;
    rotx = gyro_x / 131.0;
    roty = gyro_y / 131.0;
    rotz = gyro_z / 131.0;
}

void loop()
{
    // put your main code here, to run repeatedly:
    Wire.beginTransmission(MPU_ADD);
    Wire.write(0x38);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADD, (7 * 2), true); // request 14 registers from MPU_ADD;
    gyro_x = Wire.read() << 8 | Wire.read();
    gyro_y = Wire.read() << 8 | Wire.read();
    gyro_z = Wire.read() << 8 | Wire.read();
    calcu_rot();
    delay(2);
    analogWrite(A1, intialspeed); // start movement;
    if (rotx < intialangle)
    {
        int difference = rotx - intialangle;
        intialspeed = degree_to_pwm(difference);
        analogWrite(A1, intialspeed);
    }
    if (roty < intialangle)
    {
        int difference = intialangle - roty;
        intialspeed = degree_to_pwm(difference);
        analogWrite(A1, intialspeed);
    }
}