//SPI总线读写25XX320EEPROM  master:microcontroller  slave:EEPROM
#include <reg51.h>
#include <intrins.h>

sbit CS=P1^3; 
sbit SO=P1^2;
sbit SI=P1^1; 
sbit SCK=P1^0; //SCK=0; //CS=1;

/**************延时n微秒***************/ 
void delaynus(unsigned char n) 
{  
    while(n--);
} 
/**************写允许函数**************/ 
void write_enable(unsigned char state) 
{  
    unsigned char i;
    unsigned char datatmp = state;
    CS=0;   
    SCK=0; 
    delaynus(2);  
    for(i=0;i<8;i++)    //上升沿有效
    {  
        // SI=datatmp&0x80;
        datatmp<<=1;
        SI=CY;
        delaynus(2);  
        SCK=1;    
        delaynus(2);  
        SCK=0;  
    }
    CS=1;  
    delaynus(5); 
}

/****************写指令函数***************/ 
void write_com(unsigned char com) 
{  
    unsigned char i;
    unsigned char datatmp = com;
    CS=0;   
    SCK=0;  
    delaynus(2);  
    for(i=0;i<8;i++)  
    {  
        datatmp<<=1;
        SI=CY;  
        delaynus(2);  
        SCK=1;   
        delaynus(2);  
        SCK=0;  
    } 
} 
/****************写地址函数***************/ 
void write_addr(unsigned int addr) 
{  
    unsigned char i;
    unsigned int addrtmp = addr;
    // unsigned char addr_l = (unsigned char)(addr&0x00FF);
    // unsigned char addr_h = (unsigned char)((addr>>8)&0xFF);
    CS=0;  
    SCK=0;  
    delaynus(2);  
    for(i=0;i<16;i++)  
    {  
        addrtmp<<=1;
        SI=CY;  
        delaynus(2);  
        SCK=1;  
        delaynus(2);  
        SCK=0;  
    }   
} 
/****************写数据函数***************/ 
void write_data(unsigned char dat) 
{  
    unsigned char i;
    unsigned char datatmp = dat;
    CS=0;  
    SCK=0;  
    delaynus(2);  
    for(i=0;i<8;i++)  
    {  
        datatmp<<=1;
        SI=CY;  
        delaynus(2);  
        SCK=1;   
        delaynus(2);  
        SCK=0;  
    } 
} 
/****************读命令函数***************/ 
void read_com(unsigned char read) 
{  
    unsigned char i;
    unsigned char datatmp = read;
    CS=0;  
    SCK=0;  
    delaynus(2); 
    for(i=0;i<8;i++)  
    {  
        datatmp<<=1;
        SI=CY;  
        delaynus(2);  
        SCK=1;  
        delaynus(2);  
        SCK=0;  
    } 
} 
/****************读数据函数***************/ 
unsigned char read_data() 
{  
    unsigned char i;  
    unsigned char dat=0;  
    delaynus(2);  
    SCK=0;  
    CS=0;  
    for(i=0;i<8;i++)    //下降沿有效
    {  
        SCK=1;  
        dat<<=1;
        if(SO==1)  
            dat|=0x01;  
        delaynus(2);  
        SCK=0;  
        delaynus(2);  
    }
    CS=1;  
    return dat; 
} 
void main() 
{  
    unsigned char rdtmp;
    CS=0;  
    write_enable(0x06);  
    write_com(0x02); 
    write_addr(0x00);  
    write_data(0x80);  
    CS=1; 
    delaynus(20);  
    CS=0; 
    read_com(0x03); 
    write_addr(0x00);  
    delaynus(2);  
    rdtmp=read_data();  
    P3=rdtmp;  
    CS=1; 
}   
   
