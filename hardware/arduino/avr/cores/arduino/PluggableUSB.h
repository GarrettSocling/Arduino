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


// TODO remove old node style
typedef struct __attribute__((packed))
{
  bool (*setup)(USBSetup& setup, u8 i);
  int (*getInterface)(u8* interfaceNum);
  int (*getDescriptor)(int8_t t);
  int8_t numEndpoints;
  int8_t numInterfaces;
  uint8_t *endpointType;
} PUSBCallbacks;

class PUSBListNode {
public:
  PUSBListNode *next = NULL;
  PUSBCallbacks *cb;
  PUSBListNode(PUSBCallbacks *ncb) {cb = ncb;}
};

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
  int8_t PUSB_AddFunction(CUSBDevice* device);
  
  // Variables used to calculate endpoints etc
  uint8_t numModules = 0;
  u8 lastInterface = CDC_ACM_INTERFACE + CDC_INTERFACE_COUNT;
  u8 lastEndpoint = CDC_FIRST_ENDPOINT + CDC_ENPOINT_COUNT;
  
  CUSBDevice* rootDevice = NULL;
  
  // TODO add root device, search functions etc
};

// TODO remove old wrappers

int8_t PUSB_AddFunction(PUSBListNode *node, u8 *interface);

int PUSB_GetInterface(u8* interfaceNum);

int PUSB_GetDescriptor(int8_t t);

bool PUSB_Setup(USBSetup& setup, u8 i);

#endif
