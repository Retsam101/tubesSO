void printString(char*);
void readString(char*);
void readSector(char* buffer, int sector);
void writeSector(char* buffer, int sector);
void handleInterrupt21 (int AX, int BX, int CX, int DX);
void terminate();

main(){
	int i;
	char line[80];
	char sector[512];
	//char buff[13312];
	//char b[512];
	makeInterrupt21();

	 printString(",____________, \r\n\0");
   printString("|  API       | \r\n\0");
   printString("|   OS v.0.1 | \r\n\0");
   printString("|____________| \r\n\0");
	 printString("\r\n\0");
	 printString("Creator By. \r\n\0");
	 printString("Ari Bambang K (14115062) \r\n\0");
	 printString("Putra Abi A (14115011) \r\n\0");
	 printString("Irfan Gerard W (14115016) \r\n\0");
	 printString("Selamat datang di terminal p2_kernel\r\n\0");
	interrupt(0x21,0x00, "shell>\0", 0, 0);// display prompt
	interrupt(0x21,0x01,line,0,0);// read string
	interrupt(0x21,0x00,line,0,0);// print string
	interrupt(0x21, 0x02, sector, 30, 0);// read sector
	interrupt(0x21,0x00, sector,0,0);// print string

    while(1){

    }
}

void handleInterrupt21 (int AX, int BX, int CX, int DX){
		int ah;

		ah = AX >> 8;

		if (ah == 9){
			interrupt(0x10, 0xe*256+'H', 0, 0, 0);
			interrupt(0x10, 0xe*256+'e', 0, 0, 0);
			interrupt(0x10, 0xe*256+'l', 0, 0, 0);
			interrupt(0x10, 0xe*256+'l', 0, 0, 0);
			interrupt(0x10, 0xe*256+'o', 0, 0, 0);
			interrupt(0x10, 0xe*256+' ', 0, 0, 0);
			interrupt(0x10, 0xe*256+'W', 0, 0, 0);
			interrupt(0x10, 0xe*256+'o', 0, 0, 0);
			interrupt(0x10, 0xe*256+'r', 0, 0, 0);
			interrupt(0x10, 0xe*256+'l', 0, 0, 0);
			interrupt(0x10, 0xe*256+'d', 0, 0, 0);
			interrupt(0x10, 0xe*256+'!', 0, 0, 0);
		}
		else if (ah == 0x4C){
			terminate();
		}

        if (AX == 0){
            printString(BX);
        }
        else if (AX ==1){
            readString(BX);
        }
        else if(AX == 2){
			/* Buffer, sector */
            readSector(BX,30);
        }
		else if (AX == 5){
			terminate();
		}
		else if (AX == 6){
			/* BX - address of char array, CX- sector number*/
			writeSector(BX,CX);
		}
		else {
            printString("Invalid interrupt!\0");
        }
}

/* BX = address of character array holding the file name, CX = address of character array holding the file to be written, DX = number of sectors */
void terminate(){
	char shell[6];
	shell[0] = 's';
	shell[1] = 'h';
	shell[2] = 'e';
	shell[3] = 'l';
	shell[4] = 'l';
	shell[5] = 0x0;
	interrupt(0x21,4,shell,0x2000,0);
}

/* BX - address of char array, CX- sector number*/

void writeSector(char* buffer, int sector){

       /* relative sector = ( sector MOD 18 ) + 1*/
        int relSector = mod(sector,18) + 1;
        /*head = ( sector / 18 ) MOD 2		(this is integer division, so the result should be rounded down)*/
        int op = div(sector,18);
        int head = mod(op,2);
        /*track = ( sector / 36 )*/
        int track = div(sector,36);
        /* call interrupt 0x13 */
        interrupt(0x13,3*256+1,buffer,track*256+relSector,head*256+0);
}

void readSector(char* buffer, int sector){

       /* relative sector = ( sector MOD 18 ) + 1*/
        int relSector = mod(sector,18) + 1;
        /*head = ( sector / 18 ) MOD 2		(this is integer division, so the result should be rounded down)*/
        int op = div(sector,18);
        int head = mod(op,2);
        /*track = ( sector / 36 )*/
        int track = div(sector,36);
        /* call interrupt 0x13 */
        interrupt(0x13,2*256+1,buffer,track*256+relSector,head*256+0);


}

void readString(char* buff){
    int dashn = 0xa;
    int endStr = 0x0;
    int enter = 0xd;
    int backsp = 0x8;
    int dashr = 0xd;
    int loop = 1;
    int count = 2;
    buff[0] = dashr;
    buff[1] = dashn;
    while(loop){
            /* Call interrupt 0x16 */
            /* interrupt #, AX, BX, CX, DX */
            int ascii = interrupt(0x16,0,0,0,0);
            if (ascii == enter){
				buff[count] = 0x0;
                buff[count+1] = dashr;
                buff[count+2] = dashn;
                return;
            }
            else if (ascii == backsp){
                if (count > 1){
                    buff[count] = 0x0;
                    count--;
                    interrupt(0x10,0xe*256+0x8,0,0,0);
                    count++;
                    interrupt(0x10,0xe*256+0x0,0,0,0);
                    count--;
                    interrupt(0x10,0xe*256+0x8,0,0,0);

               }
            }
            else{
                buff[count] = ascii;
                interrupt(0x10, 0xe*256+ascii, 0, 0, 0);
                count++;
            }
    }
}

void printString(char* chars){


    int i = 0;
    while(chars[i] != '\0'){
            int ch = chars[i];
            /* interrupt #, AX, BX, CX, DX */
		        interrupt(0x10, 0xe*256+ch, 0, 0, 0);
            i++;
    }


}

int mod(int a, int b){
    while(a >= b){
        a = a - b;
    }
    return a;
}

int div(int a, int b){
    int q = 0;
    while(q*b <=a){
        q = q+1;
    }
    return q-1;

}
