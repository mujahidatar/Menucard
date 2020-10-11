#include <stdio.h>	//Define I/O Functions
#include <reg51.h>	//Define 8051 Registers
#define DATA P3	//Define DATA to Port1
#define DATA1 P0
void lcd_init(void); //LCD Initialization
void lcd_init1(void);
void menu(void); //DIGITAL MENU CARD
void table(void); //enter table no
void order(void); //enter order no
void qty(void); //enter qty
void menu2(void); //DIGITAL MENU CARD
void table2(void); //enter table no
void order2(void); //enter order no
void qty2(void); //enter qty
void cnf(void); //cnf order
void fnl(void); 
void tnx(void);// thank you
void lcd_cmd(unsigned char);	//LCD Command Function
void lcd_cmd1(unsigned char);
void lcd_display(unsigned char);	//LCD Display Function
void lcd_display1(unsigned char);
void Key_Scan(void);	//KeyScan Function
void DelayMs(int);	//DelayMs Function
sbit RS = P2^1;	//Register Select
//sbit RW = P2^5;	//LCD Read/Write
sbit lcd_e = P2^0;	//LCD Enable
sbit RES = P2^6;	//Register Select
sbit BUZZER1 = P2^4;	//LCD Read/Write
sbit lcd_e1 = P2^7;	//LCD Enable
sbit start = P2^2;
sbit BUZZER2 = P2^3;
unsigned char X,Y,Z,R,C,ch;
unsigned int i=0;
unsigned char Key[4][4] = {'1','4','7','*',	
                           '2','5','8','0',
                           '3','6','9','#',
                           'A','B','C','D',
                           };

code unsigned char menu1[] = ("DIGITAL MENUCARD");//Display the Message

code unsigned char table1[] = (" ENTER TABLE NO ");

code unsigned char order1[] = (" ENTER ORDER");	

code unsigned char qty1[] = (" ENTER QUANTITY ");	

code unsigned char menu3[] = ("DIGITAL MENUCARD");//Display the Message

code unsigned char table3[] = ("  TABLE NO ");

code unsigned char order3[] = (" ORDER");	

code unsigned char qty3[] = ("QUANTITY ");

code unsigned char cnf1[] = (" PRESS C TO CONFIRM ORDER ");

code unsigned char fnl1[] = ("TBL   ORD   QNT ");
													 
code unsigned char tnx1[] = (" THANK YOU....... ");
//-------------------------------
// Main Program
//-------------------------------


