// Example code for the PhOut12 sheild for the Teensy LC (probably works with other Teensys).
// v2 code
// Tools > USB Type > Serial + MIDI


// #include <Bounce.h>
#include <Servo.h> 

// the MIDI channel number to send messages
const int setChannel = 1;

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

const int servo1_pin = 17;
const int servo2_pin = 20;
const int servo3_pin = 22;
const int servo4_pin = 23;

const int wait_time = 5000;

elapsedMillis msec = 0;

int myservo1_value;
int previous_myservo1_value;
int myservo1_value_counter;

int myservo2_value;
int previous_myservo2_value;
int myservo2_value_counter;

int myservo3_value;
int previous_myservo3_value;
int myservo3_value_counter;

int myservo4_value;
int previous_myservo4_value;
int myservo4_value_counter;

int pwm_on3;
int pwm_on4;
int pwm_on6;
int pwm_on9;
int pwm_on10;
int pwm_on13;
int pwm_on16;

int velocity_mapped;  

const int midiOut1 = 10; // 10 = pan position
const int midiOut2 = 11; // 11 = volume/expression

const int input1 = 15; // analog signal from input 1
const int input2 = 14; // analog signal from input 2

const int input1Connectpin = 18; // this pin is used to tell the computer if input is connected
const int input2Connectpin = 19; // this pin is used to tell the computer if input is connected

int input1Connect = 0;
int input2Connect = 0;
 
int pos = 0;

int n0 = 0;
int n1 = 0;

void setup()
{   
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(16, OUTPUT);
  
  pinMode(input1, INPUT_PULLUP);
  pinMode(input2, INPUT_PULLUP);
  pinMode(input1Connectpin, INPUT_PULLUP);
  pinMode(input2Connectpin, INPUT_PULLUP);
  
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;
  usbMIDI.setHandleControlChange(OnControlChange);
  
  analogWriteResolution(8);
  analogWriteFrequency(23, 50);
  myservo1.attach(servo1_pin);
  myservo2.attach(servo2_pin);
  myservo3.attach(servo3_pin);
  myservo4.attach(servo4_pin);
  
  Serial.begin(9600);
}

int previousMapped1 = -1;
int previousMapped2 = -1;
int mapped1 = 0;
int mapped2 = 0;

void OnNoteOn(byte channel, byte note, byte velocity)
{
  velocity_mapped = map(velocity, 0, 127, 0, 255);
  if (channel == setChannel){

  if (note == 3) {digitalWrite(3, HIGH);}
  if (note == 4) {digitalWrite(4, HIGH);}
  if (note == 5) {digitalWrite(5, HIGH);}
  if (note == 6) {digitalWrite(6, HIGH);}
  if (note == 7) {digitalWrite(7, HIGH);}
  if (note == 8) {digitalWrite(8, HIGH);}
  if (note == 9) {digitalWrite(9, HIGH);}
  if (note == 10) {digitalWrite(10, HIGH);}
  if (note == 11) {digitalWrite(11, HIGH);}
  if (note == 12) {digitalWrite(12, HIGH);}
  if (note == 13) {digitalWrite(13, HIGH);}
  if (note == 16) {digitalWrite(16, HIGH);}
  }
}

void OnControlChange(byte channel, byte control, byte value)
{
  myservo1_value = map(value, 0, 127, 0, 180); // map midi values to servo values. these could be different for each servo. myservo1_value = map(value, 0, 127, 0, 180)
  if (control == 1 && channel == setChannel) {
      myservo1.attach(servo1_pin);
      myservo1.write(myservo1_value);
    }
// (value, 0, 127, 0, 50) good for digital servo
// (value, 0, 70, 13, 49) also used in the past
  myservo2_value = map(value, 0, 127, 0, 180); // map midi values to servo values. these could be different for each servo.
  if (control == 2 && channel == setChannel) {
      myservo2.attach(servo2_pin);
      myservo2.write(myservo2_value);
}

  myservo3_value = map(value, 0, 127, 0, 180); // map midi values to servo values. these could be different for each servo.
  if (control == 3 && channel == setChannel) {
      myservo3.attach(servo3_pin);
      myservo3.write(myservo3_value);
}
  myservo4_value = map(value, 0, 127, 0, 180); // map midi values to servo values. these could be different for each servo.
  if (control == 4 && channel == setChannel) {
      myservo4.attach(servo4_pin);
      myservo4.write(myservo4_value);
}
  pwm_on3 = map(value, 0, 127, 0, 255); // pwm control on output 1
  if (control == 103 && channel == setChannel) {
      analogWrite(3, pwm_on3);
}
  pwm_on4 = map(value, 0, 127, 0, 255); // pwm control on output 2
  if (control == 104 && channel == setChannel) {
      analogWrite(4, pwm_on4);
}
  pwm_on6 = map(value, 0, 127, 0, 255); // pwm control on output
  if (control == 106 && channel == setChannel) {
      analogWrite(6, pwm_on6);
}
  pwm_on9 = map(value, 0, 127, 0, 255); // pwm control on output
  if (control == 109 && channel == setChannel) {
      analogWrite(9, pwm_on9);
}
  pwm_on10 = map(value, 0, 127, 0, 255); // pwm control on output
  if (control == 110 && channel == setChannel) {
      analogWrite(10, pwm_on10);
}
  pwm_on16 = map(value, 0, 127, 0, 255); // pwm control on output
  if (control == 116 && channel == setChannel) {
      analogWrite(16, pwm_on16);
}
}

