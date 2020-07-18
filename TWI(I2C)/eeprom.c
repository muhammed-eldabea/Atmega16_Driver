/*
 * 		[file name]   : eeprom.h
 *  	[Created on]  : Jul 15, 2020
 *      [Author]      : Muhammed Eldabea Hashem
 *      [Description] : Function declarations and configuration used
 *
 */


/* =================================================================== *
      ------------------------>includes<----------------------------
 * =================================================================== */

#include "eeprom.h"

/* =================================================================== *
       -------------------->Global Variable<--------------------------
 * =================================================================== */



/* ==================================================================== *
      	  	  	 ----------------->ISR<--------------------
 * ==================================================================== */




/* ==================================================================== *
      ----------------->Functions Definitions<--------------------
 * ==================================================================== */


void EEPROM_init(TWI_Configuration * ptr)
{

	/*----------------------------------------------------------------
	[FUNCTION NAME] : EEPROM_init
	[DESRIPTION]    : initialize the EEPROM by initialize
					  the TWI module itself
	[ARGUMENT(S)]  :
	   	   	   	   [IN]  : a pointer to TWI_configuration
	   	   	   	   	   	   	 structure and pass it to the
	    					 TWI_init() function
	   	   	   	   [OUT] : void
	[Return]      : void

	------------------------------------------------------------------*/


	TWI_init(ptr) ;
}

unsigned char EEPROM_WriteData(unsigned short Addresse,unsigned char DATA)
{

	/*-------------------------------------------------------------
	[FUNCTION NAME] : EEPROM_WriteData
	[DESRIPTION]    : write the data to EEPROM
	[ARGUMENT(S)]  :
	   	   	   	   [IN]  : 1-> 16-bit Address
	   	   	   	   	   	   2->  8-bit Data
	   	   	   	   [OUT] : a flag represent the error
	[Return]      : void

	---------------------------------------------------------------*/

	/*start the sending operation*/
	TWI_start() ;
	if (TWI_getStatus() != TW_START)
		return ERROR;
	/*
	 * EEPROM address is consist of  11-bit size(A0 to A10)
	 *  Device ID is 0b1010
	 *  we will divide the address into to part
	 *  first part :
	 *  	(0b1010)>>A10>>A9>>A8>>(R/W)
	 *  Second part is
	 * 		From A7 to A0
	 * */

	TWI_write((unsigned char )((0xA0) | ((Addresse & 0x0700)>>7))) ;
	if (TWI_getStatus() != TW_MT_SLA_W_ACK)
		return ERROR ;

	TWI_write((unsigned char )Addresse) ;
	if(TWI_getStatus() != TW_MT_DATA_ACK)
		return ERROR ;

	TWI_write(DATA) ;
	if(TWI_getStatus() != TW_MT_DATA_ACK)
		return ERROR ;

	TWI_stop() ;


}

unsigned char EPPROM_ReadData(unsigned short Address,unsigned char * DATA)
{


	/*-------------------------------------------------------------
	[FUNCTION NAME] : EEPROM_ReadData
	[DESRIPTION]    : Get the data From EEPROM
	[ARGUMENT(S)]  :
	   	   	   	   [IN]  : 1-> 16-bit address
	   	   	   	   	   	   2-> pointer to a 8-bit data
	   	   	   	   [OUT] :  a flag represent the error
	[Return]      : void

	---------------------------------------------------------------*/


	/*set start condition and check for it */
	TWI_start() ;
	if (TWI_getStatus() != TW_START)
		return ERROR;

	/*
	 * EEPROM address is consist of  11-bit size(A0 to A10)
	 *  Device ID is 0b1010
	 *  we will divide the address into to part
	 *  first part :
	 *  	(0b1010)>>A10>>A9>>A8>>(R/W)
	 *  Second part is
	 * 		From A7 to A0
	 * */


	TWI_write((unsigned char )((0xA0) | ((Address & 0x0700)>>7))) ;
	if(TWI_getStatus()!= TW_MT_SLA_W_ACK)
		return ERROR ;

	TWI_write((unsigned char )Address) ;
	if(TWI_getStatus()!= TW_MT_DATA_ACK)
		return ERROR ;

	/*send a repeated start */
	TWI_start() ;
	/*check for repeated bit transmitted */
	if (TWI_getStatus() != TW_REP_START)
		return ERROR;

	TWI_write((0xA0  | (((Address) & (0x0700)>>7) ) | 1  )) ;
	if (TWI_getStatus() != TW_MT_DATA_ACK)
		return ERROR  ;

	*DATA = TWI_readWithNACK() ;
	if(TWI_getStatus() != TW_MR_DATA_NACK)
		return ERROR ;

	TWI_stop() ;

}


