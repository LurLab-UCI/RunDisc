
//#include <TimerOne.h>
//#include <MsTimer2.h>
//#include "TimerThree.h"
#include "EveryTimerB.h"
#define Timer1 TimerB2    // use TimerB2 as a drop in replacement for Timer1


#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;
//#define MAX9744_I2CADDR 0x4B
#define DAC_RESOLUTION    (8)



//The entire sketch is

enum PinAssignments {
encoderPinA = 2,
encoderPinB = 3,
testp9 = 9,
testp8 = 8,
};

int16_t encoderPos = 0;
int16_t lastReportedPos = 1;
uint32_t temp = 0;
uint32_t ctemp = 0;

boolean A_set = false;
boolean B_set = false;


void setup() {


  pinMode(13, OUTPUT);    
  pinMode(testp8, OUTPUT);    
  pinMode(testp9, OUTPUT);    
//  Timer1.initialize(); //
//  Timer1.attachInterrupt( timerIsr ); // attach the service routine here
//  Timer1.setPeriod(2000000); //
  
  
pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  digitalWrite(encoderPinA, HIGH);  // turn on pull-up resistor
  digitalWrite(encoderPinB, HIGH);  // turn on pull-up resistor
  digitalWrite(testp8, LOW);
  digitalWrite(testp9, LOW);

  // encoder pin on interrupt 0 (pin 2)
  
//  attachInterrupt(0, doEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), doEncoderA, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
//  attachInterrupt(1, doEncoderB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), doEncoderB, CHANGE);

  Serial.begin(115200);

 dac.begin(0x62);
//  dac.setVoltage(00, false);          
  temp = 0;
}

//-------------------------------------------------------------------------
void loop() {

    temp = millis();
    temp = temp - ctemp;
    //Serial.println(temp);

    //delay(1);


  if (temp > 19)
  {
    digitalWrite( testp9, HIGH);
    ctemp = millis();
    dac.setVoltage(encoderPos, false);          
    //delay(1);
    digitalWrite( testp9, LOW);
   }

//    digitalWrite( testp9, HIGH);
//    delay(1);
//    digitalWrite( testp9, LOW);

//  digitalWrite( lastReportedPos, HIGH);
 //dac.setVoltage(lastReportedPos, false);          
//  digitalWrite( testp, LOW);
//  Serial.println(lastReportedPos);
//o  delay(100);
  //delay(1);

// if no timer1 interrupt use the code here in the main loop
//    digitalWrite( 13, digitalRead( 13 ) ^ 1 );
/*
  if (lastReportedPos != encoderPos) {
  //  Serial.print("Index:");
    //digitalWrite( 13, HIGH);
    Serial.print(encoderPos, DEC);
    Serial.println();
    lastReportedPos = encoderPos;
    //digitalWrite( 13, LOW);
  }
  */

}

//----------------------------------------------------------------------





// Interrupt on A changing state
void doEncoderA() {
  // Test transition
    digitalWrite( testp8, HIGH);
  A_set = digitalRead(encoderPinA) == HIGH;
  // and adjust counter + if A leads B
  encoderPos += (A_set != B_set) ? +1 : -1;
    digitalWrite( testp8, LOW);
}

// Interrupt on B changing state
void doEncoderB() {
  // Test transition
  B_set = digitalRead(encoderPinB) == HIGH;
  // and adjust counter + if B follows A
  encoderPos += (A_set == B_set) ? +1 : -1;
}



/// --------------------------
/// Custom ISR Timer Routine
/// --------------------------
void timerIsr()
{
  temp == 1;
 //Serial.println("----------------");

  // Toggle LED
    digitalWrite( testp8,HIGH);
    delay(1);

  if (lastReportedPos != encoderPos) {
    lastReportedPos = encoderPos;
    //  digitalWrite(testpin,LOW);
  }
    digitalWrite(testp8,LOW);
//   dac.begin(0x62);
//   dac.setVoltage(lastReportedPos, false);          
  // digitalWrite( testp8, LOW);
   

  
}
