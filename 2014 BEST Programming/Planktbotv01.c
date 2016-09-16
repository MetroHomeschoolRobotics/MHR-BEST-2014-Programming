#pragma config(Sensor, in1,    ptest,          sensorPotentiometer)
#pragma config(Motor,  port2,           motor1,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           smotor1,       tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           servo1,        tmotorServoStandard, openLoop)
#pragma config(Motor,  port5,           servo2,        tmotorServoStandard, openLoop)
#pragma config(Motor,  port6,           servo3,        tmotorServoStandard, openLoop)
#pragma config(Motor,  port7,           servo4,        tmotorServoStandard, openLoop)
#pragma config(Motor,  port8,           smotor2,       tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           motor2,        tmotorServoContinuousRotation, openLoop)
//Stolen from 2013 Plankbot

int ANUMBER;
int rightW;
int leftW;
//int leftS;

task manumana(){
	//Doo doo duh do do

	while(true){


		if(rightW<-1){
			motor[motor1] = 177;
			}else if(rightW>1){
			motor[motor1] = -128;
			}else{
			motor[motor1] = 0;
		}

/*
		if(leftW<-1){
			leftS--;
			wait1Msec(2);
			}else if(leftW>1){
			leftS++;
			wait1Msec(2);
			}
			*/
		motor[motor2] = leftW;

		if(vexRT(Btn8R)){
			if(ANUMBER<127){
				ANUMBER++;
				motor[servo3] = ANUMBER;
				wait1Msec(4);
			}
			}else if(vexRT(Btn8L)){
			if(ANUMBER>-128){
				ANUMBER--;
				motor[servo3] = ANUMBER;
				wait1Msec(4);
			}
		}
	}
}

task main(){
	startTask(manumana);
	while(true){
		// NOTHING AT ALL
		rightW = vexRT(Ch2);
		leftW = vexRT(Ch3);
	}
}
