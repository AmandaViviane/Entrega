/**
 *	20-UART 
 * Prof. Rafael Corsi
 *
 *    (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 */

#include "asf.h"
#include "conf_board.h"
#include "conf_clock.h"



/************************************************************************/
/* Configurações                                                        */
/************************************************************************/

#define STRING_EOL    "\r"
#define STRING_VERSAO "-- "BOARD_NAME" --\r\n" \
					  "-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

#define CONF_UART_BAUDRATE 115200		
#define CONF_UART          CONSOLE_UART

/** 
 * LEDs
 */ 
#define PIN_LED_BLUE	19
#define PORT_LED_BLUE	PIOA
#define ID_LED_BLUE		ID_PIOA
#define ID_LED_GREEN	ID_PIOA
#define ID_LED_RED  	ID_PIOC
#define MASK_LED_BLUE	(1u << PIN_LED_BLUE)
#define MASK_LED_RED	(1u << PIN_LED_RED)
#define MASK_LED_GREEN	(1u << PIN_LED_GREEN)

#define PIN_LED_BLUE	19
#define PIN_LED_RED		20
#define PIN_LED_GREEN	20

#define PORT_LED_BLUE	PIOA
#define PORT_LED_GREEN	PIOA
#define PORT_LED_RED	PIOC

uint8_t byteCount = 0;
uint8_t rx[16];
uint8_t blinkBlue = 0;
uint8_t blinkRed = 0;
uint8_t blinkGreen = 0;


/************************************************************************/
/*                                                                      */
/************************************************************************/
void UART0_Handler(void){
	
	volatile uint32_t ul_dummy;

    /****************************************************************
	* Devemos indicar ao TC que a interrupção foi satisfeita.
    ******************************************************************/
	ul_dummy = usart_get_status(UART0);

	/* Avoid compiler warning */
	UNUSED(ul_dummy);
	
	usart_serial_getchar((Usart *)CONSOLE_UART, &rx[byteCount]);
	
	byteCount++;
	
	if (byteCount == 4)
	{
		byteCount = 0;
	}
}

/************************************************************************/
/* Configura UART                                                       */
/************************************************************************/
void config_uart(void){
	
	/* configura pinos */
	gpio_configure_group(PINS_UART0_PIO, PINS_UART0, PINS_UART0_FLAGS);
	
	/* ativa clock */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	
	/* Configuração UART */
	const usart_serial_options_t uart_serial_options = {
		.baudrate   = CONF_UART_BAUDRATE,
		.paritytype = UART_MR_PAR_NO,
		.stopbits   = 0
	};
	
     stdio_serial_init((Usart *)CONF_UART, &uart_serial_options);
	 usart_enable_interrupt(UART0, US_IER_RXRDY);
     NVIC_EnableIRQ((IRQn_Type)UART0_IRQn);
}


/************************************************************************/
/* Display Menu                                                         */
/************************************************************************/
static void display_menu(void)
{
	puts("Online");
}


