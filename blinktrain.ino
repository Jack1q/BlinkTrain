int pins[] = {13, 12, 3, 11, 2, 8, 5, 6};

const int trigPin = 10;
const int echoPin = 9;

bool isForward;
int currentPin;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  isForward = true;
  currentPin = 0;
}

void loop() {
  // forwardBlinkTrain(0);
  int distance = getDistance();
  if (distance <= 10) {
    isForward = !isForward;
    delay(300);
    Serial.println("Changed Direction!");
  }
  if (isForward) {
    if (currentPin < 8) {
      blink(currentPin);
      currentPin++;
    }
    else {
     blink(0);
     currentPin = 1;
    }
  }
  else {
    if (currentPin >= 0) {
      blink(currentPin);
      currentPin--;
    }
    else {
      blink(7);
      currentPin = 6;
    }
  }
  }


int getDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long time = pulseIn(echoPin, HIGH);
  // speed of sound = 343 meters / second = 0.0343 cm / microsecond (in dry air at room temp)
  // we can calculate the distance travelled by dividing the time by 2 
  // (because sound travels to the object, then returns, thus covering the same distance twice)
  // and then multiplying that times the speed of sound in cm / microsecond
  int distance = time / 2 * 0.0343;

  return distance;
}

void blink(int pin) {
  pin = pins[pin];
  digitalWrite(pin, HIGH);
  delay(100);
  digitalWrite(pin, LOW);
  delay(100);
}






















void staggeredBlink() {
  int distance = getDistance();
  int ledsToLight = 0;
  if (distance >= 34) 
    ledsToLight++;
  if (distance >= 30)
    ledsToLight++;
  if (distance >= 26)
    ledsToLight++;
  if (distance >= 22)
    ledsToLight++;
  if (distance >= 18)
    ledsToLight++;
  if (distance >= 14)
    ledsToLight++;
  if (distance >= 10)
    ledsToLight++;
  if (distance >= 6)
    ledsToLight++;

  for (int i = 0; i < ledsToLight; i++) {
    digitalWrite(pins[i], HIGH);
  }
  for (int i = ledsToLight; i < 8; i++) {
    digitalWrite(pins[i], LOW);
  }
}






// only lights up while object is within 20 cm
void syncBlink() {
  int distance = getDistance();
  while (distance <= 20) {
    for (int i = 0; i < 8; i++) {
      digitalWrite(pins[i], HIGH);
  }
  distance = getDistance();
  }
  for (int i = 0; i < 8; i++) {
    digitalWrite(pins[i], LOW);
  }
  
}

void randomBlink() {
  int randomNumberA = pins[rand() % 8];
  int randomNumberB = pins[rand() % 8];
  while (randomNumberA == randomNumberB) {
    randomNumberB = pins[rand() % 8];
  }
  digitalWrite(randomNumberA, HIGH);
  digitalWrite(randomNumberB, HIGH);
  delay(250);
  digitalWrite(randomNumberA, LOW);
  digitalWrite(randomNumberB, LOW);
  delay(250);


}

void forwardBlinkTrain(int current) {
    for (int i = current; i < 8; i++) {
      int distance = getDistance();
      if (distance <= 15) {
        reverseBlinkTrain(i);
        break;
      }
      else {
        blink(pins[i]);
      }
  }
}

void reverseBlinkTrain(int current) {
  for (int i = current; i >= 0; i--) {
    int distance = getDistance();
    if (distance > 10) {
      forwardBlinkTrain(i);
      break;
    }
    else {
      blink(pins[i]);
    }
  }
}
