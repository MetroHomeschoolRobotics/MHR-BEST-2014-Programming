#pragma config(Motor,  port2,           motorl,        tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           shoulder,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           claw,          tmotorServoStandard, openLoop, reversed)
#pragma config(Motor,  port8,           arm,           tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           motorr,        tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//[1,2]
float ranalogx, lanalogx;
float ranalogy, lanalogy;
bool on = true;
float thresh = 15;
float thresh2 = thresh + 5;
int lowerbound = -70;
int upperbound = 90;
int speed = 1; // Raise to slow
float track = 0;
float track2 = 0;


task drive(){
	while(on){
		if(vexRT(Btn5U)){
			ranalogx = 0;
		}
		if(vexRT(Btn5D)) {
			motor[motorr] = ranalogy;
			motor[motorl] = lanalogy;
			} else if(vexRT(Btn7D)) {
			if(abs(ranalogx)/abs(ranalogy)>15){ ranalogy = 0; }
			motor[motorr] = (-ranalogy)+(ranalogx);
			motor[motorl] = (-ranalogy)+(-ranalogx);
			} else {
			if(abs(ranalogx)/abs(ranalogy)>15){ ranalogy = 0; }
			motor[motorr] = pow(((ranalogy)+(-ranalogx)),1.8)/48.5;
			motor[motorl] = pow(((ranalogy)+(ranalogx)),1.8)/48.5;
		}
		if(vexRT[Btn6D]){
			motor[motorr] = (-lanalogx)/2;
			motor[motorl] = (lanalogx)/2;
		}
		track = (pow(((ranalogy)+(-ranalogx)),1.8))/48.5;
		track2 = (pow(((ranalogy)+(-ranalogx)),1.8));
	}
}
task manipulator() {
	while(on) {
		if(vexRT[Btn6U]) {
			motor[arm] = lanalogy;
			} else {
			motor[arm] = 0;
		}
		if(vexRT(Btn8R)&&motor[claw]>lowerbound){
			motor[claw] = motor[claw] - 1;
			wait1Msec(speed);
			}else if(vexRT(Btn8L)&&motor[claw]<upperbound){
			motor[claw] = motor[claw] + 1;
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
