/*
 * 		[file name]   : twi.c
 *  	[Created on]  : Jul 15, 2020
 *      [Author]      : Muhammed Eldabea Hashem
 *      [Description] : Function defination used
 *
 */



/* =================================================================== *
      ------------------------> includes <----------------------------
 * =================================================================== */

#include "twi.h"


/* =================================================================== *
       --------------------> Global Variable <--------------------------
 * =================================================================== */
/*a global pointer pointer to function with a void input
 * and return a void
 * */
volatile void (*G_ptrtofunc)(void) =(void*)0 ;


/* ==================================================================== *
      	  	  	 -----------------> ISR <--------------------
 * ==================================================================== */

#if TWI_Interrupt_Enable ==1
ISR(TWI_vect)
{
	if(G_ptrtofunc != (void*)0)
	{
	(*G_ptrtofunc)() ;
	}
}

#endif


/* ==================================================================== *
      	-----------------> Functions Definitions <--------------------
 * ==================================================================== */


void TWI_init(TWI_Configuration *ptr)
{
	/*-----------------------------------------------------------------
	[FUNCTION NAME]  : TWI_init
	[DESRIPTION]   	 : used to initialize the TWI(I2C) module be
						handling some configuration
						like address , bit rate and pre-scaler values

	[ARGUMENT(S)]  	 :
	   [IN] : a pointer to configuration structure that have a three values
	   	   	   	1-> a 8-bit Bit-rate value
	   	   	   	2-> a 8-bit Pre-scaler value
	   	   	   	3-> a 8-bit Address value
	   [OUT] : VOID
	[Return]      : void
	---------------------------------------------------------------------*/

	/*the bit rate value */
TWBR = ptr->TWI_BitRate_value ;

#if TWI_Interrupt_Enable ==1
SREG |=(1<<7) ; /*Global interrupt */
TWCR |=(1<<0) ; /*enable the interrupt bit */
#endif

#if TWI_ General_Call_Recognition  ==1
TWAR |=(1<<0) ; /*TWI_ General_Call_Recognition */
#endif

/*address of the device */
TWAR = (TWAR & 0xFE) | ((ptr->TWI_AddressRegister & 0x7F)<<1) ;

/*pre-scaler value*/
TWSR = (TWSR & 0xfC) | (ptr->TWI_PreScaler & 0x03) ;

/*set the enable bit*/
TWCR |=(1<<2) ;

}


void TWI_start(void)
{
    /*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void)
{
    /*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_write(unsigned char  data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

unsigned char  TWI_readWithACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

unsigned char TWI_readWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

unsigned char TWI_getStatus(void)
{
	unsigned char status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}

