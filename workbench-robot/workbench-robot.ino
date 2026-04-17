// ------------------- RELAY MOTOR PINS (Main Drive Motors) -------------------
int relay1 = 2;
int relay2 = 3;
int relay3 = 4;
int relay4 = 5;

// ------------------- ULTRASONIC SENSOR PINS -------------------
const int trigPin = 8;  // Trigger Pin
const int echoPin = 9;  // Echo Pin

// ------------------- HEAD MOTOR (via L298N) -------------------
int headIN1 = 10;
int headIN2 = 11;
int headENA = 6;  // ✅ PWM pin for head motor

// ------------------- VARIABLES -------------------
String data;
long distanceCM;

// ------------------- SETUP -------------------
void setup() {
  Serial.begin(9600);

  // Motor relays
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  // Ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Head motor pins
  pinMode(headIN1, OUTPUT);
  pinMode(headIN2, OUTPUT);
  pinMode(headENA, OUTPUT);

  analogWrite(headENA, 200);  // Adjust head rotation speed

  stopRobot();

  Serial.println("🤖 Aided Robot Ready!");
  Serial.println("Type 'start' to begin visiting benches.");
  Serial.println("---------------------------------------");
}

// ------------------- MOTOR CONTROL -------------------
void moveFront() {
  Serial.println("Moving Forward...");
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
}

void moveLeft() {
  Serial.println("Turning Left...");
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
}

void moveRight() {
  Serial.println("Turning Right...");
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
}

void stopRobot() {
  Serial.println("Stopping...");
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  headScan();  // Move head when robot stops
}

// ------------------- HEAD MOVEMENT -------------------
void headLeft() {
  digitalWrite(headIN1, HIGH);
  digitalWrite(headIN2, LOW);
}

void headRight() {
  digitalWrite(headIN1, LOW);
  digitalWrite(headIN2, HIGH);
}

void headStop() {
  digitalWrite(headIN1, LOW);
  digitalWrite(headIN2, LOW);
}

// Smooth scanning left-right when stopped
void headScan() {
  Serial.println("👀 Scanning surroundings...");
 
  analogWrite(headENA, 180);
  headLeft();
  delay(1000);

  headRight();
  delay(1000);

  headStop();
  Serial.println("🧠 Scan complete.");
}

// ------------------- ULTRASONIC SENSOR -------------------
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 20000); // 20ms timeout
  long cm = duration / 29 / 2;
  return cm;
}

// ------------------- SAFE MOVEMENT -------------------
void safeMoveFront(unsigned long durationMS = 8000) {
  moveFront();
  unsigned long startTime = millis();

  while (millis() - startTime < durationMS) {
    distanceCM = getDistance();
    Serial.print("Distance: ");
    Serial.print(distanceCM);
    Serial.println(" cm");

    if (distanceCM <= 20 && distanceCM != 0) {
      stopRobot();
      Serial.println("⚠️ Obstacle detected! Waiting...");
      while (getDistance() < 20 && getDistance() != 0) {
        delay(100);
      }
      Serial.println("✅ Path clear. Resuming...");
      moveFront();
    }

    delay(100);
  }

  stopRobot();
}

// ------------------- ROUTINE -------------------
void visitBenches() {
  // Bench 1
  //safeMoveFront();
  Serial.println("Reached Bench 1");
  delay(3000); // Stop at bench

  moveRight();
  delay(2000); // Wait after turning
  delay(5000); // ✅ Extra delay before moving forward
  //safeMoveFront();
 
  // Bench 2
  Serial.println("Reached Bench 2");
  delay(3000); // Stop at bench

  moveLeft();
  delay(2000); // Wait after turning
  delay(5000); // ✅ Extra delay before moving forward
  //safeMoveFront();
 
  // Bench 3
  Serial.println("Reached Bench 3");
  delay(3000); // Stop at bench

  moveRight();
  delay(2000); // Wait after turning
  delay(5000); // ✅ Extra delay before moving forward
  //safeMoveFront();
 
  // Bench 4
  Serial.println("Reached Bench 4");
  delay(3000); // Stop at bench

  moveLeft();
  delay(2000); // Wait after turning
  delay(5000); // ✅ Extra delay before moving forward
  //safeMoveFront();
 
  Serial.println("✅ Returned to Rest Position");
  stopRobot();
}

// ------------------- MAIN LOOP -------------------
void loop() {
  if (Serial.available() > 0) {
    data = Serial.readStringUntil('\n');
    data.trim();

    if (data == "start") {
      Serial.println("🏁 Starting Bench Visit Routine...");
      moveFront();
      delay(5000);
      stopRobot();
      delay(3000);
      moveLeft();
      delay(3000);
       stopRobot();
      delay(3000);
      moveFront();
       delay(5000);
       stopRobot();
      delay(2000);
      moveLeft();
      delay(3000);
       stopRobot();
      delay(3000);
       moveFront();
       delay(5000);
       stopRobot();
      delay(2000);
    }
    else if (data == "front") {
      moveFront();
      delay(5000);
      stopRobot();
      delay(3000);
      moveLeft();
      delay(3000);
       stopRobot();
      delay(3000);
      moveFront();
       delay(5000);
       stopRobot();
      delay(2000);
      moveLeft();
      delay(3000);
       stopRobot();
      delay(3000);
       moveFront();
       delay(5000);
       stopRobot();
      delay(2000);
    }
    else if (data == "left") {
      moveLeft();
      delay(2000);
      stopRobot();
    }
    else if (data == "right") {
      moveRight();
      delay(2000);
      stopRobot();
    }
    else if (data == "stop") {
      stopRobot();
    }
  }
}
