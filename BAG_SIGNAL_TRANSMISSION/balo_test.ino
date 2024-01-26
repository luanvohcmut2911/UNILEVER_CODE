//Tay trái: servo1, DC6
//Tay phải: servo2, DC5
#define sensor 21

#define PUL1 45
#define PUL2 46
#define DIR1 29
#define DIR2 47

#define CHA2 7
#define CHB2 6
#define RPWM5 48
#define LPWM5 50
#define LEN5 A15
#define REN5 A14
#define LIS5 13
#define RIS5 A12

#define CHA1 9
#define CHB1 8
#define RPWM6 43
#define LPWM6 41
#define LEN6 49
#define REN6 51
#define LIS6 53
#define RIS6 52

#define LIS1 A1
#define RIS1 A0
#define LIS2 A7
#define RIS2 A6

#define LEN1 A3
#define REN1 A2
#define LEN2 A9
#define REN2 A8
#define LEN3 13
#define REN3 12
#define LEN4 4
#define REN4 5

#define LPWM1 A5
#define RPWM1 A4
#define LPWM2 A11
#define RPWM2 A10
#define LPWM3 11
#define RPWM3 10
#define LPWM4 2
#define RPWM4 3 
unsigned long timemark;
int signal;
int qty;
int PreviousLine, CurrentLine;
int balo_speed = 200; // 0-255
int servo_speed =200; // 0-255
float angleleft=0;
float angleright=0;

void Stop() {
  digitalWrite(LPWM1,LOW);
  digitalWrite(RPWM1,LOW);
  digitalWrite(LPWM2,LOW);
  digitalWrite(RPWM2,LOW);
  digitalWrite(LPWM5,LOW);
  digitalWrite(RPWM5,LOW);
  digitalWrite(LPWM6,LOW);
  digitalWrite(RPWM6,LOW);
}

void LineChoosing() {
  if ( qty > 0 && qty <= 4) 
    CurrentLine = 4;
  else if ( qty > 4 && qty <= 8)
    CurrentLine = 3;
  else if ( qty > 8 && qty <= 12)
    CurrentLine = 2;
  else if ( qty > 12 && qty <= 16)
    CurrentLine = 1;
}

void drop(int CurrentLine) {
  if (CurrentLine == 1) {
    analogWrite(LPWM1,0);
    analogWrite(RPWM1,balo_speed);
  }
  if (CurrentLine == 2) {
    analogWrite(LPWM2,0);
    analogWrite(RPWM2,balo_speed);
  }
  if (CurrentLine == 3) {
    analogWrite(LPWM5,0);
    analogWrite(RPWM5,balo_speed);
  }
  if (CurrentLine == 4) {
    analogWrite(LPWM6,0);
    analogWrite(RPWM6,balo_speed);
  }
}

void balo() {
  while ( digitalRead(sensor) == 1 ) {
    if( millis() - timemark > 1000 ) {
      qty--;
      timemark = millis();
    }
    LineChoosing();
    if ( CurrentLine != PreviousLine ) {
      Stop();
      drop(CurrentLine);
      PreviousLine = CurrentLine;
    }
  }
  Stop();
  qty--;
  signal = 0;
}

float angleLeft() {
  if ( CHA1 ==1 && CHB1 == 0) angleleft += 22.5/168;
  else if( CHA1==1 && CHB1 ==1) angleleft -= 22.5/168;
  return angleleft;
}

float angleRight() {
  if ( CHA2 ==1 && CHB2 == 0) angleright += 22.5/168;
  else if( CHA2==1 && CHB2 ==1) angleright -= 22.5/168;
  return angleright;
}

