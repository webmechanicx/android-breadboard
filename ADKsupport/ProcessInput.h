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
#ifndef __ProcessInput_h__
#define __ProcessInput_h__

#include "Arduino.h"
#include "pins_arduino.h"
#include "ADKAccessory.h"
#include "CommandPacket.h"

#define COMMAND_BASE            (0x00)  
#define COMMAND_SYSTEM            COMMAND_BASE  

// from 0x00~0x20 
// most popular command
#define COMMAND_PIN_MODE         (COMMAND_BASE+0x01)
#define COMMAND_DIGITAL_READ   (COMMAND_BASE+0x02)
#define COMMAND_DIGITAL_WRITE   (COMMAND_BASE+0x03)
#define COMMAND_ANALOG_READ    (COMMAND_BASE+0x04)
#define COMMAND_ANALOG_WRITE    (COMMAND_BASE+0x05)
#define COMMAND_DELAY           (COMMAND_BASE+0x06)
#define COMMAND_DELAYMICROS     (COMMAND_BASE+0x07)
#define COMMAND_MILLIS           (COMMAND_BASE+0x08)
#define COMMAND_MICROS           (COMMAND_BASE+0x09)

#define COMMAND_USER            (COMMAND_BASE+0xff)

#define SHIELD_TYPE      (0x00)
#define SHIELD_ULTRASONIC       (SHIELD_TYPE)
#define SHIELD_DC_MOTOR    (SHIELD_TYPE + 1)
#define SHIELD_TWO_WHEEL_ROBOT (SHIELD_TYPE + 2)	

// ultrasonic
#define SHIELD_ULTRASONIC_MEASURE  (0x00)  

// dc motor
#define SHIELD_DC_MOTOR_MOVE (0x00) 

// two wheel robot
#define SHIELD_TWO_WHEEL_ROBOT_FORWARD  0x00	
#define SHIELD_TWO_WHEEL_ROBOT_BACKWARD  0x01	
#define SHIELD_TWO_WHEEL_ROBOT_STOP  0x02	
#define SHIELD_TWO_WHEEL_ROBOT_LEFT  0x03	
#define SHIELD_TWO_WHEEL_ROBOT_RIGHT  0x04

#define REPLY_BASE        (0x09)
#define REPLY_OK          (REPLY_BASE)
#define REPLY_NOK         (REPLY_BASE+1)

extern void ProcessInput(ADKAccessory &acc, byte *msg, int len);
extern void ProcessUserCommand(CommandPacket& pktRead, ADKAccessory &acc, int shield_id); 

/*
class a {
private:  
  int i;
public:
  a() { 
    i = 0; 
  }
  
  void inc() {
    i++;
  }
  
  void printa() { 
    Serial.print("i = "); 
    Serial.println(i); 
  }
};

extern void func_b(a &d);
*/
#endif /* __ProcessInput_h__ */
