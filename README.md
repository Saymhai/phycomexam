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

<h2>Keypad + 7 segment(Common Cathod)</h2>
<img width="860" height="592" alt="image" src="https://github.com/user-attachments/assets/85b3a715-8621-4cb2-9386-a3d6233345f1" />

```
int num_array[14][7] = {{ 1,1,1,1,1,1,0 },    // 0
                        { 0,1,1,0,0,0,0 },    // 1
                        { 1,1,0,1,1,0,1 },    // 2
                        { 1,1,1,1,0,0,1 },    // 3
                        { 0,1,1,0,0,1,1 },    // 4
                        { 1,0,1,1,0,1,1 },    // 5
                        { 1,0,1,1,1,1,1 },    // 6
                        { 1,1,1,0,0,0,0 },    // 7
                        { 1,1,1,1,1,1,1 },    // 8
                        { 1,1,1,0,0,1,1 },    // 9
						{ 1,1,1,0,1,1,1 },    // A
						{ 0,0,1,1,1,1,1 },    // b
                        { 1,0,0,1,1,1,0 },    // C
                        { 0,1,1,1,1,0,1 }};   // d
const int segment_a = A0; 
const int segment_b = A1; 
const int segment_c = A2;
const int segment_d = A3;
const int segment_e = A4;
const int segment_f = A5;
const int segment_g = 0;

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
  pinMode(segment_a, OUTPUT);   
  pinMode(segment_b, OUTPUT);   
  pinMode(segment_c, OUTPUT);   
  pinMode(segment_d, OUTPUT);   
  pinMode(segment_e, OUTPUT);   
  pinMode(segment_f, OUTPUT);   
  pinMode(segment_g, OUTPUT);  
}

void loop()
{
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(2, HIGH);
  
  if (digitalRead(9) == LOW) {
    displayDigit(1);
  } else if (digitalRead(8) == LOW) {
    displayDigit(4);
  } else if (digitalRead(7) == LOW) {
    displayDigit(7);
  }
  
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(2, HIGH);
  
  if (digitalRead(9) == LOW) {
    displayDigit(2);
  } else if (digitalRead(8) == LOW) {
    displayDigit(5);
  } else if (digitalRead(7) == LOW) {
    displayDigit(8);
  } else if (digitalRead(6) == LOW) {
    displayDigit(0);
  }
  
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(2, HIGH);
  
  if (digitalRead(9) == LOW) {
    displayDigit(3);
  } else if (digitalRead(8) == LOW) {
    displayDigit(6);
  } else if (digitalRead(7) == LOW) {
    displayDigit(9);
  }
  
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(2, LOW);
  
  if (digitalRead(9) == LOW) {
    displayDigit(10);
  } else if (digitalRead(8) == LOW) {
    displayDigit(11);
  } else if (digitalRead(7) == LOW) {
    displayDigit(12);
  } else if (digitalRead(6) == LOW) {
    displayDigit(13);
  }
}

void displayDigit(int digit) {
  // Set each segment according to the num_array for the given digit
  digitalWrite(segment_a, num_array[digit][0]);
  digitalWrite(segment_b, num_array[digit][1]);
  digitalWrite(segment_c, num_array[digit][2]);
  digitalWrite(segment_d, num_array[digit][3]);
  digitalWrite(segment_e, num_array[digit][4]);
  digitalWrite(segment_f, num_array[digit][5]);
  digitalWrite(segment_g, num_array[digit][6]);
}
```

<h2>7 Segment-2(Common Cathod)</h2>
<img width="990" height="600" alt="image" src="https://github.com/user-attachments/assets/094abcd6-4357-4766-b6c5-209d6c2ee700" />

```
int num_array[10][7] = {  { 1,1,1,1,1,1,0 },    // 0
                          { 0,1,1,0,0,0,0 },    // 1
                          { 1,1,0,1,1,0,1 },    // 2
                          { 1,1,1,1,0,0,1 },    // 3
                          { 0,1,1,0,0,1,1 },    // 4
                          { 1,0,1,1,0,1,1 },    // 5
                          { 1,0,1,1,1,1,1 },    // 6
                          { 1,1,1,0,0,0,0 },    // 7
                          { 1,1,1,1,1,1,1 },    // 8
                          { 1,1,1,0,0,1,1 }};   // 9
const int segment_a = 2; 
const int segment_b = 3; 
const int segment_c = 4;
const int segment_d = 5;
const int segment_e = 6;
const int segment_f = 7;
const int segment_g = 8;
const int digit_left  = 12;  
const int digit_right = 13;


void setup()
{
  pinMode(segment_a, OUTPUT);   
  pinMode(segment_b, OUTPUT);   
  pinMode(segment_c, OUTPUT);   
  pinMode(segment_d, OUTPUT);   
  pinMode(segment_e, OUTPUT);   
  pinMode(segment_f, OUTPUT);   
  pinMode(segment_g, OUTPUT);
  pinMode(digit_left, OUTPUT);
  pinMode(digit_right, OUTPUT);
}

void loop()
{
  int left[4] = {6, 0, 0, 9};
  int right[4] = {8, 7, 1, 4};
  for (int i = 0; i<4; i++) {
    for (int j = 0; j < 10; j++) {

      displayDigit(left[i]);
      digitalWrite(digit_left, LOW);
      digitalWrite(digit_right, HIGH);
      delay(50);

      displayDigit(right[i]);
      digitalWrite(digit_left, HIGH);
      digitalWrite(digit_right, LOW);
      delay(50);
    }
  }
}


void displayDigit(int digit) {
  // Set each segment according to the num_array for the given digit
  digitalWrite(segment_a, num_array[digit][0]);
  digitalWrite(segment_b, num_array[digit][1]);
  digitalWrite(segment_c, num_array[digit][2]);
  digitalWrite(segment_d, num_array[digit][3]);
  digitalWrite(segment_e, num_array[digit][4]);
  digitalWrite(segment_f, num_array[digit][5]);
  digitalWrite(segment_g, num_array[digit][6]);
}
```

<h2>LED Fading</h2>
<img width="761" height="636" alt="image" src="https://github.com/user-attachments/assets/2dcb90d2-a3f3-4153-9488-918f7eb95435" />

```
// C++ code
//
void setup()
{
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop()
{
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
	analogWrite(11, fadeValue);
	delay(30);
	}
  
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 10) {
	analogWrite(10, fadeValue);
	delay(30);
	}
  
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
	analogWrite(6, fadeValue);
	delay(30);
	}
  
  for (int fadeValue = 127 ; fadeValue <= 255; fadeValue += 5) {
	analogWrite(5, fadeValue);
	delay(30);
	}

}
```

<h2>LED(Common Anode)</h2>
<img width="934" height="522" alt="image" src="https://github.com/user-attachments/assets/0becbb5a-db00-41b0-9c15-076c4f8e0621" />

```
void setup()
{
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop()
{
  digitalWrite(9, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(9, LOW);
  digitalWrite(6, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(6, LOW);
  digitalWrite(3, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(3, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(6, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(6, LOW);
  digitalWrite(3, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(9, LOW);
  digitalWrite(6, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(9, HIGH);
}
```


ฉุกเฉิน : https://github.com/Apich01/Code_BookArduino
