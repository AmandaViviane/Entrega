/***************************************************************
 * Biblioteca de Aquisição Analógica                           *
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
 * Funções e Procedimentos                                     *                            
 ***************************************************************/ 
	
/***************************************************************
 * analogSetBuffer(&buffer_addr);                              *
 *                                                             *
 * Função para seleção do endereço do buffer de leitura;       *
 *                                                             *
 * uint16_t *buffer_addr -> endereço para o buffer             *  
 *                                                             * 
 * void -> não retorna valor;                                  *
 ***************************************************************/
void analogSetBuffer(uint16_t * buffer_addr);
	
/***************************************************************
 * analogDataAvailable():                                      *
 *                                                             *
 * Verifica se a lista de valores do ADC foi preenchida        *
 *                                                             *
 * bool -> retorna true se a lista está completa, retorna      *
 *         se a lista ainda estiver sendo preenchida           * 
 *                                                             *
 ***************************************************************/
  bool analogDataAvailable(void);
	
/***************************************************************
 * analogRun(channel)                                          *
 *                                                             *
 * Realiza série de medições para atualização do valor do ADC  *
 *                                                             * 
 * void -> não retorna valor                                   *
 ***************************************************************/ 
 void analogRun(void);
	

	
