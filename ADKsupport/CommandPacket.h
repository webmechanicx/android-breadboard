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

#ifndef __CommandPacket_h__
#define __CommandPacket_h__

#include "Arduino.h"
#include "pins_arduino.h"
#include "ADKAccessory.h"

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
    bool isAvailable();	
    byte readByte(); 
    int readInt();
    long readLong();
    byte writeByte(byte b);
    int writeInt(int i);
    int writeLong(long l);
    void Flush(ADKAccessory &acc);
};

extern void SendReplyInt(ADKAccessory &acc, int shield_id, int ret, int value);
extern void SendReplyLong(ADKAccessory &acc, int shield_id, int ret, long d);

#endif /* __CommandPacket_h__ */
