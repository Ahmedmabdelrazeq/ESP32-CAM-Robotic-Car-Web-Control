//*****************************************ESP32 CAM ROBOT *************************arduino nano code

#define TRIG_PIN   6
#define ECHO_PIN   7

#define IN1        8
#define IN2        9
#define IN3        10
#define IN4        11

int distance = 0;
char command = 'v';
char lastCommand = ' ';

unsigned long previousTimeDistance = 0;
const unsigned long intervalDistance = 100; 

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();

  // Update distance measurement at a regular interval
  if (currentTime - previousTimeDistance >= intervalDistance) {
    previousTimeDistance = currentTime;
    distance = getDistance();
    Serial.println(String(distance));
  }

  // Receive commands from Serial input
  if (Serial.available() > 0) {
        Serial.println(String(distance));

    char tempCommand = Serial.read();
    if (tempCommand == 'f' || tempCommand == 'b' || tempCommand == 'l' || tempCommand == 'r' || tempCommand == 'v') {
      command = tempCommand;
    }
  }

  // Execute the command
  executeCommand();
}
bool isMovingForward = false; // Variable to track if the car is moving forward

void executeCommand() {
  // Check if the command has changed
  if (command != lastCommand) {
    // Execute forward command only if distance is greater than 10 cm
    if ((command == 'f') && (distance > 20)) {
      moveForward();
      isMovingForward = true; // Update state to "moving forward"
    } 
    // Execute backward command
    else if (command == 'b') {
      moveBackward();
      isMovingForward = false; // Not moving forward
    } 
    // Execute left turn command
    else if (command == 'l') {
      turnLeft();
      isMovingForward = false; // Not moving forward
    } 
    // Execute right turn command
    else if (command == 'r') {
      turnRight();
      isMovingForward = false; // Not moving forward
    } 
    // Execute stop command
    else if (command == 'v') {
      stopMotors();
      isMovingForward = false; // Not moving forward
    }

    // Update the last command
    lastCommand = command;
  }

  // Stop the car if it's moving forward and distance is less than or equal to 10 cm
  if (isMovingForward && distance <= 10) {
    stopMotors();           // Stop the car
    isMovingForward = false; // Update state to "stopped"
  }
}


int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;
  
  
  return distance;
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
