/***************************************************************
 * Biblioteca de Temporização                                  *
 ***************************************************************/
 
 /* Autor: Felipe Antonio Montagneri Lucchini
    Data : 25/09/2015
	*/
	
/***************************************************************/

#include "stm8s.h"
#include "stm8s_timer.h"
#include "jiga_park.h"

uint8_t i           = 0;

bool    timeBase_1ms = FALSE;
bool    timeBase_1us = FALSE;

/***************************************************************
 * Vetor de Timers                                             *
 ***************************************************************/
timer timerUnit[TIMER_QTY]; 

/***************************************************************
 * Funções e Procedimentos                                     *                            
 ***************************************************************/
/***************************************************************
 * void timerInit(void);                                       *
 *                                                             * 
 * Configurações do Timer 4:                                   *
 *                                                             * 
 * Prescaler = 1                                               * 
 * Overflow  = 16                                              *
 *                                                             *
 * T = PRESCALER * OVERFLOW / FREQUENCIA DE CLOCK              *
 *                                                             *
 * T = 64 * 250 / 16.000.000 = 1ms                             *                            
 ***************************************************************/
void timerInit(void){
	
	TIM4_DeInit      ();                       
  TIM4_TimeBaseInit(TIM4_PRESCALER_64, 250); 	
  TIM4_ITConfig    (TIM4_IT_UPDATE, ENABLE);
  TIM4_Cmd         (ENABLE);

}

/***************************************************************
 * timerEnable (unit, enableCount);                            *
 *                                                             *
 * Controle de habilitação do timer                            *   
 *                                                             *
 * uint8_t unit        -> índice do timer a ser utilizado;     *
 * _Bool   enableCount	-> valor de hab/inib do timer;         *
 *                                                             *
 * void -> não retorna valor;                                  * 
 ***************************************************************/
void timerEnable(uint8_t unit, _Bool enableTimer){
	
	if(enableTimer){
		
		timerUnit[unit].enable = 1;
	
	}else{
		
		timerUnit[unit].enable = 0;
		
	}
	
}

/***************************************************************
 * timerReset (unit);                                          *   
 *                                                             *
 * Reset do valor de contagem do timer                         *
 *                                                             *
 * uint8_t unit        -> índice do timer a ser utilizado;     *
 *                                                             *
 * void -> não retorna valor;                                  * 
 ***************************************************************/
bool timerGetOverflow(uint8_t unit){
	
	if(timerUnit[unit].overflow == 1){
						
		return 1;
	
	}else{
		
		return timerUnit[unit].overflow;
		
	}
	
}

/***************************************************************
 * timerGetCount (unit);                                       *   
 *                                                             *
 * Leitura do valor de contagem do timer                       *
 *                                                             *
 * uint8_t unit        -> índice do timer a ser utilizado;     *
 *                                                             *
 * uint16_t -> contagem do timer;                              * 
 ***************************************************************/
uint16_t timerGetCount(uint8_t unit){
	
	return timerUnit[unit].count;
	
}

/***************************************************************
 * timerSetOverflowValue (unit, maxValue);                     *
 *                                                             *
 * Define o valor de overflow do timer                         *   
 *                                                             *
 * uint8_t unit     -> índice do timer a ser utilizado;        *
 * int     maxvalue -> valor de overflow do timer;             *
 *                                                             *
 * void -> não retorna valor;                                  * 
 ***************************************************************/
void timerSetOverflowValue(uint8_t unit, int maxValue){
	
	timerUnit[unit].maxCount = maxValue;
	
}

/***************************************************************
 * timerGetOverflow (unit);                                    *
 *                                                             *
 * Verifica se ocorreu overflow no timer                       *   
 *                                                             *
 * uint8_t unit        -> índice do timer a ser utilizado;     *
 *                                                             *
 * _Bool -> retorna o valor de overflow do timer;              * 
 ***************************************************************/
void timerReset(uint8_t unit){
	
	timerUnit[unit].count    = 0;
	timerUnit[unit].overflow = 0;
	
}

/***************************************************************
 * timerDelay (delay);                                         *
 *                                                             *
 * Função de delay                                             *   
 *                                                             *
 * uint8_t delay -> valor de duração do delay, em ms;          *
 *                                                             *
 * Bool -> retorna true enquanto não houve overflow no timer;  * 
 ***************************************************************/
bool timerDelay(uint16_t delay){
	
	if(timerUnit[0].count == 0){
		
		timerSetOverflowValue(0, delay);
	  timerReset           (0);
	  timerEnable          (0, ENABLE);
		
	}
	
	if(timerGetOverflow(0)){
		
		timerEnable(0, DISABLE);
		timerReset (0);
		
		return TRUE;
		
	}else{
		
		return FALSE;
		
	}
}

/***************************************************************
 * bool timeBase1ms();                                         *
 *                                                             *
 * Verificação de base de tempo de 1ms                         *   
 *                                                             *
 * Bool -> retorna true após um intervalo de 1ms;              * 
 ***************************************************************/
bool timeBase1ms(void){
	
	if(timeBase_1ms){
		
		timeBase_1ms = FALSE;
		
		return TRUE;
		
	}else{
		
		return FALSE;
		
	}
	
}

/***************************************************************
 * bool timeBase1us();                                         *
 *                                                             *
 * Verificação de base de tempo de 1us                         *   
 *                                                             *
 * Bool -> retorna true após um intervalo de 1us;              * 
 ***************************************************************/
bool timeBase1us(void){
	
	if(timeBase_1us){
		
		timeBase_1us = FALSE;
		
		return TRUE;
		
	}else{
		
		return FALSE;
		
	}
	
}


/***************************************************************
  * Interrupção do TIM4 (Timer físico do controlador;          *
***************************************************************/ 
#ifdef STM8S903
/**
  * @brief Timer6 Update/Overflow/Trigger Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM6_UPD_OVF_TRG_IRQHandler, 23)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#else /*STM8S208, STM8S207, STM8S105 or STM8S103 or STM8AF52Ax or STM8AF62Ax or STM8AF626x */
/**
  * @brief Timer4 Update/Overflow Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23)
 	{		
		
		TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
		
		timeBase_1ms = TRUE;
		
		for(i = 0; i < TIMER_QTY; i++){
			
			if(timerUnit[i].enable == 1){
				
				if(timerUnit[i].count >= timerUnit[i].maxCount){
					
					timerUnit[i].overflow = 1;
					
			  }
				
			  timerUnit[i].count++;
				
		  }
	  }
	}

#endif /*STM8S903*/







