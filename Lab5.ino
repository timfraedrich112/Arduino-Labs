#include <TimerOne.h>

//pins
int bluePin = 4;
int greenPin = 5;
int redPin = 6;

//other variables
int arr[50];
int nextTask = 1;
int count = 0;
bool task1 = false;
bool task2 = false;
bool task3 = false;

void setup() {
  Serial.begin(9600);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);

  //interupts
  Timer1.initialize(50000);
  Timer1.attachInterrupt(tasks);
}

void tasks(void) {
  if (nextTask == 1) { // TASK 1
    green();
    task1 = true;
    if (task3) {
      Serial.println("T1 waiting");
    }
    while (task3) {
      delay(1);
    }
    nextTask = 2;
    for (int i = 0; i < 50; i++) {
      int num = random(1, 50);
      arr[i] = num;
      Serial.print("T1 made number: ");
      Serial.println(num);
    }
    if (!task2) {
      Serial.println("T1 waiting");
    }
    task1 = false;

  } else if (nextTask == 2) { // TASK 2
    blue();
    task2 = true;
    if (task1) {
      Serial.println("T2 Waiting");
    }
    while (task1) {
      delay(1);
    }
    for(int i = 0; i < 49; i++) { //bubble sort
      for(int j = 0; j < 49; j++) {
        if(arr[j] > arr[j+1]) {
          int temp = arr[j];
          arr[j] = arr[j+1];
          arr[j+1] = temp;
        }
      }
      Serial.println("T2 bubble run");
    }
    Serial.println("T2 done");
    nextTask = 3;
    task2 = false;

  } else if (nextTask == 3) { // TASK 3
    red();
    task3 = true;
    if (task2) {
      Serial.println("T3 Waiting");
    }
    while (task2) {
      delay(1);
    }
    if (count < 50) {
      Serial.print(count);
      Serial.print(":\t");
      Serial.println(arr[count]);
      count++;
    } else {
      nextTask = 1;
      count = 0;
      task3 = false;
    }
  }
}

void green() {
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, LOW);
}

void blue() {
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
  digitalWrite(redPin, LOW);
}

void red() {
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, HIGH);
}

void off() {
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, LOW);
}