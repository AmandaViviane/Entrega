/***************************************************************
 * Biblioteca de Controle de �gua                              *
 ***************************************************************/
 
 /* Autor: Felipe Antonio Montagneri Lucchini
    Data : 26/11/2016
	*/
	
/***************************************************************/

#include "stm8s.h"
#include "stm8s_io.h"
#include "water_control.h"


/***************************************************************
 * Fun��es e Procedimentos                                     *
 ***************************************************************/
/***************************************************************
 * waterControl(enable);                                       *
 *                                                             *
 * Procedimento de controle de �gua;                           *
 *                                                             *
 * bool -> recebe true para abrir a v�lvula;                   *
 *                                                             *
 * void -> n�o retorna valor;                                  *
 ***************************************************************/
void waterControl(bool enable){
	 
	 if(enable){
		 
		 GPIO_WriteHigh(WATER);
		 
	  }else{
			
		 GPIO_WriteLow(WATER);	
			
		}	 
  }