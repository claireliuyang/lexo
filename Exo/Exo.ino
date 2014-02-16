// Exo-skeleton ASL learning glove

#include <Servo.h> 

// Struct to manage fingers
struct Finger {
  Servo servo;
  int pos;    
};

// **************************** //
//          Constants           //
// **************************** //

Servo thumbServo, indexServo, middleServo, ringServo, pinkyServo;
Finger thumb = {thumbServo, 0}, 
       index = {indexServo, 0}, 
       middle = {middleServo, 0}, 
       ring = {ringServo, 0}, 
       pinky = {pinkyServo, 0};       

//Finger fingers[] = {thumb, index, middle, ring, pinky};       
Finger fingers[] = {pinky};

int fingerPos[26][5] = {
  {100, 90, 90, 90, 90}, // a
  {0, 90, 90, 90, 90}, // b
  {180, 90, 90, 90, 90}, // c
  {90, 90, 90, 90, 90}, // d
  {90, 90, 90, 90, 90}, // e
  {90, 90, 90, 90, 90}, // f
  {90, 90, 90, 90, 90}, // g
  {90, 90, 90, 90, 90}, // h
  {90, 90, 90, 90, 90}, // i
  {90, 90, 90, 90, 90}, // j
  {90, 90, 90, 90, 90}, // k
  {90, 90, 90, 90, 90}, // l
  {90, 90, 90, 90, 90}, // m
  {90, 90, 90, 90, 90}, // n
  {90, 90, 90, 90, 90}, // o
  {90, 90, 90, 90, 90}, // p
  {90, 90, 90, 90, 90}, // q
  {90, 90, 90, 90, 90}, // r
  {90, 90, 90, 90, 90}, // s
  {90, 90, 90, 90, 90}, // t
  {90, 90, 90, 90, 90}, // u
  {90, 90, 90, 90, 90}, // v
  {90, 90, 90, 90, 90}, // w
  {90, 90, 90, 90, 90}, // x
  {90, 90, 90, 90, 90}, // y
  {90, 90, 90, 90, 90} // z 
};

void setup() 
{   
//  thumb.servo.attach(9);
//  index.servo.attach(9);  // attaches the servo on pin 9 to the servo object
//  middle.servo.attach(9);
//  ring.servo.attach(9);
  pinky.servo.attach(9);  
  Serial.println("Motors attached to pins.");
  
  Serial.println("Servos set to 0.");
  
  Serial.println("Testing the fingers");  
  
  Serial.begin(9600);     
} 
 
 
void loop() 
{
  // send data only when you receive data:
  driveIndex(150);
  delay(1000);
  driveIndex(0);
  delay(1000);
  driveIndex(90);
  
  if (Serial.available() > 0) {
    // read the incoming byte:          
    char incomingChar = (char) Serial.read();
    
    // say what you got:
    Serial.print("Teaching..");
    Serial.println(incomingChar);
  }
};

/*
* Takes in a reference to a Finger struct,
* as well as the target position.
*/
//void drive(struct Finger* finger, int target) {
//  // Get the step size, +1 or -1
//  int stepsize = finger->pos < target ? 95: -95;
//  Serial.println(stepsize);
//  // Keep rotating until the position is the target!
//  while (finger->pos <= target) {
//    finger->servo.write(finger->pos);
//    finger->pos+=stepsize;
//    delay(15);
//  };
//};

// Drive the index finger.
void driveIndex(int target) {
  int stepsize = index.pos < target ? 1: -1;
  // Keep rotating until the position is the target!
  while (index.pos != target) {
    Serial.println(index.pos);
    index.servo.write(index.pos);
    index.pos+=stepsize;
    delay(15);
  };
}


void teach(char letter) 
{
  // Translate the letter input to an index.
  String alphabet = "abcdefghijklmnopqrstuvwxyz";
  int letterIndex = alphabet.indexOf(letter);  
  // Drive all of the fingers to the appropriate positions.
  driveIndex(fingerPos[letterIndex][0]);
//  for (int i = 0; i < sizeof(fingers); i++) {
////    drive(&fingers[i], fingerPos[letterIndex][i]);
//    driveIndex(fingerPos[letterIndex][i]);
//  }  
};
