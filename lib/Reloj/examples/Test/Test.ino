#include <Reloj.h>

#define RtcSquareWavePin 3 // Ard Uno 3, node any except gpio16(3)
#define RtcSquareWaveInterrupt 1 // Ard Uno 1, node same as above

volatile uint16_t interuptCount = 0;
volatile bool interuptFlag = false;

void InteruptServiceRoutine()
{
    interuptCount++;
    interuptFlag = true;
}

Reloj time;

void setup ()
{
    Serial.begin(9600);

    pinMode(RtcSquareWavePin, INPUT);

    time.set_time();

    time.reset_alarm();

    time.set_alarm(17, 43);  //hour, minutes

    attachInterrupt(RtcSquareWaveInterrupt, InteruptServiceRoutine, FALLING);
}

void loop ()
{
    time.printDateTime();
    int hour = time.get_time_hours();

    for (int timeCount = 0; timeCount < 20; timeCount++)
    {
        if (Alarmed())
        {
            Serial.print(">>Interupt Count: ");
            Serial.print(interuptCount);
            Serial.println("<<");
            delay(5000);
            time.reset_alarm();
        }
        delay(500);
    }
}

bool Alarmed()
{
    bool wasAlarmed = false;
    if (interuptFlag)  // check our flag that gets sets in the interupt
    {
        wasAlarmed = true;
        interuptFlag = false; // reset the flag

            Serial.println("Alarm triggered");
    }
    return wasAlarmed;
}
