const int gasSmoothReadings = 10;

const int steeringPin = A0;
const int gasPin = A1;

int gasReadings[gasSmoothReadings];
int currentIndex = 0;

int gasTotal = 0;
int gasAverage = 0;
int gasValue = 0;

int steeringReading = 0;
int steeringValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  pinMode(13, OUTPUT);

  for (int i = 0; i < gasSmoothReadings; i++)
  {
    gasReadings[i] = 0;
  }

  analogWrite(3, 135);
  analogWrite(5, 140);

  while (digitalRead(2) == HIGH) {
    delay(10);
  }

  for (int i = 140; i > 120; i--) {
    analogWrite(5, i);
    delay(100);
  }

  digitalWrite(13, HIGH);

}

void loop() {
  gasTotal = gasTotal - gasReadings[currentIndex];
  gasReadings[currentIndex] = analogRead(gasPin);
  gasTotal = gasTotal + gasReadings[currentIndex];

  gasAverage = gasTotal / gasSmoothReadings;

  steeringReading = analogRead(steeringPin);

  steeringValue = constrain(steeringReading, 359, 605);
  steeringValue = map(steeringValue, 359, 605, 30, 240);

  gasValue = constrain(gasAverage, 315, 500);
  if (digitalRead(4) == HIGH) {
    gasValue = map(gasValue, 315, 500, 120, 180);
  } else {
    gasValue = map(gasValue, 315, 500, 120, 0);
  }

  //Serial.println('$' + String(gasValue) + ' ' + String(30) + ';');
  //Serial.println('$' + String(gasValue) + ' ' + String(gasReadings[readIndex]) + ';');
  Serial.println('$' + String(gasValue) + ' ' + String(steeringValue) + ';');

  analogWrite(3, steeringValue);
  analogWrite(5, gasValue);

  currentIndex++;
  if (currentIndex >= gasSmoothReadings)
    currentIndex = 0;

  delay(10);
}
