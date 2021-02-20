

  // RECIVER CODE FOR HAND GESTURE CONTROLLED AC LIGHT DIMMER //

#include <VirtualWire.h>               // LIBRARY USED , AVAILABLE AT GITHUB 
int AC_LOAD = 3;                       // MOC3021 DRIVING PIN WHICH FURTHER FIRING TRIAC
int dimming ;                          // DIMMING LEVEL (0-100)  0 = ON, 100 = OFF
int ZEROCROSSINGPin = 2;               // SET D2 PIN FOR CHK ZERO CROSSING OF SINEWAVE
int PINState = 0;                      //BY DEFAULT PIN STATE LOW
#include<String.h>
String msg;
int c ;
void setup()
{
Serial.begin(9600);                  //ENABLE FOR SERIAL MONITOR
  vw_set_rx_pin(12);                   //SET D12 AS RX PIN 
  vw_setup(4000);                      // BITS PER SECONDS
  vw_rx_start();                       // START RECIVEING
  pinMode(AC_LOAD, OUTPUT);            // SET AC_LOAD PIN 3 AS OUTPUT
  pinMode(12, INPUT);                  // SET D12 PIN AS INPUT
}


void mainfunction()
{
    dimming = c;                       // DIMMING LEVEL
int dimtime = (70*dimming);            // FOR 50HZ   
  delayMicroseconds(dimtime);          // WAIT TILL FIRING THE TRIAC    
  digitalWrite(AC_LOAD, LOW);          // FIRE THE TRIAC TRIAC
  delayMicroseconds(25);               // TRIAC ON DELAY      
  digitalWrite(AC_LOAD,HIGH);          // NO LONGER TRIGGER THE TRIAC (the next zero crossing will swith it off) TRIAC


                           
  uint8_t buf[2];                      // RECIVE DATA AND CONVERT IT IN TO INTEZER
  uint8_t buflen = sizeof(buf);;
  if (vw_get_message(buf, &buflen))   
  {
    int i;
    msg = ((char*)buf);
  }
  c = msg.substring(0,2). toInt();;    
  Serial.println(c);                   // FOR TESTING PURPOSE ONLY
 
        }
        
void loop()
{
  int PINState = digitalRead(ZEROCROSSINGPin);
  if (PINState == CHANGE) {
  mainfunction();                     // IN MAIN FUNCTION DATA RECIVED AND LIGH DIMMING AS PER DATA RECIVED
  }
}



  

  
