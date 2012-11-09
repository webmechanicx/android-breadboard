/*
 */

#include "Arduino.h"
#include "pins_arduino.h"

#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h> // for acc access
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
    temp = (msg[index] << 24) + (msg[index+1] << 16) + (msg[index+2] << 8) + (msg[index+3]); 
    index += 4;
    return temp;
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

void CommandPacket::Flush(AndroidAccessory &acc)
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

void SendReplyInt(AndroidAccessory &acc, int shield_id, int ret, int value)
{
  byte msg[MAX_LEN];
  CommandPacket pktWrite(msg, MAX_LEN);

  pktWrite.writeInt(shield_id);
  pktWrite.writeByte((byte)ret);
  pktWrite.writeInt(value);
  pktWrite.Flush(acc);
//  Serial.println("reply sent");
}
