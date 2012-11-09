
#include <Max3421e.h>
#include <Usb.h>
#include <ProcessInput.h>

void ProcessInput(byte *inMsg, int len)
{
  int pin, mode, value;
  int shield_id;
  int command;

  CommandPacket pktRead(inMsg, len);

  shield_id = pktRead.readInt(); // shield id for response
  command = pktRead.readInt();
  switch(command) {
  case COMMAND_PIN_MODE :
      pin = pktRead.readByte();
      mode = pktRead.readByte();
      DebugPrint("ProcessInput: Pinmode ");
      DebugPrint("pin = ");
      DebugPrint(pin);
      DebugPrint(" mode = ");
      DebugPrintln(mode);
      pinMode(pin, mode);
      break;

  case COMMAND_DIGITAL_READ:
      pin = pktRead.readByte();
      value = digitalRead(pin);
      // send data to mobile
      DebugPrint("ProcessInput: DigitalRead ");
      DebugPrint("pin = ");
      DebugPrint(pin);
      DebugPrint(" value = ");
      DebugPrintln(value);
      SendReplyInt(acc, shield_id, REPLY_OK, value);
      break;

  case COMMAND_DIGITAL_WRITE:
      pin = pktRead.readByte();
      value = pktRead.readByte();
      digitalWrite(pin, value);
      DebugPrint("ProcessInput: DigitalWrite ");
      DebugPrint("pin = ");
      DebugPrint(pin);
      DebugPrint(" value = ");
      DebugPrintln(value);
      break;
  case COMMAND_ANALOG_READ:
       pin = pktRead.readByte();
       value = analogRead(pin);
       // send data to mobile
       DebugPrint("ProcessInput: AnalogRead ");
       DebugPrint("pin = ");
       DebugPrint(pin);
       DebugPrint(" value = ");
       DebugPrintln(value);
       SendReplyInt(acc, shield_id, REPLY_OK, value);
       break;

  case COMMAND_ANALOG_WRITE:
       pin = pktRead.readByte();
       value = pktRead.readInt();
       DebugPrint("ProcessInput: AnalogWrite ");
       DebugPrint("pin = ");
       DebugPrint(pin);
       DebugPrint(" value = ");
       DebugPrintln(value);
       analogWrite(pin, value);
       break;

  case COMMAND_DELAY:
       value = pktRead.readByte();
       DebugPrint("ProcessInput: Delay ");
       DebugPrint(" value = ");
       DebugPrintln(value); 
       delay(value);
       break;

  case COMMAND_USER:
       DebugPrint("ProcessInput: User Command command id = ");
       DebugPrintln(command);
       ProcessUserCommand(pktRead, acc, shield_id);
       break;

  default:
       DebugPrint("ProcessInput: Unknown command:");
       DebugPrintln(command);
       break;
  }
}

