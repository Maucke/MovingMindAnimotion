#include "OLED_GFX.h"

#include "stdlib.h"


uint8_t Row,Column;
FONT_SIZE Font_Size;


#ifdef __cplusplus
extern "C"  {
#endif
  
OLED_GFX::OLED_GFX(void)  {
  Row = 0;
  Column = 0;
  Font_Size = FONT_5X8;
}
  
  
void OLED_GFX::Draw_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
  // Update in subclasses if desired!
  if(x0 == x1)  {
    if(y0 > y1) swap(y0, y1);
    Draw_FastVLine(x0, y0, y1 - y0 );
  } 
  else if(y0 == y1) {
    if(x0 > x1)
      swap(x0, x1);
    Draw_FastHLine(x0, y0, x1 - x0 );
  }
  else
    Write_Line(x0, y0, x1, y1);
}
  
void OLED_GFX::Draw_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1,uint16_t color) {
  // Update in subclasses if desired!
  if(x0 == x1)  {
    if(y0 > y1) swap(y0, y1);
    Draw_FastVLine(x0, y0, y1 - y0 ,color);
  } 
  else if(y0 == y1) {
    if(x0 > x1)
      swap(x0, x1);
    Draw_FastHLine(x0, y0, x1 - x0 ,color);
  }
  else
    Write_Line(x0, y0, x1, y1,color);
}
  
void  OLED_GFX::Draw_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8 with, uint16_t color)
{  int32   dx;						// ֱ��x���ֵ����
   int32   dy;          			// ֱ��y���ֵ����
   int16    dx_sym;					// x����������Ϊ-1ʱ��ֵ����Ϊ1ʱ��ֵ����
   int16    dy_sym;					// y����������Ϊ-1ʱ��ֵ����Ϊ1ʱ��ֵ����
   int32   dx_x2;					// dx*2ֵ���������ڼӿ������ٶ�
   int32   dy_x2;					// dy*2ֵ���������ڼӿ������ٶ�
   int32   di;						// ���߱���
   
   int32   wx, wy;					// �߿����
   int32   draw_a, draw_b;
   
   /* �������� */
   if(with==0) return;
   if(with>50) with = 50;
   
   dx = x1-x0;						// ��ȡ����֮��Ĳ�ֵ
   dy = y1-y0;
   
   wx = with/2;
   wy = with-wx-1;
   
   /* �ж��������򣬻��Ƿ�Ϊˮƽ�ߡ���ֱ�ߡ��� */
   if(dx>0)							// �ж�x�᷽��
   {  dx_sym = 1;					// dx>0������dx_sym=1
   }
   else
   {  if(dx<0)
      {  dx_sym = -1;				// dx<0������dx_sym=-1
      }
      else
      {  /* dx==0������ֱ�ߣ���һ�� */
         wx = x0-wx;
         if(wx<0) wx = 0;
         wy = x0+wy;
         
         while(1)
         {  x0 = wx;
					 
						if(y0 > y1)
							swap(y0, y1);
            Draw_FastVLine(x0, y0, y1 - y0, color);
            if(wx>=wy) break;
            wx++;
         }
         
      	 return;
      }
   }
   
   if(dy>0)							// �ж�y�᷽��
   {  dy_sym = 1;					// dy>0������dy_sym=1
   }
   else
   {  if(dy<0)
      {  dy_sym = -1;				// dy<0������dy_sym=-1
      }
      else
      {  /* dy==0����ˮƽ�ߣ���һ�� */
         wx = y0-wx;
         if(wx<0) wx = 0;
         wy = y0+wy;
         
         while(1)
         {  y0 = wx;
						if(x0 > x1)
							swap(x0, x1);
							Draw_FastHLine(x0, y0, x1 - x0 ,color);
            if(wx>=wy) break;
            wx++;
         }
      	 return;
      }
   }
    
   /* ��dx��dyȡ����ֵ */
   dx = dx_sym * dx;
   dy = dy_sym * dy;
 
   /* ����2����dx��dyֵ */
   dx_x2 = dx*2;
   dy_x2 = dy*2;
   
   /* ʹ��Bresenham�����л�ֱ�� */
   if(dx>=dy)						// ����dx>=dy����ʹ��x��Ϊ��׼
   {  di = dy_x2 - dx;
      while(x0!=x1)
      {  /* x����������������y���򣬼�����ֱ�� */
         draw_a = y0-wx;
         if(draw_a<0) draw_a = 0;
         draw_b = y0+wy;
				if(draw_a > draw_b)
					swap(draw_a, draw_b);
         Draw_FastVLine(x0, draw_a, draw_b - draw_a, color);
         
         x0 += dx_sym;				
         if(di<0)
         {  di += dy_x2;			// �������һ���ľ���ֵ
         }
         else
         {  di += dy_x2 - dx_x2;
            y0 += dy_sym;
         }
      }
      draw_a = y0-wx;
      if(draw_a<0) draw_a = 0;
      draw_b = y0+wy;
				if(draw_a > draw_b)
					swap(draw_a, draw_b);
      Draw_FastVLine(x0, draw_a, draw_b - draw_a, color);
   }
   else								// ����dx<dy����ʹ��y��Ϊ��׼
   {  di = dx_x2 - dy;
      while(y0!=y1)
      {  /* y����������������x���򣬼���ˮƽ�� */
         draw_a = x0-wx;
         if(draw_a<0) draw_a = 0;
         draw_b = x0+wy;
				if(draw_a > draw_b)
					swap(draw_a, draw_b);
         Draw_FastHLine(draw_a, y0, draw_b - draw_a, color);
         
         y0 += dy_sym;
         if(di<0)
         {  di += dx_x2;
         }
         else
         {  di += dx_x2 - dy_x2;
            x0 += dx_sym;
         }
      }
      draw_a = x0-wx;
      if(draw_a<0) draw_a = 0;
      draw_b = x0+wy;
				if(draw_a > draw_b)
					swap(draw_a, draw_b);
      Draw_FastHLine(draw_a, y0, draw_b - draw_a, color);
   } 
  
}

