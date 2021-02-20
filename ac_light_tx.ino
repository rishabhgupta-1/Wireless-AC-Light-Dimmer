// TRANSMITTOR CODE FOR HAND GESTURE CONTROLLED AC LIGHT DIMMER 


#include <VirtualWire.h>                         // LIBRARY 
#include <Wire.h>                                //ALL LIBRARY AVAILABLE AT GITHUB
#include <MPU6050.h> 
#include <String.h>                               //ALL LIBRARY AVAILABLE AT GITHUB
MPU6050 gy_521;
int16_t ax, ay, az;
int16_t gx, gy, gz;
void setup()
{
  Wire.begin( );
//Serial.begin(9600); // initializing serial //ONLY ENABLE FOR TESTING PURPOSE 
Serial.println ("Initializing MPU and testing connections");
gy_521.initialize ( );
Serial.println(gy_521.testConnection( ) ? "Successfully Connected" : "Connection failed");
Serial.begin(9600);  

      vw_set_tx_pin(11);                          // Sets pin D12 as the TX pin
    vw_setup(4000);                               // Bits per sec
}


void sense()                                     // FUNCTION FOR SENSE X AXIS AND Y AXIS
{
gy_521.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
ay = map(ay, -17000, 17000, 40, 77);             // AY = Y AXIS AND Y = 40 TO 77

ax = map(ax, -17000, 17000, 0, 100);            //AX = X AXIS AND X = 0 TO 100

}
void sendd()                                     // FUNCTION FOR SEND DATA THROUGH RF MODULE 
{

  String data = String(ay);
 const char *msg = data.c_str();;
  vw_send((uint8_t *)msg, strlen(msg));    
  vw_wait_tx();
  delay(50);
 Serial.println (ay);                    // ONLY ENABLE FOR TESTING PURPOSE 
Serial.println (ax);                     // ONLY ENABLE FOR TESTING PURPOSE 

}


void loop()                                //RUN REPEATLY
{
    sense();                               // SENSING
    if (ax>30 && ax <70)                   //CHK IF UR HAND IS NOT IN PROPER POSITION THEN DATA IS NOT SEND 
    {
sendd();                                   //SEND DATA
}
}
