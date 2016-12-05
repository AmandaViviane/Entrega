/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_io.h"
#include "stm8s_timer.h"
#include "stm8s_analog.h"
#include "stm8s_counter.h"

#include "sensor_control.h"
#include "water_control.h"
#include "power_control.h"


#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t control = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public  functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void){
	  
	 CLK->CKDIVR = 0;
	 
	 enableInterrupts();
	 
	 ioInit     ();	
   timerInit  ();
   counterInit();	 
	 
	 
	 analogSetBuffer(&control);		 
	  
   while (1){
		 
		 if(sensorGetStatus()){
			 
			 powerControl(control);	
			 waterControl(ENABLE);
			 
		  }else{
				
			 powerOff();	
			 
			 waterControl(DISABLE);
				
			}		 
		  
		 sensorControl();
		  
	   if(timeBase1ms()){
			 
			 sensorRead();
			 
			 analogRun();
		   
	    }	    
	  }  
  }