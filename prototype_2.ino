#define in1 2
#define in2 3
#define in3 4
#define in4 5 

int enl=10;
int enr=9;

#define leftfarSensor A0
#define leftSensor A1
#define centerSensor A2
#define rightSensor A3
#define rightfarSensor A4


int a[5];
int last_proportional=0;
int integral=0;

char select_turn(unsigned char found_left,unsigned char found_right,unsigned char found_st);

int mod(int v);
int set_motors(int a,int b);
void turn(char dir);
void PID();

int right=0;
int left=0;

void setup() {
  // put your setup code here, to run once:
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);
  pinMode (in3, OUTPUT);
  pinMode (in4, OUTPUT);
  pinMode(enl,OUTPUT);
  pinMode(enr,OUTPUT);
  pinMode(leftfarSensor, INPUT);
  pinMode(leftSensor, INPUT);
  pinMode(centerSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(rightfarSensor, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  PID();

    set_motors(120,120);
    delay(30);
  unsigned char found_left=0;
  unsigned char found_right=0;
  unsigned char found_st=0;

readline();
 if(a[0]==HIGH)
  found_left=1;

 if(a[3]==HIGH)
  found_right=1;

 if(a[2]==HIGH)
  found_st=1;

 unsigned char dir;

 dir = select_turn(found_left,found_right,found_st);
 turn(dir);
  
}

int set_motors(int l,int r)
{
  if(l>0&&r>0)
  {
    analogWrite(enl,mod(l));
    analogWrite(enr,mod(r));
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if(l<0&&r>0)
  {
    analogWrite(enl,mod(l));
    analogWrite(enr,mod(r));
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if(l>0&&r<0)
  {
    analogWrite(enl,mod(l));
    analogWrite(enr,mod(r));
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if(l==0&&r==0)
  {
    analogWrite(enl,0);
    analogWrite(enr,0);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);
  }
}

int readline()
{
  a[0]     = digitalRead(leftfarSensor);
  a[1]    = digitalRead(leftSensor);
  a[2] = digitalRead(centerSensor);
  a[3]   = digitalRead(rightSensor);
  a[4]   = digitalRead(rightfarSensor);
  int v =0;
  v=(4000*a[0]+3000*a[1]+2000*a[2]+1000*a[3]+0*a[4])/(a[0]+a[1]+a[2]+a[3]+a[4]);
  return v;
}

int stop()
{
  analogWrite(enl,255);
   analogWrite(enl,255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
}

void turn(char dir)
{
  switch(dir)
  {
    case 'L':
      set_motors(-120,120);
      delay(250);
      break;
    case 'R':
      set_motors(120,-120);
      delay(250);
      break;
    case 'B':
      set_motors(120,-120);
      delay(500);
      break;
    case 'S':
      break;
  }
}

void PID()
{ 
  int i;
  int power_difference=0;
  float Kp,Ki,Kd;
  unsigned int position =0;
  int derivative,proportional;
  while(1)
  {
    position = readline();
    proportional=((int)position-2000);
    

    derivative = proportional - last_proportional;
    integral = integral+proportional;

    last_proportional=proportional;
    Kp=0.5;
    Ki=0.001;
    Kd=0.9;

    power_difference=proportional*Kp + integral*Ki + derivative*Kd;
   
    const int max=120;
    if(power_difference>max)
      power_difference=max;
    if(power_difference<-max)
      power_difference=(-1*max);

    if(power_difference<0)
    {
      set_motors(max+power_difference,max);
    }
    else
    {
      set_motors(max,max-power_difference);
    }
    readline();
    if(a[0]==HIGH&&a[1]==HIGH&&a[2]==HIGH&&a[3]==HIGH&&a[4]==HIGH)
      return;

    else if(a[0]==LOW||a[4]==LOW)
      return;
  }
}

char select_turn(unsigned char found_left,unsigned char found_right,unsigned char found_st)
{
  if(found_left==1)
    return 'L';
  else if(found_st==1)
    return 'S';
  else if(found_right==1)
    return 'R';
  else
    return 'B';
}



int mod(int v)
{
  if(v<0)
  return -1*v;
  else if(v>0)
  return 1*v;
}
