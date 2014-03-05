#include <Servo.h>

Servo servoArray[4];
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;


//Set constants for Motors
//Can only use PWM pins, must be 3,5,6,9 on Uno
const int fl = 3;  //Front left
const int fr = 5;  //Front right
const int bl = 6;  //Back left
const int br = 9;  //Back right

/*Define controllers. Names are the same as motor constants
 with a C added afterword */

Servo flc;
Servo frc; 
Servo blc;
Servo brc;

//Current speed values of each servo
int flc_s = 0;
int frc_s = 0;
int blc_s = 0;
int brc_s = 0;

//TODO - Make sure the actual global variables are being accessed 
int speedArray[4];

void setup()
{
  /*Device setup*/
  /*This calibrates and arms the ESC controllers */

  // pinMode(RED_PIN, OUTPUT);
  // pinMode(GREEN_PIN, OUTPUT);
  // pinMode(blUE_PIN, OUTPUT);



  flc.attach(fl);
  frc.attach(fr);
  blc.attach(bl);
  brc.attach(br);

  //Initialize array of motors. Use standard PWM pins
  servoArray[0] = flc;
  servoArray[1] = frc;
  servoArray[2] = blc;
  servoArray[3] = brc;

  //Initialize array of motor speeds
  speedArray[0] = flc_s;
  speedArray[0] = frc_s;
  speedArray[0] = blc_s;
  speedArray[0] = brc_s;

  for (int i=0; i<4; i++)
  {

    /*On each motor, write lowest throttle signal (0)
     to ESC. This should be a 1 ms pulse.  Repeat this
     every 20 ms. */

    //NOTE - Timing may need to be adjusted to the specific ESC
    for (int j=0; j<1000; j++)
    {
      servoArray[i].write(0); 
      delay(20);
    }

    /*Write high throttle signal (180) for calibration */
    for (int j=0; j<1000; j++)
    {
      servoArray[i].write(180); 
      delay(20);
    }

  }


  Serial.begin(9600);


} 
void loop()
{


  /*Listen for inputs from controller. 
   */

  /* Write current set speed to each controller. Repeat every 2 ms. */
  for (int k=0;k<4;k++)
  {
    servoArray[k].write(speedArray[k]);
  }
  delay(2);



}

//Motor functions
//When calling any motor function, call hover() to reset all values;
//TODO - Is this safe? Will this cause a problem, even for a ms?
void turnLeft()
{
  //Lower power to left motors 

  //setMotorSpeed(fl,100);
  //setMotorSpeed(bl,100);

  flc_s = 100;
  blc_s = 100;

}


void turnRight()
{
  //Lower power to right motors 

  hover();

  //setMotorSpeed(fr,100);
  //setMotorSpeed(br,100);
  
  frc_s = 100;
  blc_s = 100;

}


void hover()
{
  //Clear all previous values for motors. 
  //Maintain constant height. Lock all motors at hovering speed.
  //This is the first fail-safe, use to prevent collisions.

  //Set all motors to middle speed
  /*for (int i=0; i<4;i++)
   {
   setMotorSpeed(servoArray[i],150);
   } */
   
   for (int l;l<4;l++)
   {
      speedArray[l] = 140;
   }

}

void forward()
{
  //Decrease power to forward motors
  //TODO - How to compensate rear altitude rise? 

  hover();
  /*
   //TODO - Check numbers
   setMotorSpeed(fl,100);
   setMotorSpeed(fr,100); */
   
  flc_s = 100;
  frc_s = 100;
  
}
void backward()
{
  //Decrease power to front motors

  hover();
  //   setMotorSpeed(bl,100);
  //  setMotorSpeed(br,100);
  blc_s = 100;
  brc_s = 100;

}




void setMotorSpeed(Servo servo,int s)
{
  //DEPRECATED. Use Servo methods instead
  //Set speed of motor 'motor' to value of s.
  //Speed values can only be 0-255 inclusive. Limit values to this range. 
  if (s>180)
  {
    servo.write(180);
  }
  if (s<0)
  {
    s = 0;
  }

  //QUESTION - Does this only work for one motor? how to handle concurrent motors?
  //analogWrite(motor,s);
}


void emergencyStop()
{
  //Stop all motors. This is the last failsafe.
  /* for (int i;i<=(sizeof(servoArray)/sizeof(int));i++)
   {
   setMotorSpeed(servoArray[i],0);  
   } */
   
   for (int l;l<4;l++)
   {
      speedArray[l] = 0;
   }
   
}


//Sensor functions

boolean collisionImminent()
{
  //Get distance from collision sensor, stop movement and hover if collision is near.
  hover();
}


