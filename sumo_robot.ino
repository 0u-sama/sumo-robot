const int trigpin = 11;
const int echopin = 10;
const int motorAp1 = 9;
const int motorAp2 = 8;
const int motorA = 7;
const int motorBp1 = 6;
const int motorBp2 = 5;
const int motorB = 4;
const int ir_front = 2;
const int ir_back = 3;

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

  Serial.begin(115200);
}

void loop() {
  ir();
  if (visible_enemy()){
    forward();
    Serial.println("attack");
  }else{
    search("tornado");
    Serial.println("Search Function");
  };
}

bool visible_enemy(){
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  long duration = pulseIn(echopin, HIGH);
  int distance = duration * 0.034 / 2;
  if (distance <= 160){
    return true;} else 
    {return false;
    };
}

void search(String strategy){
  if (strategy == "tornado"){
    forward_right();
  } else if (strategy == "charge"){
    forward();
  } else if (strategy == "snake"){
    forward();
    delayMicroseconds(500);
    forward_right();
    delayMicroseconds(500);
    forward_left();
    delayMicroseconds(500);
  };
}

void forward(){
  analogWrite(motorA, 255);
  analogWrite(motorB, 255);
  digitalWrite(motorAp1, HIGH);
  digitalWrite(motorAp2, LOW);
  digitalWrite(motorBp1, HIGH);
  digitalWrite(motorBp2, LOW);
}

void backword(){
  analogWrite(motorA, 255);
  analogWrite(motorB, 255);
  digitalWrite(motorAp1, LOW);
  digitalWrite(motorAp2, HIGH);
  digitalWrite(motorBp1, LOW);
  digitalWrite(motorBp2, HIGH);
}

void forward_right(){
  analogWrite(motorA, 255);
  digitalWrite(motorAp1, HIGH);
  digitalWrite(motorAp2, LOW);
  analogWrite(motorB, 0);
  digitalWrite(motorBp2, LOW);
  digitalWrite(motorBp2, LOW);
}

void forward_left(){
  analogWrite(motorA, 0);
  digitalWrite(motorAp1, LOW);
  digitalWrite(motorAp2, LOW);
  analogWrite(motorB, 255);
  digitalWrite(motorBp2, HIGH);
  digitalWrite(motorBp2, LOW);
}

void backword_left(){
  analogWrite(motorA, 0);
  digitalWrite(motorAp1, LOW);
  digitalWrite(motorAp2, LOW);
  analogWrite(motorB, 255);
  digitalWrite(motorBp2, LOW);
  digitalWrite(motorBp2, HIGH);
}

void backword_right(){
  analogWrite(motorA, 255);
  digitalWrite(motorAp1, LOW);
  digitalWrite(motorAp2, HIGH);
  analogWrite(motorB, 0);
  digitalWrite(motorBp2, LOW);
  digitalWrite(motorBp2, LOW);
}

void ir(){
  int front_ir = digitalRead(ir_front);
  int back_ir = digitalRead(ir_back);

  if (front_ir == HIGH){
    backword();
    delayMicroseconds(700);
    forward_right();
    delayMicroseconds(500);
  } else if(back_ir == HIGH){
    backword_right();
    delayMicroseconds(500);
  };
}