/***************************************************************
 * Biblioteca de Temporiza��o                                  *
 ***************************************************************/
 
 /* Autor: Felipe Antonio Montagneri Lucchini
    Data : 25/09/2015
	*/
	
/***************************************************************
 * Defini��o das contantes de tempo (base de tempo de 0,1ms):  *
 ***************************************************************/

#define TIME_BASE_1MS           1
#define TIME_BASE_100MS       100
#define TIME_BASE_200MS       200
#define TIME_BASE_250MS       250
#define TIME_BASE_500MS       500
#define TIME_BASE_800MS       800
#define TIME_BASE_1S         1000
#define TIME_BASE_2S         2000
#define TIME_BASE_3S         3000
#define TIME_BASE_4S         4000
#define TIME_BASE_5S         5000
#define TIME_BASE_10S       10000
#define TIME_BASE_20S       20000
#define TIME_BASE_DEBOUCING   100

#define TIMER_QTY 6


/***************************************************************
 * Estrutura do Timer:                                         *
 *                                                             * 
 * count    (inteiro)  - valor de contagem da bse de tempo;    *
 * maxCount (inteiro)  - valor de overflow;                    * 
 * enable   (booleano) - flag  de opera��o do timer;           *
 * overflow (booleano) - flag  de overflow do timer;           *                                                         
 ***************************************************************/

typedef struct{
	
	 uint16_t count;
	 uint16_t maxCount;
	 bool     enable;
	 bool     overflow;

} timer; 

/***************************************************************
 * Fun��es e Procedimentos                                     *                            
 ***************************************************************/ 
/***************************************************************
 * void timerInit(void);                                       *
 *                                                             * 
 * void -> n�o retorna valor                                   *
 ***************************************************************/
void timerInit(void);

 /***************************************************************
  * timerEnable (unit, enableCount);                            *
	*                                                             *
  * Controle de habilita��o do timer                            *   
  *                                                             *
	* uint8_t unit        -> �ndice do timer a ser utilizado;     *
  * _Bool   enableCount	-> valor de hab/inib do timer;          *
	*                                                             *
	* void -> n�o retorna valor;                                  * 
  ***************************************************************/
void timerEnable(uint8_t unit, _Bool enableCount);

 /***************************************************************
  * timerReset (unit);                                          *   
	*                                                             *
	* Reset do valor de contagem do timer                         *
  *                                                             *
	* uint8_t unit        -> �ndice do timer a ser utilizado;     *
	*                                                             *
	* void -> n�o retorna valor;                                  * 
  ***************************************************************/
void timerReset(uint8_t unit);

 /***************************************************************
  * timerSetOverflowValue (unit, maxValue);                     *
	*                                                             *
  * Define o valor de overflow do timer                         *   
  *                                                             *
	* uint8_t unit     -> �ndice do timer a ser utilizado;        *
  * int     maxvalue -> valor de overflow do timer;             *
	*                                                             *
	* void -> n�o retorna valor;                                  * 
  ***************************************************************/
void timerSetOverflowValue(uint8_t unit, int maxValue);
 
/***************************************************************
 * timerGetOverflow (unit);                                    *
 *                                                             *
 * Verifica se ocorreu overflow no timer                       *   
 *                                                             *
 * uint8_t unit        -> �ndice do timer a ser utilizado;     *
 *                                                             *
 * _Bool -> retorna o valor de overflow do timer;              * 
  ***************************************************************/ 
bool timerGetOverflow(uint8_t unit);

/***************************************************************
 * timerGetCount (unit);                                       *   
 *                                                             *
 * Leitura do valor de contagem do timer                       *
 *                                                             *
 * uint8_t unit        -> �ndice do timer a ser utilizado;     *
 *                                                             *
 * uint16_t -> contagem do timer;                              * 
 ***************************************************************/
uint16_t timerGetCount(uint8_t unit);

/***************************************************************
 * timerDelay (delay);                                         *
 *                                                             *
 * Fun��o de delay                                             *   
 *                                                             *
 * uint8_t delay -> valor de dura��o do delay, em ms;          *
 *                                                             *
 * Bool -> retorna true enquanto n�o houve overflow no timer;  * 
 ***************************************************************/
bool timerDelay(uint16_t delay);

/***************************************************************
 * bool timeBase1ms();                                         *
 *                                                             *
 * Verifica��o de base de tempo de 1ms                         *   
 *                                                             *
 * Bool -> retorna true ap�s um intervalo de 1ms;              * 
 ***************************************************************/
bool timeBase1ms(void);

/***************************************************************
 * bool timeBase1us();                                         *
 *                                                             *
 * Verifica��o de base de tempo de 1us                         *   
 *                                                             *
 * Bool -> retorna true ap�s um intervalo de 1us;              * 
 ***************************************************************/
bool timeBase1us(void);

/***************************************************************/
