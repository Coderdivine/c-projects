#include <stdio.h>
const int Trig = 9;
const int Echo = 8;
long Duration = 0;
void setup()
{
    // put your setup code here, to run once:
    pinMode(Trig, OUTPUT);
    pinMode(Echo, INPUT);
    Serial.begin(9600);
}

void loop()
{
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
    Duration = pulseIn(Echo, HIGH);
    long Distance_cm = Distance(Duration);
    Serial.print("Distance =>");
    Serial.print(Distance_cm);
    Serial.print("cm");
    delay(500);
}
long Distance(long time)
{
    long DistanceCalc;
    DistanceCalc = ((time * 0.034) / 2);
    // DistanceCalc = time / 74 / 2
    return DistanceCalc;
}