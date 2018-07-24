#ifndef LCD_H
#define LCD_H
#define LCDPORT P2

#define line1 0x80
#define line2 0xc0
#define clear 0x10
#define rshift 0x18
#define lshift 0x1c

extern void sendData(unsigned char val);
extern void DisplayData(unsigned char val);
extern void sendCmd(unsigned char cmd);
extern void DisplayCmd(unsigned char cmd);
extern void LcdInit();
extern void DisplayString(char * string);
extern void DisplayNum(int num);
extern void Displayfnum(float num);
#endif