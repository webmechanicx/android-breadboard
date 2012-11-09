
#include <Max3421e.h>
#include <Usb.h>
#include <ProcessInput.h>

extern float measure_distance(int trigPin, int echoPin);
extern float microsecondsToCentimeters(long microseconds);

void ProcessUserCommand(CommandPacket &pktRead, AndroidAccessory &acc, int shield_id)
{
    int sensor;
    
    sensor = pktRead.readInt();
    
    if(sensor == SHIELD_ULTRASONIC) {
        int trigPin, echoPin;  
        DebugPrintln("ProcessUserCommand: Ultrasonic Sensor ");
        if(pktRead.readInt() ==  SHIELD_ULTRASONIC_MEASURE) {
            DebugPrintln("ProcessUserCommand: Ultrasonic Sensor Measure ");
            trigPin = (int) (pktRead.readByte());
            echoPin = (int) (pktRead.readByte());
            DebugPrint("TrigPin: ");
            DebugPrintln(trigPin);
            DebugPrint(", EchoPin: ");
            DebugPrint(echoPin);
	    
            float dist = measure_distance(trigPin, echoPin);
            DebugPrint(", Dist: ");
            int iDist = (int)dist;
            DebugPrintln(iDist);
//	    if(iDist < 30) {
 //           	Serial.print(", Dist: ");
  //          	Serial.println(iDist);
//	    }
            SendReplyInt(acc, shield_id, REPLY_OK, iDist);
	    
        }
    } else if(sensor == SHIELD_DC_MOTOR) {
        DebugPrintln("ProcessUserCommand: DC motor ");  
        if(pktRead.readInt() == SHIELD_DC_MOTOR_MOVE)
        {
            int dir_pin, dir, speed_pin, speed;
            
            dir_pin = pktRead.readByte();
            dir = pktRead.readByte();
            speed_pin = pktRead.readByte();
            speed = pktRead.readInt();
      
	    /*
            Serial.print("Move: dir_pin(");
            Serial.print(dir_pin);
            Serial.print("), ");
            Serial.print("dir(");
            Serial.print(dir);
            Serial.print("), ");
            Serial.print("speed pin(");
            Serial.print(speed_pin);
            Serial.print("), speed = ");
            Serial.println(speed);
	    */
            
            digitalWrite(dir_pin, dir);  // left motor direction
            analogWrite(speed_pin, speed); // left motor speed

          //  delay(100);  
        } 
    }  else if(sensor == SHIELD_TWO_WHEEL_ROBOT) {
        int command;
	int speed;
	int leftDirPin, leftSpeedPin, rightDirPin, rightSpeedPin;
	int leftdir, leftspeed, rightdir, rightspeed;

        DebugPrintln("ProcessUserCommand: Two Wheel Robot "); 

	command = pktRead.readInt();

	leftDirPin = pktRead.readByte();
	leftSpeedPin = pktRead.readByte();
	rightDirPin = pktRead.readByte();
	rightSpeedPin = pktRead.readByte();

	if(command == SHIELD_TWO_WHEEL_ROBOT_FORWARD) {
       		speed = pktRead.readInt();
		leftdir = HIGH;
		leftspeed = speed;		
		rightdir  = HIGH;
		rightspeed = speed;

	} else if(command == SHIELD_TWO_WHEEL_ROBOT_BACKWARD) {
       		speed = pktRead.readInt();
		leftdir = LOW ;
		leftspeed = speed;		
		rightdir  = LOW;
		rightspeed = speed;
	} else if(command == SHIELD_TWO_WHEEL_ROBOT_STOP) {
		leftdir = LOW;
		leftspeed = 0;		
		rightdir  = LOW;
		rightspeed = 0;
	} else if(command == SHIELD_TWO_WHEEL_ROBOT_LEFT) {
       		speed = pktRead.readInt();
		leftdir = LOW;
		leftspeed = 0;		
		rightdir  = HIGH;
		rightspeed = speed;
	} else if(command == SHIELD_TWO_WHEEL_ROBOT_RIGHT) {
       		speed = pktRead.readInt();
		leftdir = HIGH;
		leftspeed = speed;		
		rightdir  = LOW;
		rightspeed = 0;		
	} else {
		DebugPrint("ProcessUserCommand: Unknown command. command = ");
		DebugPrintln(command);
		return;
	}


	digitalWrite(leftDirPin, leftdir);  // left motor direction
	digitalWrite(rightDirPin, rightdir);  // right motor direction
        analogWrite(leftSpeedPin, leftspeed); // left motor speed
        analogWrite(rightSpeedPin, rightspeed); // right motor speed

    } else {
        DebugPrint("ProcessUserCommand: Unknown shield, id =  ");  
        DebugPrintln(sensor);  
    } 

}

float measure_distance(int trigPin, int echoPin)
{
  long duration;
  float cm;
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  // mesaure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  duration =  pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);

  return cm;  
}

float microsecondsToCentimeters(long microseconds)
{
  return microseconds / 27.6233 / 2.0;
}

