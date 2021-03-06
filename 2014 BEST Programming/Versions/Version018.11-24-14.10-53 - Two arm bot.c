#pragma config(Motor,  port2,           motorl,        tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           arm2,          tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           claw,          tmotorServoStandard, openLoop)
#pragma config(Motor,  port5,           clawright,     tmotorServoStandard, openLoop)
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

//[1,2]
float ranalogx, lanalogx;
float ranalogy, lanalogy;
bool on = true;// Bool (boolean) means: a binary variable, having two possible values called �true� and �false.� (I Googled it)
float thresh = 15;
float thresh2 = thresh + 5;
int lowerbound = -73;//large claw/opens claw/ raise to open more
int upperbound = 90;//large claw/closes claw/ raise to close more
int lowerbound2 = -73;//small claw
int upperbound2 = 90;//small claw
int speed = 1; // Raise to slow


task drive(){// drive code duh
	while(on){
		if(vexRT(Btn5D)){
			ranalogx = 0;
		}
		if(vexRT(Btn7D)) {
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

		if(vexRT[Btn5U]) {// move the arm up and down
			motor[arm] = lanalogy;


			if(vexRT(Btn8L)&&motor[claw]>lowerbound){// back claw (open the claw)
				motor[claw] = motor[claw] - 1;
				wait1Msec(speed);
				} else if(vexRT(Btn8R)&&motor[claw]<upperbound) {// back claw (close the claw)
				motor[claw] = motor[claw] + 1;
				wait1Msec(speed);
			}
			} else {
			motor[arm] = 0;
		}

		if(vexRT[Btn6U]) {// move the claws up and down
			motor[arm2] = lanalogy;
			if(vexRT(Btn8L)&&motor[clawright]>lowerbound){// back claw (open the claw)
				motor[clawright] = motor[clawright] - 1;
				wait1Msec(speed);
				} else if(vexRT(Btn8R)&&motor[clawright]<upperbound) {// back claw (close the claw)
				motor[clawright] = motor[clawright] + 1;
				wait1Msec(speed);
			}
			} else {
			motor[arm2] = 0;
		}
			if(vexRT(Btn8L)&&motor[clawright]>lowerbound2){// clawright (open the claw)
		motor[clawright] = motor[clawright] - 1;
		wait1Msec(speed);
		} else if(vexRT(Btn8R)&&motor[clawright]<upperbound2) {//  clawright (close the claw)
		motor[clawright] = motor[clawright] + 1;
		wait1Msec(speed);
		}
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
