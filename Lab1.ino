int bluePin = 4;
int greenPin = 5;
int redPin = 6;
int pbtPin = 8;
int tiltPin = 11;
int count = 0;
int prevStatus = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(pbtPin, INPUT_PULLUP);
  pinMode(tiltPin, INPUT_PULLUP);

  Serial.begin(9800);
}

void loop() {
  // put your main code here, to run repeatedly:

  int tilt = digitalRead(tiltPin);
  if(!tilt) { // tilt ball is tilted
    count = 0;
    flashYellow();
  }

  int status = digitalRead(pbtPin);
  if (prevStatus && !status) { // button pressed down
    switch(count) {
      case 0: // 0
        longBlue();
        longBlue();
        longBlue();
        longBlue();
        longBlue();
        break;
      case 1: // 0
        longBlue();
        longBlue();
        longBlue();
        longBlue();
        longBlue();
        break;
      case 2: // 7
        longBlue();
        longBlue();
        shortCyan();
        shortCyan();
        shortCyan();
        break;
      case 3: // 0
        longBlue();
        longBlue();
        longBlue();
        longBlue();
        longBlue();
        break;
      case 4: // 4
        shortCyan();
        shortCyan();
        shortCyan();
        shortCyan();
        longBlue();
        break;
      case 5: // 4
        shortCyan();
        shortCyan();
        shortCyan();
        shortCyan();
        longBlue();
        break;
      case 6: // 6
        longBlue();
        shortCyan();
        shortCyan();
        shortCyan();
        shortCyan();
        break;
      case 7: // 2
        shortCyan();
        shortCyan();
        longBlue();
        longBlue();
        longBlue();
        break;
      default: // error, passed digits
        digitalWrite(redPin, HIGH);
        delay(2000);
        digitalWrite(redPin, LOW);
        delay(500);
        break;
	  }
    count++;
  }
  prevStatus = status;
} 

void longBlue() {
  digitalWrite(bluePin, HIGH);
  delay(1000);
  digitalWrite(bluePin, LOW);
  delay(500);
}

void shortCyan() {
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
  delay(200);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  delay(500);
}

void flashYellow() {
  digitalWrite(greenPin, HIGH);
  digitalWrite(redPin, HIGH);
  delay(100);
  digitalWrite(greenPin, LOW);
  digitalWrite(redPin, LOW);
  delay(100);
  digitalWrite(greenPin, HIGH);
  digitalWrite(redPin, HIGH);
  delay(100);
  digitalWrite(greenPin, LOW);
  digitalWrite(redPin, LOW);
  delay(100);
  digitalWrite(greenPin, HIGH);
  digitalWrite(redPin, HIGH);
  delay(100);
  digitalWrite(greenPin, LOW);
  digitalWrite(redPin, LOW);
  delay(1000);
}