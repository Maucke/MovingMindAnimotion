#ifndef __OLED_ANIMATION_H
#define __OLED_ANIMATION_H

#include "stm32f1xx_hal.h"
#include "OLED_GFX.h"
#include "stdlib.h"
#include "sys.h"

#define MINDMAX 14

typedef enum
{
  OLED_OK       = 0x00U,
  OLED_ERROR    = 0x01U,
  OLED_BUSY     = 0x02U,
  OLED_IDLE     = 0x03U,
} OLED_STATUS;

extern OLED_GFX oled;
#ifdef __cplusplus
extern "C" {
#endif

  class OLED_Animation {
    
    public: 
			OLED_Animation(void);
			void Motion_MindInit(void);
			void Motion_Mind(void);
    private:  
      OLED_STATUS OLED_MovMind(u8 Index);

  };





#ifdef __cplusplus
}
#endif
  
#endif
