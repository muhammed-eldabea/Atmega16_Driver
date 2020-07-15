/*
 * 		[file name]   : spi.h
 *  	[Created on]  : Jul 7, 2020
 *      [Author]      : Muhammed Eldabea Hashem
 *      [Description] : Function declarations and configuration used
 *
 */




/* =================================================================== *
      ------------------------>includes<----------------------------
 * =================================================================== */
#include "spi.h"


/* =================================================================== *
       -------------------->Global Variable<--------------------------
 * =================================================================== */

volatile void(*G_SPI_ptr)(void) ; /*global pointer to a void function*/

/* ==================================================================== *
      	  	  	 ----------------->ISR<--------------------
 * ==================================================================== */
#if SPI_Enable_inteerupt ==1
ISR(SPI_STC_vect)
{
	(*G_SPI_ptr)() ;
}
#endif


/* ==================================================================== *
      ----------------->Functions Definitions<--------------------
 * ==================================================================== */
void SPI_init(SPI_configuration *ptr )
{

	/*----------------------------------------------------------------
	[FUNCTION NAME] : SPI_initt
	[DESRIPTION] : used to initialize a SPI module by a given configuration
	[ARGUMENT(S)]  :
	   [IN]  : a pointer to a structure that have the configuration
	    	   these configuration are :
	    		>>SPI_operationMode>>CLk_polarity>>CLK_phase>>pre_scaler
	   [OUT] : void
	[Return]      : void

	---------------------------------------------------------------------*/
#if SPI_Enable_inteerupt ==1
	SREG |=(1<<7) ; /*Global interrupt*/
	SPCR |=(1<<7) ; /*enable the SPI interrupt*/
#endif

#if SPI_LSB_DataOrder ==1
	SPCR |=(1<<5) ; /*LSB data order*/
#endif

	/*master / slave configuration*/
	SPCR = (SPCR & 0xEF) | ((ptr->SPI_MAsterSlaveSelect & 0x01)<<4) ;
	/*Clock polarity configuration */
	SPCR = (SPCR & 0xF7) | ((ptr->SPI_ClockPolarity     & 0x01)<<3) ;
	/*clock phase configuration */
	SPCR = (SPCR & 0xFB) | ((ptr->SPI_ClockPolarity     & 0x01)<<2) ;
	/*clock pre-scaler*/
	SPCR = (SPCR & 0xFC) | ((ptr->SPI_ClockPhase        & 0x03)<<0) ;
	/*double speed configuration */
	SPSR = (SPSR & 0xFE) | (ptr->SPI_preScaler          & 0x04 )    ;
	if(ptr->SPI_MAsterSlaveSelect ==SPI_Master_select){
		/*configure pin for master operation*/
		DDRB = DDRB | (1<<PB4);
		DDRB = DDRB | (1<<PB5);
		DDRB = DDRB & ~(1<<PB6);
		DDRB = DDRB | (1<<PB7);
	}
	else {
		/*Configure DIO for slave operation*/
		DDRB = DDRB & (~(1<<PB4));
		DDRB = DDRB & (~(1<<PB5));
		DDRB = DDRB | (1<<PB6);
		DDRB = DDRB & (~(1<<PB7));

	}

	SPCR = (1<<6); /*set the SPI enable bit */
}

void SPI_SENDDATA(unsigned char Data)
{
	/*----------------------------------------------------------------
	[FUNCTION NAME] : SPI_initt
	[DESRIPTION] : used to send a data using SPI
	[ARGUMENT(S)]  :
	   [IN]  : a 8-bit data size
	   [OUT] : void
	[Return] : void

	---------------------------------------------------------------------*/
SPDR = Data ;
/*wait until SPIF is set */
while (!(SPSR &(1<<7))){}

}

unsigned char SPI_GETDATA(void)
{
	/*----------------------------------------------------------------
	[FUNCTION NAME] : SPI_GETDATA
	[DESRIPTION] : used to get a data using SPI
	[ARGUMENT(S)]  :
	   [IN]  : void
	   [OUT] : a 8-bit data size
	[Return] : return the data that jas beens send using SPI

	---------------------------------------------------------------------*/

/*wait until SPIF is set */
while (!(SPSR &(1<<7))){}

return SPDR ;



}





void SPI_callback(void(*ptr(void)))
{
	/*
	 *  used to call a function in ISR of the SPi interrupt
	 * */

	G_SPI_ptr = ptr ;


}
