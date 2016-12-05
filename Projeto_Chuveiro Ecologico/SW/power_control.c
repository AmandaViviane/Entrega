/***************************************************************
 * Biblioteca de Controle de Potência                          *
 ***************************************************************/
 
 /* Autor: Felipe Antonio Montagneri Lucchini
    Data : 05/04/2016
	*/
	
/***************************************************************/

#include "stm8s.h"
#include "stm8s_io.h"
#include "stm8s_counter.h"
#include "power_control.h"

uint8_t powerRate = 1;

/***************************************************************
 * Funções e Procedimentos                                     *
 ***************************************************************/
/***************************************************************
 * powerControl(rate);                                         *
 *                                                             *
 * Procedimento de controle de Potência;                       *
 *                                                             *
 * uint8_t -> quantidade de cliclos ativos;                    *
 *                                                             *
 * void -> não retorna valor;                                  *
 ***************************************************************/
void powerControl(uint16_t rate){
	 
	 if(rate < 500){ // 10%
		 
		 powerRate = 1;
		 
		 setMaxCount(20);
		 
	  }
		
	 if((rate > 500)&&(rate < 1000)){ // 20%
		 
		 powerRate = 6;
		 
		 setMaxCount(20);
		 
	  }
	 
	 if((rate > 1000)&&(rate < 1500)){ // 30%
		 
		 powerRate = 9;
		 
		 setMaxCount(20);
		 
	  }
		
	 if((rate > 1500)&&(rate < 2000)){ // 40%
		 
		 powerRate = 11;
		 
		 setMaxCount(20);
		 
	  }
		
	 if((rate > 2000)&&(rate < 2500)){ // 50%
		 
		 powerRate = 13;
		 
		 setMaxCount(20);
		 
	  }
		
	 if((rate > 2500)&&(rate < 3000)){ // 60%
		 
		 powerRate = 14;
		 
		 setMaxCount(20);
		 
	  }
		
	 if((rate > 3000)&&(rate < 3500)){ // 70%
		 
		 powerRate = 16;
		 
		 setMaxCount(20);
		 
	  }
		
	 if((rate > 3500)&&(rate < 4000)){ // 80%
		 
		 powerRate = 18;
		 
		 setMaxCount(20);
		 
	  }
		
	 if((rate > 4000)&&(rate < 4500)){ // 90%
		 
		 powerRate = 19;
		 
		 setMaxCount(20);
		 
	  }
		
	 if(rate > 4500){ // 100%
		 
		 powerRate = 20;
		 
		 setMaxCount(20);
		 
	  }
	 
	 if(counterGetValue() <= powerRate){
		 
		 GPIO_WriteLow(POWER_CONTROL);
		 
		 counterEnable();
		 
	  }else{
			
		 GPIO_WriteHigh(POWER_CONTROL);
			
		}
	 
	}
	
/***************************************************************
 * powerOff();                                                 *
 *                                                             *
 * Procedimento de corte de energia;                           *
 *                                                             *
 * void -> não recebe parâmetros;                              *
 *                                                             *
 * void -> não retorna valor;                                  *
 ***************************************************************/
void powerOff(void){
  	
	 GPIO_WriteHigh(POWER_CONTROL);	
		
  }
 

