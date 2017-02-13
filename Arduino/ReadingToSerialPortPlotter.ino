const int numReadings = 9;

int gasReadings[numReadings];
int steeringReadings[numReadings];

int readIndex = 0;

int gasTotal = 0;
int steeringTotal = 0;

int gasAverage = 0;
int steeringAverage = 0;

int gasPin = A1;
int steeringPin = A0;

void setup()
{
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) 
  {
    gasReadings[thisReading] = 0;
    steeringReadings[thisReading] = 0;
  }
}

void loop()
{
  gasTotal = gasTotal - gasReadings[readIndex];
  steeringTotal = steeringTotal - steeringReadings[readIndex];

  int gasRading = analogRead(gasPin);
  int steeringReading = analogRead(steeringPin);
  
  gasReadings[readIndex] = gasRading;
  steeringReadings[readIndex] = steeringReading;

  gasTotal = gasTotal + gasReadings[readIndex];
  steeringTotal = steeringTotal + steeringReadings[readIndex];

  readIndex = readIndex + 1;

  if (readIndex >= numReadings) 
  {
    readIndex = 0;
  }

  gasAverage = gasTotal / numReadings;
  steeringAverage = steeringTotal / numReadings;

  //Test
  gasAverage = map(gasAverage, 300, 530, 0, 100);
  
  Serial.println('$' + String(gasAverage) + ' ' + String(gasRading + 20) + ';');
  //Serial.println('$' + String(steeringAverage) + ' ' + String(steeringReading) + ';');
  
  delay(10);
}