static void configure_tc(uint16_t frequency)
{
	/*
	* Aqui atualizamos o clock da cpu que foi configurado em sysclk init
	*
	* O valor atual est'a em : 120_000_000 Hz (120Mhz)
	*/
	uint32_t ul_sysclk = sysclk_get_cpu_hz();
	
	/****************************************************************
	* Ativa o clock do periférico TC 0
	*****************************************************************
	* 
    * Parametros : 
    *  1 - ID do periferico
    * 
	*
	*****************************************************************/
	pmc_enable_periph_clk(ID_TC0);

	/*****************************************************************
	* Configura TC para operar no modo de comparação e trigger RC
	*****************************************************************
    *
	* Configura TC para operar no modo de comparação e trigger RC
	* devemos nos preocupar com o clock em que o TC irá operar !
	*
	* Cada TC possui 3 canais, escolher um para utilizar.
	*
    * No nosso caso :
    * 
	*	MCK		= 120_000_000
	*	SLCK	= 32_768		(rtc)
	*
	* Uma opção para achar o valor do divisor é utilizar a funcao, como ela
    * funciona ?
	* tc_find_mck_divisor()
	*
    *
    * Parametros
    *   1 - TC a ser configurado (TC0,TC1, ...)
    *   2 - Canal a ser configurado (0,1,2)
    *   3 - Configurações do TC :
    *
    * 
  Configurações de modo de operação :
	*	    TC_CMR_ABETRG  : TIOA or TIOB External Trigger Selection 
	*	    TC_CMR_CPCTRG  : RC Compare Trigger Enable 
	*	    TC_CMR_WAVE    : Waveform Mode 
	*
	*     Configurações de clock :
	*	    TC_CMR_TCCLKS_TIMER_CLOCK1 : Clock selected: internal MCK/2 clock signal 
	*	    TC_CMR_TCCLKS_TIMER_CLOCK2 : Clock selected: internal MCK/8 clock signal 
	*	    TC_CMR_TCCLKS_TIMER_CLOCK3 : Clock selected: internal MCK/32 clock signal 
	*	    TC_CMR_TCCLKS_TIMER_CLOCK4 : Clock selected: internal MCK/128 clock signal
	*	    TC_CMR_TCCLKS_TIMER_CLOCK5 : Clock selected: internal SLCK clock signal 
	*
	*****************************************************************/
	tc_init(TC0, 0, TC_CMR_CPCTRG | TC_CMR_TCCLKS_TIMER_CLOCK5);
    
    /*****************************************************************
	* Configura valor trigger RC
    *****************************************************************
	*
	* Aqui devemos configurar o valor do RC que vai trigar o reinicio da contagem
	* devemos levar em conta a frequência que queremos que o TC gere as interrupções
	* e tambem a frequencia com que o TC está operando.
	*
	* Devemos configurar o RC para o mesmo canal escolhido anteriormente.
	*	
	*   ^ 
	*	|	Contador (incrementado na frequencia escolhida do clock)
	*   |
	*	|	 	Interrupcao	
	*	|------#----------- RC
	*	|	  /
	*	|   /
	*	| /
	*	|-----------------> t
	*
    * Parametros :
    *   1 - TC a ser configurado (TC0,TC1, ...)
    *   2 - Canal a ser configurado (0,1,2)
    *   3 - Valor para trigger do contador (RC)
    *****************************************************************/
   
   frequency = 32768/frequency;
   
    tc_write_rc(TC0, 0, frequency);
	
	/*****************************************************************
	* Configura interrupção no TC
    *****************************************************************
    * Parametros :
    *   1 - TC a ser configurado
    *   2 - Canal
    *   3 - Configurações das interrupções 
	* 
	*        Essas configurações estão definidas no head : tc.h 
	*
	*	        TC_IER_COVFS : 	Counter Overflow 
	*	        TC_IER_LOVRS : 	Load Overrun 
	*	        TC_IER_CPAS  : 	RA Compare 
	*	        TC_IER_CPBS  : 	RB Compare 
	*	        TC_IER_CPCS  : 	RC Compare 
	*	        TC_IER_LDRAS : 	RA Loading 
	*	        TC_IER_LDRBS : 	RB Loading 
	*	        TC_IER_ETRGS : 	External Trigger 
	*****************************************************************/
	tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
    
    /*****************************************************************
	* Ativar interrupção no NVIC
    *****************************************************************
    *
    * Devemos configurar o NVIC para receber interrupções do TC 
    *
    * Parametros :
    *   1 - ID do periférico
	*****************************************************************/
	NVIC_SetPriority(TC0_IRQn,0);
	NVIC_EnableIRQ(TC0_IRQn);
    
    /*****************************************************************
	* Inicializa o timer
    *****************************************************************
    *
    * Parametros :
    *   1 - TC
    *   2 - Canal
	*****************************************************************/
    tc_start(TC0, 0);
	
}

