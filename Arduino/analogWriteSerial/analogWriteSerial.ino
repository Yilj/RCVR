const int steeringPin = A0;
const int gasPin = A1;

int steeringReading;
int gasReading;

int steeringValue;
int gasValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  steeringReading = analogRead(steeringPin);
  gasReading = analogRead(gasPin);
  
  steeringValue = map(steeringReading, 411, 612, 30, 240);
  //steeringValue = map(steeringReading, 0, 1023, 30, 240);
  //gasValue = map(gasReading, 315, 526, 140, 118);
  gasValue = map(gasReading, 315, 330, 140, 50);
  
  steeringValue = constrain(steeringValue, 30, 240);
  gasValue = constrain(gasValue, 50, 140);
  
  analogWrite(3, steeringValue);
  analogWrite(5, gasValue);

  Serial.print(steeringValue);
  Serial.print(" + ");
  Serial.println(gasValue);
}
