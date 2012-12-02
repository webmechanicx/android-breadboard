/*
 * Copyright 2012 SungChan Lee (crybaby1970@gmail.com)
 * ADK support library
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the authors nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "Arduino.h"
#include "pins_arduino.h"
#include <Max3421e.h>
#include <Usb.h>
#include <ADKAccessory.h>
#include <AndroidAccessory.h>
#include <SoftwareSerial.h>


#define USB_TYPE	1
#define BT_TYPE		2

int acc_type;
AndroidAccessory *pAcc;
SoftwareSerial *pBTAcc;
		
// usb type accessory
ADKAccessory::ADKAccessory()
{
	acc_type = -1;
}

ADKAccessory::ADKAccessory(const char *manufacturer, const char *model, const char *description, const char *version, const char *uri, const char *serial)
{
	pAcc = new AndroidAccessory(manufacturer, model, description, version, uri, serial);
	if(!pAcc) 
		Serial.println("error in usb accessory");
	acc_type = USB_TYPE;
}

ADKAccessory::ADKAccessory(int pinRX, int pinTX, int baud)
{
	pBTAcc = new SoftwareSerial(pinRX, pinTX);
	if(!pBTAcc) 
		Serial.println("error in SoftwareSerial");
	baudrate = baud;
	acc_type = BT_TYPE;
}

ADKAccessory::~ADKAccessory()
{
	if(acc_type == USB_TYPE && pAcc) {
		delete pAcc;
		pAcc = NULL;
	} else if(acc_type == BT_TYPE && pBTAcc) {
		delete pBTAcc;
		pBTAcc = NULL;
	}
}

void ADKAccessory::powerOn()
{
	if(acc_type == USB_TYPE) pAcc->powerOn();
	else if(acc_type == BT_TYPE) {
		// use 19200
		// 9600 did not work 
		pBTAcc->begin(baudrate);
	}

}

bool ADKAccessory::available()
{
	if(acc_type == USB_TYPE)
		return pAcc->isConnected();
	else if(acc_type == BT_TYPE) {
		return pBTAcc->available();
	}
	return false;
}

int ADKAccessory::read(byte *msg, int bufLen) 
{
	int len;
	// read length first
	if(acc_type == USB_TYPE) {
		// read at once for usb case
		byte temp[256];

		len = pAcc->read(temp, bufLen, 1);
		if(len == -1 || temp[0] < 1 || len != (temp[0] + 1) || temp[0] > bufLen) return -1;
		else {
			for(int i = 0; i < temp[0]; i++) msg[i] = temp[i+1];
			return temp[0];
		}

	} else if(acc_type == BT_TYPE) {
		// BT case, data is delivered together and splitted
		len = pBTAcc->read();
		Serial.print("length=");
		Serial.println(len);
		if(len < 1) return -1;
		int i, c;
		i = 0;
		while(i < len) {
			c = pBTAcc->read();
			if(c == -1) continue;
			if(i >= bufLen) return -1;
			msg[i] = (byte)c;  
			i++;
		}
		if(i == 0) return -1;
		else return i;
	}
	return -1; // not supported acc type
}

int ADKAccessory::write(byte *msg, int len)
{
	int res;
	byte temp[256+1];

	if(acc_type == USB_TYPE) {
		// write length of data first
		temp[0] = len;
		for(int i = 1; i < len; i++) {
			temp[i] = msg[i];
		}

		pAcc->write(temp, len + 1);			
		// now send the data itself
		return pAcc->write(msg, len);			
	} else if(acc_type == BT_TYPE)	{
		int i;
		pBTAcc->write(len);
		for(i = 0; i < len; i++) {
			res = pBTAcc->write(msg[i]);
			
			if(res == 0) {
				Serial.println("write failed in ADKAcessory::write");
				return -1;
			}
		}	
		if(i == 0) return -1;			
		else return i;
	}
	return -1; // not supported acc type
}

