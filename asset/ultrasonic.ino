setup() {
  pinMode(9, OUTPUT);
  pinMode(8, INPUT);
)

loop() {
  digitalWrite(9, HIGH);
  delayMicroseconds(10);
  digitalWrite(9, LOW);
  int pulseWidth = pulseIn(8, HIGH);
  long distance = pulseWidth/29/2;
}
