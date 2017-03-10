const int pin = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0) {
    int val = Serial.parseInt();
    if (Serial.read() == '\n') {
      val = constrain(val, 0, 255);
      analogWrite(pin, val);
      Serial.println(val);
    }
  }
}
