#pragma config(Motor,  port2,           lmotor1,       tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           lmotor2,       tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//[1,2]


task drive(){
	if(vexRT(Ch2)>1||vexRT(Ch2)<-1){
		motor[lmotor1] = vexRT(Ch2);
	}
	if(vexRT(Ch3)>1||vexRT(Ch3)<-1){
		motor[lmotor2] = vexRT(Ch3);
	}
}


task main(){
	startTask(drive);
	while(true){
		wait1Msec(1);
	}
}
