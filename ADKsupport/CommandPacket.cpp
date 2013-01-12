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
#include "ADKAccessory.h" // for acc access
#include "CommandPacket.h"


CommandPacket::CommandPacket(byte *pInMsg, int length) 
{  // for reading
	msg = pInMsg;
	len = length;
	index = 0;
}

byte CommandPacket::readByte() 
{
    byte temp;
    if(index >= len) {
	    DebugPrintln("CommandPacket:Error in readByte, trying to read beyond limit");
	    return (byte)-1;
    }
    temp = msg[index];
    index++;
    return temp;
}

int CommandPacket::readInt()
{ 
    int temp;
    if(index + 3 >= len) {
	    DebugPrintln("CommandPacket:Error in readInt, trying to read beyond limit");
	    return -1;
    }
    temp = (msg[index] << 24) + (msg[index+1] << 16) + (msg[index+2] << 8) + msg[index+3]; 
    index += 4;
    return temp;
}

long CommandPacket::readLong()
{ 
	long d;
	int high, low;

    if(index + 7 >= len) {
	    DebugPrintln("CommandPacket:Error in readInt, trying to read beyond limit");
	    return -1;
    }


    // low int comes first
    low = (msg[index] << 24) + (msg[index+1] << 16) + (msg[index+2] << 8) + msg[index+3]; 
    high = (msg[index+4] << 24) + (msg[index+5] << 16) + (msg[index+6] << 8) + msg[index+7]; 
    Serial.println("CommandPacket:Read Long low");
    Serial.println(low);
    Serial.println("CommandPacket:Read Long high");
    Serial.println(high);
    d = low + (high << 32); 
    Serial.println("CommandPacket:d=");
    Serial.println(d);
    index += 8;
    return d;
}

byte CommandPacket::writeByte(byte b)
{ 
    if(index < len) {
	msg[index++] = b;
     	return b;
   } else {
	DebugPrintln("CommandPacket:Error in writeByte, buffer limit exceeded");
     	return -1;
   }
} 

int CommandPacket::writeInt(int i)
{
  if(index + 3 < len) {
  	msg[index] = (byte) (i >> 24);
     	msg[index+1] = (byte) (i >> 16);
     	msg[index+2] = (byte) (i >> 8);
     	msg[index+3] = (byte) i;
     	index += 4;     
     	return i;
  } else {
	DebugPrintln("CommandPacket:Error in writeByte, buffer limit exceeded");
     	return -1;
  }
}

int CommandPacket::writeLong(long l)
{
	int high, low;
	low = (int)(l & 0xFFFFFFFF);
	high = (int)((l >> 32) & 0xFFFFFFFF);

  if(index + 7 < len) {
  	msg[index] = (byte) (low >> 24);
     	msg[index+1] = (byte) (low >> 16);
     	msg[index+2] = (byte) (low >> 8);
     	msg[index+3] = (byte) low;

  	msg[index+4] = (byte) (high >> 24);
     	msg[index+5] = (byte) (high >> 16);
     	msg[index+6] = (byte) (high >> 8);
     	msg[index+7] = (byte) high;
     	index += 8;     
     	return 8; // 8 bytes written
  } else {
	DebugPrintln("CommandPacket:Error in writeByte, buffer limit exceeded");
     	return -1;
  }
}

bool CommandPacket::isAvailable()
{
    if(index >= len) return false; // not available 
    else return true;

}

void CommandPacket::Flush(ADKAccessory &acc)
{
	int i;

	Serial.println("In Flush len= ");
	Serial.println(index);

	for(i = 0; i < index; i++) {
		Serial.print("msg[");
		Serial.print(i);
		Serial.print("]=");
		Serial.println(msg[i]);
	}

   	i = acc.write(msg, index);
   	Serial.print(i);
   	Serial.println("bytes sent");
   	index = 0;
};

void SendReplyInt(ADKAccessory &acc, int shield_id, int ret, int value)
{
  byte msg[32];
  CommandPacket pktWrite(msg, 32);

  pktWrite.writeInt(shield_id);
  pktWrite.writeByte((byte)ret);
  pktWrite.writeInt(value);
  pktWrite.Flush(acc);
}

void SendReplyLong(ADKAccessory &acc, int shield_id, int ret, long value)
{
  byte msg[64];
  CommandPacket pktWrite(msg, 64);

  pktWrite.writeInt(shield_id);
  pktWrite.writeByte((byte)ret);
  pktWrite.writeLong(value);
  pktWrite.Flush(acc);
}