void OLED_GFX::Write_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1)  {
    
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    
  if (steep)  {
    swap(x0, y0);
    swap(x1, y1);
  }
  if (x0 > x1)  {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if(y0 < y1) {
    ystep = 1;
  } 
  else  {
    ystep = -1;
  }

  for(; x0<=x1; x0++) {
    if(steep)
      Draw_Pixel(y0, x0);
    else
      Draw_Pixel(x0, y0);
    err -= dy;
      
    if(err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

void OLED_GFX::Write_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1,uint16_t color)  {
    
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    
  if (steep)  {
    swap(x0, y0);
    swap(x1, y1);
  }
  if (x0 > x1)  {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if(y0 < y1) {
    ystep = 1;
  } 
  else  {
    ystep = -1;
  }

  for(; x0<=x1; x0++) {
    if(steep)
      Draw_Pixel(y0, x0,color);
    else
      Draw_Pixel(x0, y0,color);
    err -= dy;
      
    if(err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

  // Draw a rectangle
void OLED_GFX::Draw_Rect(int16_t x, int16_t y, int16_t w, int16_t h) {
    
  Draw_FastHLine(x, y, w);
  Draw_FastHLine(x, y+h, w);
  Draw_FastVLine(x, y, h);
  Draw_FastVLine(x+w, y, h);
}
  // Draw a rectangle
void OLED_GFX::Draw_Rect(int16_t x, int16_t y, int16_t w, int16_t h,uint16_t color) {
    
  Draw_FastHLine(x, y, w, color);
  Draw_FastHLine(x, y+h, w, color);
  Draw_FastVLine(x, y, h, color);
  Draw_FastVLine(x+w, y, h, color);
}

/**************************************************************************/
/*!
    @brief  Draws a filled rectangle using HW acceleration
*/
/**************************************************************************/
void OLED_GFX::Fill_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {

	uint16_t i,j;
  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT))
  return;

  // Y bounds check
  if (y+h > SSD1351_HEIGHT) {
    h = SSD1351_HEIGHT - y;
  }

  // X bounds check
  if (x+w > SSD1351_WIDTH)  {
    w = SSD1351_WIDTH - x;
  }

	for(i=x;i<=w+x;i++)
		for(j=y;j<=h+y;j++)
			Draw_Pixel(i,j);
}

/**************************************************************************/
/*!
    @brief  Draws a filled rectangle using HW acceleration
*/
/**************************************************************************/
void OLED_GFX::Fill_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h,uint16_t color) {

	uint16_t i,j;
  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT))
  return;

  // Y bounds check
  if (y+h > SSD1351_HEIGHT) {
    h = SSD1351_HEIGHT - y ;
  }

  // X bounds check
  if (x+w > SSD1351_WIDTH)  {
    w = SSD1351_WIDTH - x ;
  }

	for(i=x;i<=w+x;i++)
		for(j=y;j<=h+y;j++)
			Draw_Pixel(i,j, color);
}
void OLED_GFX::Fill_Circle(int16_t x0, int16_t y0, int16_t r) {
  
  Draw_FastVLine(x0, y0-r, 2*r);
  FillCircle_Helper(x0, y0, r, 3, 0);
}
void OLED_GFX::Fill_Circle(int16_t x0, int16_t y0, int16_t r,uint16_t color) {
  
  Draw_FastVLine(x0, y0-r, 2*r, color);
  FillCircle_Helper(x0, y0, r, 3, 0, color);
}

// Used to do circles and roundrects
void OLED_GFX::FillCircle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t corner, int16_t delta)  {

  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while(x<y)  {
    if(f >= 0)  {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    if(corner & 0x1)  {
      Draw_FastVLine(x0+x, y0-y, 2*y+delta);
      Draw_FastVLine(x0+y, y0-x, 2*x+delta);
    }
    if(corner & 0x2)  {
      Draw_FastVLine(x0-x, y0-y, 2*y+delta);
      Draw_FastVLine(x0-y, y0-x, 2*x+delta);
    }
  }
}

// Used to do circles and roundrects
void OLED_GFX::FillCircle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t corner, int16_t delta,uint16_t color)  {

  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while(x<y)  {
    if(f >= 0)  {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    if(corner & 0x1)  {
      Draw_FastVLine(x0+x, y0-y, 2*y+delta, color);
      Draw_FastVLine(x0+y, y0-x, 2*x+delta, color);
    }
    if(corner & 0x2)  {
      Draw_FastVLine(x0-x, y0-y, 2*y+delta, color);
      Draw_FastVLine(x0-y, y0-x, 2*x+delta, color);
    }
  }
}

// Draw a circle outline
void OLED_GFX::Draw_Circle(int16_t x0, int16_t y0, int16_t r) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  Draw_Pixel(x0  , y0+r);
  Draw_Pixel(x0  , y0-r);
  Draw_Pixel(x0+r, y0  );
  Draw_Pixel(x0-r, y0  );

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    Draw_Pixel(x0 + x, y0 + y);
    Draw_Pixel(x0 - x, y0 + y);
    Draw_Pixel(x0 + x, y0 - y);
    Draw_Pixel(x0 - x, y0 - y);
    Draw_Pixel(x0 + y, y0 + x);
    Draw_Pixel(x0 - y, y0 + x);
    Draw_Pixel(x0 + y, y0 - x);
    Draw_Pixel(x0 - y, y0 - x);
    }
}
// Draw a circle outline
void OLED_GFX::Draw_Circle(int16_t x0, int16_t y0, int16_t r,uint16_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  Draw_Pixel(x0  , y0+r, color);
  Draw_Pixel(x0  , y0-r, color);
  Draw_Pixel(x0+r, y0  , color);
  Draw_Pixel(x0-r, y0  , color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    Draw_Pixel(x0 + x, y0 + y, color);
    Draw_Pixel(x0 - x, y0 + y, color);
    Draw_Pixel(x0 + x, y0 - y, color);
    Draw_Pixel(x0 - x, y0 - y, color);
    Draw_Pixel(x0 + y, y0 + x, color);
    Draw_Pixel(x0 - y, y0 + x, color);
    Draw_Pixel(x0 + y, y0 - x, color);
    Draw_Pixel(x0 - y, y0 - x, color);
    }
}

