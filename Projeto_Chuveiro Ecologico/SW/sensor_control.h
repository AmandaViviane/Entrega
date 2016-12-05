/***************************************************************
 * Biblioteca de Leitura do Sensor de Movimento                *
 ***************************************************************/
 
 /* Autor: Felipe Antonio Montagneri Lucchini
    Data : 26/11/2016
	*/
	
/***************************************************************/

#include "stm8s.h"

enum sensor{
	 
	 SENSOR_IDLE,
	 SENSOR_READING   	
	 
  };

/***************************************************************
 * Fun��es e Procedimentos                                     *
 ***************************************************************/
/***************************************************************
 * sensorControl();                                            *
 *                                                             *
 * Procedimento de controle do Sensor de Movimento;            *
 *                                                             *
 * void -> n�o recebe par�metros;                              *
 *                                                             *
 * void -> n�o retorna valor;                                  *
 ***************************************************************/
void sensorControl(void);
	
/***************************************************************
 * sensorRead();                                               *
 *                                                             *
 * Procedimento de leitura do status do sensor;                *
 *                                                             *
 * void -> n�o recebe par�metros;                              *
 *                                                             *
 * void -> n�o retorna valor;                                  *
 ***************************************************************/
void sensorRead(void);

/***************************************************************
 * sensorGetStatus();                                          *
 *                                                             *
 * Procedimento de leitura do status do sensor;                *
 *                                                             *
 * void -> n�o recebe par�metros;                              *
 *                                                             *
 * _bool -> retorna true se foi detectado movimento;           *
 ***************************************************************/
bool sensorGetStatus(void);

/***************************************************************/