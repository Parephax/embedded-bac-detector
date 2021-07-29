/*
SE4130 Spring 2019 - Lab 5
Names: Jacob Plapp, Tod Jones, Sarah Higgens

Project: Interface with keypad, LCD (4-bit), and a serial port.
Read and write data to the onboard EEPROM.
*/

#include <htc.h>;
#include <stdio.h>;
#include "main.h";
#include "lcd.h";

// Osc = HS, Watchdog Off, all other features disabled
__CONFIG(0x3F39);

#define _XTAL_FREQ 4000000 // 4MHz Processor

typedef unsigned char byte;

static unsigned int counter = 0;
static char cnt_str[6];

/*
Program Main - Lab 5
*/
void main(){
	TRISB = 0xFF;
	TRISC = 0x00;
	TRISD = 0x00;
	nRBPU = 0;
	LCDInit();
	while(1){
    	LCDClear();
    	LCDSetCursor(0, 0x00);
	    switch(PORTB & 0x3F){
	        case 0x00: BAC_Mode();
	            break;
	        case 0x01: RADC_Mode(0);
	            break;
	        case 0x21: RADC_Mode(1);
	            break;
	        case 0x11: RADC_Mode(2);
	            break;
	        case 0x31: RADC_Mode(3);
	            break;
	        case 0x09: RADC_Mode(4);
	            break;
	        case 0x29: RADC_Mode(5);
	            break;
	        case 0x03: FTemp_Mode();
	            break;
	        case 0x23: CTemp_Mode();
	            break;
	        case 0x13: RATemp_Mode();
	            break;
	        case 0x07: LCDTest_Mode();
	            break;
	        case 0x27: Buzz_Mode(0);
	            break;
	        case 0x17: Buzz_Mode(1);
	            break;
	        default: Inv_Mode();
	            break;
	    }   
	    counter++;
	    __delay_ms(250);
	}
}

void Inv_Mode(){
	LCDWriteString("Invalid Mode!");
	LCDSetCursor(1, 0x00);
	LCDWriteString("Check Config.");
}

void BAC_Mode(){
	LCDWriteString("BAC % Monitor");
	LCDSetCursor(1, 0x00);
}    

void RADC_Mode(int res){
    //res == 0 --> use default RL
    //else use RL(res)  
	LCDWriteString("Raw ADC Gas R");
}      

void FTemp_Mode(){
	LCDWriteString("Sensor Temp F");
	LCDSetCursor(1, 0x00);
} 

void CTemp_Mode(){
	LCDWriteString("Sensor Temp C");
	LCDSetCursor(1, 0x00);
}

void RATemp_Mode(){
	LCDWriteString("Raw ADC Temp");
	LCDSetCursor(1, 0x00);
} 

void LCDTest_Mode(){
	LCDWriteString("LCD Test Mode");
	LCDSetCursor(1, 0x00);
	sprintf(cnt_str, "%u", counter);
	LCDWriteString(cnt_str);
}    

void Buzz_Mode(int freq){
    LCDWriteString("Buzzer Test ");
    if(freq == 0){
        LCDWriteString("Low");
        LCDSetCursor(1, 0x00);
    } else {
        LCDWriteString("High");
        LCDSetCursor(1, 0x00);
    }    
}       
         