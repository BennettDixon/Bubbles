#include <AFMotor.h>
#include <Arduino.h>

int numberCollector;  // to build the number from serial
byte serialNumber = 0;  // to store the ASCI number from serial
int opticCount = 6;  // how many optic stations there are - you also need to update line 7
int parameterCount = 3; //number of seeting to be stored in array for each optic
int parameterSize = 2; //the required number of digit for each parameter being sent

int drinkMatrix[6][3] = {
  "07,30,01,68,90,01,72,10,00,70,00,00,74,01,00,71,01,00,"
  };

//The below is for the contact switch.

const int  buttonPin = 2;    // the pin that the pushbutton is attached to
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

//----------------------

//The below is for the stepper motors

AF_Stepper motor1(48, 1);
AF_Stepper motor2(48, 2);

//---------------------

// Below is for the RGB LED

//---------------------

//The below are for running the machine:

int raftFound = false;
int drinkRequested = false;

//---------------------

void setup() {

// for the contact switch 

  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  // initialize serial communication:
  Serial.begin(9600);
  
//--------------------------------

//  For the stepper motors

  motor1.setSpeed(600);
   motor2.setSpeed(600);

//--------------------------------

// For LED


//-------------------------------

}


void loop(){ 
  
//Lets find the location of the float:
if (raftFound == false){
  Serial.println("Raft location not known yet");
  delay(1000);
  Serial.print("Looking for the raft...");
  buttonState = digitalRead(buttonPin); // read the pushbutton input pin:
//move the stepper until the contact switch is triggered
  while(buttonState == LOW && raftFound == false){
    motor1.step(10, FORWARD, SINGLE); 
    buttonState = digitalRead(buttonPin);
   }
 raftFound = true;
 Serial.println("ahh! There it is. :)");
 motor1.release();
 delay(700); // Delay a little bit to calm everything down
} 


//working through the dispensing instructions until drink is complete and paddle is at last optic position:
if (drinkRequested == true){  
  for (int optic = 0; optic < opticCount; optic++) { //Move to pump 
motor1.step((drinkMatrix[optic][0] * 10), BACKWARD, SINGLE); //move the paddle according to instruciton, x10 to allow us to compress serial data transfer length
motor1.release(); // let the motor's magnets relax
//dispense what is required then resume moving to the next position:
while(drinkMatrix[optic][2] > 0 && raftFound == true){
        delay(500);
        motor2.step(3700, BACKWARD, DOUBLE);
        motor2.release();
        delay((drinkMatrix[optic][1]) * 100);
        motor2.step(3700, FORWARD, DOUBLE);
        motor2.release();
        drinkMatrix[optic][2] = drinkMatrix[optic][2]-1;
         delay(500); 
    }
  }

//Drink complete  
  Serial.println("Drinks ready, enjoy.");
  drinkRequested = false;
  raftFound=false;
}

 while(drinkRequested == false){
 delay(200);

   if (Serial.available()) {
    for (int optic = 0; optic < opticCount; optic++){
      for (int parameter = 0; parameter < parameterCount; parameter++){     
        for (int parameterMeasure = 0; parameterMeasure < parameterSize; parameterMeasure++){
          if (Serial.available()) {
            serialNumber = Serial.read(); /* load the number from serial buffer */
            serialNumber = serialNumber - 48; /* convert number to text number */
            numberCollector = numberCollector * 10 + serialNumber; /*store and build the number*/
          } else {
            delay(250);
            serialNumber = Serial.read(); /* load the number from serial buffer */
            serialNumber = serialNumber - 48; /* convert number to text number */
            numberCollector = numberCollector * 10 + serialNumber; /*store and build the number*/     
          }
        }
       drinkMatrix[optic][parameter] = numberCollector;   /* store the value in the array  */
       numberCollector =  0;   /* Prepare variable for next number  */
       serialNumber = Serial.read(); /* to clear the comma from the buffer */
      }
      }
    CheckArray();
    Serial.println("Done loading");
    drinkRequested = true;
    }
    
 }
    
}


void CheckArray(){
//print out the array to check it:
for(int i = 0; i < opticCount; i++) {
  for(int j = 0; j < parameterCount; j++) {
    Serial.print(drinkMatrix[i][j]);
    Serial.print(",");
  }
  Serial.println();
}
}