void main()
{

while(1)
{
start=1;
while(start==1);	
lcd_init();
lcd_init1();
menu();
menu2();
DelayMs(500);
lcd_cmd(0x01) ;
lcd_cmd1(0x01);

lcd_cmd(0x80);
table();
lcd_cmd1(0x80);
table2();
Key_Scan();
ch = Key[C][R];	//Assign Key value to ch;
SBUF=ch;	//[C][R] denotes Column
X=ch;	
 lcd_cmd(0xc0);
DelayMs(35);	//and Row Value of Keypad
lcd_display(ch);
lcd_cmd1(0xc0);
DelayMs(35);	//and Row Value of Keypad
lcd_display1(ch);
DelayMs(500);
lcd_cmd(0x01);	//Clear display screen
lcd_cmd1(0x01);
DelayMs(15);

lcd_cmd(0x80);
DelayMs(35);
order();
lcd_cmd1(0x80);
DelayMs(35);
order2();
Key_Scan();
ch = Key[C][R];	//Assign Key value to ch;
SBUF=ch;	//[C][R] denotes Column
Y=ch;
 lcd_cmd(0xc0);
DelayMs(35);	//and Row Value of Keypad
lcd_display(ch);
lcd_cmd1(0xc0);
DelayMs(35);	//and Row Value of Keypad
lcd_display1(ch);
DelayMs(500);
lcd_cmd(0x01);	//Clear display screen
lcd_cmd1(0x01);
DelayMs(15);

lcd_cmd(0x80);
DelayMs(35);
qty();
lcd_cmd1(0x80);
DelayMs(35);
qty2();
Key_Scan();
ch = Key[C][R];	//Assign Key value to ch;
SBUF=ch;	//[C][R] denotes Column
Z=ch;
 lcd_cmd(0xc0);
DelayMs(35);	//and Row Value of Keypad
lcd_display(ch);
lcd_cmd1(0xc0);
DelayMs(35);	//and Row Value of Keypad
lcd_display1(ch);
DelayMs(500);
lcd_cmd(0x01);	//Clear display screen
lcd_cmd1(0x01);
DelayMs(15);

lcd_cmd(0x80);
DelayMs(35);
cnf();
Key_Scan();
ch = Key[C][R];	//Assign Key value to ch;
SBUF=ch;	//[C][R] denotes Column
 BUZZER1 = 0;
 lcd_cmd(0xc0);
DelayMs(35);	//and Row Value of Keypad
lcd_display(ch);
DelayMs(3000);
lcd_cmd(0x01);	//Clear display screen
DelayMs(15);
BUZZER1= 1;


lcd_cmd(0x80);
DelayMs(35);
tnx();
DelayMs(1000);
lcd_cmd(0x01);	//Clear display screen
DelayMs(15);

BUZZER2=0;
DelayMs(1000);
lcd_cmd1(0x80);
DelayMs(35);
fnl();
BUZZER2=1;
lcd_cmd1(0xc1);
DelayMs(35);	//and Row Value of Keypad
lcd_display1( X );
lcd_cmd1(0xc7);
DelayMs(35);
lcd_display1( Y );
lcd_cmd1(0xcd);
DelayMs(35);
lcd_display1( Z );
DelayMs(3000);
lcd_cmd1(0x01);	//Clear display screen
DelayMs(15);
}
}


//-------------------------------
// Key Scan Function 
//-------------------------------


void Key_Scan(void)	
{
unsigned int i = 0;
P1= 0xff;
//Scanning for Row Value	
P1 = 0x0F;	//Initialize Port2 to 0Fh
while(P1 == 0x0F);
if(P1 == 0x0E)	//Checking for Row0
R = 0;
else if(P1 == 0x0D)	//Checking for Row1
R = 1;
else if(P1 == 0x0B)	//Checking for Row2
R = 2;
else if(P1 == 0x07)	//Checking for Row3
R = 3;
//Scanning for Column Value
P1 = 0xF0;	//Initialize Port2 to F0h
while(P1 == 0xF0);
if(P1 == 0xE0)	//Checking for Column0
C = 0;
else if(P1 == 0xD0)	//Checking for Column1
C = 1;
else if(P1 == 0xB0)	//Checking for Column2
C = 2;
else if(P1 == 0x70)	//Checking for Column3
C = 3;
DelayMs(50);
}


//-------------------------------
// LCD command Function
//-------------------------------


void lcd_cmd(unsigned char cmnd)	
{
DATA = cmnd;
RS = 0;	//RS:Register Select
//RW = 0;	//RW:Read/Write
lcd_e = 1;	//LCD Enable
DelayMs(35);
lcd_e = 0;
}

//-------------------------------
// LCD command Function
//-------------------------------


void lcd_cmd1(unsigned char cmnd1)	
{
DATA1 = cmnd1;
RES = 0;	//RS:Register Select
	//RW:Read/Write
lcd_e1 = 1;	//LCD Enable
DelayMs(35);
lcd_e1 = 0;
}


//-------------------------------
//	LCD Data Function
//-------------------------------


void lcd_display(unsigned char dat)	
{
lcd_cmd(0x0c);
DATA = dat;
RS = 1;	//RS:Register Select
//RW = 0;	//RW:Read/Write
lcd_e = 1;
DelayMs(35);
lcd_e = 0;
}

