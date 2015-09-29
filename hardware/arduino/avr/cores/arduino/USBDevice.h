// Include guard
#pragma once

#define USBDEVICE_INCLUDED

#include <stdint.h>
#include <Arduino.h>

//http://stackoverflow.com/questions/1837165/can-two-classes-see-each-other-using-c

class PUSB_;
extern PUSB_ PUSB;

// Important note: USBDevice is somehow reserved, do not use the name.
class CUSBDevice
{
public:
  CUSBDevice(const int8_t numEP, const int8_t numIF, const uint8_t* epType);
  
  // Needs to be public for static PUSB_ function access
  // Inherit this device private and everything should be fine
//private:
  CUSBDevice* next = NULL;
  
  virtual bool setup(USBSetup& setup, u8 i) = 0;
  virtual int getInterface(u8* interfaceNum) = 0;
  virtual int getDescriptor(int8_t t) = 0;

  const int8_t numEndpoints;
  const int8_t numInterfaces;
  int8_t firstEndpoint;
  int8_t firstInterface;
  const uint8_t *endpointType;


protected:

};