void OLED_GFX::Draw_Circle(int16_t x0, int16_t y0, int16_t r,u8 Type,uint16_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;
	switch(Type)
	{
		case 1:
				Draw_Pixel(x0  , y0+r, color);
				Draw_Pixel(x0+r, y0  , color);break;//����
		case 2:
				Draw_Pixel(x0  , y0+r, color);
				Draw_Pixel(x0-r, y0  , color);break;//����
		case 3:
				Draw_Pixel(x0  , y0-r, color);
				Draw_Pixel(x0+r, y0  , color);break;//����
		case 4:
				Draw_Pixel(x0-r, y0  , color);
				Draw_Pixel(x0  , y0-r, color);break;//����
	}

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

	switch(Type)
	{
		case 1:
    Draw_Pixel(x0 + x, y0 + y, color);
    Draw_Pixel(x0 + y, y0 + x, color);break;
		case 2:
    Draw_Pixel(x0 - x, y0 + y, color);
    Draw_Pixel(x0 - y, y0 + x, color);break;
		case 3:
    Draw_Pixel(x0 + x, y0 - y, color);
    Draw_Pixel(x0 + y, y0 - x, color);break;
		case 4:
    Draw_Pixel(x0 - y, y0 - x, color);
    Draw_Pixel(x0 - x, y0 - y, color);break;
	}
		
		
		
    }
}

