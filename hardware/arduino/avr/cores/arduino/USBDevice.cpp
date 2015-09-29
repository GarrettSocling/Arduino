
#include "USBDevice.h"
#include "PluggableUSB.h"

#if defined(USBCON)	
#ifdef PLUGGABLE_USB_ENABLED

CUSBDevice::CUSBDevice(const int8_t numEP, const int8_t numIF, const uint8_t* epType) :
numEndpoints(numEP), numInterfaces(numIF), firstEndpoint(-1), firstInterface(-1), endpointType(epType)
{
    PUSB.PUSB_AddFunction(this);
}


#endif

#endif /* if defined(USBCON) */
