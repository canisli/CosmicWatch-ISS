const int detectorPin = 28;
const int triggerReset = 1;
int max_so_far = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  analogReadResolution(12);

  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH); // Improves ADC aparently, ARDUINO DOESNT NEED THIS

  pinMode(detectorPin, INPUT);

  // pinMode(triggerReset, OUTPUT);
  // digitalWrite(triggerReset, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x = analogRead(detectorPin);

  // max_so_far = max(max_so_far, x);
  // Serial.println(max_so_far);
  
  if (x > 100) {
    Serial.print("Detection: ");
    Serial.println(x);
    // digitalWrite(triggerReset, HIGH);
    delayMicroseconds(10);
    // digitalWrite(triggerReset, LOW);
  }
}
