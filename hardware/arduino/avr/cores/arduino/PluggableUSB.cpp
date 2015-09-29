/*
  PluggableUSB.cpp
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

#include "PluggableUSB.h"

#if defined(USBCON)	
#ifdef PLUGGABLE_USB_ENABLED

#include "USBDevice.h"

PUSB_ PUSB;

PUSB_::PUSB_(void)
{

}

int PUSB_::PUSB_GetInterface(u8* interfaceNum)
{
	int ret = 0;
	CUSBDevice* device = rootDevice;
	for (u8 i=0; i < numModules; i++) {
		ret = device->getInterface(interfaceNum);
		device = device->next;
	}
	return ret;
}

int PUSB_::PUSB_GetDescriptor(int8_t t)
{
	int ret = 0;
	CUSBDevice* device = rootDevice;
	for (u8 i=0; i < numModules; i++) {
		ret = device->getDescriptor(t);
		if(ret)
			break;
		device = device->next;
	}
	return ret;
}

bool PUSB_::PUSB_Setup(USBSetup& setup, u8 j)
{
	bool ret = false;
	CUSBDevice* device = rootDevice;
	for (u8 i=0; i < numModules; i++) {
		ret = device->setup(setup, j);
		if(ret)
			break;
		device = device->next;
	}
	return ret;
}

int8_t PUSB_::PUSB_AddFunction(CUSBDevice* device)
{
	if (numModules >= MAX_MODULES) {
		return 0;
	}

	if (numModules == 0) {
		rootDevice = device;
	}
	else {
		CUSBDevice *current = rootDevice;
		while(current->next != NULL) {
			current = current->next;
		}
		current->next = device;
	}

	*device->endpointType = lastInterface;
	lastInterface += device->numInterfaces;
	for (u8 i = 0; i < device->numEndpoints; i++) {
		_initEndpoints[lastEndpoint] = device->endpointType[i];
		lastEndpoint++;
	}
	numModules++;
	return lastEndpoint - device->numEndpoints;
	// restart USB layer???
}


// TODO remove wrappers
int PUSB_GetInterface(u8* interfaceNum)
{
	return PUSB.PUSB_GetInterface(interfaceNum);
}

int PUSB_GetDescriptor(int8_t t)
{
	return PUSB.PUSB_GetDescriptor(t);
}

bool PUSB_Setup(USBSetup& setup, u8 j)
{
	return PUSB.PUSB_Setup(setup, j);
}

int8_t PUSB_AddFunction(PUSBListNode *node, u8* interface)
{
	// TODO not implemented, incompatible with "old" API
	return 0;
	/*
	if (modules_count >= MAX_MODULES) {
		return 0;
	}

	if (modules_count == 0) {
		rootNode = node;
	} else {
		PUSBListNode *current = rootNode;
		while(current->next != NULL) {
			current = current->next;
		}
		current->next = node;
	}

	*interface = lastIf;
	lastIf += node->cb->numInterfaces;
	for ( u8 i = 0; i< node->cb->numEndpoints; i++) {
		_initEndpoints[lastEp] = node->cb->endpointType[i];
		lastEp++;
	}
	modules_count++;
	return lastEp - node->cb->numEndpoints;
	// restart USB layer???
	*/
}

#endif

#endif /* if defined(USBCON) */
