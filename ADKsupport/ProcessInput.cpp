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

#include <Max3421e.h>
#include <Usb.h>
#include <ProcessInput.h>

#undef DebugPrintln
#define DebugPrintln(a) Serial.println(a)

void ProcessInput(ADKAccessory &acc, byte *inMsg, int len)
{
  int pin, mode, value;
  int shield_id;
  int command;
  long d;

  CommandPacket pktRead(inMsg, len);

  shield_id = pktRead.readInt(); // shield id for response
  command = pktRead.readInt();
  switch(command) {
  case COMMAND_PIN_MODE :
      pin = pktRead.readByte();
      mode = pktRead.readByte();
      DebugPrintln("ProcessInput: Pinmode ");
      DebugPrintln("pin = ");
      DebugPrintln(pin);
      DebugPrintln(" mode = ");
      DebugPrintln(mode);
      pinMode(pin, mode);
      break;

  case COMMAND_DIGITAL_READ:
      pin = pktRead.readByte();
      value = digitalRead(pin);
      // send data to mobile
      DebugPrintln("ProcessInput: DigitalRead ");
      DebugPrintln("pin = ");
      DebugPrintln(pin);
      DebugPrintln(" value = ");
      DebugPrintln(value);
      SendReplyInt(acc, shield_id, REPLY_OK, value);
      break;

  case COMMAND_DIGITAL_WRITE:
      pin = pktRead.readByte();
      value = pktRead.readByte();
      digitalWrite(pin, value);
      DebugPrintln("ProcessInput: DigitalWrite ");
      DebugPrintln("pin = ");
      DebugPrintln(pin);
      DebugPrintln(" value = ");
      DebugPrintln(value);
      break;

  case COMMAND_ANALOG_READ:
       pin = pktRead.readByte();
       value = analogRead(pin);
       // send data to mobile
       DebugPrintln("ProcessInput: AnalogRead ");
       DebugPrintln("pin = ");
       DebugPrintln(pin);
       DebugPrintln(" value = ");
       DebugPrintln(value);
       // 0~1023
       SendReplyInt(acc, shield_id, REPLY_OK, value);
       break;

  case COMMAND_ANALOG_WRITE:
       pin = pktRead.readByte();
       value = pktRead.readByte(); // 0~255
       DebugPrintln("ProcessInput: AnalogWrite ");
       DebugPrintln("pin = ");
       DebugPrintln(pin);
       DebugPrintln(" value = ");
       DebugPrintln(value);
       analogWrite(pin, value);
       break;

  case COMMAND_DELAY:
       d = pktRead.readLong();
       DebugPrintln("ProcessInput: Delay ");
       DebugPrintln(" value = ");
       DebugPrintln(d); 
       delay(d);
       break;

  case COMMAND_DELAYMICROS:
       value = pktRead.readInt();
       DebugPrintln("ProcessInput: DelayMicroseconds ");
       DebugPrintln(" value = ");
       DebugPrintln(value); 
       delayMicroseconds(value);
       break;

  case COMMAND_MILLIS:
       DebugPrintln("ProcessInput: Millis ");
       d = millis();
       SendReplyLong(acc, shield_id, REPLY_OK, d);
       break;

  case COMMAND_MICROS:
       DebugPrintln("ProcessInput: Micros ");
       d = micros();
       SendReplyLong(acc, shield_id, REPLY_OK, d);
       break;

  case COMMAND_USER:
       DebugPrintln("ProcessInput: User Command command id = ");
       DebugPrintln(command);
       ProcessUserCommand(pktRead, acc, shield_id);
       break;

  default:
       DebugPrintln("ProcessInput: Unknown command:");
       DebugPrintln(command);
       break;
  }
}

