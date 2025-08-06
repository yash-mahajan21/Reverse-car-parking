#include <LPC21XX.H>

#include "project_header.h"




void delay_sec( unsigned int sec)

{

int a[] ={15,60,30,15,15};

unsigned int  pclk;

pclk=a[VPBDIV]*1000000;

T0PC=0;

T0PR=pclk-1;

T0TC=0;

T0TCR=1;

while(T0TC<sec);

T0TCR=0;

}


 void delay_ms(unsigned int  ms)

{

int a[] ={15,60,30,15,15};

unsigned int pclk;;

pclk=a[VPBDIV]*1000;

T0PC=0;

T0PR=pclk-1;

T0TC=0;

T0TCR=1;

while(T0TC<ms);

T0TCR=0;

}


 

 void delay_us(unsigned int us)   //1us

{

   	T1PC=0;

	T1TC=0;

    T1PR=59;

    T1TCR=0X02;//reset

    T1TCR=1;

    while(T1TC<us);

	T1TCR=0;

}





