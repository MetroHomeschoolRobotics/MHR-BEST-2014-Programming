#pragma config(Sensor, dgtl2,  rightls,        sensorTouch)
#pragma config(Sensor, dgtl3,  leftls,         sensorTouch)
#pragma config(Motor,  port2,           motorl,        tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           slider,        tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port4,           claw,          tmotorServoStandard, openLoop)
#pragma config(Motor,  port5,           clawfront,     tmotorServoStandard, openLoop)
#pragma config(Motor,  port8,           arm,           tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           motorr,        tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/********************************************************\
|This is the best code ;) for the 2014 BEST competition. |
|Written by: Tanner, Dalton, George, Caleb, and          |
|whoever wants to help with programming. If you need help|
|programming, or just want an advisor please come to MHR |
|and ask the main programmers.If they have time, they    |
|will help you, otherwise, they will assign a subordinate|
|to assist you. Thank You.                               |
\********************************************************/

/******************************************************************************************************\
|Button5U + right joystick = strait (only front & back)                                                |
|Button5D + both joysticks (tank drive) (left joystick = left wheel, vice varsa for the right joystick)|
|Button6U + left joystick (up & down) = arm up & down                                                  |
|Button6D + left joystick (left and right) = arm left & right                                          |
|Button7L = reset the arm/tower to the left of the robot                                               |
|Button8L = close the claw                                                                             |
|Button8R = open  the claw                                                                             |
|Right Joystick (without tank drive) = normal drive                                                    |
|Left joystick = nothing, without any button being pressed                                             |
\******************************************************************************************************/

//[1,2]
float ranalogx, lanalogx;
float ranalogy, lanalogy;
bool on = true;// Bool (boolean) means: a binary variable, having two possible values called �true� and �false.� (I Googled it)
float thresh = 15;
float thresh2 = thresh + 5;
int lowerbound = -128;//front claw/opens claw/ raise to open more
int upperbound = 127;//front claw/closes claw/ raise to close more
//int lowerbound2 = -60;//back claw
//int upperbound2 = 25;//back claw
int speed = 1; // Raise to slow
bool reset = false;


task drive(){// drive code duh
	while(on){
		if(vexRT(Btn5U)){
			ranalogx = 0;
		}
		if(vexRT(Btn5D)) {
			motor[motorr] = ranalogy;
			motor[motorl] = lanalogy;
			} else if(vexRT(Btn7D)) {
			if(abs(ranalogx)/abs(ranalogy)>15){
				ranalogy = 0;
			}
			motor[motorr] = (-ranalogy)+(ranalogx);// right wheel
			motor[motorl] = (-ranalogy)+(-ranalogx);// left wheel
			} else {
			if(abs(ranalogx)/abs(ranalogy)>15){
				ranalogy = 0;
			}
			motor[motorr] = (ranalogy)+(-ranalogx);
			motor[motorl] = (ranalogy)+(ranalogx);
		}
	}
}
task manipulator() {
	while(on) {

		if(vexRT[Btn6U]) {// move the claws up and down
			motor[arm] = lanalogy;
			} else {
			motor[arm] = 0;
		}

		if(vexRT[Btn6D]){
			if((SensorValue(rightls) == 0)&&(lanalogx>0)){//This line of code is for the sliders on the robot.
				//We need it for not breaking the manipulators by coming off the robot.
				motor[slider] = lanalogx;
				} else if((SensorValue(leftls) == 0)&&(lanalogx<0)){
				motor[slider] = lanalogx;
				} else if((SensorValue(leftls) != 0)&&(SensorValue(rightls) != 0)){
				motor[slider] = lanalogx;
				} else {
				motor[slider] = 0;
			}
			} else {
			motor[slider] = 0;
		}


		if(vexRT(Btn7L)) {
			if (SensorValue(leftls) && reset == false) {
				reset = true;
				} else if (reset == true) {
				reset = false;
			}
		}

		while(reset == true) {
			motor[slider] = 127;
			if(vexRT[Btn6U]) {// move the claws up and down
				motor[arm] = lanalogy;
				} else {
				motor[arm] = 0;
			}
			if(vexRT(Btn6D)) {
				motor[slider] = 0;
				reset = false;
			}
			if(!SensorValue(leftls)) {
				motor[slider] = 0;
				reset = false;
			}
		}

		if(vexRT(Btn8L)&&motor[claw]>lowerbound){// back claw (open the claw)
			motor[claw] = motor[claw] - 2;
			wait1Msec(speed);
			} else if(vexRT(Btn8R)&&motor[claw]<upperbound) {// back claw (close the claw)
			motor[claw] = motor[claw] + 2;
			wait1Msec(speed);
		}

		/*	if(vexRT(Btn8L)&&motor[clawfront]>lowerbound2){// front claw (open the claw)
		motor[clawfront] = motor[clawfront] -1;
		wait1Msec(speed);
		} else if(vexRT(Btn8R)&&motor[clawfront]<upperbound2) {//  claw (close the claw)
		motor[clawfront] = motor[clawfront] +1;
		wait1Msec(speed);
		}*/
	}
}

task main(){
	startTask(drive);
	startTask(manipulator);
	while(on){
		ranalogx = vexRT(Ch1);
		if(abs(ranalogx)<thresh2){
			ranalogx = 0;
		}
		ranalogy = vexRT(Ch2);
		if(abs(ranalogy)<thresh){
			ranalogy = 0;
		}
		lanalogy = vexRT(Ch3);
		if((abs(lanalogy)<thresh)&&!vexRT(Btn5D)){
			lanalogy = 0;
		}
		lanalogx = vexRT(Ch4);
		if(abs(lanalogx)<thresh){
			lanalogx = 0;
		}
	}
}
