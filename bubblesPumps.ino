#include <Arduino.h>

const int perPump1 = 2;
const int perPump2 = 3;
const int perPump3 = 4;
const int sumpPump1 = 7;
const int sumpPump2 = 6;
const int sumpPump3 = 5;

int sumpPumpTime = 900;

byte serialNumber = 0;
void CheckMatrix();
int numberCollector;
int pumpCount = 6;
int paramaterCount = 2;
int paramaterSize = 2;

int pumpingMatrix[6][2] { 
  "00,30,01,20,02,00,03,40,04,00,05,00," };

bool readyToPump = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(perPump1, OUTPUT);
  pinMode(perPump2, OUTPUT);
  pinMode(perPump3, OUTPUT);
  pinMode(sumpPump1, OUTPUT);
  pinMode(sumpPump2, OUTPUT);
  pinMode(sumpPump3, OUTPUT);
  digitalWrite(perPump1, HIGH);
  digitalWrite(perPump2, HIGH);
  digitalWrite(perPump3, HIGH);
  digitalWrite(sumpPump1, HIGH);
  digitalWrite(sumpPump2, HIGH);
  digitalWrite(sumpPump3, HIGH);

  Serial.begin(19200);

  Serial.println("Starting Pump Monitors");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  if (readyToPump == true)
  {
    delay(1000);
    //pump from matrix
    for (int pump = 0; pump < pumpCount; pump++)
    {
      int timeToPump = pumpingMatrix[pump][1];
      
      if (timeToPump <= 0) { continue; }

      Serial.print("Pumping Pump: ");
      Serial.print(pump);
      Serial.println();
      Serial.print("For ");
      Serial.print(timeToPump);
      Serial.print(" seconds");
      Serial.println();
      
      int pumpToPump = 0;
      if (pump = 0) { pumpToPump = perPump1; }
      if (pump = 1) { pumpToPump = perPump2; }
      if (pump = 2) { pumpToPump = perPump3; }
      if (pump = 3) { pumpToPump = sumpPump1; }
      if (pump = 4) { pumpToPump = sumpPump2; }
      if (pump = 5) { pumpToPump = sumpPump3; }
     
      if (pumpToPump <= 4) //4 is our highest pin for percise pumps, sump pumps on higher pins
      {
        timeToPump = timeToPump * 1000;
        digitalWrite(pumpToPump, LOW);
        delay(timeToPump);
        digitalWrite(pumpToPump, HIGH);
        delay(200);
      }
      else
      {
        int numTimesToPump = timeToPump;//number of 1 oz pours we should make (we make 1oz pours in 0.8 sec flicks w/ a delay)
        for (int timesPumped = 0; timesPumped < timeToPump; timesPumped++)
        {
          digitalWrite(pumpToPump, LOW);
          delay(sumpPumpTime);
          digitalWrite(pumpToPump, HIGH);
          delay(2500);
        }
      }
    }
    readyToPump = false;
  }
  

  while (readyToPump == false)
  {
    delay(200);
    if (Serial.available()) 
    {
      for (int _pump = 0; _pump < pumpCount; _pump++){
        for (int paramater = 0; paramater < paramaterCount; paramater++){
          for (int paramaterMeasure = 0; paramaterMeasure < paramaterSize; paramaterMeasure++){
            if (Serial.available()) {
              serialNumber = Serial.read();
              serialNumber = serialNumber - 48;
              numberCollector = numberCollector * 10 + serialNumber;
            }
          }
          pumpingMatrix[_pump][paramater] = numberCollector;
          numberCollector = 0;
          serialNumber = Serial.read(); //clear comma from buffer
        }
      }
      CheckMatrix();
      Serial.println("Done loading");
      readyToPump = true;
    }
  }
}

void CheckMatrix()
{
  for ( int i = 0; i < pumpCount; i++)
  {
    for(int j = 0; j < paramaterCount; j++)
    {
      Serial.print(pumpingMatrix[i][j]);
      Serial.print(",");
    }
    Serial.println();
  }
}
