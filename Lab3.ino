#include <EEPROM.h>

//pins
int bluePin = 4;
int greenPin = 5;
int redPin = 6;
int pbtPin = 8;
int tiltPin = 11;

//serial inputs
char read;
int dotInput = 0;
int dashInput = 0;
int idInput = 0;
int speedInput = 0;

//counts
int count = 0;
int idCount = 0;

//input parameters
int prevStatus = 1;
int dotColor = -1;
int dashColor = -1;
int ID[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int dotSpeed = 300;
int dashSpeed = 1200;

void setup() {
  // put your setup code here, to run once:
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(pbtPin, INPUT_PULLUP);
  pinMode(tiltPin, INPUT_PULLUP);

  Serial.begin(9600);

  count = 0;
  idCount = 0;
  for (int i = 0; i < 8; i++) {
    ID[i] = EEPROM.read(i);
  }
  dotColor = EEPROM.read(8);
  dashColor = EEPROM.read(9);
  dotSpeed = EEPROM.read(10) * 100;
  dashSpeed = EEPROM.read(11) * 100;
}

void loop() {
  // put your main code here, to run repeatedly:

  int tilt = digitalRead(tiltPin);
  if(!tilt) { // tilt ball is tilted
    count = 0;
    idCount = 0;
    dotColor = -1;
    dashColor = -1;
    for (int i = 0; i < 8; i++) {
      ID[i] = 0;
    }
    dotSpeed = 300;
    dashSpeed = 1200;
    flashReset();
  }

  int amount = Serial.available();
  if (amount > 0) {
    read = Serial.read();
    switch(read) {
      case 'd': dotInput = 1;
        break;
      case 'D': dashInput = 1;
        break;
      case 'i': idInput = 1;
        break;
      case 's': speedInput = 1;
        break;
      case 'r':
                if (dotInput == 1) 
                {
                  dotColor = redPin;
                  dotInput = 0;
                  if (EEPROM.read(8) != redPin) EEPROM.write(8, redPin);
                }
                else if (dashInput == 1)
                {
                  dashColor = redPin;
                  dashInput = 0;
                  if (EEPROM.read(9) != redPin) EEPROM.write(9, redPin);
                }
                break;
      case 'g':
                if (dotInput == 1) 
                {
                  dotColor = greenPin;
                  dotInput = 0;
                  if (EEPROM.read(8) != greenPin) EEPROM.write(8, greenPin);
                }
                else if (dashInput == 1)
                {
                  dashColor = greenPin;
                  dashInput = 0;
                  if (EEPROM.read(9) != greenPin) EEPROM.write(9, greenPin);
                }
                break;
      case 'b':
                if (dotInput == 1) 
                {
                  dotColor = bluePin;
                  dotInput = 0;
                  if (EEPROM.read(8) != bluePin) EEPROM.write(8, bluePin);
                }
                else if (dashInput == 1)
                {
                  dashColor = bluePin;
                  dashInput = 0;
                  if (EEPROM.read(9) != bluePin) EEPROM.write(9, bluePin);
                }
                break;
      case '1':
                if (idInput == 1)
                {
                  ID[idCount] = 1;
                  if (EEPROM.read(idCount) != ID[idCount]) EEPROM.write(idCount, ID[idCount]);
                  if (idCount < 7) idCount++;
                  else idInput = 0;
                }
                else if (speedInput == 1)
                {
                  dotSpeed = 600;
                  dashSpeed = 2000;
                  speedInput = 0;
                  if (EEPROM.read(10) != (dotSpeed / 100)) EEPROM.write(10, dotSpeed / 100);
                  if (EEPROM.read(11) != (dashSpeed / 100)) EEPROM.write(11, dashSpeed / 100);
                }
                break;
      case '2':
                if (idInput == 1)
                {
                  ID[idCount] = 2;
                  if (EEPROM.read(idCount) != ID[idCount]) EEPROM.write(idCount, ID[idCount]);
                  if (idCount < 7) idCount++;
                  else idInput = 0;
                }
                else if (speedInput == 1)
                {
                  dotSpeed = 300;
                  dashSpeed = 1200;
                  speedInput = 0;
                  if (EEPROM.read(10) != (dotSpeed / 100)) EEPROM.write(10, dotSpeed / 100);
                  if (EEPROM.read(11) != (dashSpeed / 100)) EEPROM.write(11, dashSpeed / 100);
                }
                break;
      case '3':
                if (idInput == 1)
                {
                  ID[idCount] = 3;
                  if (EEPROM.read(idCount) != ID[idCount]) EEPROM.write(idCount, ID[idCount]);
                  if (idCount < 7) idCount++;
                  else idInput = 0;
                }
                else if (speedInput == 1)
                {
                  dotSpeed = 100;
                  dashSpeed = 600;
                  speedInput = 0;
                  if (EEPROM.read(10) != (dotSpeed / 100)) EEPROM.write(10, dotSpeed / 100);
                  if (EEPROM.read(11) != (dashSpeed / 100)) EEPROM.write(11, dashSpeed / 100);
                }
                break;
      case '4':
                if (idInput == 1)
                {
                  ID[idCount] = 4;
                  if (EEPROM.read(idCount) != ID[idCount]) EEPROM.write(idCount, ID[idCount]);
                  if (idCount < 7) idCount++;
                  else idInput = 0;
                }
                break;
      case '5':
                if (idInput == 1)
                {
                  ID[idCount] = 5;
                  if (EEPROM.read(idCount) != ID[idCount]) EEPROM.write(idCount, ID[idCount]);
                  if (idCount < 7) idCount++;
                  else idInput = 0;
                }
                break;
      case '6':
                if (idInput == 1)
                {
                  ID[idCount] = 6;
                  if (EEPROM.read(idCount) != ID[idCount]) EEPROM.write(idCount, ID[idCount]);
                  if (idCount < 7) idCount++;
                  else idInput = 0;
                }
                break;
      case '7':
                if (idInput == 1)
                {
                  ID[idCount] = 7;
                  if (EEPROM.read(idCount) != ID[idCount]) EEPROM.write(idCount, ID[idCount]);
                  if (idCount < 7) idCount++;
                  else idInput = 0;
                }
                break;
      case '8':
                if (idInput == 1)
                {
                  ID[idCount] = 8;
                  if (EEPROM.read(idCount) != ID[idCount]) EEPROM.write(idCount, ID[idCount]);
                  if (idCount < 7) idCount++;
                  else idInput = 0;
                }
                break;
      case '9':
                if (idInput == 1)
                {
                  ID[idCount] = 9;
                  if (EEPROM.read(idCount) != ID[idCount]) EEPROM.write(idCount, ID[idCount]);
                  if (idCount < 7) idCount++;
                  else idInput = 0;
                }
                break;
      case '0':
                if (idInput == 1)
                {
                  ID[idCount] = 0;
                  if (EEPROM.read(idCount) != ID[idCount]) EEPROM.write(idCount, ID[idCount]);
                  if (idCount < 7) idCount++;
                  else idInput = 0;
                }
                break;
      default: //unwanted inputs
        break;
    }
  }

  int status = digitalRead(pbtPin);
  if (prevStatus && !status) // button pressed down
  {
    if (count < 8) 
    {
      outputNumber(ID[count]);
      count++;
    }
    else
    {
      digitalWrite(redPin, HIGH);
      delay(2000);
      digitalWrite(redPin, LOW);
      delay(300);
    }
  }
  prevStatus = status;
} 

void outputNumber(int num) {
  switch(num) {
    case 0:
      dash();
      dash();
      dash();
      dash();
      dash();
      break;
    case 1:
      dot();
      dash();
      dash();
      dash();
      dash();
      break;
    case 2:
      dot();
      dot();
      dash();
      dash();
      dash();
      break;
    case 3:
      dot();
      dot();
      dot();
      dash();
      dash();
      break;
    case 4:
      dot();
      dot();
      dot();
      dot();
      dash();
      break;
    case 5:
      dot();
      dot();
      dot();
      dot();
      dot();
      break;
    case 6:
      dash();
      dot();
      dot();
      dot();
      dot();
      break;
    case 7:
      dash();
      dash();
      dot();
      dot();
      dot();
      break;
    case 8:
      dash();
      dash();
      dash();
      dot();
      dot();
      break;
    case 9:
      dash();
      dash();
      dash();
      dash();
      dot();
      break;
    default: // error, should never happen
      digitalWrite(redPin, HIGH);
      delay(2000);
      digitalWrite(redPin, LOW);
      delay(300);
      break;
  }
}

void dot() {
  digitalWrite(dotColor, HIGH);
  delay(dotSpeed);
  digitalWrite(dotColor, LOW);
  delay(300);
}

void dash() {
  digitalWrite(dashColor, HIGH);
  delay(dashSpeed);
  digitalWrite(dashColor, LOW);
  delay(300);
}

void flashReset() {
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