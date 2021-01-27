#ifndef __OLED_DRIVER_H
#define __OLED_DRIVER_H

#include "stm32f1xx_hal.h"
#include "sys.h"


#define OCX 64
#define OCY 64
#define PI 3.14159f

#define SSD1351_WIDTH   128
#define SSD1351_HEIGHT  128

#define SSD1351_CMD_SETCOLUMN       0x15
#define SSD1351_CMD_SETROW          0x75
#define SSD1351_CMD_WRITERAM        0x5C
#define SSD1351_CMD_READRAM         0x5D
#define SSD1351_CMD_SETREMAP        0xA0
#define SSD1351_CMD_STARTLINE       0xA1
#define SSD1351_CMD_DISPLAYOFFSET 	0xA2
#define SSD1351_CMD_DISPLAYALLOFF 	0xA4
#define SSD1351_CMD_DISPLAYALLON  	0xA5
#define SSD1351_CMD_NORMALDISPLAY 	0xA6
#define SSD1351_CMD_INVERTDISPLAY 	0xA7
#define SSD1351_CMD_FUNCTIONSELECT 	0xAB
#define SSD1351_CMD_DISPLAYOFF      0xAE
#define SSD1351_CMD_DISPLAYON     	0xAF
#define SSD1351_CMD_PRECHARGE       0xB1
#define SSD1351_CMD_DISPLAYENHANCE  0xB2
#define SSD1351_CMD_CLOCKDIV        0xB3
#define SSD1351_CMD_SETVSL          0xB4
#define SSD1351_CMD_SETGPIO 		    0xB5
#define SSD1351_CMD_PRECHARGE2      0xB6
#define SSD1351_CMD_SETGRAY         0xB8
#define SSD1351_CMD_USELUT          0xB9
#define SSD1351_CMD_PRECHARGELEVEL 	0xBB
#define SSD1351_CMD_VCOMH           0xBE
#define SSD1351_CMD_CONTRASTABC     0xC1
#define SSD1351_CMD_CONTRASTMASTER  0xC7
#define SSD1351_CMD_MUXRATIO        0xCA
#define SSD1351_CMD_COMMANDLOCK     0xFD
#define SSD1351_CMD_HORIZSCROLL     0x96
#define SSD1351_CMD_STOPSCROLL      0x9E
#define SSD1351_CMD_STARTSCROLL     0x9F


#define swap(a, b) { uint16_t t = a; a = b; b = t; }

#define OLED_CS PAout(6)
#define OLED_RST PAout(4)
#define OLED_A0 PAout(5)
#define OLED_WR PBout(0)
#define OLED_RD PBout(1)  

#define DATAOUT(x) GPIOC->ODR = x; //数据输出
#define DATAIN     GPIOC->IDR;   //数据输入

#define OLED_CMD  0		    //写命令
#define OLED_DATA 1				//写数据

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
typedef unsigned char  uint8;                   /* defined for unsigned 8-bits integer variable 	无符号8位整型变量  */
typedef signed   char  int8;                    /* defined for signed 8-bits integer variable		有符号8位整型变量  */
typedef unsigned short uint16;                  /* defined for unsigned 16-bits integer variable 	无符号16位整型变量 */
typedef signed   short int16;                   /* defined for signed 16-bits integer variable 		有符号16位整型变量 */
typedef unsigned int   uint32;                  /* defined for unsigned 32-bits integer variable 	无符号32位整型变量 */
typedef signed   int   int32;                   /* defined for signed 32-bits integer variable 		有符号32位整型变量 */
typedef float          fp32;                    /* single precision floating point variable (32bits) 单精度浮点数（32位长度） */
typedef double         fp64;                    /* double precision floating point variable (64bits) 双精度浮点数（64位长度） */


#ifdef __cplusplus
extern "C" {
#endif

  class OLED_Driver {
    
    public: 
      OLED_Driver(void);
		
			void MOLED_Fill(uint16_t data);
		
			u16 ConvertColor(u8 red,u8 green,u8 blue);
      void Device_Init(void);
      void Clear_Screen(void);
      void Refrash_Screen(void);
      void Fill_Color(uint16_t color);
      void Fill_Color(void);
      void Set_Coordinate(uint16_t x, uint16_t y);
			uint16_t RandomColor(void);

      void Write_text(uint8_t data1);
      void Set_Address(uint8_t column, uint8_t row);
      
      void Set_Color(uint16_t color);
      void Set_FillColor(uint16_t color);
    
      void Invert(bool v);
      void Draw_Pixel(int16_t x, int16_t y);
      void Draw_Pixel(int16_t x, int16_t y,uint16_t color);
    
      void Write_Data(uint8_t dat);
      void Write_Data(uint8_t* dat_p, uint16_t length);
    
      void Draw_FastHLine(int16_t x, int16_t y, int16_t length);
      void Draw_FastHLine(int16_t x, int16_t y, int16_t length,uint16_t color);
			
      void Draw_FastVLine(int16_t x, int16_t y, int16_t length);
      void Draw_FastVLine(int16_t x, int16_t y, int16_t length,uint16_t color);
      void Write_Command(uint8_t data1);
			
			
			void Set_DampColor(uint16_t color);
			void Set_Wheel(uint16_t WheelPos);
			void Set_Wheelf(uint16_t WheelPos);
			u16 WheelP(u16 WheelPos);
    private:  
      uint8_t Float2U8(float Input);
      void RAM_Address(void);
			void Calc_Color(void);
  };



#ifdef __cplusplus
}
#endif
  
#endif

