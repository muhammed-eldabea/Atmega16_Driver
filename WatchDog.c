/*****************************************************************************
 *[Author]     	: Muhammed eldabea Hasheem
 *
 *[filename]   	: Watchdog.c
 *
 *[Date]       	: 9 June 2020
 *
 *[Description] : contain function definition that can run watchdog in  ATmega 16
 *
 ******************************************************************************/ 



/*=============================================================================
 * 						  		    Include
 *=============================================================================*/


#include "WatchDog.h" 


/*=============================================================================
 * 		 						Function Definition
 *=============================================================================*/

void Watchdog_start(Watchdog_configuration *ptr) 
{
   

	/*==========================================================================
	[FUNCTION NAME] : watchdog_start

	[DESRIPTION]    : run the watchdog with a given time pre-scaler

	[ARGUMENT(S)]   :

	   [IN]  		: pointer to watchdog_Configuration Structure  
	   			      that have a timer pre-scaler configuration 

	   [Return] 	: void


	============================================================================*/

WDTCR = (WDTCR & 0xF8)  | (ptr->WatchdogTimer_prescaler & 0x07)  ; /*set the pre-scaler */ 

WDTCR |=(1<<3) ; /*enable the module */ 


} 



void Watchdog_off(void) 
{


/*to clear both the bit we need to set the WDE and WDTOE*/ 

	WDTCR =(1<<4) | (1<<3) ; 

/*we need to wait a four cycle */ 

	delay_us(4) ;  
 /*clear the WDTCR */ 
	WDTCR=0xE0 ; 



}
