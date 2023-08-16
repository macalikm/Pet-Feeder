#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include <SPI.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

const unsigned long SECOND = 1000;
const unsigned long MINUTE = 60*SECOND;
const unsigned long HOUR = 3600*SECOND;
const unsigned long REVOLUTION = 200;

void DoubleCoil(int);
void AlertCats();
#define buzzer 13

void setup() 
{
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);           // set up Serial library at 9600 bps
  while (!Serial);
  Serial.println("Stepper test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
  myMotor->setSpeed(50);  // 50 rpm
}

void loop() {
  AlertCats();
  DoubleCoil(1);
  
  myMotor->release();
  Serial.println("Waiting...");
  delay(1*MINUTE);
}

void DoubleCoil(int x)
{
  Serial.print("Vending ");
  Serial.print(x);
  Serial.println(" Cat Food");
  for (int i=0;i < x; i++) {
  myMotor->step(REVOLUTION, FORWARD, DOUBLE);
  //  myMotor->step(100, BACKWARD, DOUBLE);
  }
}

void AlertCats()
{
  Serial.println("Alert Cats. ");
  tone(buzzer, 10000, 500);
  noTone(buzzer);
}