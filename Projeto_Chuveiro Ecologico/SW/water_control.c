/***************************************************************
 * Biblioteca de Controle de Água                              *
 ***************************************************************/
 
 /* Autor: Felipe Antonio Montagneri Lucchini
    Data : 26/11/2016
	*/
	
/***************************************************************/

#include "stm8s.h"
#include "stm8s_io.h"
#include "water_control.h"


/***************************************************************
 * Funções e Procedimentos                                     *
 ***************************************************************/
/***************************************************************
 * waterControl(enable);                                       *
 *                                                             *
 * Procedimento de controle de água;                           *
 *                                                             *
 * bool -> recebe true para abrir a válvula;                   *
 *                                                             *
 * void -> não retorna valor;                                  *
 ***************************************************************/
void waterControl(bool enable){
	 
	 if(enable){
		 
		 GPIO_WriteHigh(WATER);
		 
	  }else{
			
		 GPIO_WriteLow(WATER);	
			
		}	 
  }