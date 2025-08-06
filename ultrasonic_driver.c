#include<lpc21xx.h>
#include "project_header.h"
#define TRIG (1<<8)             //P0.8
#define ECHO (1<<9)

 


void ultrasonic_init()
{
    IODIR0|=TRIG;
	IODIR0 &= ~(ECHO);
	T0TCR = 0x02;    
    T0PR = 59;
    T0TCR = 1;
}

void send_pulse()
{
    T0TC=0;
	T0PC=0;
	T0PR = 59;
    IOSET0=TRIG;                            //trig=1
    delay_us(10);                       //10us delay
    IOCLR0=TRIG;
	IODIR0 &= ~(ECHO) ;		                            //trig=0
}

u32 get_range()
{
  u32 time;
  u32 d;
  send_pulse();
  while(!((IO0PIN & ECHO)));//waiting for echo to high
  T0TCR=1;
  while((IO0PIN & ECHO));//waiting for ech t0o go low 
  T0TCR=0;

  time=T0TC;
  
	

   // IOCLR0=ECHO;
//	 
//  if(time<38000)
//   time=time/59;
//   else
//   time=0;
  
    d=(0.0343 * time)/2;
  return d;

 // return time;
   }





  
   


