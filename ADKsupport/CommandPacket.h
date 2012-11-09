/*
 */

#ifndef __CommandPacket_h__
#define __CommandPacket_h__

#include "Arduino.h"
#include "pins_arduino.h"
#include "AndroidAccessory.h"

#define MAX_LEN 256 

//#define __DEBUG

#ifdef __DEBUG
#define DebugPrint(a) Serial.print(a)
#define DebugPrintln(a) Serial.println(a)
#else
#define DebugPrint(a) 
#define DebugPrintln(a) 
#endif

class CommandPacket {
private:
    byte *msg;
    int len;
    int index;

public:
    CommandPacket(byte *inMsg, int length);
	
    byte readByte(); 
    int readInt();
    byte writeByte(byte b);
    int writeInt(int i);
    void Flush(AndroidAccessory &acc);
};

extern void SendReplyInt(AndroidAccessory &acc, int shield_id, int ret, int value);

#endif /* __CommandPacket_h__ */
