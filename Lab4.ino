//pins
int bluePin = 4;
int greenPin = 5;
int redPin = 6;
int joyPinX = A0;
int joyPinY = A1;
int tempPin = A5;
int lightPin = A3;

//other variables
char read;
char xPos, yPos;
int colorInput = 0;
int bright = 0;
int outputColor;

void setup() {
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);

  pinMode(tempPin, INPUT);
  pinMode(lightPin, INPUT);
  pinMode(joyPinX, INPUT);
  pinMode(joyPinY, INPUT);

  Serial.begin(9600);
}

void loop() {
  int temp = analogRead(tempPin);

  double light = analogRead(lightPin);
  //from testing -> upper limit: 1023

  double brightness = ((1023 - light) / 1023) * 100;

  int joyX = analogRead(joyPinX);
  if (joyX > 530) xPos = 'E';
  else if (joyX < 500) xPos = 'W';
  else xPos = '0';

  int joyY = analogRead(joyPinY); 
  if (joyY > 530) yPos = 'S';
  else if (joyY < 500) yPos = 'N';
  else yPos = '0';

  int amount = Serial.available();
  if (amount > 0) {
    read = Serial.read();
    switch(read) {
      case 't': 
        Serial.print("Temperature: ");
        Serial.println(temp); 
        break;
      case 'l': 
        Serial.print("Light: "); 
        Serial.print(brightness);
        Serial.println("%");
        break;
      case 'j': 
        Serial.print("Joy: (");
        Serial.print(xPos);
        Serial.print(", ");
        Serial.print(yPos);
        Serial.println(")");
        break;
      case 'r': 
        colorInput = 1;
        outputColor = redPin;
        break;
      case 'g': 
        colorInput = 1;
        outputColor = greenPin;
        break;
      case 'b': 
        colorInput = 1;
        outputColor = bluePin;
        break;
      case '1':
        if (colorInput == 1) {
          colorInput = 0;
          bright = 25;
        }
        break;
      case '2':
        if (colorInput == 1) {
          colorInput = 0;
          bright = 130;
        }
        break;
      case '3':
        if (colorInput == 1) {
          colorInput = 0;
          bright = 255;
        }
        break;
      case 'o': 
        analogWrite(outputColor, bright); //255 is placeholder, make it use proper brightness
        delay(1000);
        analogWrite(outputColor, 0); //turn off light
        delay(300);
        break;
      default:
        break;
    }
  }

  //test temp
  //Serial.print("Temp: ");
  //Serial.println(temp);

  //test light and brightness percent
  //Serial.print("Light: ");
  //Serial.print(light);
  //Serial.print(", ");
  //Serial.println(brightness);

  //test joystick
  //Serial.print("Joy: (");
  //Serial.print(xPos);
  //Serial.print(", ");
  //Serial.print(yPos);
  //Serial.println(")");
  

  //delay(1000);
}