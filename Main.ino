#include <Servo.h>

Servo pan_servo;    //Head movement right or left
Servo tilt_servo;   //Head movement up or down

//Pins for motor driver
int ena = 5;        //Switch motor a on / off and speed control
int in1 = 6;        //Motor a pin1
int in2 = 7;        //Motor a pin2
int in3 = 4;        //Motor b pin1
int in4 = 8;        //Motor b pin2
int enb = 9;        //Switch motor b on / off and speed control

//Pins for Compound Eye
int enable_eye = 10;    //Pin to on / off IR LEDs
int left = A0;          //IR-Sensor left
int top = A1;           //IR-Sensor above
int right = A2;         //IR-Sensor right
int bottom = A3;        //IR-Sensor below


//Variables for ambient light + infrared
int absolute_top = 0;
int absolute_left = 0;
int absolute_bottom = 0;
int absolute_right = 0;
 
//Variables for only ambient light
int offset_top = 0;
int offset_left = 0;
int offset_bottom = 0;
int offset_right = 0;
 
//Variables for difference
int relative_top = 0;
int relative_left = 0;
int relative_bottom = 0;
int relative_right = 0;


//Variables for positions of the servos
int pan_pos = 0;
int tilt_pos = 0;
int servo_step = 1;  //How fast the servo should move per step

int robot_speed = 100; //Robot Speed
int pan_zero = 90;     //Pan-Servo start position
int tilt_zero = 90;    //Tilt-Servo start position
int udmax = 165;
int udmin = 80;
int lrmax = 165;
int lrmin = 15;

//==================================================================================================================================================

void setup()
{
  //Pins for motor driver as output
  pinMode(ena , OUTPUT);
  pinMode(in1 , OUTPUT);
  pinMode(in2 , OUTPUT);
  pinMode(in3 , OUTPUT);
  pinMode(in4 , OUTPUT);
  pinMode(enb , OUTPUT); 
 
  //Disable the motors
  analogWrite(ena , 0);
  analogWrite(enb , 0);
  
  //Pin for the Compound Eye as an output
  pinMode(enable_eye , OUTPUT);
  
  pan_servo.attach(11);  //Pan-Servo is attached to Pin 11
  tilt_servo.attach(10); //Tilt-Servo is attached to Pin 10
  
  pan_servo.write(pan_zero);     //Setting Pan-Servo to middle
  tilt_servo.write(tilt_zero);   //Setting Tilt-Servo to middle
  
  Serial.begin(9600);
   
}

//Moving Forward
void fwd()
{
  analogWrite(ena , robot_speed);
  digitalWrite(in1 , HIGH);
  digitalWrite(in2 , LOW);
  analogWrite(enb , robot_speed);
  digitalWrite(in3 , HIGH);
  digitalWrite(in4 , LOW);
  
}

//Not Moving at all
void brake ()
{
  digitalWrite(ena , LOW);
  digitalWrite(enb , LOW);
}


//Moving Backward
void bwd()
{
  analogWrite(ena , robot_speed);
  digitalWrite(in1 , LOW);
  digitalWrite(in2 , HIGH);
  analogWrite(enb , robot_speed);
  digitalWrite(in3 , LOW);
  digitalWrite(in4 , HIGH); 
  
}

//Moving to the left
void rotate_left()
{
  analogWrite(ena , robot_speed);
  digitalWrite(in1 , HIGH);
  digitalWrite(in2 , LOW);
  analogWrite(enb , robot_speed);
  digitalWrite(in3 , LOW);
  digitalWrite(in4 , HIGH); 
}

//Moving to the Right
void rotate_right()
{
  analogWrite(ena , robot_speed);
  digitalWrite(in1 , LOW);
  digitalWrite(in2 , HIGH);
  analogWrite(enb , robot_speed);
  digitalWrite(in3 , HIGH);
  digitalWrite(in4 , LOW);  
}

//==================================================================================================================================================

void loop()
{
  
  //Read values when IR = ON
  digitalWrite(enable_eye , HIGH);    //IR-LEDs turn on
  delay(1);                           //very short delay for reading values
  
  //Reading values in light radiation (ambient light and IR light from LEDs)
  absolute_top = analogRead(top);    
  absolute_left = analogRead(left);
  absolute_bottom = analogRead(bottom);
  absolute_right = analogRead(right);
 
  //Read values when IR = OFF
  digitalWrite(enable_eye , LOW);     //IR-LEDs turn off
  delay(1);                           //very short delay for reading values
 
 //Reading values in light (only ambient light)
  offset_top = analogRead(top);
  offset_left = analogRead(left);
  offset_bottom = analogRead(bottom);
  offset_right = analogRead(right);
 
  //Calculating difference (total irradiation - ambient light)
  relative_top = absolute_top-offset_top;
  relative_left = absolute_left-offset_left;
  relative_bottom = absolute_bottom-offset_bottom;
  relative_right = absolute_right-offset_right;
 


  //If the radiation on the left stronger than on the right move left
  if(relative_left > relative_right)
  {
    pan_pos = pan_pos-servo_step;    //remove 1degree from servo position
  }

  //If the radiation on the right stronger than on the left move right
  else if(relative_left < relative_right )
  {
    pan_pos = pan_pos+servo_step;  //adding 1degree to the servo position
  }
 
  //Make sure that the servo is between 15degrees - 165degrees
  if(pan_pos > lrmax)
  {
    pan_pos = lrmax;
  }
  if(pan_pos < lrmin)
  {
    pan_pos = lrmin;
  }

  //Servo position is written to the servo
  pan_servo.write(pan_pos);
 
 
 
  //If the radiation below is stronger than above move downwards
  if(relative_bottom > relative_top)
  {
    tilt_pos = tilt_pos-servo_step;    //remove 1degree from the servo position
  }

  //If the radiation above is stronger than below move upwards
  else if(relative_bottom < relative_top)
  {
    tilt_pos = tilt_pos+servo_step;    //adding 1degree to the servo position
  }
  
  //Make sure that the servo is between 80degrees and 165degrees
  if(tilt_pos > udmax)
  {
    tilt_pos = udmax;
  }
  if(tilt_pos < udmin)
  {
    tilt_pos = udmin;
  }
  
  //Servo position is written to the servo
  tilt_servo.write(tilt_pos);
 
//==================================================================================================================================================
    
  //When the servo has reached the angle 115degrees turn right
  if(pan_pos > 115)
  {
    rotate_right(); 
  }
  
  //When the servo has reached the angle 75degrees turn left
  else if(pan_pos < 75)
  {
    rotate_left();
  }

 
  //If the angle is less than 115 ° AND the IR radiation is less than 300(top AND bottom AND right and left) move forward
  else if(tilt_pos < 115 && relative_top < 300 && relative_bottom < 300 && relative_left < 300 && relative_right < 300)
  {
    fwd();
  }
 
  //If the angle is less than 115 ° AND the IR radiation is greater than 600(top AND bottom AND right and left) move backward
  else if(tilt_pos < 115 && relative_top > 600 && relative_bottom > 600 && relative_left > 600 && relative_right > 600)
  {
    bwd();
  }

  //In all other cases stop
  else
  {
    brake();
  }

  delay(10);        //Short break for smooth flow
  
}
