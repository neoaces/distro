
task main()
{
	int color = 0;
	while (true) {
		if(getColorName(S4) == colorGreen) {
			color = 1;
			break;
		}
		else if(getColorName(S4) == colorRed) {
			color = 2;
			break;
		}
		else if(getColorName(S4) == colorYellow) {
			color = 3;
			break;
		}
	}
	motor[motorC] = motor[motorD] = 25;
	nMotorEncoder[motorC] = 0;
	while(abs(nMotorEncoder[motorC]) <= 200) {}
	motor[motorC] = motor[motorD] = 0;
	nMotorEncoder[motorB] = 0;
	setMotorTarget(motorB, 950, 40);
	switch (color) {
		case 1:
			motor[motorA] = -25;
			wait1Msec(750);
			motor[motorA] = 0;
			break;
		case 2:
			motor[motorA] = 25;
			wait1Msec(750);
			motor[motorA] = 0;
			break;
		case 3:
			//Assuming sorter is to the right
			setMotorTarget(motorA, 37, 25);
			break;
	}
	waitUntilMotorStop(motorB);
  wait1Msec(1000);
	setMotorTarget(motorB, 0, 40);
	waitUntilMotorStop(motorB);


}
