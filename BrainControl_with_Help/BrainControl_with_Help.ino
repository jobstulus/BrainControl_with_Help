// Arduino Brain Library
// Serial out example, 	grabs the brain data and sends CSV out over the hardware serial.
// Eric Mika, 2010

#include "Adafruit_NeoPixel.h"
#include <Brain.h>
#include <Servo.h> 

// Not all pins defined by this have to be specifically defined.
// But if you want do wire your arduino board, a glimpse in this list will do the trick.


#define RXPIN   0   // has not to be defined elsewhere, is here just for info
#define NOPE    1   // this one is not connected
#define US_EC_1 2   // ultrasonic echo pin from the lever one position
#define SRV_1   3   // servo motor control lever one position
#define US_EC_2 4   // ultrasonic echo pin from the lever two position
#define SRV_2   5   // servo motor control lever two position
#define SRV_3   6   // servo motor control lever three position
#define US_TRG  7   // this pin triggers all the ultrasonic sensors for sending signals

#define US_EC_3 8   // ultrasonic echo pin from the lever three position
#define SRV_4   9   // servo motor control lever four position
#define US_EC_4 10  // ultrasonic echo pin from the lever four position
#define MODE    11  // Reserved for further use... not used now
#define PIX_DAT 12  // control output for Neo_Pixel LEDs


bool lastValue = false;
int count = 0;

Servo servo1; 
Servo servo2;
Servo servo3;
Servo servo4; 

// this constant won't change.  It's the pin number
// of the sensor's output:
int sonicSensor1 = US_EC_1;
int sonicSensor2 = US_EC_2;
int sonicSensor3 = US_EC_3;
int sonicSensor4 = US_EC_4;

Servo servo[4] = {servo1,servo2,servo3,servo4};
int sonicSensor[4] = {sonicSensor1,sonicSensor2,sonicSensor3,sonicSensor4};

void load_auto(int servo_id){
  servo[servo_id].write(0);
  delay(300);
  servo[servo_id].write(135);
  
}

void fire_auto(int servo_id){
  servo[servo_id].write(180); 
  delay(160);
  load_auto(servo_id);

}

void init_auto(){
  servo[0].attach(SRV_1);
  servo[1].attach(SRV_2);
  servo[2].attach(SRV_3);
  servo[3].attach(SRV_4);
  pinMode(sonicSensor[0], INPUT);
  pinMode(sonicSensor[1], INPUT);
  pinMode(sonicSensor[2], INPUT);
  pinMode(sonicSensor[3], INPUT);
  pinMode(MODE, INPUT);
  for(int i=0;i<4;i++){  
    load_auto(i);
  }
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void analizeSonicSensor(int sensor_id){
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  //pinMode(sonicSensor[sensor_id], OUTPUT);
  pinMode(US_TRG, OUTPUT);
  digitalWrite(US_TRG, LOW);
  delayMicroseconds(2);
  digitalWrite(US_TRG, HIGH);
  delayMicroseconds(12);
  digitalWrite(US_TRG, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(sonicSensor[sensor_id], INPUT);
  duration = pulseIn(sonicSensor[sensor_id], HIGH,1200);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  
  //Serial.println("Sonic Sensor: "+String(sensor_id)+" Value: "+String(cm));
  if(cm < 20 && cm > 0){
    fire_auto(sensor_id);
  }
}




////////////////////////////////////////


// Set up the brain parser, pass it the hardware serial object you want to listen on.
Brain brain(Serial);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, PIX_DAT, NEO_GRB + NEO_KHZ800);


void setup() {
	// Start the hardware serial.
	Serial.begin(9600);

  init_auto();

  strip.begin();
  strip.show();
}

void loop() {
	// Expect packets about once per second.
	// The .readCSV() function returns a string (well, char*) listing the most recent brain data, in the following format:
	// "signal strength, attention, meditation, delta, theta, low alpha, high alpha, low beta, high beta, low gamma, high gamma"	
	
  	if (brain.update()) {
    	       Serial.println(brain.readErrors());
  	       Serial.println(brain.readCSV());
                 Serial.println(brain.readAttention());
                 
                 strip.setBrightness(30);
  
                 if(brain.readAttention() > 5){
                    strip.setPixelColor(0, 255, 0, 0);
                    strip.show();
                 } else if  (brain.readAttention() < 25 ) {
                    strip.setPixelColor(0, 0, 0, 0);
                    strip.show();
                    lastValue = false;
                 }
  
                             
                 if(brain.readAttention() > 25){
                    strip.setPixelColor(1, 255, 165, 0);
                    strip.show();
                 } else if  (brain.readAttention() < 40 ) {
                    strip.setPixelColor(1, 0, 0, 0);
                    strip.show();
                    lastValue = false;
                 }
  
  
                 if(brain.readAttention() > 40){
                    strip.setPixelColor(2, 255, 215, 0);
                    strip.show();
                   
                 } else if  (brain.readAttention() < 60 ) {
                    strip.setPixelColor(2, 0, 0, 0);
                    strip.show();
                    lastValue = false;
                 }
               
  
                 if(brain.readAttention() > 60){
                    strip.setPixelColor(3, 0, 128, 0);
                    strip.show();
                    lastValue = true;
                    
                 } else if  (brain.readAttention() < 60 ) {
                    strip.setPixelColor(3, 0, 0, 0);
                    strip.show();
                    lastValue = false;
                 }
  
                 
  	  }
	
   for(int i=0;i<4;i++){
    if(i!=3)
      analizeSonicSensor(i);
    else if(lastValue==true)
      analizeSonicSensor(3);
  }
}
