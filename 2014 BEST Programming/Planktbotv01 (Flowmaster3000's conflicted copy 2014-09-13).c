int ANUMBER;

task manumana(){
	//Doo do duh doo doo poo poo
	while(true){

	  if(vexRT(Btn7L)){
	  	motor[LEFHT] = 100;
	  }else{
	  	motor[LEFHT] = 0;
	  }

	  if(vexRT(Btn7R)){
	  	motor[RITE] = 100;
	  }else{
	  	motor[RITE] = 0;
	  }

	  if(vexRT(Btn5D)){
	  	ANUMBER++;
	  	if(ANUMBER>127){

	  	}
	  }
	}
}

task main()

startTask(manumana);
