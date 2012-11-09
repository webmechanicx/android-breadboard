#ifndef __ProcessInput_h__
#define __ProcessInput_h__

#include "Arduino.h"
#include "pins_arduino.h"

#include "AndroidAccessory.h"
#include "CommandPacket.h"

extern AndroidAccessory acc;

#define COMMAND_BASE            (0x00)  

// from 0x00~0x20 
// most popular command
#define COMMAND_PIN_MODE         (COMMAND_BASE+0x01)
#define COMMAND_DIGITAL_READ   (COMMAND_BASE+0x02)
#define COMMAND_DIGITAL_WRITE   (COMMAND_BASE+0x03)
#define COMMAND_ANALOG_READ    (COMMAND_BASE+0x04)
#define COMMAND_ANALOG_WRITE    (COMMAND_BASE+0x05)
#define COMMAND_DELAY           (COMMAND_BASE+0x06)

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

extern void ProcessInput(byte *msg, int len);
extern void ProcessUserCommand(CommandPacket& pktRead, AndroidAccessory &acc, int shield_id); 

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
