void printString(char* String);
int main() {
   printString("Welcome to BamzOS\r\n\0");
   printString("\r\n\0");
   // related to step 1    
   printString("-------------- \r\n\0");
   printString("| Bamz       | \r\n\0");
   printString("|     OS v.0 | \r\n\0");
   printString("|____________| \r\n\0");
printString("\r\n\0");
printString("Creator By. \r\n\0"); 
printString("Ari Bambang K (14115062) \r\n\0"); 
printString("Putra Abi A (14115011) \r\n\0"); 
printString("Irfan Gerard W (14115016) \r\n\0"); 

    putInMemory(0xB000, 0x8140, 'H');
    putInMemory(0xB000, 0x8141, 0x4);
    putInMemory(0xB000, 0x8142, 'e');
    putInMemory(0xB000, 0x8143, 0xE);
    putInMemory(0xB000, 0x8144, 'l');
    putInMemory(0xB000, 0x8145, 0x2);
    putInMemory(0xB000, 0x8146, 'l');
    putInMemory(0xB000, 0x8147, 0x1);
    putInMemory(0xB000, 0x8148, 'o');
    putInMemory(0xB000, 0x8149, 0x5);
    putInMemory(0xB000, 0x814A, ' ');
    putInMemory(0xB000, 0x814B, 0x0);
    putInMemory(0xB000, 0x814C, 'W');
    putInMemory(0xB000, 0x814D, 0x4);
    putInMemory(0xB000, 0x814E, 'o');
    putInMemory(0xB000, 0x814F, 0xE);
    putInMemory(0xB000, 0x8150, 'r');
    putInMemory(0xB000, 0x8151, 0x2);
    putInMemory(0xB000, 0x8152, 'l');
    putInMemory(0xB000, 0x8153, 0x1);
    putInMemory(0xB000, 0x8154, 'd');
    putInMemory(0xB000, 0x8155, 0x5);
    putInMemory(0xB000, 0x8156, '!');
    putInMemory(0xB000, 0x8157, 0xF);
    printString("login: \0");

	while(1) {
	}
return 0;
}


void printString(char* String) {
	int i = 0;
	char c = String[i];
	while (c != 0) {
		interrupt(0x10, 0xE * 256 + c, 0, 0, 0);
		c = String[++i];
	}
}
