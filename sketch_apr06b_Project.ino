/* 
 Remote controlled lamps
 
 This program controls a simple arduino Uno controlled autonomous robot to navigate an already known 
 path with 8 stations. The code continuosly wait for user input (from a connected IR remote controller 
 and 1838T IR receiver) for destination. It then uses a combination of the saved current robot station 
 and the user destination to call the corresponding navigation function
 */
 
 
 
 #include <IRremote.h>

int dir1PinB = 8;                             //pin to control the direction of right DC motor
int dir2PinB = 9;                             //pin to control the direction of right DC motor
int rgtMtrSpd = 10;                             //pin to control the speed of right DC motor
int dir1PinA = 13;                             //pin to control the direction of left DC motor                  
int dir2PinA = 12;                             //pin to control the direction of left DC motor
int lftMtrSpd = 11;                             //pin to control the speed of left DC motor
int RMT_RECV_PIN =6;                           //pin 6 used as IR receiver signal

 
int intCnt=1;                                   //intersection counter
int dstCnt;                                  //destination counter
int lftSnsr = 3;                                      //left sensor
int rgtSnsr = 2;                                      //right sensor





long REMOTE_RIGHT = 0x00FF02FD;
long REMOTE_LEFT = 0x00FF22DD;
long REMOTE_STOP = 0x00FFC23D;
long REMOTE_ONE = 0x00FF30CF;
long REMOTE_TWO = 0x00FF18E7;
long REMOTE_THREE = 0x00FF7A85;
long REMOTE_FOUR = 0x00FF10EF;
long REMOTE_FIVE = 0x00FF38C7;
long REMOTE_SIX = 0x00FF5AA5;
long REMOTE_SEVEN = 0x00FF42BD;
long REMOTE_EIGHT = 0x00FF4AB5;


//PIN 12 AND 13 CONTROL LEFT MOTOR AND PIN 3 CONTROL LEFT SENSOR
//PIN 10 AND 9 CONTROL RIGHT MOTOR AND PIN 2 CONTROL RIGHT SENSOR

void path(int num1, int num2);

IRrecv irrecv(RMT_RECV_PIN);
decode_results IRvalue;

void setup() { 
  Serial.begin(9600);                                             // baud rate
  pinMode(lftSnsr, INPUT);                                                                                    
  pinMode(rgtSnsr,INPUT);                                                                                    
  pinMode(lftMtrSpd, OUTPUT);                                                                                  
  pinMode(dir1PinB, OUTPUT);
  pinMode(dir2PinB,OUTPUT);
  pinMode(rgtMtrSpd, OUTPUT);
  pinMode(dir1PinA,OUTPUT);
  pinMode(dir2PinA,OUTPUT);
  pinMode(RMT_RECV_PIN, INPUT);
  irrecv.enableIRIn();                                                                                          //Start the 1838T IR receiver  

}

void loop() 
{
  int i=0;
   if (irrecv.decode(&IRvalue)) 
   {
   irrecv.resume();                                                                                             //Continuously wait for input from receiver 
   dstCnt = IRvalue.value;                                                                                      //input value is destination
   path(intCnt, dstCnt);                                                          //call the path function using the current station = intCnt and the destination = dstCnt
   }
  
}







void goforward()
{
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);
  analogWrite(lftMtrSpd, 60);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
  analogWrite(rgtMtrSpd, 50);
}

void left()
{
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, LOW);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
}

void right()
{
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, LOW);
}

void STOP(int del)
{
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, LOW);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, LOW);
  delay(del);
}
   
void rleft()
{
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, LOW);
}
   
void rright()
{
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, LOW);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
}

void goforward1()
{
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
}

void turnback()
{
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, LOW);
  delay(900);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, LOW);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
  delay(600);
}
 
