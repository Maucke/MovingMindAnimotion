#include "OLED_Animation.h"
#include "main.h"
#include "gpio.h"
#include "sys.h"
#include "math.h"


#ifdef __cplusplus
extern "C"  {
#endif
	
OLED_Animation::OLED_Animation(void) {
}

typedef struct
{
	float x;//�˶���˼ά��λ������
	float y;//�˶���˼ά��λ������
	float dirx;//�˶���˼ά��λ�������˶���
	float diry;//�˶���˼ά��λ�������˶���
	float r;//
	u16 color;//�˶���˼ά��λ��ɫ
}MTMOVMIND;

MTMOVMIND mtmovmind[MINDMAX];
  

OLED_STATUS OLED_Animation::OLED_MovMind(u8 Index)
{
	if(mtmovmind[Index].x<=3)
	{	
		mtmovmind[Index].x = 4;
		return OLED_IDLE;
	}
	else if(mtmovmind[Index].x>=SSD1351_WIDTH-2)
	{
		mtmovmind[Index].x = SSD1351_WIDTH-3;
		return OLED_IDLE;
	}
	else if(mtmovmind[Index].y<=0)
	{
		mtmovmind[Index].y = 1;
		return OLED_IDLE;
	}
	else if(mtmovmind[Index].y>=SSD1351_HEIGHT-2)
	{
		mtmovmind[Index].y = SSD1351_HEIGHT-3;
		return OLED_IDLE;
	}
	else
	{
		mtmovmind[Index].x += mtmovmind[Index].dirx;
		mtmovmind[Index].y += mtmovmind[Index].diry;
	}
  return OLED_BUSY;
}

u16 GetMindDistanceSquare(u16 x0,u16 y0,u16 x1,u16 y1)
{
	return ((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1));
}

void OLED_Animation::Motion_MindInit(void)
{
	int i;
	for(i=0;i<MINDMAX;i++)
	{
		mtmovmind[i].color = oled.RandomColor();
		__ASM("NOP");
		mtmovmind[i].x = rand()%(SSD1351_WIDTH-4)+4;
		__ASM("NOP");
		mtmovmind[i].y = rand()%SSD1351_HEIGHT;
		
		mtmovmind[i].dirx = (rand()%30-15)*0.1f;
		mtmovmind[i].diry = (rand()%30-15)*0.1f;
		if(mtmovmind[i].dirx<0.2&&mtmovmind[i].dirx>-0.2)
			mtmovmind[i].dirx = 0.5;
		if(mtmovmind[i].diry<0.2&&mtmovmind[i].diry>-0.2)
			mtmovmind[i].diry = 0.5;
	}
}


void OLED_Animation::Motion_Mind(void)
{
	int i,j;
	for(i=0;i<MINDMAX;i++)
	{
		if(OLED_MovMind(i) == OLED_IDLE)
		{
			mtmovmind[i].color = oled.RandomColor();
			mtmovmind[i].dirx = (rand()%30-15)*0.1f;
			mtmovmind[i].diry = (rand()%30-15)*0.1f;
			if(mtmovmind[i].dirx<0.2&&mtmovmind[i].dirx>-0.2)
				mtmovmind[i].dirx = 0.5;
			if(mtmovmind[i].diry<0.2&&mtmovmind[i].diry>-0.2)
				mtmovmind[i].diry = 0.5;
		}
	}
	
	for(i=0;i<MINDMAX;i++)
	{
		for(j=0;j<MINDMAX;j++)
		{
			if((mtmovmind[i].x-mtmovmind[j].x)*(mtmovmind[i].x-mtmovmind[j].x)+(mtmovmind[i].y-mtmovmind[j].y)*(mtmovmind[i].y-mtmovmind[j].y)<900)
			{
				oled.Draw_Line(mtmovmind[j].x,mtmovmind[j].y,mtmovmind[i].x,mtmovmind[i].y,0xFFFF);
			}
		}
	}
	
	for(i=0;i<MINDMAX;i++)
		oled.Fill_Circle(mtmovmind[i].x,mtmovmind[i].y,2,mtmovmind[i].color);
}

#ifdef __cplusplus
}
#endif


