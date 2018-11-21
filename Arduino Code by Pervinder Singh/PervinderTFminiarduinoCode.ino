 /*
  * @File  : PervinderTFminiarduinoCode.ino
  * @Brief : This example use TFmini to measure distance
  *         With initialization completed, we can get x,y,z co-ordinate of the point
  *
  *             GNU Lesser General Public License
  *
  * @version  V1.0
  * @date  2018-1-10
  */
  
#include <DFRobot_TFmini.h>
#include <Servo.h>

SoftwareSerial mySerial(0, 1); // RX, TX

Servo servoRotate;
Servo servoScan;

int servoRotatePosition = 0;
int servoScanPosition = 0;

int servoRotateDirection = 1;
int servoScanDirection = 1;


DFRobot_TFmini  TFmini;
uint16_t  distance;

void setup(){

    servoRotate.attach(9);  //Servo making the pan movement
    servoScan.attach(7);    //Servo making the tilt movement
    //Serial.begin(9600); 

  
    Serial.begin(115200);
    TFmini.begin(mySerial);

    while (!Serial);
    Serial.println ("0 0 0");

    

    servoRotate.write(180);
    servoScan.write(180);
    delay(1000);

    while (!Serial.available()) {}

    //Moving to initial position
    servoRotate.write(servoRotatePosition);
    servoScan.write(servoScanPosition);
    delay(1000);

    
}

void loop(){

   if (servoScanPosition <= 180)
  {

    servoRotate.write(servoRotatePosition);
    servoScan.write(servoScanPosition);


    // Pooling the sensor from inside nested loops was giving bugs and freezing the loops
    // The following code will make both servos move using only the built-in arduino loop()

    //Making the pan servo move both ways
    if (servoRotateDirection == 1)
      servoRotatePosition++;
    else
      servoRotatePosition--;


    //Changing the direction in the edges
    //Moving the tilt servo only when the pan reaches each side
    if (servoRotatePosition == 180 || servoRotatePosition == 0 )
    {
      servoRotateDirection = -servoRotateDirection;
      servoScanPosition = (servoScanPosition + 1)%182;
    }

    //Delay to allow servos moving and sensor reading
    delay(20);

    
  }
    if(TFmini.measure()){                      //Measure Distance and get signal strength
        distance = TFmini.getDistance();       //Get distance data
        Serial.print(distance);
        Serial.print(" ");
        Serial.print(servoRotatePosition);
        Serial.print("  ");
        Serial.print(servoScanPosition);
        Serial.println("  ");
        
      
        delay(25);
    }
    
}
