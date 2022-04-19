#define leftfarSensor A0
#define leftSensor A1
#define centerSensor A2
#define rightSensor A3
#define rightfarSensor A4

int leftReading;
int leftfarReading;
int centerReading;
int rightReading;
int rightfarReading;

#define leaptime 40

#define in1 2
#define in2 3
#define in3 4
#define in4 5 
#define en1 9
#define en2 10


void setup() {
  // put your setup code here, to run once:
  pinMode(leftfarSensor, INPUT);
  pinMode(leftSensor, INPUT);
  pinMode(centerSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(rightfarSensor, INPUT);
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);
  pinMode (in3, OUTPUT);
  pinMode (in4, OUTPUT);
  pinMode (en1, OUTPUT);
  pinMode (en2, OUTPUT);
}

void readSensors()
{
  leftfarReading     = digitalRead(leftfarSensor);
  leftReading     = digitalRead(leftSensor);
  centerReading = digitalRead(centerSensor);
  rightReading   = digitalRead(rightSensor);
  rightfarReading   = digitalRead(rightfarSensor);
}
void loop() {
  // put your main code here, to run repeatedly:
  readSensors();
  if(leftfarReading==0 && leftReading==0 && centerReading==1 && rightReading==0 && rightfarReading==0) 
  { 
    straight();                                                                                    
  }
  if(leftfarReading==0 && leftReading==1 && centerReading==0 && rightReading==0 && rightfarReading==0)
  {
    sleft();
  }
  if(leftfarReading==0 && leftReading==0 && centerReading==0 && rightReading==1 && rightfarReading==0)
  {
    sright();
  }
  else
  {
    lsrbalgo();
  }
}

void lsrbalgo()
{ 
  readSensors();
  if(leftfarReading==1 && rightfarReading==0)
  {
    analogWrite(en1,135);
  analogWrite(en2,140);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
    delay(leaptime);
    readSensors();
    if(leftfarReading==0 && leftReading==0 && centerReading==0 && rightReading==0 && rightfarReading==0)
    {
      turnleft();
    }
    return;
  }
  else if(leftfarReading==1 && rightfarReading==0)
  {
    analogWrite(en1,135);
  analogWrite(en2,140);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
    delay(leaptime);
    readSensors();
    if(leftfarReading==0 && leftReading==0 && centerReading==1 && rightReading==0 && rightfarReading==0)
    {
      turnleft();
    }
    return;
  }
  else if(leftfarReading==0 && leftReading==0 && centerReading==0 && rightReading == 0 && rightfarReading==1)
  {
    analogWrite(en1,135);
  analogWrite(en2,140);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
    delay(leaptime);
    readSensors(); 
    if(leftfarReading==0 && leftReading==0 && centerReading==0 && rightReading==0 && rightfarReading==0)
    {
      turnright();
    }
    readSensors();
    return;
  }
  else if(leftfarReading==1 && rightfarReading==1 && leftReading==1 && centerReading==1 && rightReading==1) //T intersection
  {
    analogWrite(en1,135);
  analogWrite(en2,140);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
    delay(leaptime);
    readSensors();
    if(leftfarReading==0 && leftReading==0 && centerReading==0 && rightReading==0 && rightfarReading==0)
    {
      turnleft();
    }
    if(leftfarReading==1 && leftReading==1 && centerReading==1 && rightReading==1 && rightfarReading==1)
    {
      finish();
    }
    readSensors();
    return;
  }
  else if(leftfarReading==0 && leftReading==0 && centerReading==1 && rightReading==0 && rightfarReading==0)
  {
    analogWrite(en1,135);
  analogWrite(en2,140);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
    delay(leaptime);
    readSensors();
    if(leftfarReading==0 && leftReading==0 && centerReading==0 && rightReading==0 && rightfarReading==0)
    {
      back();
    }
    if(leftfarReading==1 && leftReading==1 && centerReading==1 && rightReading==1 && rightfarReading==1)
    {
      finish();
    }
    readSensors();
    return;
  }
  
}

void straight ()
{
  analogWrite(en1,135);
  analogWrite(en2,140);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
}
void sleft ()
{
  analogWrite(en1,120);
  analogWrite(en2,120);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
}
void sright ()
{
  analogWrite(en1,120);
  analogWrite(en2,120);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
}
void turnleft()
{
  analogWrite(en1,140);
  analogWrite(en2,140);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
}
void turnright()
{
  analogWrite(en1,140);
  analogWrite(en2,140); 
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  
}
void back()
{
  analogWrite(en1,140);
  analogWrite(en2,140);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
    
}
void finish()
{
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
analogWrite(en1,0);
analogWrite(en2,0); 
}
