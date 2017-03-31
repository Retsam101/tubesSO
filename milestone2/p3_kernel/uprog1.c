main(){

interrupt(0x21,0x02,"WooHoo! I'm a user program!\r\n\0",0x2000,0);
while(1);
} 
