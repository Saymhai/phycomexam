int tempRaw = analogRead(A0);
double voltage = (tempRaw * 5.0) / 1023.0;
double temp = (voltage - 0.5) * 100.0;
