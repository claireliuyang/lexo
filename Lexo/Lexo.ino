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
    
const int EXTD = SERVO_MAX_POS;
const int ONEQ = 105; // 1/3 bent
const int HALF = (SERVO_MAX_POS-SERVO_MIN_POS)/2;
const int THRQ = 25; // 3/4 bent
const int BENT = SERVO_MIN_POS;
// Finger array!
Servo fingers[5];

int fingerPos[26][5] = {
// THUMB INDEX MIDDL RING  PINKY
  {THRQ, BENT, BENT, BENT, BENT}, // A
  {BENT, EXTD, EXTD, EXTD, EXTD}, // B
  {HALF, ONEQ, ONEQ, ONEQ, ONEQ}, // C
  {THRQ, EXTD, HALF, HALF, HALF}, // D
  {BENT, THRQ, THRQ, THRQ, THRQ}, // E
  {THRQ, THRQ, EXTD, EXTD, EXTD}, // F
  {HALF, EXTD, BENT, BENT, BENT}, // G
  {HALF, EXTD, EXTD, BENT, BENT}, // H
  {THRQ, BENT, BENT, BENT, EXTD}, // I
  {THRQ, BENT, BENT, BENT, EXTD}, // J (needs motion)
  {EXTD, EXTD, EXTD, BENT, BENT}, // k
  {EXTD, EXTD, BENT, BENT, BENT}, // L
  {BENT, BENT, BENT, BENT, BENT}, // M (order matters)
  {BENT, BENT, BENT, BENT, BENT}, // N (order matters)
  {HALF, THRQ, THRQ, THRQ, THRQ}, // O
  {EXTD, EXTD, HALF, BENT, BENT}, // P
  {EXTD, EXTD, BENT, BENT, BENT}, // Q
  {THRQ, EXTD, EXTD, BENT, BENT}, // R
  {BENT, BENT, BENT, BENT, BENT}, // S (order matters)
  {BENT, ONEQ, BENT, BENT, BENT}, // T (order matters)
  {BENT, EXTD, EXTD, BENT, BENT}, // U
  {BENT, EXTD, EXTD, BENT, BENT}, // V (need lateral separation b/t one and two
  {BENT, EXTD, EXTD, EXTD, BENT}, // W (need lateral separation b/t one and two and three
  {BENT, ONEQ, BENT, BENT, BENT}, // X
  {EXTD, BENT, BENT, BENT, EXTD}, // Y
  {HALF, EXTD, BENT, BENT, BENT}  // Z (needs motion)
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
  for (int i = 0; i < 5; i++) {
    driveFinger(i, SERVO_MAX_POS);
  }
  
//  delay(2000);
  
  for (int i = 0; i < 5; i++) {
    driveFinger(i, SERVO_MIN_POS);
  }
  
  delay(2000);
    
  for (int i = 0; i < 5; i++) {
    driveFinger(i, SERVO_MAX_POS);
  }
 
  Serial.println("Set up at min pos");
  
  Serial.println("Ready to go!");
  
  
    
}
int cmd;

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
  
//    // Wait for and get position command
//  Serial.print(">>");                            // Prompt next command
//  while (!Serial.available()) continue;
//  cmd = Serial.parseInt();
//  Serial.println("");
//  Serial.println(cmd);              // Echo command
//  if (cmd > 180 || cmd < 0) goto endloop;        // If not valid command, break
//  if (cmd == 180) cmd = 179;                       // Remap cmd = 180 value (technically invalid) to correct value for UX
//  drive(cmd);                  // Else, valid command --> go to position
//  
//  Serial.print("Index finger is now at: ");
//  Serial.println(cmd);
//
//endloop:
//    Serial.println("");
   
  // Looping to test servo 
//  fingers[0].write(SERVO_MAX_POS);
//  delay(2000);
//  fingers[0].write(SERVO_MIN_POS);
//  delay(2000);
  
}

void drive(int cmd) {
  fingers[0].write(cmd); // pin9
  delay(1000);
  
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
