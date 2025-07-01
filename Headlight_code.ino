// C++ code
//
int ambient = 0;

void setup()
{
  pinMode(5, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(3, OUTPUT);
}

void loop()
{
  digitalWrite(5, HIGH);
  ambient = analogRead(A0);
  Serial.println(ambient);
  if (ambient < 3.25) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }
  delay(10); // Delay a little bit to improve simulation performance
}