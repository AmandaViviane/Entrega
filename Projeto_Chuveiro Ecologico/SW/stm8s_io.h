/***************************************************************
 * Biblioteca de Contagem                                      *
 ***************************************************************/
 
 /* Autor: Felipe Antonio Montagneri Lucchini
    Data : 05/04/2016
	*/
	
/***************************************************************/

#include "stm8s.h"

#define ZERO_CROSSING GPIOC, GPIO_PIN_2
#define POWER_CONTROL GPIOD, GPIO_PIN_0
#define BUZZER        GPIOC, GPIO_PIN_6
#define SENSOR        GPIOD, GPIO_PIN_5
#define WATER         GPIOC, GPIO_PIN_7


/***************************************************************
 * Funções e Procedimentos                                     *                            
 ***************************************************************/
/***************************************************************
 * void ioInit(void);                                          *
 *                                                             * 
 * Inicialização dos IO's                                      *       
 *                                                             * 
 ***************************************************************/
 void ioInit(void);
/***************************************************************/