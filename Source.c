//Displaying "HELLO" on LCD for Dragon12+ Trainer Board 
//with HCS12 Serial Monitor Program installed. This code is for CodeWarrior IDE
//Modified from Mazidi's book with contribution from Travis Chandler
//On Dragon12+ LCD data pins of D7-D4 are connected to Pk5-Pk2, En=Pk1,and RS=Pk0,

 
#include <hidef.h>      /* common defines and macros */
#include "mc9s12dg256.h"      /* derivative-specific definitions */
  
  
#define LCD_DATA PORTK
#define LCD_CTRL PORTK
#define RS 0x01
#define EN 0x02
#define KEYPAD PORTA

void COMWRT4(unsigned char);
void DATWRT4(unsigned char);
void KEYPADSCAN();
void MSDelay(unsigned int);


void main(void) 
{

        DDRK = 0xFF; 
        DDRA = 0x0F;  
        COMWRT4(0x33);   //reset sequence provided by data sheet
        MSDelay(1);
        COMWRT4(0x32);   //reset sequence provided by data sheet
        MSDelay(1);
        COMWRT4(0x28);   //Function set to four bit data length
                                         //2 line, 5 x 7 dot format
        MSDelay(1);
        COMWRT4(0x06);  //entry mode set, increment, no shift
        MSDelay(1);
        COMWRT4(0x0E);  //Display set, disp on, cursor on, blink off
        MSDelay(1);
        COMWRT4(0x01);  //Clear display
        MSDelay(1);
        COMWRT4(0x80);  //set start posistion, home position
        MSDelay(1);
        
        /*DATWRT4('H');
        MSDelay(1);
        DATWRT4('E');
        MSDelay(1);
        DATWRT4('L');
        MSDelay(1);
        DATWRT4('L');
        MSDelay(1);
        DATWRT4('O');
        */
        
        for(;;)       //stay here 
             KEYPADSCAN();



	
}
void COMWRT4(unsigned char command)
  {
        unsigned char x;
        
        x = (command & 0xF0) >> 2;         //shift high nibble to center of byte for Pk5-Pk2
        LCD_DATA =LCD_DATA & ~0x3C;          //clear bits Pk5-Pk2
        LCD_DATA = LCD_DATA | x;          //sends high nibble to PORTK
        MSDelay(1);
        LCD_CTRL = LCD_CTRL & ~RS;         //set RS to command (RS=0)
        MSDelay(1);
        LCD_CTRL = LCD_CTRL | EN;          //rais enable
        MSDelay(5);
        LCD_CTRL = LCD_CTRL & ~EN;         //Drop enable to capture command
        MSDelay(15);                       //wait
        x = (command & 0x0F)<< 2;          // shift low nibble to center of byte for Pk5-Pk2
        LCD_DATA =LCD_DATA & ~0x3C;         //clear bits Pk5-Pk2
        LCD_DATA =LCD_DATA | x;             //send low nibble to PORTK
        LCD_CTRL = LCD_CTRL | EN;          //rais enable
        MSDelay(5);
        LCD_CTRL = LCD_CTRL & ~EN;         //drop enable to capture command
        MSDelay(15);
  }

void DATWRT4(unsigned char data)
  {
    unsigned char x;
            
        x = (data & 0xF0) >> 2;
        LCD_DATA =LCD_DATA & ~0x3C;                     
        LCD_DATA = LCD_DATA | x;
        MSDelay(1);
        LCD_CTRL = LCD_CTRL | RS;
        MSDelay(1);
        LCD_CTRL = LCD_CTRL | EN;
        MSDelay(1);
        LCD_CTRL = LCD_CTRL & ~EN;
        MSDelay(5);
       
        x = (data & 0x0F)<< 2;
        LCD_DATA =LCD_DATA & ~0x3C;                     
        LCD_DATA = LCD_DATA | x;
        LCD_CTRL = LCD_CTRL | EN;
        MSDelay(1);
        LCD_CTRL = LCD_CTRL & ~EN;
        MSDelay(15);
  }
  
void KEYPADSCAN() {
        //coloana 1
         KEYPAD = KEYPAD & 0xF7;
        while(KEYPAD == 0x77)
          DATWRT4('/');
        while(KEYPAD == 0xB7)
          DATWRT4('*');
        while(KEYPAD == 0xD7)
          DATWRT4('-');
        while(KEYPAD == 0xE7)
          DATWRT4('+');
         
        //coloana 2
        KEYPAD = KEYPAD & 0xFB;
        if(KEYPAD == 0x7B)
          DATWRT4('.');
        if(KEYPAD == 0xBB)
          DATWRT4('9');
        if(KEYPAD == 0xDB)
          DATWRT4('6');
        if(KEYPAD == 0xEB)
          DATWRT4('3');
         
        //coloana 3 
        KEYPAD = KEYPAD & 0xFD;
        if(KEYPAD == 0x7D)
          DATWRT4('0');
        if(KEYPAD == 0xBD)
          DATWRT4('8');
        if(KEYPAD == 0xDD)
          DATWRT4('5');
        if(KEYPAD == 0xED)
          DATWRT4('2');
        
        //coloana 4  
        KEYPAD = KEYPAD & 0xFE;
        if(KEYPAD == 0x7E)
          DATWRT4('=');
        if(KEYPAD == 0xBE)
          DATWRT4('7');
        if(KEYPAD == 0xDE)
          DATWRT4('4');
        if(KEYPAD == 0xEE)
          DATWRT4('1');
        
}


 void MSDelay(unsigned int itime)
  {
    unsigned int i; unsigned int j;
    for(i=0;i<itime;i++)
      for(j=0;j<4000;j++);
 }