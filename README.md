<h2>Digital termometer</h2>
<img width="1272" height="574" alt="image" src="https://github.com/user-attachments/assets/be6e2b33-335f-4ab9-802f-7e84d7a0ef09" />

```
#include <LiquidCrystal_I2C.h>

double voltage = 0;
double temp = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop()
{
  int tempRaw = analogRead(A0);
  voltage = (tempRaw * 5.0) / 1023.0; 
  temp = 100.0 * (voltage - 1.0) + 50.0; 
 
  lcd.setCursor(0, 0);
  lcd.print("C:");
  lcd.print(temp, 2);
  lcd.print(" ");

  delay(500);
}
```

<h2>Ultrasonic Sensor</h2>
<img width="1198" height="611" alt="image" src="https://github.com/user-attachments/assets/079ba67a-0403-4c89-b6aa-809ab99ad6bb" />

```
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  pinMode(9, OUTPUT);
  pinMode(8, INPUT);
  
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void loop()
{
  digitalWrite(9, HIGH);
  delayMicroseconds(10);
  digitalWrite(9, LOW);
  
  int pulseWidth = pulseIn(8, HIGH);
  
  long distance = pulseWidth/29/2;
  
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance, 1);
  lcd.print(" cm   ");

  delay(250);
}
```

<h2>Keypad + LCD</h2>
<img width="690" height="625" alt="image" src="https://github.com/user-attachments/assets/c0ab78b3-9b3f-4a3e-93d6-8a29fb2c9d14" />

```
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  pinMode(9, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.backlight();
  lcd.clear();
}

void loop()
{ 
  lcd.setCursor(0, 0);
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(2, HIGH);
  
  if (digitalRead(9) == LOW) {
    lcd.print(1);
  } else if (digitalRead(8) == LOW) {
    lcd.print(4);
  } else if (digitalRead(7) == LOW) {
    lcd.print(7);
  } else if (digitalRead(6) == LOW) {
    lcd.print("*");
  }
  
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(2, HIGH);
  
  if (digitalRead(9) == LOW) {
    lcd.print(2);
  } else if (digitalRead(8) == LOW) {
    lcd.print(5);
  } else if (digitalRead(7) == LOW) {
    lcd.print(8);
  } else if (digitalRead(6) == LOW) {
    lcd.print(0);
  }
  
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(2, HIGH);
  
  if (digitalRead(9) == LOW) {
    lcd.print(3);
  } else if (digitalRead(8) == LOW) {
    lcd.print(6);
  } else if (digitalRead(7) == LOW) {
    lcd.print(9);
  } else if (digitalRead(6) == LOW) {
    lcd.print("#");
  }
  
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(2, LOW);
  
  if (digitalRead(9) == LOW) {
    lcd.print("A");
  } else if (digitalRead(8) == LOW) {
    lcd.print("B");
  } else if (digitalRead(7) == LOW) {
    lcd.print("C");
  } else if (digitalRead(6) == LOW) {
    lcd.print("D");
  }
  
  delay(100);
}
```
