#include <PS3USB.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
PS3USB PS3(&Usb); 

int l1=32, l2=33, r1=34, r2=35, w1=36, w2=37, d1=38, d2=39;
int minxy=117, maxxy=137;

void disp_hat();
void ctrl_hat();
void ctrl_WASD();

void ctrl_test(); 
//make different functions for all 8 motions and control functions using UP, DOWN, RIGHT, LEFT, Shapes and Joystick button R3, L3


void setup() 
{  
Serial.begin(115200);
pinMode(l1,OUTPUT);
pinMode(l2,OUTPUT);
pinMode(r1,OUTPUT);
pinMode(r2,OUTPUT);
pinMode(w1,OUTPUT);
pinMode(w2,OUTPUT);
pinMode(d1,OUTPUT);
pinMode(d2,OUTPUT); 
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) 
  {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 USB Library Started"));
  
  digitalWrite(r1,LOW);
  digitalWrite(r2,LOW);
  digitalWrite(l1,LOW);
  digitalWrite(l2,LOW);
}

void loop() 
{
  Usb.Task();
  if (PS3.PS3Connected)
  {
    if (PS3.getAnalogHat(LeftHatX) > maxxy || PS3.getAnalogHat(LeftHatX) < minxy || PS3.getAnalogHat(LeftHatY) > maxxy || PS3.getAnalogHat(LeftHatY) < minxy || PS3.getAnalogHat(RightHatX) > maxxy || PS3.getAnalogHat(RightHatX) < minxy || PS3.getAnalogHat(RightHatY) > maxxy || PS3.getAnalogHat(RightHatY) < minxy) 
    {
        ctrl_hat();
    }   

    ctrl_WASD();
    
    if(PS3.getButtonPress(TRIANGLE)||(PS3.getButtonPress(L3))||(PS3.getButtonPress(R3)))
    {
      Serial.print(F("\r\nSTOP"));
      digitalWrite(r1,LOW);
      digitalWrite(r2,LOW);
      digitalWrite(l1,LOW);
      digitalWrite(l2,LOW);
      digitalWrite(d1,LOW);
      digitalWrite(d2,LOW);
    }

    if(PS3.getButtonPress(CROSS))
    { 
      Serial.print(F("\r\nSTOP ALL"));
      digitalWrite(r1,LOW);
      digitalWrite(r2,LOW);
      digitalWrite(l1,LOW);
      digitalWrite(l2,LOW);
      digitalWrite(d1,LOW);
      digitalWrite(d2,LOW);
      digitalWrite(w1,LOW);
      digitalWrite(w2,LOW);
    }
    
    if(PS3.getButtonPress(CIRCLE)||(PS3.getButtonPress(SQUARE)))
    {
      Serial.print(F("\r\nPADDLE REVERSE"));
      digitalWrite(w1,LOW);
      digitalWrite(w2,HIGH);
    }
    
    if (PS3.getAnalogButton(L2)>10)                         //LEFT zero turn     
      {
          Serial.print(F("\r\nZERO LEFT"));
          digitalWrite(r1,HIGH);
          digitalWrite(r2,LOW);
          digitalWrite(l1,LOW);
          digitalWrite(l2,HIGH);
          digitalWrite(d1,LOW);
          digitalWrite(d2,HIGH);
      }

    if (PS3.getAnalogButton(R2)>10)                         //RIGHT zero turn
      { 
          Serial.print(F("\r\nZERO RIGHT"));
          digitalWrite(r1,LOW);
          digitalWrite(r2,HIGH);
          digitalWrite(l1,HIGH);
          digitalWrite(l2,LOW);
          digitalWrite(d1,HIGH);
          digitalWrite(d2,LOW);
      }
    
    /*if((PS3.getAnalogButton(L2)<10)&&(PS3.getAnalogButton(R2)<10))
    {
      Serial.print(F("\r\nSTOP ZERO"));
      digitalWrite(r1,LOW);
      digitalWrite(r2,LOW);
      digitalWrite(l1,LOW);
      digitalWrite(l2,LOW);
      digitalWrite(d1,LOW);
      digitalWrite(d2,LOW);      
    }*/
    
   if (PS3.getButtonClick(SELECT))
      {                                       
        Serial.print(F("\r\nPADDLE STOP"));  
        digitalWrite(w1,LOW);
        digitalWrite(w2,LOW);                                        
      }                                      
    
   if (PS3.getButtonClick(START))
      {                                       
      Serial.print(F("\r\nPADDLE START"));                                    
      digitalWrite(w1,HIGH);
      digitalWrite(w2,LOW);
      }     

/*   else  
      {
            digitalWrite(r1,LOW);
            digitalWrite(r2,LOW);
            digitalWrite(l1,LOW);
            digitalWrite(l2,LOW);
            digitalWrite(d1,LOW);
            digitalWrite(d2,LOW);
      }*/
    }
}

