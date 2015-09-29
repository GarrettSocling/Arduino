
#include "USBDevice.h"
#include "PluggableUSB.h"

#if defined(USBCON)	
#ifdef PLUGGABLE_USB_ENABLED

CUSBDevice::CUSBDevice(void)
{
    //PUSB.AppendDescriptor(this);
}


#endif

#endif /* if defined(USBCON) */
