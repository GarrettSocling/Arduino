// Include guard
#pragma once

#define HID_h

#include <stdint.h>
#include <Arduino.h>

//http://stackoverflow.com/questions/1837165/can-two-classes-see-each-other-using-c

class PUSB_;
extern PUSB_ PUSB;

class USBDevice
{
public:
  USBDevice(void);
  
  // Needs to be public for static PUSB_ function access
  // Inherit this device private and everything should be fine
//private:
  USBDevice* next = NULL;


protected:

};