void TC0_Handler(void)
{
	volatile uint32_t ul_dummy;

    /****************************************************************
	* Devemos indicar ao TC que a interrupção foi satisfeita.
    ******************************************************************/
	ul_dummy = tc_get_status(TC0, 0);

	/* Avoid compiler warning */
	UNUSED(ul_dummy);

	/** Muda o estado do LED */
	
	if(blinkBlue){
	if (PORT_LED_BLUE->PIO_ODSR & MASK_LED_BLUE) {
		/* Value to be driven on the I/O line: 0. */
		pio_clear(PORT_LED_BLUE, MASK_LED_BLUE);
		} else {
		/* Value to be driven on the I/O line: 1. */
		pio_set(PORT_LED_BLUE, MASK_LED_BLUE);
	}
	}
	
	if(blinkGreen){
		if (PORT_LED_GREEN->PIO_ODSR & MASK_LED_GREEN) {
			/* Value to be driven on the I/O line: 0. */
			pio_clear(PORT_LED_GREEN, MASK_LED_GREEN);
			} else {
			/* Value to be driven on the I/O line: 1. */
			pio_set(PORT_LED_GREEN, MASK_LED_GREEN);
		}
	}
	
	if(blinkRed){
		if (PORT_LED_RED->PIO_ODSR & MASK_LED_RED) {
			/* Value to be driven on the I/O line: 0. */
			pio_clear(PORT_LED_RED, MASK_LED_RED);
			} else {
			/* Value to be driven on the I/O line: 1. */
			pio_set(PORT_LED_RED, MASK_LED_RED);
		}
	}
}


/************************************************************************/
/* Main                                                                 */
/************************************************************************/
int main(void)
{
	uint8_t uc_key;

	/* Initialize the system */
	sysclk_init();
	board_init();

	/* Configure LED 1 */
	pmc_enable_periph_clk(ID_LED_BLUE);
	pmc_enable_periph_clk(ID_LED_RED);
	pmc_enable_periph_clk(ID_LED_GREEN);
	pio_set_output(PORT_LED_BLUE  , MASK_LED_BLUE	,1,0,0);
	pio_set_output(PORT_LED_GREEN , MASK_LED_GREEN  ,1,0,0);
	pio_set_output(PORT_LED_RED	  , MASK_LED_RED	,1,0,0);

	/* Initialize debug console */
	config_uart();
	
	/* Config tc */
    configure_tc(1);
	
	/* frase de boas vindas */
	/*puts(" ---------------------------- \n\r"
	 	 " Bem vindo terraquio !		\n\r"
		 " ---------------------------- \n\r");*/
		 
	/* display main menu */
	display_menu();
	
	

	while (1) {
		
		switch(rx[0]){
			
			case '0':
			pio_set(PORT_LED_BLUE, MASK_LED_BLUE);
			blinkBlue = 0;
			break;
			case '1':
			pio_clear(PORT_LED_BLUE, MASK_LED_BLUE);
			blinkBlue = 0;
			break;
			case '2':
			blinkBlue = 1;
			break;			
		}
		switch(rx[1]){
			
			case '0':
			pio_set(PORT_LED_GREEN, MASK_LED_GREEN);
			blinkGreen = 0;
			break;
			case '1':
			pio_clear(PORT_LED_GREEN, MASK_LED_GREEN);
			blinkGreen = 0;
			break;
			case '2':
			blinkGreen = 1;
			break;			
		}
		switch(rx[2]){
			
			case '0':
			pio_clear(PORT_LED_RED, MASK_LED_RED);	
			blinkRed = 0;		
			break;
			case '1':
			pio_set(PORT_LED_RED, MASK_LED_RED);
			blinkRed = 0;
			break;
			case '2':
			blinkRed = 1;
			break;			
		} 
		switch(rx[3]){
			
			case '1':
			tc_write_rc(TC0, 0, 32768);		
			break;
			case '2':
			tc_write_rc(TC0, 0, 32768/2);		
			break;
			case '3':
			tc_write_rc(TC0, 0, 32768/3);		
			break;
			case '4':
			tc_write_rc(TC0, 0, 32768/4);		
			break;
			case '5':
			tc_write_rc(TC0, 0, 32768/5);		
			break;
			case '6':
			tc_write_rc(TC0, 0, 32768/6);		
			break;
			case '7':
			tc_write_rc(TC0, 0, 32768/7);		
			break;
			case '8':
			tc_write_rc(TC0, 0, 32768/8);		
			break;		
			case '9':
			tc_write_rc(TC0, 0, 32768/9);		
			break;		
					
			
					
					
		}
		
				
	}
}