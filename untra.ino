/*

    Obstacle Avoiding Robot with Arduino UNO + HY-SRF05
    For more details visit:
    https://robotsiam.blogspot.com/2017/12/arduino-uno-hy-srf05.html

*/

/*-------definning SRF05------*/
#define DistanceEn_Pin 2
int i = 0;
long unsigned distance = 0;
uint8_t distanceValue[4] = {0,0,0,0};
const unsigned int BAUD_RATE = 9600;

/*-------definning Outputs------*/

int MA1 = 4;     // Motor A1
int MA2 = 5;     // Motor A2
int PWM_A =  11;   // Speed Motor A

int MB1 =  6;     // Motor B1
int MB2 =  7;     // Motor B2
int PWM_B =  10;  // Speed Motor B
int count= 0;

int SPEED1_FOWARD = 90; //RIGHT 90     // Speed PWM สามารถปรับความเร็วได้ถึง 0 - 255
int SPEED2_FOWARD = 94;  //LEFT 94

int SPEED1_BACKWARD = 96; //RIGHT     
int SPEED2_BACKWARD = 94;  //LEFT

int SPEED1_TURNRIGHT = 96; //RIGHT     
//int SPEED2_TURNRIGHT = 94;  //LEFT

int SPEED1_TURNLEFT = 96; //RIGHT     
//int SPEED2_TURNLEFT = 94;  //LEFT


void Distance()
{
  
  while(Serial.read() >= 0);         //Empty the serial buffer
  digitalWrite(DistanceEn_Pin,0);      //Ultrasound can open
  while(Serial.available() <= 4)       //Waiting for the ultrasonic data window
  { 
  }
  distanceValue[0] = Serial.read();    //Extract the data
  if( distanceValue[0] == 0xff )       //Determine if data for ultrasonic module
  {
    for(i = 1;i <= 3;i ++)
    {
      distanceValue[i] = Serial.read();
    }
   }
 
  digitalWrite(DistanceEn_Pin,1);       //Ultrasound can make
 
  distance = distanceValue[1] * 256 + distanceValue[2];                   //Data processing, calculating distance
  if((distanceValue[3] == distanceValue[1] + distanceValue[2] - 1))       //Data and check, can be removed
  {
    Serial.print("The distance is : ");
    Serial.print(distance);
    Serial.println(" mm");
  }
}



void Backward(int time)
{
  digitalWrite(MA1, HIGH);
  digitalWrite(MA2, LOW);
  analogWrite(PWM_A, SPEED1_BACKWARD);

  digitalWrite(MB1, HIGH);
  digitalWrite(MB2, LOW);
  analogWrite(PWM_B, SPEED2_BACKWARD);

  delay(time);
}

void Forward (int time)
{
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, HIGH);
  analogWrite(PWM_A, SPEED1_FOWARD);

  digitalWrite(MB1, LOW);
  digitalWrite(MB2, HIGH);
  analogWrite(PWM_B, SPEED2_FOWARD);

  delay(time);
}

void turnLeft(int time)
{
  digitalWrite(MA1, HIGH);
  digitalWrite(MA2, LOW);
  analogWrite(PWM_A, SPEED1_TURNLEFT);

  digitalWrite(MB1, LOW);
  digitalWrite(MB2, LOW);
  analogWrite(PWM_B, 0);

  delay(time);
}

void turnRight(int time)
{
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, LOW);
  analogWrite(PWM_A, 0);

  digitalWrite(MB1, LOW);
  digitalWrite(MB2, HIGH);
  analogWrite(PWM_B, SPEED1_TURNRIGHT);

  delay(time);
}

void Stop(int time)
{
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, LOW);
  analogWrite(PWM_A, 0);

  digitalWrite(MB1, LOW);
  digitalWrite(MB2, LOW);
  analogWrite(PWM_B, 0);

  delay(time);

}

void setup() {
  //Setup Channel A
  pinMode(MA1, OUTPUT); //Motor A1
  pinMode(MA2, OUTPUT); //Motor A2
  pinMode(PWM_A, OUTPUT); //Speed PWM Motor A

  //Setup Channel B
  pinMode(MB1, OUTPUT);  //Motor B1
  pinMode(MB2, OUTPUT);  //Motor B2
  pinMode(PWM_B, OUTPUT); //Speed PWM Motor B

  Serial.begin(BAUD_RATE);
  pinMode(DistanceEn_Pin, OUTPUT);
  digitalWrite(DistanceEn_Pin, 1);
}


void loop() {
  
  if(count==0){
  delay(3000);
  count++;
  }
  

  Distance();

  if ((distance > 25 && distance < 200))  {

    digitalWrite(DistanceEn_Pin, HIGH);
    Stop(1000);
    digitalWrite(DistanceEn_Pin, LOW);
    Backward(800);
    Stop(500);
    turnLeft(500);
    Serial.print("distance to nearest object:");
    Serial.println(distance);
    Serial.println(" mm");

  }

  else {

    digitalWrite(DistanceEn_Pin, LOW);
    Forward(10);
    Serial.print("distance to nearest object:");
    Serial.println(distance);
    Serial.println(" mm");

  }
delay(100);

}
