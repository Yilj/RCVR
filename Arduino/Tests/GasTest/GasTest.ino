const int gasPin = A1;
const int numReadings = 10;

int gasReadings[numReadings];
int readIndex = 0;

int gasTotal = 0;
int gasAverage = 0;
int gasValue = 0;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < numReadings; i++) 
  {
    gasReadings[i] = 0;
  }
}

void loop() {
  gasTotal = gasTotal - gasReadings[readIndex];
  gasReadings[readIndex] = analogRead(gasPin);
  gasTotal = gasTotal + gasReadings[readIndex];

  gasAverage = gasTotal / numReadings;

  gasValue = constrain(gasAverage, 315, 500);
  gasValue = map(gasValue, 315, 500, 0, 185);

  Serial.println('$' + String(gasValue) + ' ' + String(30) + ';');
  //Serial.println('$' + String(gasValue) + ' ' + String(gasReadings[readIndex]) + ';');

  readIndex = readIndex + 1;
  if (readIndex >= numReadings)
    readIndex = 0;
}
