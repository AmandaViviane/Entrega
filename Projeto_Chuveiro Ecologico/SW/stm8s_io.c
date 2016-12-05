/***************************************************************
 * Biblioteca de Contagem                                      *
 ***************************************************************/
 
 /* Autor: Felipe Antonio Montagneri Lucchini
    Data : 05/04/2016
	*/
	
/***************************************************************/

#include "stm8s.h"
#include "stm8s_io.h"


/***************************************************************
 * Funções e Procedimentos                                     *                            
 ***************************************************************/
/***************************************************************
 * void ioInit(void);                                          *
 *                                                             * 
 * Inicialização dos IO's                                      *       
 *                                                             * 
 ***************************************************************/
 void ioInit(void){ 
	 
// GPIO_Init(ZERO_CROSSING, GPIO_MODE_IN_FL_NO_IT);
   GPIO_Init(SENSOR,        GPIO_MODE_IN_FL_NO_IT);
	 GPIO_Init(POWER_CONTROL, GPIO_MODE_OUT_OD_LOW_SLOW);
	 GPIO_Init(BUZZER,        GPIO_MODE_OUT_PP_LOW_SLOW);
	 GPIO_Init(WATER,         GPIO_MODE_OUT_PP_LOW_SLOW);
	 
	}
