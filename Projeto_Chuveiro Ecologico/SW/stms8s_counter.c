/***************************************************************
 * Biblioteca de Contagem                                      *
 ***************************************************************/
 
 /* Autor: Felipe Antonio Montagneri Lucchini
    Data : 05/04/2016
	*/
	
/***************************************************************/

#include "stm8s.h"
#include "stm8s_counter.h"

uint8_t  count      = 0;
uint8_t  limitCount = 0;


/***************************************************************
 * Fun��es e Procedimentos                                     *                            
 ***************************************************************/
/***************************************************************
 * void counterInit(void);                                     *
 *                                                             * 
 * Inicializa��o do TIMER1 com clock externo                   *       
 *                                                             * 
 ***************************************************************/
 void counterInit(void){
	 
	 TIM1_DeInit();
	 
	 TIM1_TimeBaseInit(99, TIM1_COUNTERMODE_UP, 3200, 0);
	 
   TIM1_ICInit(TIM1_CHANNEL_2, TIM1_ICPOLARITY_RISING, TIM1_ICSELECTION_DIRECTTI,  TIM1_ICPSC_DIV1, 0x00);

  }
 
/***************************************************************
 * void setMaxCount(maxCount);                                 *
 *                                                             * 
 * uint16_t maxValue -> sele��o do maior valor de contagem;    *  
 *                                                             * 
 * void -> n�o retorna valor;                                  * 
 ***************************************************************/
void setMaxCount(uint8_t maxCount){
   
	 limitCount = maxCount;
   
  }
	
/***************************************************************
 * uint8_t counterGetValue();                                         *
 *                                                             * 
 * void -> n�o recebe par�metros;                              *  
 *                                                             * 
 * uint8_t -> retorna o valor da contagem;                     * 
 ***************************************************************/
uint8_t counterGetValue(void){
	 
	 return count;
	 
  }
 
/***************************************************************
 * void counterEnable();                                       *
 *                                                             * 
 * void -> n�o retorna valor;                                  *       
 *                                                             * 
 ***************************************************************/
void counterEnable(void){
	 
	 TIM1_ITConfig(TIM1_IT_CC2,    ENABLE);
	 TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);
	 
	 TIM1_Cmd(ENABLE);
	 
  }
 
/***************************************************************
  * Interrup��o do TIM1 (Capture e Compare);                   *
 ***************************************************************/ 
 INTERRUPT_HANDLER(TIM1_CAP_COM_IRQHandler, 12){
	 
	 TIM1_ClearITPendingBit(TIM1_IT_CC2);
   	
	 count++;
	 
	 if(count > (limitCount)){
		 
		 count = 1;
		 
	  }
	 
	 TIM1_SetCounter(0);
	 
  }
 
/***************************************************************
  * Interrup��o do TIM1 (Overflow);                            *
 ***************************************************************/
 INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_BRK_IRQHandler, 11){
	 
	 TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
	 
	 count = limitCount + 1;
	  
  }

