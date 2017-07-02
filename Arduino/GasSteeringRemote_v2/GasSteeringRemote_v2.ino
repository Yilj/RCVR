//SETTINGS
	//gasSmooth
	const int gasSmoothLevel = 10;
	//VALUES
		//INPUTS
			//gas
			const int gasInputNull = 315;
			const int gasInputFull = 500;
			//sterring
			const int steeringInputLeft = 359;
			const int steeringInputRight = 605;
		//OUTPUTS
			//gas
			const int gasOutputInitialtize = 140;
			const int gasOutputNull = 120;
			const int gasOutputForward = 0;
			const int gasOutputBackward = 180;
			//sterring
			const int steeringOutputMiddle = 135;
			const int steeringOutputLeft = 30;
			const int steeringOutputRight = 240;

// PINS
	//outputs
	const int gasOutputPin = 5;
	const int steeringOutputPin = 3;
	const int ledOutputPin = 13;
	//inputs
	const int gasInputPin = A1;
	const int steeringInputPin = A0;
	const int startSwitchInputPin = 4;
	const int backwardSwitchInputPin = 2;

//GLOABAL VARIABLES
	//gas
	int gasReadings[gasSmoothLevel];
	int currentGasReadingIndex = 0;
	int gasTotal = 0;
	int gasAverage = 0;
	int gasValue = 0;
	bool gasDirection = true; //true = forward; false = backward;
	bool gasDirectionSwitched = false;
	int gasTransitionAdjustment = 0;
	int newGasValue = 0;
	//steering
	int steeringReading = 0;
	int steeringValue = 0;


//SETUP
void setup() {
	//PINS
		//outputs
		pinMode(gasOutputPin, OUTPUT);
		pinMode(steeringOutputPin, OUTPUT);
		pinMode(ledOutputPin, OUTPUT);
		//inputs
		pinMode(startSwitchInputPin, INPUT);
		pinMode(backwardSwitchInputPin, INPUT);
		//interrupts
		attachInterrupt(digitalPinToInterrupt(backwardSwitchInputPin), switchGasDirection, CHANGE);

	//VARIABLES
		//gas
		for(int i = 0; i < gasSmoothLevel; i++) {
			gasReadings[i] = 0;
		}

  //SERIAL
    Serial.begin(9600);

	//INITIALIZE
		//gas
		analogWrite(gasOutputPin, gasOutputInitialtize);
		//steering
		analogWrite(steeringOutputPin, steeringOutputMiddle);
		//wait for startSwitchInput
		while(digitalRead(startSwitchInputPin) == HIGH);
		//transition
		for(int i = gasOutputInitialtize; i > gasOutputNull; i--) {
			analogWrite(gasOutputPin, i);
			delay(100);
		}

	//END
		//turn LED on
		digitalWrite(ledOutputPin, HIGH);
}


//LOOP
void loop() {
	//INPUT
		//GAS
			//remove last form total
			gasTotal = gasTotal - gasReadings[currentGasReadingIndex];
			//add current to array
			gasReadings[currentGasReadingIndex] = analogRead(gasInputPin);
			//add current to total
			gasTotal += gasReadings[currentGasReadingIndex];
			//recalculate average
			gasAverage = gasTotal / gasSmoothLevel;
			//increase currentGasReadingIndex
			currentGasReadingIndex++;
			if (currentGasReadingIndex >= gasSmoothLevel)
				currentGasReadingIndex = 0;
		//STEERING
			steeringReading = analogRead(steeringInputPin);

	//CONSTRAIN & MAP
		//GAS
		gasAverage = constrain(gasAverage, gasInputNull, gasInputFull);
		if(gasDirection) { //forward
			gasValue = map(gasAverage, gasInputNull, gasInputFull, gasOutputNull, gasOutputForward);
		}
		else { //backward
			gasValue = map(gasAverage, gasInputNull, gasInputFull, gasOutputNull, gasOutputBackward);
		}
		gasValue += gasTransitionAdjustment;
		//STEERING
		steeringValue = constrain(steeringReading, steeringInputLeft, steeringInputRight);
		steeringValue = map(steeringValue, steeringInputLeft, steeringInputRight, steeringOutputLeft, steeringOutputRight);

	//SWITCH GAS DIRECTION
		//swich gas direction
		if(gasDirectionSwitched) {
			//reset variable
			gasDirectionSwitched = false;
			//switch direction
			gasDirection = !gasDirection;
			//calculate newGasValue
			if(gasDirection) { //forward
				newGasValue = map(gasAverage, gasInputNull, gasInputFull, gasOutputNull, gasOutputForward);
			}
			else { //backward
				newGasValue = map(gasAverage, gasInputNull, gasInputFull, gasOutputNull, gasOutputBackward);
			}
			//clculate gasTransitionAdjustment
			gasTransitionAdjustment = gasValue - newGasValue;
		}
		//update gasTransitionAdjustment
		else if(gasTransitionAdjustment != 0) {
      	//closer than 5
      	if(gasTransitionAdjustment <= 5 || gasTransitionAdjustment >= -5) {
        		gasTransitionAdjustment = 0;
      	}
      	//above 0
			else if(gasTransitionAdjustment > 0) {
				gasTransitionAdjustment -= 5;
			}
      	//below 0
			else {
				gasTransitionAdjustment += 5;
			}
		}

	//OUTPUT
		analogWrite(gasOutputPin, gasValue);
		analogWrite(steeringOutputPin, steeringValue);

  //SERIAL
  Serial.println(String(steeringValue) + ',' + String(gasValue));

	//END
	delay(20);
}


//SWITCH GAS DIRECTION INTERRUPT
void switchGasDirection() {
	gasDirectionSwitched = true;
}
