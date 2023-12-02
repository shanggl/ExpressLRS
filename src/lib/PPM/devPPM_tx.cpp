#include "targets.h"
#include "devPPM.h"
#include "PPMReader.h"
#include "crsf_protocol.h"

#include "logging.h"

#ifdef HAS_PPM_INPUT

static PPMReader  *ppmReader=nullptr;

static void initPPM()
{
   
}

static int start()
{ 
    if(!ppmReader){
    DBGLN("init PPM Using %d",GPIO_PIN_INPUT_PPM)
    ppmReader= new PPMReader(GPIO_PIN_INPUT_PPM);
    }
    ppmReader->start();
    DBGLN("PPM start")
    return 1;
}

static int timeout()
{
    return 1;
}

static int  event()
{
    return 1;
}

device_t PPM_device = {
    .initialize = initPPM,
    .start = start,
    .event = event,
    .timeout = timeout
};

#endif