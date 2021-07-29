/*
SE4130 Spring 2019 - Lab 5
Names: Jacob Plapp, Tod Jones, Sarah Higgens

Project: Interface with keypad, LCD (4-bit), and a serial port.
Read and write data to the onboard EEPROM.
*/

#ifndef _MAIN_H
#define _MAIN_H

#include "main.h";

typedef unsigned char byte;

byte DIP_Code();
void Inv_Mode();
void BAC_Mode();
void RADC_Mode(int res);
void FTemp_Mode();
void CTemp_Mode();
void RATemp_Mode();
void LCDTest_Mode();
void Buzz_Mode(int freq);

#endif