void OnNoteOff(byte channel, byte note, byte velocity)
{
  if (channel == setChannel){
  if (note == 3) {digitalWrite(3, LOW);}
  if (note == 4) {digitalWrite(4, LOW);}
  if (note == 5) {digitalWrite(5, LOW);}
  if (note == 6) {digitalWrite(6, LOW);}
  if (note == 7) {digitalWrite(7, LOW);}
  if (note == 8) {digitalWrite(8, LOW);}
  if (note == 9) {digitalWrite(9, LOW);}
  if (note == 10) {digitalWrite(10, LOW);}
  if (note == 11) {digitalWrite(11, LOW);}
  if (note == 12) {digitalWrite(12, LOW);}
  if (note == 13) {digitalWrite(13, LOW);}
  if (note == 16) {digitalWrite(16, LOW);}
  }
}


void loop()
{

  if (myservo1_value != previous_myservo1_value){
  myservo1_value_counter = 0;
  previous_myservo1_value = myservo1_value;
  }
  if(myservo1_value_counter < wait_time){
    ++ myservo1_value_counter;}
//  else{
//    pinMode(servo1_pin, INPUT); // this line turns the servo off after moving. only works on digital servos.
//    }


 /////


  if (myservo2_value != previous_myservo2_value){
  myservo2_value_counter = 0;
  previous_myservo2_value = myservo2_value;
  }
  if(myservo2_value_counter < wait_time){
    ++ myservo2_value_counter;}
//  else{
//    pinMode(servo2_pin, INPUT); // this line turns the servo off after moving. only works on digital servos.
//    }
    

/////

  if (myservo3_value != previous_myservo3_value){
  myservo3_value_counter = 0;
  previous_myservo3_value = myservo3_value;
  }
  if(myservo3_value_counter < wait_time){
    ++ myservo3_value_counter;}
//  else{
//    pinMode(servo3_pin, INPUT); // this line turns the servo off after moving. only works on digital servos.
//}

/////

  if (myservo4_value != previous_myservo4_value){
  myservo4_value_counter = 0;
  previous_myservo4_value = myservo4_value;
  }
  if(myservo4_value_counter < wait_time){
    ++ myservo4_value_counter;}
//  else{
//    pinMode(servo4_pin, INPUT); // this line turns the servo off after moving. only works on digital servos.
//    }

    if (msec >= 20) {
    msec = 0;
    n0 = analogRead(input1);
    n1 = analogRead(input2);
//    input1Connect = digitalRead(input1Connectpin);
//    input2Connect = digitalRead(input2Connectpin);
    // only transmit MIDI messages if analog input changed
    mapped1 = map(n0, 0, 1024, 0, 127);
    if (mapped1 != previousMapped1) {
//      if (n0 <= 535) {
//        n0 = 535;
//      }
//      if (n0 >= 1016){
//        n0 = 1016;
//      }
      usbMIDI.sendControlChange(midiOut1, mapped1, setChannel);
      previousMapped1 = mapped1;
      Serial.print(n0);
      Serial.println(", ");
    }
    mapped2 = map(n1, 0, 1024, 0, 127);
    Serial.print(n0);
      Serial.print(", ");
      Serial.println(n1);
    if (mapped2 != previousMapped2) {
//      if (n1 <= 10) {
//        n1 = 535;
//      }
//      if (n1 >= 1016){
//        n1 = 1016;
//      }
      usbMIDI.sendControlChange(midiOut2, mapped2, setChannel);
      previousMapped2 = mapped2;
    }
  }

    usbMIDI.read(); 
}










