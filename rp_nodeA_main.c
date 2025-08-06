#include<lpc21xx.h>

#include "project_header.h"


#define RG ((IOPIN0>>14)&1)	 

#define LED (1<<17)

#define BUZZER (1<<21)


CAN1 v1,v2,m1;

u32 flag,timer_flag,sw;

u32 count;


main()
{
u32 sw=0,data_flag=0;

IODIR0=RG|LED|BUZZER;

IOSET0=LED;

can1_init();

uart0_init(9600);

en_can1_interupt();

config_vic_for_can1();

v1.id=0x123;

v1.dlc=2;

while(1)

{

if(RG==0)

{

while(RG==0);

sw^=1;	


 if(sw)

{

IOCLR0=LED;

uart0_tx_string("switch is pressed\r\n");

data_flag=0;

v1.rtr=1;

can1_tx(v1);

uart0_tx_string("remote frame is sent\r\n");

}


else

{

IOSET0=LED;

IOCLR0=BUZZER;

data_flag=1;

v1.rtr=0;

can1_tx(v1);

uart0_tx_string("data frame is sent\r\n");

}

}




if(data_flag)

IOCLR0=BUZZER;




if(flag==1)

 {

flag=0;

v2.id=m1.id;

v2.dlc=m1.dlc;

if(v2.rtr==0)

{

v2.byteA=m1.byteA;

uart0_tx_integer(v2.byteA);

uart0_tx_string("cm\r\n");

}

//}


if(v2.byteA>=300 && v2.byteA<=400)

{

IOSET0=BUZZER;

delay_ms(1000);

IOCLR0=BUZZER;

delay_ms(1000);

}


else if(v2.byteA>=101 && v2.byteA<=200)

{


IOSET0=BUZZER;

delay_ms(500);

IOCLR0=BUZZER;

delay_ms(500);

}


else if(v2.byteA>=31  && v2.byteA<=100)	   

{

IOSET0=BUZZER;

delay_ms(250);

IOCLR0=BUZZER;

delay_ms(250);

}


else if(v2.byteA>=11 && v2.byteA<=30)

{

IOSET0=BUZZER;

delay_ms(100);

IOCLR0=BUZZER;

delay_ms(100);

}


 else if(v2.byteA>=2 && v2.byteA<10)

 {


 IOSET0=BUZZER;


 }


 }

 }

}


