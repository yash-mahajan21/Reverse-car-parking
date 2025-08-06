 #include <lpc21xx.h>

#include "project_header.h"

CAN1 m1,m2;

u32 flag;


main()

{

u32 distance,r;

can1_init();

config_vic_for_can1();

en_can1_interupt();

ultrasonic_init();

uart0_init(9600);


while(1)

{


if(flag==1)

{


flag=0;

uart0_tx_string("remote frame is recived\r\n");

if(m1.rtr==1)

{	

r=1;						   

m2.dlc=m1.dlc;

m2.id=m1.id;

}

else

r=0;

}


  if(r==1)

  {

 distance=get_range();

 delay_ms(50);

 uart0_tx_integer(distance);

 m2.byteA=distance;

 m2.rtr=0;

 can1_tx(m2);

 uart0_tx_string("response to remote frame\r\n");

 }

	 }
	 }

