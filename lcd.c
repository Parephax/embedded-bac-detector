/*
SE4130 Spring 2019 - Lab 5
Names: Jacob Plapp, Tod Jones, Sarah Higgens

Enables interface with 2x16 LCD screen. (4-bit support)
Initialize, clear, and update an attached LCD.
*/

#include <htc.h>;
#include "lcd.h";

typedef unsigned char byte;

#define _XTAL_FREQ 4000000 // 4MHz Processor

#define DATA_BUS 	PORTD
#define DATA_TRIS	TRISD

#define	REG_SEL		RC6
#define	CH_EN		RC7

#define SET_FUNC_A		0x03
#define SET_FUNC_B      0x02
#define CLR_DISP        0x01
#define DISP_ON_BLINK   0x0D
#define FUNC_SET_4X2    0x28
#define FUNC_SET_8X2    0x38
#define MOV_CURS_R0C0	0x80
#define	MOV_CURS_R1C0	0xC0

#define DATA_MASK_B30	0x0F
#define DATA_MASK_B41	0x1E
#define	DATA_MASK_B50	0x3F
#define	DISP_SIZE		0x10

/*
* Turns on display and sets up cursor. 
*/
void LCDInit(){	
	DATA_TRIS = 0x00;
	REG_SEL = 0;
	__delay_ms(30);	
	LCDSendNibble(SET_FUNC_A);
	__delay_ms(6);
	LCDSendNibble(SET_FUNC_A);
	__delay_us(200);
	LCDSendNibble(SET_FUNC_A);
	LCDSendNibble(SET_FUNC_B);
	LCDSendInstruct(FUNC_SET_4X2);
	LCDSendInstruct(DISP_ON_BLINK);
	LCDSendInstruct(CLR_DISP);
	LCDSendInstruct(MOV_CURS_R0C0);
}

/*
* Sends a nibble of data to the LCD. 
*/
void LCDSendNibble(byte b){
	DATA_BUS = (b << 4); //Send on P7-P4
	CH_EN = 1;
	__delay_us(5);
	CH_EN = 0;
	__delay_us(10);
}

/*
* Sends a byte of data to the LCD by breaking it up into two nibbles. 
*/
void LCDSendByte(byte b){
	byte h = b >> 4;
	byte l = b;
	LCDSendNibble(h);
	__delay_us(50);
	LCDSendNibble(l);
	__delay_ms(1);
}

/*
* Sends an output to the LCD. 
*/
void LCDSendData(byte data){
	REG_SEL = 1;
	LCDSendByte(data);
}

/*
* Sends an instrutction to the LCD. 
*/
void LCDSendInstruct(byte inst){
	REG_SEL = 0;
	LCDSendByte(inst);
}

/*
* Sends an output string to the LCD char by char. 
*/
void LCDWriteString(const char *s){
	while(*s) LCDSendData(*s++);
}

/*
* Set cursor row (0 or 1) index and column location
*/
void LCDSetCursor(int r, byte addr){
	byte mem = (addr & DATA_MASK_B50);
	if(mem >= DISP_SIZE) 
		mem = (mem % DISP_SIZE);
	if(r == 1)
		LCDSendInstruct(MOV_CURS_R1C0|mem);
	else
		LCDSendInstruct(MOV_CURS_R0C0|mem);
}

/*
* Clears any output on LCD and rests the cursor. 
*/
void LCDClear(){
	LCDSendInstruct(CLR_DISP);
	LCDSendInstruct(MOV_CURS_R0C0);
}