/*******************************************************************************************************************************************/
/******************************************************   POINT-ONE to POINT-TWO   *********************************************************/
/*******************************************************************************************************************************************/
void One_Two()                                                                                              //begin One_Two
{
  intCnt = 1;
  while( intCnt ==1)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )
              {  
                 STOP(250);
                 right();
                 delay(1200);
                 STOP(250);
                 intCnt = 700;
              }
  }
  while (intCnt ==700)
  {
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )
              {  
                 STOP(250);
                 turnback();
                 intCnt = 2;
              }
  }

}                                                                                              //end One_Two
/*******************************************************************************************************************************************/
/******************************************************   POINT-ONE to POINT-THREE   *******************************************************/
/*******************************************************************************************************************************************/
void One_Three()                                                                                              //begin One_Three
{
  intCnt = 1;
  while( intCnt ==1)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )
              {  
                 STOP(250);
                 right();
                 delay(1200);
                 STOP(250);
                 intCnt = 700;
              }
  }
  while (intCnt ==700)
  {
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )
              {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 2;
              }
  }
  while (intCnt ==2)
  {
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )
              {  
                 STOP(250);
                 turnback();
                 intCnt = 3;
              }
  }

}                                                                                              //end One_Three
/*******************************************************************************************************************************************/
/******************************************************   POINT-ONE to POINT-FOUR   ********************************************************/
/*******************************************************************************************************************************************/
void One_Four()                                                                                              //begin One_Four
{
  intCnt = 1;
  while( intCnt ==1)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )
              {  
                 STOP(250);
                 left();
                 delay(1200);
                 STOP(250);
                 intCnt = 700;
              }
  }
  while (intCnt ==700)
  {
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )
              {  
                 STOP(250);
                 turnback();
                 intCnt = 2;
              }
  }

}                                                                                              //end One_Four
/*******************************************************************************************************************************************/
/****************************************************   POINT-ONE to POINT-FIVE   **********************************************************/
/*******************************************************************************************************************************************/
void One_Five()                                                                                              //begin One_five
{
  intCnt = 1;
  while( intCnt ==1)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 700;
                }
  }                                                 //Go to 700 junction
  while( intCnt ==700)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(1000);
                 STOP(100);
                 intCnt = 800;
                }
  }                                                 //Go to 800 junction
  
        
  while (intCnt ==800)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 5;
              } 
  }

  
}                                                                                                  //end one_five
/*******************************************************************************************************************************************/
/****************************************************   POINT-ONE to POINT-SIX   ***********************************************************/
/*******************************************************************************************************************************************/
void One_Six()                                                                                              //begin One_Six
{
  intCnt = 1;
  while( intCnt ==1)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 700;
                }
  }                                                 //Go to 700 junction
  while( intCnt ==700)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 800;
                }
  }                                                                                                   //Go to 800 junction
  while( intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 left();
                 delay(1000);
                 STOP(100);
                 intCnt = 900;
                }
  }                                                                                                     //Go to 900 junction
  while (intCnt ==900)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 6;
              } 
  }

}                                                                                                                         //end One_Six
/*******************************************************************************************************************************************/
/****************************************************   POINT-ONE to POINT-SEVEN   *********************************************************/
/*******************************************************************************************************************************************/
void One_Seven()                                                                                              //begin One_Seven
{
  intCnt = 1;
  while( intCnt ==1)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 700;
                }
  }                                                 //Go to 700 junction
  while( intCnt ==700)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 800;
                }
  }                                                                                                   //Go to 800 junction
  while( intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(1000);
                 STOP(100);
                 intCnt = 900;
                }
  }                                                                                                     //Go to 900 junction
  while (intCnt ==900)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 7;
              } 
  }

}                                                                                                                         //end One_Seven
/*******************************************************************************************************************************************/
/****************************************************   POINT-ONE to POINT-EIGHT   *********************************************************/
/*******************************************************************************************************************************************/
void One_Eight()                                                                                              //begin One_Eight
{
  intCnt = 1;
  while( intCnt ==1)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 700;
                }
  }                                                 //Go to 700 junction
  while( intCnt ==700)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 800;
                }
  }                                                                                                   //Go to 800 junction
  while( intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 900;
                }
  }                                                                                                     //Go to 900 junction
  while (intCnt ==900)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 8;
              } 
  }

}                                                                                                                         //end One_Eight
/*******************************************************************************************************************************************/
/******************************************************   POINT-TWO to POINT-ONE   ********************************************************/
/*******************************************************************************************************************************************/
void Two_One()                                                                                              //begin Two_One
{
  intCnt = 2;
  while( intCnt ==2)
    {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 left();
                 delay(1000);
                 STOP(100);
                 intCnt ==700;
                }
   }                                                                                            //Go to 700 junction
  while (intCnt ==700)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 1;
              } 
  }

}                                                                                                                         //end Two_One 
/*******************************************************************************************************************************************/
/******************************************************   POINT-TWO to POINT-THREE   *******************************************************/
/*******************************************************************************************************************************************/
void Two_Three()                                                                                              //begin Two_Three
{
  intCnt = 2;
  while( intCnt ==2)
    {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(1000);
                 STOP(100);
                 intCnt ==3;
                }
   }   
}                                                                                                             //end Two_Three    
/*******************************************************************************************************************************************/
/******************************************************   POINT-TWO to POINT-FOUR   ********************************************************/
/*******************************************************************************************************************************************/
void Two_Four()                                                                                              //begin Two_Four
{
  intCnt = 2;
  while( intCnt ==2)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 intCnt = 700;
                 goforward();
                 delay(400);
                 STOP(100);
                }
  }                                                 //Go to 700 junction
        
  while (intCnt ==700)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 4;
              } 

  }

  
}                                                                                              //end Two_Four  
/*******************************************************************************************************************************************/
/******************************************************   POINT-TWO to POINT-FIVE   ********************************************************/
/*******************************************************************************************************************************************/
void Two_Five()                                                                                              //begin Two_Five
{
  intCnt = 2;
  while( intCnt ==2)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 intCnt = 700;
                 goforward();
                 delay(400);
                 STOP(100);
                }
  }                                                 //Go to 700 junction
  while( intCnt ==700)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(1000);
                 STOP(100);
                 intCnt = 800;
                }
  }                                                 //Go to 800 junction
  
        
  while (intCnt ==800)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 5;
              } 
  }

  
}                                                                                                  //end Two_Five
/*******************************************************************************************************************************************/
/******************************************************   POINT-TWO to POINT-SIX   ********************************************************/
/*******************************************************************************************************************************************/
void Two_Six()                                                                                              //begin Two_Six
{
  intCnt = 2;
  while( intCnt ==2)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(1000);
                 STOP(100);
                 intCnt = 700;
                }
  }                                                 //Go to 700 junction
  while( intCnt ==700)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 800;
                }
  }                                                                                                   //Go to 800 junction
  while( intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 left();
                 delay(1000);
                 STOP(100);
                 intCnt = 900;
                }
  }                                                                                                     //Go to 900 junction
  while (intCnt ==900)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 6;
              } 
  }

}                                                                                                                         //end Two_Six  
/*******************************************************************************************************************************************/
/******************************************************   POINT-TWO to POINT-SEVEN   ********************************************************/
/*******************************************************************************************************************************************/
void Two_Seven()                                                                                              //begin Two_Seven
{
  intCnt = 2;
  while( intCnt ==2)
    {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(1000);
                 STOP(100);
                 intCnt = 700;
                }
  }                                                 //Go to 700 junction 
    while( intCnt ==700)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 800;
                }
  }                                                                                                   //Go to 800 junction
  while( intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(1000);
                 STOP(100);
                 intCnt = 900;
                }
  }                                                                                                     //Go to 900 junction
  while (intCnt ==900)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 7;
              } 
  }

}                                                                                                                         //end Two_Seven
/*******************************************************************************************************************************************/
/******************************************************   POINT-TWO to POINT-EIGHT   *******************************************************/
/*******************************************************************************************************************************************/
void Two_Eight()                                                                                              //begin Two_Eight
{
  intCnt = 2;
  while( intCnt ==2)
    {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(1000);
                 STOP(100);
                 intCnt = 700;
                }
  }                                                 //Go to 700 junction  
  while( intCnt ==700)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 800;
                }
  }                                                                                                   //Go to 800 junction
  while( intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 900;
                }
  }                                                                                                     //Go to 900 junction
  while (intCnt ==900)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 8;
              } 
  }

}                                                                                                                         //end Two_Eight
/*******************************************************************************************************************************************/
/******************************************************   POINT-THREE to POINT-ONE   *******************************************************/
/*******************************************************************************************************************************************/
void Three_One()                                                                                              //begin Three_One
{
  intCnt = 3;
  while( intCnt ==3)
    {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 2;
                }
  }                                                 //Go to station 2
  while( intCnt ==2)
    {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 left();
                 delay(1000);
                 STOP(100);
                 intCnt ==700;
                }
   }                                                                                            //Go to 700 junction
  while (intCnt ==700)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 1;
              } 
  }

}                                                                                                                         //end Three_One
/*******************************************************************************************************************************************/
/******************************************************   POINT-THREE to POINT-TWO   *******************************************************/
/*******************************************************************************************************************************************/
void Three_Two()                                                                                              //begin Three_Two
{
  intCnt = 3;
  while( intCnt ==3)
    {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 turnback();
                 intCnt = 2;
                }
  }                                                 
}                                                                                                     //end of Three_two 
/*******************************************************************************************************************************************/
/******************************************************   POINT-THREE to POINT-FOUR   ******************************************************/
/*******************************************************************************************************************************************/
void Three_Four()                                                                                              //begin Three_Four
{
  intCnt = 3;
  while( intCnt ==3)
    {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 2;
                }
  }                                                                                                   //Go to station 2
