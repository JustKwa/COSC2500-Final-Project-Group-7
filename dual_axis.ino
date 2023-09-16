#include <Servo.h>
//defining Servos for horizontal movement
Servo servoHori;
int servoHoriPos = 0;
const int SERVO_HORI_HIGH_LIMIT = 160;
const int SERVO_HORI_LOW_LIMIT = 20;

//defining Servos for vertical movement
Servo servoVert; 
int servoVertPos = 0; 
const int SERVO_VERT_HIGH_LIMIT = 160;
const int SERVO_VERT_LOW_LIMIT = 20;

//Assigning LDRs
int ldrtopl = 12; //top left LDR 
int ldrtopr = 13; //top right LDR 
int ldrbotl = 14; // bottom left LDR 
int ldrbotr = 15; // bottom right LDR 
void setup () 
{
  servoHori.attach(10);
  servoHori.write(0);
  servoVert.attach(9);
  servoVert.write(0);
  delay(500);
}

void loop()
{
  servoHoriPos = servoHori.read();
  servoVertPos = servoVert.read();

  //capturing analog values of each LDR
  int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);

  // calculating average
  int avgtop = (topl + topr) / 2; //average of top LDRs
  int avgbot = (botl + botr) / 2; //average of bottom LDRs
  int avgleft = (topl + botl) / 2; //average of left LDRs
  int avgright = (topr + botr) / 2; //average of right LDRs

  if (avgtop < avgbot)
  {
    servoVert.write(servoVertPos +1);
    if (servoVertPos > SERVO_VERT_HIGH_LIMIT) 
     { 
      servoVertPos = SERVO_VERT_HIGH_LIMIT;
     }
    delay(10);
  }
  else if (avgbot < avgtop)
  {
    servoVert.write(servoVertPos -1);
    if (servoVertPos < SERVO_VERT_LOW_LIMIT)
  {
    servoVertPos = SERVO_VERT_LOW_LIMIT;
  }
    delay(10);
  }
  else 
  {
    servoVert.write(servoVertPos);
  }
  
  if (avgleft > avgright)
  {
    servoHori.write(servoHoriPos +1);
    if (servoHoriPos > SERVO_HORI_HIGH_LIMIT)
    {
    servoHoriPos = SERVO_HORI_HIGH_LIMIT;
    }
    delay(10);
  }
  else if (avgright > avgleft)
  {
    servoHori.write(servoHoriPos -1);
    if (servoHoriPos < SERVO_HORI_LOW_LIMIT)
     {
     servoHoriPos = SERVO_HORI_LOW_LIMIT;
     }
    delay(10);
  }
  else 
  {
    servoHori.write(servoHoriPos);
  }
  delay(50);
}