#include <Servo.h> 


// **************************** //
//          Constants           //
// **************************** //
int SERVO_MAX_POS = 160,
    SERVO_MIN_POS = 20,
    SERVO_SPEED = 20,
    SERVO_PIN_THUMB = 9,
    SERVO_PIN_INDEX = 10,
    SERVO_PIN_MIDDLE = 11,
    SERVO_PIN_RING = 12,
    SERVO_PIN_PINKY = 13;
    
// Finger array!
Servo fingers[5];

int fingerPos[26][5] = {
  {20, 90, 160, 90, 20}, // a
  {90, 20, 20, 160, 90}, // b
  {160, 10, 90, 90, 90}, // c
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

void setup() {
  
  // Set up the servo pins  
  fingers[0].attach(SERVO_PIN_THUMB);
  fingers[1].attach(SERVO_PIN_INDEX);
  fingers[2].attach(SERVO_PIN_MIDDLE);
  fingers[3].attach(SERVO_PIN_RING);
  fingers[4].attach(SERVO_PIN_PINKY);
  
  Serial.begin(9600);
  Serial.println("Began the serial at 9600");
  
  // Some kind of setup procedure
  driveFinger(0, SERVO_MAX_POS);
  delay(2000);  
  driveFinger(0, 90);
  delay(2000);
  driveFinger(0, SERVO_MIN_POS);
    
}


int command[2];

void loop() {  
  String msg = "";
  
  while (Serial.available() > 0) {
    char incomingChar = (char) Serial.read();    
    msg.concat(incomingChar);
  }
  
  if (msg.length() > 0) {     
    Serial.print("Read the message: ");
    Serial.println(msg); 
  }
  
  if (msg.length() > 1) {
//    int fingerNum = (int) msg.charAt(0);
//    int pos = msg.substring(1).toInt();
//    
//    Serial.print("Finger Number: ");
//    Serial.print(fingerNum);
//    Serial.print(" Moving to position: ");
//    Serial.println(pos);
    
  } else if (msg.length() == 1) {
    Serial.print("Teaching...");
    Serial.println(msg);
    teach(msg.charAt(0));
  }
   
  // Looping to test servo 
//  fingers[0].write(SERVO_MAX_POS);
//  delay(2000);
//  fingers[0].write(SERVO_MIN_POS);
//  delay(2000);
  
}

// Loop through the chars and adjust to the proper finger coordinates
void teach(char letter) {
  // Translate the letter input to an index
  String alphabet = "abcdefghijklmnopqrstuvwxyz";
  int letterIndex = alphabet.indexOf(letter);
  Serial.print("Letter index of: ");
  Serial.println(letterIndex);
  // Drive all of the fingers to the appropriate positions.
  for (int i = 0; i < 5; i++) {
    Serial.print("Finger number ");
    Serial.print(i);
    Serial.print(" Moving to position: ");
    Serial.println(fingerPos[letterIndex][i]);
    driveFinger(i, fingerPos[letterIndex][i]);
  }
}

// Drive a finger, of fingerNum to a target value
void driveFinger(int fingerNum, int target) {
  fingers[fingerNum].write(target);  
}
