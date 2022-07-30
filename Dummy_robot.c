#include <stdio.h>
// in_1 => DC_MOTOR pin 3;
// Trig pin in Ultrasoinc sensor => 9;
// Echo pin in Ultrasoinc sensor => 8
const int in_1 = 3;
const int Trig = 9;
const int Echo = 8;
long Duration = 0;
// For providing logic to L298 IC to choose the direction of the DC motor

void setup()
{
    pinMode(Trig, OUTPUT); // set trig to OUTPUT( sends sound waves)
    pinMode(Echo, INPUT);  // set Echo to INPUT(recieve);
    pinMode(in_1, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    digitalWrite(Trig, LOW);
    // digitalWrite(in_1,HIGH);
    // analogWrite(pwm,255) ;
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
    Duration = pulseIn(Echo, HIGH);
    long Distance_cm = Distance(Duration);
    Serial.print("Distance =>");
    Serial.print(Distance_cm);
    Serial.print("cm \n");
    delay(200);
    /*setting pwm of the motor to 255
    we can change the speed of rotaion
    by chaning pwm input but we are only
    using arduino so we are using higest
    value to driver the motor  */

    ////Clockwise for 3 secs
    // delay(3000) ;
    //
    ////For brake
    // digitalWrite(in_1,HIGH);
    // delay(1000) ;
    //
    ////For Anti Clock-wise motion - IN_1 = LOW , IN_2 = HIGH
    // digitalWrite(in_1,LOW);
    // delay(3000) ;
    //
    ////For brake
    // digitalWrite(in_1,HIGH);
    // delay(1000) ;
}
long Distance(long time)
{
    long DistanceCalc;
    DistanceCalc = ((time * 0.034) / 2);
    // DistanceCalc = time / 74 / 2
    return DistanceCalc;
}