//-------------------------------
//	LCD Data Function
//-------------------------------


void lcd_display1(unsigned char dat1)	
{
lcd_cmd1(0x0c);
DATA1 = dat1;
RES = 1;	//RS:Register Select
	//RW:Read/Write
lcd_e1 = 1;
DelayMs(35);
lcd_e1 = 0;
}

//-------------------------------
// LCD Initialization
//-------------------------------


void lcd_init(void)	
{

lcd_cmd(0x38);	//2x16 Character 5x7 dot 
DelayMs(15);	//matrix LCD,8-bit format
lcd_cmd(0x0c);	//Display On, cursor off
DelayMs(15);
lcd_cmd(0x06);	//Shift Cursor to right
DelayMs(15);
lcd_cmd(0x01);	//Clear display screen
DelayMs(15);
}


//-------------------------------
// LCD Initialization
//-------------------------------


void lcd_init1(void)	
{

lcd_cmd1(0x38);	//2x16 Character 5x7 dot 
DelayMs(15);	//matrix LCD,8-bit format
lcd_cmd1(0x0c);	//Display On, cursor off
DelayMs(15);
lcd_cmd1(0x06);	//Shift Cursor to right
DelayMs(15);
lcd_cmd1(0x01);	//Clear display screen
DelayMs(15);
}
//------------------------------------
// First Line Message Display
//------------------------------------

//lcd_cmd(0x80);	//First Line Initialization
//DelayMs(35);

void menu(void)
{
unsigned char i;
i=0;
while(menu1[i]!='\0')
{
lcd_display(menu1[i]);
i++;
}
DelayMs(50);
}

void table(void)
{
unsigned char i;
i=0;
while(table1[i]!='\0')
{
lcd_display(table1[i]);
i++;
}
DelayMs(50);
}

void order(void)
{
unsigned char i;
i=0;
while(order1[i]!='\0')
{
lcd_display(order1[i]);
i++;
}
DelayMs(50);
}

void qty(void)
{
unsigned char i;
i=0;
while(qty1[i]!='\0')
{
lcd_display(qty1[i]);
i++;
}
DelayMs(50);
}

void menu2(void)
{
unsigned char i;
i=0;
while(menu3[i]!='\0')
{
lcd_display1(menu3[i]);
i++;
}
DelayMs(50);
}

void table2(void)
{
unsigned char i;
i=0;
while(table3[i]!='\0')
{
lcd_display1(table3[i]);
i++;
}
DelayMs(50);
}

void order2(void)
{
unsigned char i;
i=0;
while(order3[i]!='\0')
{
lcd_display1(order3[i]);
i++;
}
DelayMs(50);
}

void qty2(void)
{
unsigned char i;
i=0;
while(qty3[i]!='\0')
{
lcd_display1(qty3[i]);
i++;
}
DelayMs(50);
}

void cnf(void)
{
unsigned char i;
i=0;
while(cnf1[i]!='\0')
{
lcd_display(cnf1[i]);
i++;
}
DelayMs(50);
}

  void tnx(void)
{
unsigned char i;
i=0;
while(tnx1[i]!='\0')
{
lcd_display(tnx1[i]);
i++;
}
DelayMs(50);
}

  void fnl(void)
{
unsigned char i;
i=0;
while(fnl1[i]!='\0')
{
lcd_display1(fnl1[i]);
i++;
}
DelayMs(50);
}
//------------------------------------
// Second Line Message Display	
//------------------------------------

//lcd_cmd(0xc0);	//Second Line Initialization
//DelayMs(35);
//i=0;
//while(msg1[i]!='\0')
//{
//lcd_display(msg1[i]);
//i++;
//} 
//DelayMs(50);
//}

//--------------------------
// DelayMs Function 
//--------------------------

void DelayMs(int k)
{
unsigned int a,b;
for(a=0;a<=k;a++)
for(b=0;b<=275;b++);
}