void ctrl_WASD()
{
    if(PS3.getButtonPress(RIGHT)&&!PS3.getButtonPress(LEFT)&&!PS3.getButtonPress(UP)&&!PS3.getButtonPress(DOWN))       //right
    {
          digitalWrite(r1,LOW);
          digitalWrite(r2,HIGH);
          digitalWrite(l1,HIGH);
          digitalWrite(l2,LOW);
          digitalWrite(d1,LOW);
          digitalWrite(d2,HIGH); 
          Serial.print(F("\nRight"));
    }
    
    if(!PS3.getButtonPress(RIGHT)&&PS3.getButtonPress(LEFT)&&!PS3.getButtonPress(UP)&&!PS3.getButtonPress(DOWN))       //left
    {
          digitalWrite(l1,LOW);
          digitalWrite(l2,HIGH);
          digitalWrite(r1,HIGH);
          digitalWrite(r2,LOW);
          digitalWrite(d1,HIGH);
          digitalWrite(d2,LOW);  
          Serial.print(F("\nLeft"));
    }

    if(!PS3.getButtonPress(RIGHT)&&!PS3.getButtonPress(LEFT)&&PS3.getButtonPress(UP)&&!PS3.getButtonPress(DOWN))       //forward
    {
      digitalWrite(l1,HIGH);
      digitalWrite(l2,LOW);
      digitalWrite(r1,HIGH);
      digitalWrite(r2,LOW);
      digitalWrite(d1,LOW);
      digitalWrite(d2,LOW);  
      Serial.print(F("\nForward"));
    }

    if(!PS3.getButtonPress(RIGHT)&&!PS3.getButtonPress(LEFT)&&!PS3.getButtonPress(UP)&&PS3.getButtonPress(DOWN))       //reverse
    {
      digitalWrite(l1,LOW);
      digitalWrite(l2,HIGH);
      digitalWrite(r1,LOW);
      digitalWrite(r2,HIGH);
      digitalWrite(d1,LOW);
      digitalWrite(d2,LOW);
      Serial.print(F("\nReverse"));
    }

    if(!PS3.getButtonPress(RIGHT)&&PS3.getButtonPress(LEFT)&&PS3.getButtonPress(UP)&&!PS3.getButtonPress(DOWN))      //forward left
    {
       digitalWrite(r1,HIGH);
       digitalWrite(r2,LOW);
       digitalWrite(d1,HIGH);
       digitalWrite(d2,LOW);  
       digitalWrite(l1,LOW);
       digitalWrite(l2,LOW);
       Serial.print(F("\nForward and LEFT"));
    }

    if(PS3.getButtonPress(RIGHT)&&!PS3.getButtonPress(LEFT)&&PS3.getButtonPress(UP)&&!PS3.getButtonPress(DOWN))      //forward right
    {
       digitalWrite(l1,HIGH);
       digitalWrite(l2,LOW);
       digitalWrite(d1,LOW);
       digitalWrite(d2,HIGH);
       digitalWrite(r1,LOW);
       digitalWrite(r2,LOW);
       Serial.print(F("\nForward and RIGHT"));
    }

    if(!PS3.getButtonPress(RIGHT)&&PS3.getButtonPress(LEFT)&&!PS3.getButtonPress(UP)&&PS3.getButtonPress(DOWN))      //reverse left
    {
       digitalWrite(l1,LOW);
       digitalWrite(l2,HIGH);
       digitalWrite(d1,HIGH);
       digitalWrite(d2,LOW);  
       digitalWrite(r1,LOW);
       digitalWrite(r2,LOW);
       Serial.print(F("\nReverse and LEFT"));
    }

    if(PS3.getButtonPress(RIGHT)&&!PS3.getButtonPress(LEFT)&&!PS3.getButtonPress(UP)&&PS3.getButtonPress(DOWN))      //reverse right
    {
       digitalWrite(r1,LOW);
       digitalWrite(r2,HIGH);
       digitalWrite(d1,LOW);
       digitalWrite(d2,HIGH);
       digitalWrite(l1,LOW);
       digitalWrite(l2,LOW);  
       Serial.print(F("\nReverse and RIGHT"));
    }
}
void disp_left_hat()
{
    if (PS3.getAnalogHat(LeftHatX) > maxxy || PS3.getAnalogHat(LeftHatX) < minxy || PS3.getAnalogHat(LeftHatY) > maxxy || PS3.getAnalogHat(LeftHatY) < minxy || PS3.getAnalogHat(RightHatX) > maxxy || PS3.getAnalogHat(RightHatX) < minxy || PS3.getAnalogHat(RightHatY) > maxxy || PS3.getAnalogHat(RightHatY) < minxy) 
    {
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(PS3.getAnalogHat(LeftHatX));
      Serial.print(F("\tLeftHatY: "));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      Serial.print(F("\tRightHatX: "));
      Serial.print(PS3.getAnalogHat(RightHatX));
      Serial.print(F("\tRightHatY: "));
      Serial.print(PS3.getAnalogHat(RightHatY));
    }  
}