void hand() {
  //Stepper phải up
  digitalWrite(DIR1,LOW);
  delayMicroseconds(5);
  digitalWrite(PUL1,LOW);
  delayMicroseconds(2.5);
  for (int i=1; i<=599; i++) {
    digitalWrite(PUL1,HIGH);
    delayMicroseconds(2.5);
    // digitalWrite(PUL1,LOW);
    // delayMicroseconds(2.5);
  }
  digitalWrite(PUL1,HIGH);
  //Stepper trái up
  digitalWrite(DIR2,HIGH);
  delayMicroseconds(5);
  digitalWrite(PUL2,LOW);
  delayMicroseconds(2.5);
  for (int i=1; i<=599; i++) {
    digitalWrite(PUL2,HIGH);
    delayMicroseconds(2.5);
    digitalWrite(PUL2,LOW);
    delayMicroseconds(2.5);
  }
  digitalWrite(PUL2,HIGH);

  //servo trái
  while (angleLeft() >=-60) {
    digitalWrite(LPWM4,LOW);
    analogWrite(RPWM4,servo_speed);
  }
  while (angleLeft() <=60) {
    analogWrite(LPWM4,servo_speed);
    digitalWrite(RPWM4,LOW);
  }
  while (angleLeft() >=-60) {
    digitalWrite(LPWM4,LOW);
    analogWrite(RPWM4,servo_speed);
  }
  while (angleLeft() <=60) {
    analogWrite(LPWM4,servo_speed);
    digitalWrite(RPWM4,LOW);
  }
  while (angleLeft() >=0) {
    digitalWrite(LPWM4,LOW);
    analogWrite(RPWM4,servo_speed);
  }
    digitalWrite(LPWM4,LOW);
    digitalWrite(RPWM4,LOW);

  //servo phải
  while (angleRight() <=60) {
   analogWrite(LPWM3,servo_speed);
    digitalWrite(RPWM3,LOW);
  } 
  while (angleRight() >=-60) {
    digitalWrite(LPWM3,LOW);
    analogWrite(RPWM3,servo_speed);   
  }
  while (angleRight() <=60) {
    analogWrite(LPWM3,servo_speed);
    digitalWrite(RPWM3,LOW);
  } 
  while (angleRight() >=-60) {
    digitalWrite(LPWM3,LOW);
    analogWrite(RPWM3,servo_speed);
  }
  while (angleRight() <=0) {
    analogWrite(LPWM3,servo_speed);
    digitalWrite(RPWM3,LOW);
  }
  digitalWrite(LPWM3,LOW);
  digitalWrite(RPWM3,LOW);
  //Stepper phải down
  digitalWrite(DIR1,HIGH);
  delayMicroseconds(5);
  digitalWrite(PUL1,LOW);
  delayMicroseconds(2.5);
  for (int i=1; i<=599; i++) {
    digitalWrite(PUL1,HIGH);
    delayMicroseconds(2.5);
    digitalWrite(PUL1,LOW);
    delayMicroseconds(2.5);
  }
  digitalWrite(PUL1,HIGH);
  //Stepper trái down
  digitalWrite(DIR2,LOW);
  delayMicroseconds(5);
  digitalWrite(PUL2,LOW);
  delayMicroseconds(2.5);
  for (int i=1; i<=599; i++) {
    digitalWrite(PUL2,HIGH);
    delayMicroseconds(2.5);
    digitalWrite(PUL2,LOW);
    delayMicroseconds(2.5);
  }
  digitalWrite(PUL2,HIGH);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PUL1,OUTPUT);
  pinMode(PUL2,OUTPUT);
  pinMode(DIR1,OUTPUT);
  pinMode(DIR2,OUTPUT);
  pinMode(CHA1,INPUT);
  pinMode(CHB1,INPUT);
  pinMode(CHA2,INPUT);
  pinMode(CHB2,INPUT);
  pinMode(sensor,INPUT);
  pinMode(LIS1,OUTPUT);
  pinMode(RIS1,OUTPUT);
  pinMode(LIS2,OUTPUT);
  pinMode(RIS2,OUTPUT);
  pinMode(LIS6,OUTPUT);
  pinMode(RIS6,OUTPUT);
  pinMode(LIS5,OUTPUT);
  pinMode(RIS5,OUTPUT);
  pinMode(LEN1,OUTPUT);
  pinMode(REN1,OUTPUT);
  pinMode(LEN2,OUTPUT);
  pinMode(REN2,OUTPUT);
  pinMode(LEN3,OUTPUT);
  pinMode(REN3,OUTPUT);
  pinMode(LEN4,OUTPUT);
  pinMode(REN4,OUTPUT);
  pinMode(LPWM4,OUTPUT);
  pinMode(RPWM4,OUTPUT);
  pinMode(LEN6,OUTPUT);
  pinMode(REN6,OUTPUT);
  pinMode(LPWM6,OUTPUT);
  pinMode(RPWM6,OUTPUT);
  pinMode(LEN5,OUTPUT);
  pinMode(REN5,OUTPUT);
  pinMode(LPWM5,OUTPUT);
  pinMode(RPWM5,OUTPUT);

  digitalWrite(LIS1,LOW);
  digitalWrite(RIS1,LOW);
  digitalWrite(LIS2,LOW);
  digitalWrite(RIS2,LOW);
  digitalWrite(LIS6,LOW);
  digitalWrite(RIS6,LOW);
  digitalWrite(LIS5,LOW);
  digitalWrite(RIS5,LOW);
  
  digitalWrite(LEN1,HIGH);
  digitalWrite(REN1,HIGH);
  digitalWrite(LEN2,HIGH);
  digitalWrite(REN2,HIGH);
  digitalWrite(LEN3,HIGH);
  digitalWrite(REN3,HIGH);
  digitalWrite(LEN4,HIGH);
  digitalWrite(REN4,HIGH);
  digitalWrite(LEN6,HIGH);
  digitalWrite(REN6,HIGH);
  digitalWrite(LEN5,HIGH);
  digitalWrite(REN5,HIGH);

  signal= 0 ;
  PreviousLine = 0;
  qty = 16;
}

void loop() {
  // put your main code here, to run repeatedly:
  // if ( Serial.available() > 0 )
  //   signal = Serial.read();
  //   Serial.println(signal);
  // if ( signal == 10 )
  // {
  //   timemark = millis();
  //   balo();
  // } else if ( signal == 50) {
  //   hand();
  // }
  // balo();
  // analogWrite(LPWM1,0);
  // analogWrite(RPWM1,150);
  // Serial.println(qty);
  // Serial.println(digitalRead(sensor));
  // hand();
  digitalWrite(DIR2,HIGH);
  delayMicroseconds(5);
  digitalWrite(PUL2,LOW);
  delayMicroseconds(2.5);
  digitalWrite(PUL2,HIGH);
  delayMicroseconds(2.5);
}
