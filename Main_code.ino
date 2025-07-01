// C++ code
//
int input1 = 0;

int input2 = 0;

int output1 = 0;

int output2 = 0;

int accelerator1 = 0;

int steeringwheel1 = 0;

int i = 0;

int ultrasonicsensor1 = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
  pinMode(3, INPUT);
  pinMode(5, INPUT);
  pinMode(2, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(A3, INPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(A2, INPUT);
  pinMode(4, OUTPUT);
}

void loop()
{
  ultrasonicsensor1 = 0.01723 * readUltrasonicDistance(7, 8);
  Serial.println(ultrasonicsensor1);
  accelerator1 = analogRead(A1);
  steeringwheel1 = analogRead(A0);
  input1 = digitalRead(3);
  input2 = digitalRead(5);
  digitalWrite(2, HIGH);
  digitalWrite(11, HIGH);
  analogWrite(6, 0);
  analogWrite(9, 0);
  if (analogRead(A3) >= 268) {
    digitalWrite(3, HIGH);
    analogWrite(5, 0);
    analogWrite(10, 0);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
  } else {
    digitalWrite(3, LOW);
    if (analogRead(A2) == 1023) {
      digitalWrite(4, HIGH);
      analogWrite(5, 0);
      analogWrite(10, 0);
    } else {
      digitalWrite(4, LOW);
      analogWrite(5, map(accelerator1, 0, 1023, 0, 250));
      analogWrite(10, map(accelerator1, 0, 1023, 0, 250));
      if (ultrasonicsensor1 < 75) {
        analogWrite(5, 10);
        analogWrite(10, 10);
      } else {
        if (analogRead(A0) > 532) {
          analogWrite(5, (map(accelerator1, 0, 1023, 19.2, 230.8) + map(steeringwheel1, 0, 1023, -20.8, 19.2)));
          analogWrite(10, (map(accelerator1, 0, 1023, 19.2, 230.8) - map(steeringwheel1, 0, 1023, -20.8, 19.2)));
        }
        if (analogRead(A0) < 492) {
          analogWrite(5, (map(accelerator1, 0, 1023, 19.2, 230.8) + map(steeringwheel1, 0, 1023, -19.2, 20.8)));
          analogWrite(10, (map(accelerator1, 0, 1023, 19.2, 230.8) - map(steeringwheel1, 0, 1023, -19.2, 20.8)));
        }
        if (analogRead(A0) < 532 && analogRead(A0) > 492) {
          analogWrite(5, map(accelerator1, 0, 1023, 0, 250));
          analogWrite(10, map(accelerator1, 0, 1023, 0, 250));
        }
        if (analogRead(A0) >= 896) {
          digitalWrite(13, HIGH);
        } else {
          digitalWrite(13, LOW);
        }
        if (analogRead(A0) <= 128) {
          digitalWrite(12, HIGH);
        } else {
          digitalWrite(12, LOW);
        }
      }
    }
  }
  delay(10); // Delay a little bit to improve simulation performance
}