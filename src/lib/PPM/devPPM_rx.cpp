#include "targets.h"
#include "devPPM.h"
#include "logging.h"
#include "PPMReader.h"
 
#if defined( HAS_PPM_INPUT) && defined(PLATFORM_ESP32)
static PPMReader *ppmReader=nullptr;

static void initPPM()
{
    pinMode(GPIO_PIN_INPUT_PPM, INPUT_PULLUP);//input
}

/* at the end of setup call this to init dev ppm 
return the timeout period in */
static int start()
{
    if(ppmReader ==nullptr){
        ppmReader=new PPMReader(GPIO_PIN_INPUT_PPM,PPM_RESOLUTION_NS);
    }
    DBGLN("START PPM ");
    ppmReader->begin();
    return DURATION_IMMEDIATELY;
}

//time out update connection status
static int timeout()
{
    return DURATION_IMMEDIATELY;
}

//event triger by main ,recv & parse ppm data 
static int  event()
{
    return DURATION_IGNORE;
  //get value from ppmreader to ChannelData
}

device_t PPM_device = {
    .initialize = initPPM,
    .start = start,
    .event = event,
    .timeout = nullptr
};

#endif