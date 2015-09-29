/*
  PluggableUSB.h
  Copyright (c) 2015 Arduino LLC

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

// Include Guard
#pragma once

#include "USBAPI.h"

#if defined(USBCON)

// TODO different for u2 series
#define MAX_MODULES	6

// TODO where defined??
extern u8 _initEndpoints[];

class CUSBDevice;

class PUSB_
{
public:
  PUSB_(void);
  
  // Called from USB-Core.cpp
  // Needs to be public
  int PUSB_GetInterface(u8* interfaceNum);
  int PUSB_GetDescriptor(int8_t t);
  bool PUSB_Setup(USBSetup& setup, u8 i);
  
  // Only access this class via the USBDevice
private:
  friend CUSBDevice;
  void PUSB_AddFunction(CUSBDevice* device);
  
  // Variables used to calculate endpoints etc
  uint8_t numModules;
  u8 lastInterface;
  u8 lastEndpoint;
  CUSBDevice* rootDevice;
};

// TODO remove old wrappers
int PUSB_GetInterface(u8* interfaceNum);

int PUSB_GetDescriptor(int8_t t);

bool PUSB_Setup(USBSetup& setup, u8 i);

#endif