void ctrl_hat()
{
    if((PS3.getAnalogHat(RightHatX) < maxxy) && (PS3.getAnalogHat(RightHatX) > minxy)&&(PS3.getAnalogHat(LeftHatX) < maxxy) && (PS3.getAnalogHat(LeftHatX) > minxy)&&(PS3.getAnalogHat(RightHatY) < maxxy) && (PS3.getAnalogHat(RightHatY) > minxy)&&(PS3.getAnalogHat(LeftHatY) < maxxy) && (PS3.getAnalogHat(LeftHatY) > minxy)&&(PS3.getAnalogButton(L2)<10)&&(PS3.getAnalogButton(R2)<10))          //stop - center position
    {
          digitalWrite(l1,LOW);
          digitalWrite(l2,LOW);
          digitalWrite(r1,LOW);
          digitalWrite(r2,LOW);
          digitalWrite(d1,LOW);
          digitalWrite(d2,LOW);
          Serial.print(F("\nSTOP-HAT"));
    }
    
    if((PS3.getAnalogHat(RightHatX) > maxxy)||(PS3.getAnalogHat(LeftHatX) > maxxy))       //right
    {
          digitalWrite(r1,LOW);
          digitalWrite(r2,HIGH);
          digitalWrite(l1,HIGH);
          digitalWrite(l2,LOW);
          digitalWrite(d1,LOW);
          digitalWrite(d2,HIGH); 
          Serial.print(F("\nRight"));
    }
    
    if((PS3.getAnalogHat(RightHatX) < minxy)||(PS3.getAnalogHat(LeftHatX) < minxy))       //left
    {
          digitalWrite(l1,LOW);
          digitalWrite(l2,HIGH);
          digitalWrite(r1,HIGH);
          digitalWrite(r2,LOW);
          digitalWrite(d1,HIGH);
          digitalWrite(d2,LOW);  
          Serial.print(F("\nLeft"));
    }

    if((PS3.getAnalogHat(RightHatY) < minxy)||((PS3.getAnalogHat(LeftHatY) < minxy)))       //forward
    {
      digitalWrite(l1,HIGH);
      digitalWrite(l2,LOW);
      digitalWrite(r1,HIGH);
      digitalWrite(r2,LOW);
      digitalWrite(d1,LOW);
      digitalWrite(d2,LOW);  
      Serial.print(F("\nForward"));
    }

    if((PS3.getAnalogHat(RightHatY) > maxxy)||((PS3.getAnalogHat(LeftHatY) > maxxy)))       //reverse
    {
      digitalWrite(l1,LOW);
      digitalWrite(l2,HIGH);
      digitalWrite(r1,LOW);
      digitalWrite(r2,HIGH);
      digitalWrite(d1,LOW);
      digitalWrite(d2,LOW);
      Serial.print(F("\nReverse"));
    }

    if(((PS3.getAnalogHat(RightHatY) < minxy)||((PS3.getAnalogHat(LeftHatY) < minxy)))&&((PS3.getAnalogHat(RightHatX) < minxy)||(PS3.getAnalogHat(LeftHatX) < minxy)))      //forward left
    {
       digitalWrite(r1,HIGH);
       digitalWrite(r2,LOW);
       digitalWrite(d1,HIGH);
       digitalWrite(d2,LOW);  
       digitalWrite(l1,LOW);
       digitalWrite(l2,LOW);
       Serial.print(F("\nForward and LEFT"));
    }

    if(((PS3.getAnalogHat(RightHatY) < minxy)||((PS3.getAnalogHat(LeftHatY) < minxy)))&&((PS3.getAnalogHat(RightHatX) > maxxy)||(PS3.getAnalogHat(LeftHatX) > maxxy)))      //forward right
    {
       digitalWrite(l1,HIGH);
       digitalWrite(l2,LOW);
       digitalWrite(d1,LOW);
       digitalWrite(d2,HIGH);
       digitalWrite(r1,LOW);
       digitalWrite(r2,LOW);
       Serial.print(F("\nForward and RIGHT"));
    }

    if(((PS3.getAnalogHat(RightHatY) > maxxy)||((PS3.getAnalogHat(LeftHatY) > maxxy)))&&((PS3.getAnalogHat(RightHatX) < minxy)||(PS3.getAnalogHat(LeftHatX) < minxy)))      //reverse left
    {
       digitalWrite(l1,LOW);
       digitalWrite(l2,HIGH);
       digitalWrite(d1,HIGH);
       digitalWrite(d2,LOW);  
       digitalWrite(r1,LOW);
       digitalWrite(r2,LOW);
       Serial.print(F("\nReverse and LEFT"));
    }

    if(((PS3.getAnalogHat(RightHatY) > maxxy)||((PS3.getAnalogHat(LeftHatY) > maxxy)))&&((PS3.getAnalogHat(RightHatX) > maxxy)||(PS3.getAnalogHat(LeftHatX) > maxxy)))      //reverse right
    {
       digitalWrite(r1,LOW);
       digitalWrite(r2,HIGH);
       digitalWrite(d1,LOW);
       digitalWrite(d2,HIGH);
       digitalWrite(l1,LOW);
       digitalWrite(l2,LOW);  
       Serial.print(F("\nReverse and RIGHT"));
    }
}

void ctrl_test() 
{
          digitalWrite(l2,LOW);
          digitalWrite(l1,HIGH);
          /*digitalWrite(r1,HIGH);
          digitalWrite(r2,LOW);
          digitalWrite(d1,HIGH);
          digitalWrite(d2,LOW);
          digitalWrite(w1,HIGH);
          digitalWrite(w2,LOW);
*/
}
