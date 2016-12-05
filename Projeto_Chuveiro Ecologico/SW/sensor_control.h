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
void sensorControl(void);
	
/***************************************************************
 * sensorRead();                                               *
 *                                                             *
 * Procedimento de leitura do status do sensor;                *
 *                                                             *
 * void -> não recebe parâmetros;                              *
 *                                                             *
 * void -> não retorna valor;                                  *
 ***************************************************************/
void sensorRead(void);

/***************************************************************
 * sensorGetStatus();                                          *
 *                                                             *
 * Procedimento de leitura do status do sensor;                *
 *                                                             *
 * void -> não recebe parâmetros;                              *
 *                                                             *
 * _bool -> retorna true se foi detectado movimento;           *
 ***************************************************************/
bool sensorGetStatus(void);

/***************************************************************/