/*
PPMReader library based on https://github.com/Hasi123/read-any-ppm
Works with Servo library

Paweł (DzikuVx) Spychalski 2017
https://quadmeup.com

License: GNU GPL v3
*/

#include "PPMReader.h"
#include "Arduino.h"

#include "logging.h"

#define NO_UPDATE_THRESHOLD 500 //if no update in this number of ms, raise alarm

volatile uint32_t lastPacketUpdate = 0; 

PPMReader::PPMReader(int pin)
{
    _pin = pin;

    pinMode(_pin, INPUT_PULLUP);//input
    // attachInterrupt(_interrupt, PPMReader::handler, CHANGE);
}



bool PPMReader::isReceiving(void) {
    if (millis() - lastPacketUpdate > NO_UPDATE_THRESHOLD) {
        return false;
    } else {
        return true;
    }
}

void PPMReader::start(void) {
    attachInterrupt(digitalPinToInterrupt(_pin), PPMReader::handler, CHANGE);
}


void PPMReader::handler()
{
    static unsigned int pulse;
    static unsigned long counter;
    static byte channel;
    static unsigned long previousCounter = 0;
    static unsigned long currentMicros = 0;
    int tmpVal;


    currentMicros = micros();
    counter = currentMicros - previousCounter;
    previousCounter = currentMicros;
    if(counter<50){//igron shakes 
        return;
    }
    if (counter < 510) { //must be a pulse
        pulse = counter;
    }
    else if (counter > 1950 || channel>= 16)//1910 
    { //sync
        channel = 0;
        lastPacketUpdate = millis();
    }
    else
    { //servo values between 810 and 2210 will end up here
        tmpVal = counter + pulse;
      

        if (tmpVal > 810 && tmpVal < 2210) {
            ChannelData[channel] = fmap(tmpVal,1000, 2000, CRSF_CHANNEL_VALUE_MIN, CRSF_CHANNEL_VALUE_MAX);
        }
        channel++;
        
    }

}