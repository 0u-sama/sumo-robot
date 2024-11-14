const int trigpin = 11;
const int echopin = 10;
const int motorAp1 = 7;
const int motorAp2 = 8;
const int motorA = 9;
const int motorBp1 = 6;
const int motorBp2 = 4;
const int motorB = 5;
const int ir_front = 2;
const int ir_back = 3;
long duration;
int distance;
int front_ir;
int back_ir;

void setup() {
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(motorAp1, OUTPUT);
  pinMode(motorAp2, OUTPUT);
  pinMode(motorA, OUTPUT);
  pinMode(motorBp1, OUTPUT);
  pinMode(motorBp2, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(ir_front, INPUT);
  pinMode(ir_back, INPUT);
  Serial.begin(9600);
}

void loop() {
  //forward();
  bool enemyDetected = visible_enemy();

  //ir();
  if (enemyDetected){
    forward();
    
  }else{
    search("snake");
    
  }; 
}

bool visible_enemy() {
  long totalDistance = 0;
  int validReadings = 0;

  // Take multiple readings for stability
  for (int i = 0; i < 5; i++) {
    // Trigger the ultrasonic sensor
    digitalWrite(trigpin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin, LOW);

    duration = pulseIn(echopin, HIGH);
    distance = duration * 0.034 / 2;

    // Ignore zero or out-of-range values
    if (distance > 0 && distance < 200) { // Adjust upper limit as needed
      totalDistance += distance;
      validReadings++;
    }

    delay(50); // Small delay between readings for stability
  }

  // Calculate the average distance if we got valid readings
  if (validReadings > 0) {
    distance = totalDistance / validReadings;
    Serial.println(distance);
  } else {
    Serial.println("No valid reading");
    return false; // No valid distance measured
  }

  // Return true if the averaged distance is within 50 cm
  return distance <= 50;
}


void search(String strategy){
  if (strategy == "tornado"){
    forward_right();
  } else if (strategy == "charge"){
    forward();
  } else if (strategy == "snake"){
    forward();
    delay(2000);
    forward_right();
    delay(3000);
    forward_left();
    delay(3000);
  };
}

void forward(){
 // stop(1000);
  analogWrite(motorA, 200);
  analogWrite(motorB, 200);
  digitalWrite(motorAp1, HIGH);
  digitalWrite(motorAp2, LOW);
  digitalWrite(motorBp1, HIGH);
  digitalWrite(motorBp2, LOW);
}

void backword(){
  //stop(1000);
  analogWrite(motorA, 255);
  analogWrite(motorB, 255);
  digitalWrite(motorAp1, LOW);
  digitalWrite(motorAp2, HIGH);
  digitalWrite(motorBp1, LOW);
  digitalWrite(motorBp2, HIGH);
}

void forward_right(){
  //stop(1000);
  analogWrite(motorA, 200);
  digitalWrite(motorAp1, HIGH);
  digitalWrite(motorAp2, LOW);
  analogWrite(motorB, 0);
  digitalWrite(motorBp1, LOW);
  digitalWrite(motorBp2, LOW);
}

void forward_left(){
  //stop(1000);
  analogWrite(motorB, 200);
  digitalWrite(motorBp1, HIGH);
  digitalWrite(motorBp2, LOW);
  analogWrite(motorA, 0);
  digitalWrite(motorAp1, LOW);
  digitalWrite(motorAp2, LOW);
}

void backword_left(){
  //stop(1000);
  analogWrite(motorB, 255);
  digitalWrite(motorBp1, LOW);
  digitalWrite(motorBp2, HIGH);
  analogWrite(motorA, 0);
  digitalWrite(motorAp1, LOW);
  digitalWrite(motorAp2, LOW);
}

void backword_right(){
  //stop(1000);
  analogWrite(motorA, 255);
  digitalWrite(motorAp1, LOW);
  digitalWrite(motorAp2, HIGH);
  analogWrite(motorB, 0);
  digitalWrite(motorBp1, LOW);
  digitalWrite(motorBp2, LOW);
  
}

void ir(){
  front_ir = digitalRead(ir_front);
  back_ir = digitalRead(ir_back);


  if (front_ir == 0){
    backword();
    delay(3000);
    forward_right();
    delay(1500);
  } else if(back_ir == 0){
    backword_right();
    delay(1500);
  };
  stop(0);
}

void stop(long stop_time) {
  analogWrite(motorA, 0);
  digitalWrite(motorAp1, LOW);
  digitalWrite(motorAp2, LOW);
  analogWrite(motorB, 0);
  digitalWrite(motorBp1, LOW);
  digitalWrite(motorBp2, LOW);

  delay(stop_time);
}