// Draw a rounded rectangle
void OLED_GFX::Draw_RoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r) {
    // smarter version

    Draw_FastHLine(x+r  , y    , w-2*r); // Top
    Draw_FastHLine(x+r  , y+h-1, w-2*r); // Bottom
    Draw_FastVLine(x    , y+r  , h-2*r); // Left
    Draw_FastVLine(x+w-1, y+r  , h-2*r); // Right
    // draw four corners
    DrawCircle_Helper(x+r    , y+r    , r, 1);
    DrawCircle_Helper(x+w-r-1, y+r    , r, 2);
    DrawCircle_Helper(x+w-r-1, y+h-r-1, r, 4);
    DrawCircle_Helper(x+r    , y+h-r-1, r, 8);
}
// Draw a rounded rectangle
void OLED_GFX::Draw_RoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r,uint16_t color) {
    // smarter version

    Draw_FastHLine(x+r  , y    , w-2*r, color); // Top
    Draw_FastHLine(x+r  , y+h-1, w-2*r, color); // Bottom
    Draw_FastVLine(x    , y+r  , h-2*r, color); // Left
    Draw_FastVLine(x+w-1, y+r  , h-2*r, color); // Right
    // draw four corners
    DrawCircle_Helper(x+r    , y+r    , r, 1, color);
    DrawCircle_Helper(x+w-r-1, y+r    , r, 2, color);
    DrawCircle_Helper(x+w-r-1, y+h-r-1, r, 4, color);
    DrawCircle_Helper(x+r    , y+h-r-1, r, 8, color);
}

void OLED_GFX::DrawCircle_Helper( int16_t x0, int16_t y0, int16_t r, uint8_t corner) {
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    if (corner & 0x4) {
      Draw_Pixel(x0 + x, y0 + y);
      Draw_Pixel(x0 + y, y0 + x);
    }
    if (corner & 0x2) {
      Draw_Pixel(x0 + x, y0 - y);
      Draw_Pixel(x0 + y, y0 - x);
    }
    if (corner & 0x8) {
      Draw_Pixel(x0 - y, y0 + x);
      Draw_Pixel(x0 - x, y0 + y);
    }
    if (corner & 0x1) {
      Draw_Pixel(x0 - y, y0 - x);
      Draw_Pixel(x0 - x, y0 - y);
    }
  }
}


void OLED_GFX::DrawCircle_Helper( int16_t x0, int16_t y0, int16_t r, uint8_t corner,uint16_t color) {
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    if (corner & 0x4) {
      Draw_Pixel(x0 + x, y0 + y, color);
      Draw_Pixel(x0 + y, y0 + x, color);
    }
    if (corner & 0x2) {
      Draw_Pixel(x0 + x, y0 - y, color);
      Draw_Pixel(x0 + y, y0 - x, color);
    }
    if (corner & 0x8) {
      Draw_Pixel(x0 - y, y0 + x, color);
      Draw_Pixel(x0 - x, y0 + y, color);
    }
    if (corner & 0x1) {
      Draw_Pixel(x0 - y, y0 - x, color);
      Draw_Pixel(x0 - x, y0 - y, color);
    }
  }
}

// Draw a triangle
void OLED_GFX::Draw_Triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)  {
  Draw_Line(x0, y0, x1, y1);
  Draw_Line(x1, y1, x2, y2);
  Draw_Line(x2, y2, x0, y0);
}
// Draw a triangle
void OLED_GFX::Draw_Triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2,uint16_t color)  {
  Draw_Line(x0, y0, x1, y1, color);
  Draw_Line(x1, y1, x2, y2, color);
  Draw_Line(x2, y2, x0, y0, color);
}


#ifdef __cplusplus
}
#endif