while( intCnt ==2)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 intCnt = 700;
                 goforward();
                 delay(400);
                 STOP(100);
                }
  }                                                 //Go to 700 junction
        
  while (intCnt ==700)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 4;
              } 

  }  
}                                                                                              //end Three_Four 
/*******************************************************************************************************************************************/
/******************************************************   POINT-THREE to POINT-FIVE   ******************************************************/
/*******************************************************************************************************************************************/
void Three_Five()                                                                                              //begin Three_Five
{
  intCnt = 3;
  while( intCnt ==3)
    {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 2;
                }
  }                                                                                                   //Go to station 2 
   while( intCnt ==2)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 intCnt = 700;
                 goforward();
                 delay(400);
                 STOP(100);
                }
  }                                                 //Go to 700 junction
  while( intCnt ==700)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(1000);
                 STOP(100);
                 intCnt = 800;
                }
  }                                                 //Go to 800 junction
  
        
  while (intCnt ==800)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 5;
              } 
  }

  
}                                                                                                  //end Three_Five
/*******************************************************************************************************************************************/
/******************************************************   POINT-THREE to POINT-SIX   *******************************************************/
/*******************************************************************************************************************************************/
void Three_Six()                                                                                              //begin Three_Six
{
  intCnt = 3;
  while( intCnt ==3)
    {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 2;
                }
  }                                                                                                   //Go to station 2
   while( intCnt ==2)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(1000);
                 STOP(100);
                 intCnt = 700;
                }
  }                                                 //Go to 700 junction
  while( intCnt ==700)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 800;
                }
  }                                                                                                   //Go to 800 junction
  while( intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 left();
                 delay(1000);
                 STOP(100);
                 intCnt = 900;
                }
  }                                                                                                     //Go to 900 junction
  while (intCnt ==900)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 6;
              } 
  }

}                                                                                                                         //end Three_Six 
/*******************************************************************************************************************************************/
/******************************************************   POINT-THREE to POINT-SEVEN   *****************************************************/
/*******************************************************************************************************************************************/
void Three_Seven()                                                                                              //begin Three_Seven
{
  intCnt = 3;
  while( intCnt ==3)
    {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 2;
                }
  }                                                                                                   //Go to station 2
  while( intCnt ==2)
    {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(1000);
                 STOP(100);
                 intCnt = 700;
                }
  }                                                 //Go to 700 junction 
  while( intCnt ==700)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 800;
                }
  }                                                                                                   //Go to 800 junction
  while( intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(1000);
                 STOP(100);
                 intCnt = 900;
                }
  }                                                                                                     //Go to 900 junction
  while (intCnt ==900)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 7;
              } 
  }
}                                                                                                                         //end Three_Seven
/*******************************************************************************************************************************************/
/******************************************************   POINT-THREE to POINT-EIGHT   *****************************************************/
/*******************************************************************************************************************************************/
void Three_Eight()                                                                                              //begin Three_Eight
{
  intCnt = 3;
  while( intCnt ==3)
    {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 2;
                }
  }                                                                                                   //Go to station 2
  while( intCnt ==2)
    {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(1000);
                 STOP(100);
                 intCnt = 700;
                }
  }                                                 //Go to 700 junction  
  while( intCnt ==700)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 800;
                }
  }                                                                                                   //Go to 800 junction
  while( intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 900;
                }
  }                                                                                                     //Go to 900 junction
  while (intCnt ==900)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 8;
              } 
  }

}                                                                                                                         //end Three_Eight
/*******************************************************************************************************************************************/
/******************************************************   POINT-FOUR to POINT-ONE   ********************************************************/
/*******************************************************************************************************************************************/
void Four_One()                                                                                              //begin Four_One
{
intCnt = 4;
while( intCnt ==4)
    {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 left();
                 delay(1000);
                 STOP(100);
                 intCnt ==700;
                }
   }                                                                                            //Go to 700 junction
  while (intCnt ==700)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 1;
              } 
  }
}                                                                                                                         //end Four_One 
/*******************************************************************************************************************************************/
/******************************************************   POINT-FOUR to POINT-TWO   ********************************************************/
/*******************************************************************************************************************************************/
void Four_Two()                                                                                              //begin Four_Two
{
intCnt = 4;
while( intCnt ==4)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 intCnt = 700;
                 goforward();
                 delay(400);
                 STOP(100);
                }
  }                                                 //Go to 700 junction       
  while (intCnt ==700)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 2;
              } 

  } 
}                                                                                              //end Four_Two 
/*******************************************************************************************************************************************/
/******************************************************   POINT-FOUR to POINT-THREE   ******************************************************/
/*******************************************************************************************************************************************/
void Four_Three()                                                                                              //begin Four_Three
{
intCnt = 4;
while( intCnt ==4)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 intCnt = 700;
                 goforward();
                 delay(400);
                 STOP(100);
                }
  }                                                 //Go to 700 junction
    while (intCnt ==700)
  {
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )
              {  
                 STOP(250);
                 intCnt = 2;
              }
  }

  while (intCnt ==2)
  {
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )
              {  
                 STOP(250);
                 turnback();
                 intCnt = 3;
              }
  }
}                                                                                              //end Four_Three       
/*******************************************************************************************************************************************/
/******************************************************   POINT-FOUR to POINT-FIVE   *******************************************************/
/*******************************************************************************************************************************************/
void Four_Five()                                                                                              //begin Four_Five
{
intCnt = 4;
while( intCnt ==4)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 left();
                 delay(1000);
                 STOP(100);
                 intCnt = 700;
                }
  }                                                 //Go to 700 junction
    while( intCnt ==700)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(1000);
                 STOP(100);
                 intCnt = 800;
                }
  }                                                 //Go to 800 junction       
  while (intCnt ==800)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 5;
              } 
  }  
}                                                                                                  //end Four_Five
/*******************************************************************************************************************************************/
/******************************************************   POINT-FOUR to POINT-SIX   ********************************************************/
/*******************************************************************************************************************************************/
void Four_Six()                                                                                              //begin Four_Six
{
intCnt = 4;
while( intCnt ==4)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 left();
                 delay(1000);
                 STOP(100);
                 intCnt = 700;
                }
  }                                                 //Go to 700 junction
   while( intCnt ==700)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 800;
                }
  }                                                                                                   //Go to 800 junction
  while( intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 left();
                 delay(1000);
                 STOP(100);
                 intCnt = 900;
                }
  }                                                                                                     //Go to 900 junction
  while (intCnt ==900)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 6;
              } 
  }
}                                                                                                                         //end Four_Six 
/*******************************************************************************************************************************************/
/******************************************************   POINT-FOUR to POINT-SEVEN   ******************************************************/
/*******************************************************************************************************************************************/
void Four_Seven()                                                                                              //begin Four_Seven
{
intCnt = 4;
while( intCnt ==4)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 left();
                 delay(1000);
                 STOP(100);
                 intCnt = 700;
                }
  }                                                 //Go to 700 junction
   while( intCnt ==700)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 800;
                }
  }                                                                                                   //Go to 800 junction
  while( intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(1000);
                 STOP(100);
                 intCnt = 900;
                }
  }                                                                                                     //Go to 900 junction
  while (intCnt ==900)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 7;
              } 
  }
}                                                                                                                         //end Four_Seven
/*******************************************************************************************************************************************/
/******************************************************   POINT-FOUR to POINT-EIGHT   ******************************************************/
/*******************************************************************************************************************************************/
void Four_Eight()                                                                                              //begin Four_Eight
{
intCnt = 4;
while( intCnt ==4)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 left();
                 delay(1000);
                 STOP(100);
                 intCnt = 700;
                }
  }                                                 //Go to 700 junction
    while( intCnt ==700)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 800;
                }
  }                                                                                                   //Go to 800 junction
  while( intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 900;
                }
  }                                                                                                     //Go to 900 junction
  while (intCnt ==900)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 8;
              } 
  }
}                                                                                                                         //end Four_Eight
/*******************************************************************************************************************************************/
/******************************************************   POINT-FIVE to POINT-ONE   ********************************************************/
/*******************************************************************************************************************************************/
void Five_One()                                                                                              //begin Five_One
{
intCnt = 5;
while( intCnt ==5)
 {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 left();
                 delay(1000);
                 STOP(100);
                 intCnt = 800;
                }
  }                                                 //Go to 800 junction
  while(intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 700;
                }
  }                                                                                                    //Go to 700 junction
    while (intCnt ==700)
  {
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )
              {  
                 STOP(250);
                 turnback();
                 intCnt = 1;
              }
  }
}                                                                                                 //end Five_One()
/*******************************************************************************************************************************************/
/******************************************************   POINT-FIVE to POINT-TWO    *******************************************************/
/*******************************************************************************************************************************************/
void Five_Two()                                                                                              //begin Five_Two
{
  intCnt = 5;
  while( intCnt ==5)
  {
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 left();
                 delay(900);
                 STOP(250);
                 intCnt = 800;
                }  
  }
  while(intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 left();
                 delay(900);
                 STOP(250);
                 intCnt = 700;
                }
  }                                                                                                    //Go to 700 junction
  while (intCnt ==700)
  {
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )
              {  
                 STOP(250);
                 turnback();
                 intCnt = 2;
              }
  }
}                                                                 //end Five_Two()
/*******************************************************************************************************************************************/
/******************************************************   POINT-FIVE to POINT-Three   ********************************************************/
/*******************************************************************************************************************************************/
void Five_Three()                                                                                              //begin Five_Three
{
  intCnt = 5;
  while( intCnt ==5)
  {
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 left();
                 delay(900);
                 STOP(250);
                 intCnt = 800;
                }  
  }
    while(intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 left();
                 delay(900);
                 STOP(250);
                 intCnt = 700;
                }
  }                                                                                                    //Go to 700 junction
  while (intCnt ==700)
  {
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )
              {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 2;
              }
  }
  while (intCnt ==2)
  {
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )
              {  
                 STOP(250);
                 turnback();
                 intCnt = 3;
              }
  }
}                                                                                              //end Five_Three
/*******************************************************************************************************************************************/
/******************************************************   POINT-FIVE to POINT-Four   ********************************************************/
/*******************************************************************************************************************************************/
void Five_Four()                                                                                              //begin Five_Four
{
  intCnt = 5;
  while( intCnt ==5)
  {
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 left();
                 delay(900);
                 STOP(250);
                 intCnt = 800;
                }  
  }
    while(intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(900);
                 STOP(250);
                 intCnt = 700;
                }
  }                                                                                                    //Go to 700 junction
  while (intCnt ==700)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 4;
              } 
  }  
}                                                                                              //end Five_Four 
/*******************************************************************************************************************************************/
/******************************************************   POINT-FIVE to POINT-Six   ********************************************************/
/*******************************************************************************************************************************************/
void Five_Six()                                                                                              //begin Five_Six
{
intCnt = 5;
  while( intCnt ==5)
  {
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(900);
                 STOP(250);
                 intCnt = 800;
                }  
  }
   while( intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 left();
                 delay(1000);
                 STOP(100);
                 intCnt = 900;
                }
  }                                                                                                     //Go to 900 junction
  while (intCnt ==900)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 6;
              } 
  }
}                                                                                                                         //end Five_Six 
/*******************************************************************************************************************************************/
/******************************************************   POINT-FIVE to POINT-Seven   ********************************************************/
/*******************************************************************************************************************************************/
void Five_Seven()                                                                                              //begin Five_Seven
{
intCnt = 5;
  while( intCnt ==5)
  {
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(900);
                 STOP(250);
                 intCnt = 800;
                }  
  }
   while( intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(1000);
                 STOP(100);
                 intCnt = 900;
                }
  }                                                                                                     //Go to 900 junction
  while (intCnt ==900)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 7;
              } 
  }
}                                                                                                                         //end Five_Seven
/*******************************************************************************************************************************************/
/******************************************************   POINT-FIVE to POINT-Eight   ********************************************************/
/*******************************************************************************************************************************************/
void Five_Eight()                                                                                              //begin Five_Eight
{
intCnt = 5;
  while( intCnt ==5)
  {
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 right();
                 delay(900);
                 STOP(250);
                 intCnt = 800;
                }  
  }
   while( intCnt ==800)
  {
          if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
                {
                 right();
                }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
                {  
                 STOP(250);
                 goforward();
                 delay(400);
                 STOP(100);
                 intCnt = 900;
                }
  }                                                                                                     //Go to 900 junction
  while (intCnt ==900)
  { 
         if(digitalRead(lftSnsr) == 0 && digitalRead(rgtSnsr) == 0)                                  //both sensor on white/non-black
                 {
                  goforward();
                 }
           
         if (digitalRead(lftSnsr) == 1 && digitalRead(rgtSnsr) == 0)
                {
               left();
                }   
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 0 )
              {
                 right();
              }
         if(digitalRead(rgtSnsr) == 1 && digitalRead(lftSnsr) == 1 )                                  //both sensor on black
              {  
                 STOP(250);
                 turnback();
                 intCnt = 8;
              } 
  }
}                                                                                                                         //end Five_Eight
/*******************************************************************************************************************************************/
/************************************************** PATH NAVIGATION FUNCTION  **************************************************************/
/*******************************************************************************************************************************************/
void path(int num1, int num2)
{
 int dstpath = num2;
 switch (dstpath)
 {
  case 1:
     if(num1 == 2)
     {
     Two_One();
     }
     else if(num1 == 3)
     {
    Three_One();
     }
    else if(num1 == 4)
     {
    Four_One();
     }
     if(num1 == 5)
     {
     Five_One();
     }
     else if(num1 == 1)
     {
    printf("Car already at Station 1\n");
     }
  break;
  case 2:
     if(num1 == 1)
     {
     One_Two();
     }
     else if(num1 == 3)
     {
    Three_Two();
     }
    else if(num1 == 4)
     {
    Four_Two();
     }
     if(num1 == 5)
     {
     Five_Two();
     }
     else if(num1 == 2)
     {
    printf("Car already at Station 2\n");
     }
  break;
  case 3:
     if(num1 == 1)
     {
     One_Three();
     }
     else if(num1 == 2)
     {
     Two_Three();
     }
    else if(num1 == 4)
     {
     Four_Three();
     }
     if(num1 == 5)
     {
     Five_Three();
     }
     else if(num1 == 3)
     {
    printf("Car already at Station 3\n");
     }
  break;
  case 4:
     if(num1 == 1)
     {
     One_Four();
     }
     else if(num1 == 2)
     {
     Two_Four();
     }
    else if(num1 == 3)
     {
     Three_Four();
     }
     if(num1 == 5)
     {
     Five_Four();
     }
     else if(num1 == 4)
     {
    printf("Car already at Station 4\n");
     }
  break;
    case 5:
     if(num1 == 1)
     {
     One_Five();
     }
     else if(num1 == 2)
     {
     Two_Five();
     }
    else if(num1 == 3)
     {
     Three_Five();
     }
     if(num1 == 4)
     {
     Four_Five();
     }
     else if(num1 == 5)
     {
    printf("Car already at Station 5\n");
     }
  break;
 }  
}
