int ENA = 5;  //muss PWM - Pin sein wenn du die Geschwindigkeit ändern willst
int IN1 = 7;
int IN2 = 8;

int ENB = 6;  // muss auch PWM Pin sein, wenn du die Geschwindigkeit ändern willst
int IN3 = 9;
int IN4 = 10;

int ECHO_PIN_LEFT = 11;
int TRIGGER_PIN_LEFT = 12;

int ECHO_PIN_RIGHT = 3;
int TRIGGER_PIN_RIGHT = 4;


void setup() {

  Serial.begin(9600);
  Serial.println("Boote Tank");

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ECHO_PIN_LEFT, INPUT);
  pinMode(TRIGGER_PIN_LEFT, OUTPUT);

  pinMode(ECHO_PIN_RIGHT, INPUT);
  pinMode(TRIGGER_PIN_RIGHT, OUTPUT);
  delay(500);

  
  Serial.println("Boot Complete");
}

void left_forward(int speedleft) {
  digitalWrite(ENB, LOW);

  Serial.println("left motor forward");
  analogWrite(ENA, speedleft);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void left_backward(int speedleft) {
  digitalWrite(ENB, LOW);

  Serial.println("left motor backward");
  analogWrite(ENA, speedleft);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void right_forward(int speedright) {
  digitalWrite(ENA, LOW);

  Serial.println("right motor forward");
  analogWrite(ENB, speedright);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right_backward(int speedright) {
  digitalWrite(ENA, LOW);

  Serial.println("right Motor backward");
  analogWrite(ENB, speedright);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void all_forward(int tankspeed) {
  Serial.println("all motors forward");
  
  analogWrite(ENA, tankspeed);
  analogWrite(ENB, tankspeed);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void all_backward(int tankspeed) {
  Serial.println("all motors backward");
  
  analogWrite(ENA, tankspeed);
  analogWrite(ENB, tankspeed);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void full_stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}

long get_distance_left() {
  long distance = 0;
  long duration = 0;
  
    digitalWrite(TRIGGER_PIN_LEFT, LOW);
    delay(5);
    digitalWrite(TRIGGER_PIN_LEFT, HIGH);
    delay(10);
    digitalWrite(TRIGGER_PIN_LEFT, LOW);
    duration = pulseIn(ECHO_PIN_LEFT, HIGH); //returns micros
    //Serial.println(duration);
    distance = ((duration/2.) *0.03432)+0.5; // +0.5 zum Runden, die 0.03432 ergeben sich aus der Schallgeschwindigkeit in Zentimeter und die /2. bedeutet der Weg wurde ja zweimal zurückgelegt, zum Hindernis und zurück
    Serial.print("Entfernung: ");
    Serial.print(distance);
    Serial.println(" cm");

    return distance;
}

long get_distance_right() {
  long distance = 0;
  long duration = 0;
  
    digitalWrite(TRIGGER_PIN_RIGHT, LOW);
    delay(5);
    digitalWrite(TRIGGER_PIN_RIGHT, HIGH);
    delay(10);
    digitalWrite(TRIGGER_PIN_RIGHT, LOW);
    duration = pulseIn(ECHO_PIN_RIGHT, HIGH); //returns micros
    //Serial.println(duration);
    distance = ((duration/2.) *0.03432)+0.5; // +0.5 zum Runden, die 0.03432 ergeben sich aus der Schallgeschwindigkeit in Zentimeter und die /2. bedeutet der Weg wurde ja zweimal zurückgelegt, zum Hindernis und zurück
    Serial.print("Entfernung: ");
    Serial.print(distance);
    Serial.println(" cm");

    return distance;
}

void loop() {
  long distance_left = get_distance_left();
  long distance_right = get_distance_right();

  if ((distance_left <= 10) || (distance_right <=10)) {
    full_stop();
  }

  else
    all_forward(150);
}
