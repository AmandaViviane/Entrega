/***************************************************************
 * Biblioteca de Aquisi��o Anal�gica                           *
 ***************************************************************/
 
 /* Autor: Felipe Antonio Montagneri Lucchini
    Data : 30/03/2016
	*/
	
#define DATA_UNAVAILABLE  0
#define DATA_AVAILABLE    1

#define SAMPLE_QTY        5 
#define CHANNEL_QTY       1

#define NOISE_REJECTION 500 
	
/***************************************************************
 * Fun��es e Procedimentos                                     *                            
 ***************************************************************/ 
	
/***************************************************************
 * analogSetBuffer(&buffer_addr);                              *
 *                                                             *
 * Fun��o para sele��o do endere�o do buffer de leitura;       *
 *                                                             *
 * uint16_t *buffer_addr -> endere�o para o buffer             *  
 *                                                             * 
 * void -> n�o retorna valor;                                  *
 ***************************************************************/
void analogSetBuffer(uint16_t * buffer_addr);
	
/***************************************************************
 * analogDataAvailable():                                      *
 *                                                             *
 * Verifica se a lista de valores do ADC foi preenchida        *
 *                                                             *
 * bool -> retorna true se a lista est� completa, retorna      *
 *         se a lista ainda estiver sendo preenchida           * 
 *                                                             *
 ***************************************************************/
  bool analogDataAvailable(void);
	
/***************************************************************
 * analogRun(channel)                                          *
 *                                                             *
 * Realiza s�rie de medi��es para atualiza��o do valor do ADC  *
 *                                                             * 
 * void -> n�o retorna valor                                   *
 ***************************************************************/ 
 void analogRun(void);
	

	
