#pragma config(Motor,  port2,           lmotorl,       tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           shoulder,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           lmotorr,       tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//[1,2]
float ranalogx, lanalogx;
float ranalogy;
bool on = true;
float thresh = 10;

task drive(){
	while(on){
	/*
	if((vexRT(Ch2)>range)|(vexRT(Ch2)<-range)){
			motor[lmotor1] = vexRT(Ch2);
		}else{
			motor[lmotor1] = 0;
		}
		if((vexRT(Ch3)>range)|(vexRT(Ch3)<-range)){
			motor[lmotor2] = -vexRT(Ch3);
		}else{
			motor[lmotor2] = 0;
		}
	}
	*/

		motor[lmotorr] = ranalogy-ranalogx;
		motor[lmotorl] = ranalogy+ranalogx;
	}
}

task manipulator() {
	while(on) {
		if(vexRT[Btn6U]) {
			motor[shoulder] = lanalogx;
		}
	}
}

task main(){
	startTask(drive);
	startTask(manipulator);
	while(on){
		ranalogx = vexRT(Ch1);
		if(abs(ranalogx)<thresh){
			ranalogx = 0;
		}
		ranalogy = vexRT(Ch2);
		if(abs(ranalogy)<thresh){
			ranalogy = 0;
		}
		lanalogx = vexRT(Ch4);
			if(abs(ranalogy)<thresh){
				lanalogx = 0;
		}
	}
}
