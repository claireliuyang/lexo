// Exo-skeleton ASL learning glove

// Based off of: Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 

// **************************** //
//          Constants           //
// **************************** //

Servo myservo;        // Instantiate servo object for finger 1/index finger
int pos = 0;     // Global variable storing servo's position
char cmd;        // User input command
int target;  // target position, as specified by user
int counter;

void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  Serial.println("G - ### (degrees, 0 - fully closed, 180 - open)");
  Serial.println("Q - Emergency stop");
  counter = 0;
} 
 
 
void loop() 
{
  // Print instructions and wait for user input

  drive(180);
  drive(1);
  drive(90);
  drive(45);
  drive(20);
  drive(180);

  /*
  target = 120;
  pos = bendme(target);
  target = 74;
  pos = bendme(target);
  counter++;
  Serial.println (pos);
  */
  
  //if (cmd == 'G' || cmd == 'g')    
  
  delay(100);
}

void drive(int target){
  // IN:    int, target position (in degrees)
  // WHAT:  Rotates motor to target position
  // OUT:   void, global variable pos at new position
  int stepsize = 1;
  if (pos > target) stepsize = -1;

  while (pos != target) {
    myservo.write(pos);
    pos += stepsize;
    delay(15);
}
