// The row pins control the 74HC595N
int rowData = 3;
int rowClock = 4;
int rowLatch = 2;
int isOn = 0;
int startTime = 0;
int endTime = 0;
int durTime = 0;
byte receivedByte[2] = 0;
int byteOneTwo = 1;
int ledLocation = 0;
int aa = 0, bb = 0, cc = 0;
int r = 0, g = 0, b = 0;

// Clock and data pins are pins from the hardware SPI, you cannot choose them yourself if you use the hardware SPI.
// Data pin is MOSI (Uno and earlier: 11, Leonardo: ICSP 4, Mega: 51, Teensy 2.0: 2, Teensy 2.0++: 22) 
// Clock pin is SCK (Uno and earlier: 13, Leonardo: ICSP 3, Mega: 52, Teensy 2.0: 1, Teensy 2.0++: 21)

// You can choose the latch pin yourself.
const int ShiftPWM_latchPin=8;

// ** uncomment this part to NOT use the SPI port and change the pin numbers. This is 2.5x slower **
// #define SHIFTPWM_NOSPI
// const int ShiftPWM_dataPin = 11;
// const int ShiftPWM_clockPin = 13;


const bool ShiftPWM_invertOutputs = false;
const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!

unsigned char maxBrightness = 31;
unsigned char pwmFrequency = 255;
int numRegisters = 12;
int numRGBleds = numRegisters*8/3;
int loopDelay = 0;


void setRow(int row)
{
  digitalWrite(rowClock, LOW);
  digitalWrite(rowLatch, LOW);
  shiftOut(rowData, rowClock, MSBFIRST, 1 << row);
  digitalWrite(rowLatch, HIGH);
}

unsigned char panel[8][32][3];

void setup()
{
  Serial.begin(115200);
  
  pinMode(rowData, OUTPUT);
  pinMode(rowClock, OUTPUT);
  pinMode(rowLatch, OUTPUT);
  
  // Sets the number of 8-bit registers that are used.
  ShiftPWM.SetAmountOfRegisters(numRegisters);

  // If your LED's are connected like this: RRRRGGGGBBBBRRRRGGGGBBBB, use SetPinGrouping(4).
  ShiftPWM.SetPinGrouping(8); 
  
  ShiftPWM.Start(pwmFrequency,maxBrightness);
  loopDelay = pwmFrequency/20;
//loopDelay = 1;
  
  
  
  
  for (int a = 0; a < 8; a++)
  {
    for (int b = 0; b < 8; b++)
    {
      for (int c = 0; c < 3; c++)
      {
        if (a % 2 == 0 && b % 2 == 0 || a % 2 == 1 && b % 2 == 1) {
          if (c == 2) {
            panel[a][b][c] = 255;
          }
        } else {
          if (c == 0){
            panel[a][b][c] = 255;
          }
        }
      }
    }
  }
}

void loop()
{
  startTime = millis();
  if (isOn != 49)
  {
    for (int a = 0; a < 8; a++)
    {
      for (int b = 0; b < 8; b++)
      {
        for (int c = 0; c < 3; c++)
        {
          panel[a][b][c] = 255;
        }
      }
    }
    } else if (isOn == 48)
  {
    for (int a = 0; a < 8; a++)
    {
      for (int b = 0; b < 8; b++)
      {
        for (int c = 0; c < 3; c++)
        {
          panel[a][b][c] = 0;
        }
      }
    }
  }
  
  
  

  
  for (int i = 0; i < 8; i++)
  {
     ShiftPWM.SetAll(0);
     setRow(i);
     delayMicroseconds(loopDelay);  
//delay(1);
     //ShiftPWM.SetAllRGB(0, 0, 255);
     for (int j = 0; j < 32; j++)
     {
       //ShiftPWM.SetAll(255);
       
       //checkerboard
//       if ((((i >> 1) << 1 == i) && (j >> 1) << 1 == j) || (((i >> 1) << 1 != i) && (j >> 1) << 1 != j))
//         ShiftPWM.SetRGB(j, 255, 0, 0);
//       else
//         ShiftPWM.SetRGB(j, 0, 255, 0);
         
       
       //Half and half
       //if (i < 4) ShiftPWM.SetRGB(j, 255, 0, 0);
       //else ShiftPWM.SetRGB(j, 0, 255, 0);
       
       //Alternating rows
//       if ( (i >> 1) << 1 == i) ShiftPWM.SetRGB(j, 255, 0, 0);
//       else ShiftPWM.SetRGB(j, 0, 255, 0);
       
       //Gradient
       //ShiftPWM.SetRGB(j, 255/8*j, 255/8*(8-j), 0);
       
       //Load pattern(random)
       ShiftPWM.SetRGB(j, panel[i][j][0], panel[i][j][1], panel[i][j][2]);
     }
//     delay(2);
   }
  endTime = millis();
  durTime = endTime - startTime;
  Serial.println(durTime);
    
}

void serialEvent() 
{ 
  receivedBytes[byteOneTwo] = Serial.read();
  processByte(receivedBytes);
  
  panel[a][b][c] = receivedByte;
  
  ledLocation++;
  
}

void processByte()
{
  if (receivedBytes[1] == b10110111 && receivedBytes[2] == b01111000)
  {
    ledLocation = 0;
    return;
  }
  
  r = receivedBytes[1] & 01111100;
  g = receivedBytes[1] & 00000011
  
  
  
  
}