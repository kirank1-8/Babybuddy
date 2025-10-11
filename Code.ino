int ledPin = 9;
int ldrFront = A0;   // Direct light
int ldrSide = A1;    // Side scattering
int vibration = 2;   // SW-420
int tdsPin = A2;     // TDS analog
int greenLed = 3;
int yellowLed = 4;
int redLed = 5;
int buzzer = 6;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); digitalWrite(ledPin,HIGH);
  pinMode(greenLed, OUTPUT); pinMode(yellowLed, OUTPUT); pinMode(redLed, OUTPUT);
  pinMode(buzzer, OUTPUT); pinMode(vibration, INPUT);
}

void loop() {
  float front = analogRead(ldrFront)*(5.0/1023.0);
  float side = analogRead(ldrSide)*(5.0/1023.0);
  int vib = digitalRead(vibration);
  float tds = analogRead(tdsPin)*(5.0/1023.0); // simple linear approximation

  // Multi-sensor fusion formula
  float pollutionIndex = (5.0 - front) + side + vib*0.5 + tds*0.5;

  Serial.print("Pollution Index: "); Serial.println(pollutionIndex);
  Serial.print("TDS (approx): "); Serial.println(tds*200); // convert to ppm approx

  if(pollutionIndex < 3.0){
    digitalWrite(greenLed,HIGH); digitalWrite(yellowLed,LOW); digitalWrite(redLed,LOW);
    digitalWrite(buzzer,LOW);
  } else if(pollutionIndex < 6.0){
    digitalWrite(greenLed,LOW); digitalWrite(yellowLed,HIGH); digitalWrite(redLed,LOW);
    digitalWrite(buzzer,LOW);
  } else {
    digitalWrite(greenLed,LOW); digitalWrite(yellowLed,LOW); digitalWrite(redLed,HIGH);
    digitalWrite(buzzer,HIGH);
  }

  delay(500);
}
