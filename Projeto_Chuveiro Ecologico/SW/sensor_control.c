/***************************************************************
 * Biblioteca de Leitura do Sensor de Movimento                *
 ***************************************************************/
 
 /* Autor: Felipe Antonio Montagneri Lucchini
    Data : 26/11/2016
	*/
	
/***************************************************************/

#include "stm8s.h"
#include "stm8s_io.h"
#include "stm8s_timer.h"
#include "sensor.h"

uint8_t sensor_state  = SENSOR_IDLE;

uint8_t sensor_status = FALSE;
uint8_t presence      = FALSE;

/***************************************************************
 * Funções e Procedimentos                                     *
 ***************************************************************/
/***************************************************************
 * sensorControl();                                            *
 *                                                             *
 * Procedimento de controle do Sensor de Movimento;            *
 *                                                             *
 * void -> não recebe parâmetros;                              *
 *                                                             *
 * void -> não retorna valor;                                  *
 ***************************************************************/
void sensorControl(void){
	 
	 switch (sensor_state){
		 
		 case SENSOR_IDLE:
		 
		 if(sensor_status){
			 
			 presence = TRUE;
			 
			 sensor_state = SENSOR_READING;
			 
		  }
		  
		 break;
		 
		 case SENSOR_READING:
		 
		 if(timerDelay(TIME_BASE_20S)){
			 
			 if(!sensor_status){
				 
				 presence = FALSE;
				 
				 sensor_state = SENSOR_IDLE;
				 
			  }
			 
		  }
		 
		 break;
		 
	  }  
	}
	
/***************************************************************
 * sensorRead();                                               *
 *                                                             *
 * Procedimento de leitura do status do sensor;                *
 *                                                             *
 * void -> não recebe parâmetros;                              *
 *                                                             *
 * void -> não retorna valor;                                  *
 ***************************************************************/
void sensorRead(void){
	
 if(GPIO_ReadInputPin(SENSOR) == 1){
		
	 sensor_status = TRUE;	
		
	}else{
   
	 sensor_status = FALSE;
	  
  }
}

/***************************************************************
 * sensorGetStatus();                                          *
 *                                                             *
 * Procedimento de leitura do status do sensor;                *
 *                                                             *
 * void -> não recebe parâmetros;                              *
 *                                                             *
 * bool -> retorna true se foi detectado movimento;            *
 ***************************************************************/
bool sensorGetStatus(void){
	 
	 return presence;
	 
  }
