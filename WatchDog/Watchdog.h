/******************************************************************************
 *[Author]     	: Muhammed eldabea Hasheem
 *
 *[filename]   	: Watchdog.h
 *
 *[Date]       	: 9 June 2020
 *
 *[Description] : contain function declaration and configuration 
 *
 ******************************************************************************/



/*=============================================================================
 * 				Include
 *=============================================================================*/

/*include the porting file */
#include "microcontroller_config.h"  


/*=============================================================================
 * 			Definition and Configuration 
 *=============================================================================*/


typedef  enum 
{
	
	/*the time after which the watchdog will reset the system if nothing stop it */
16_3ms,32_5ms,6_5ms,0_13s,0_26s,0_52s,1_0s,2_0s  

	
}Watchdog_timer_prescaler;

typedef struct 
{
	/*=========================================================================
		[Structure Name] : Watchdog_configuration
		[Description]    : configuration as timer pre-scaler for Watchdog
	==========================================================================*/

	unsigned char WatchdogTimer_prescaler : 3  ; /*configure the pre-scaler value*/
}Watchdog_configuration; 




/*=============================================================================
 			 	Function Declarations
 *=============================================================================*/

void Watchdog_start(Watchdog_configuration *ptr)  ; 
void Watchdog_off(void)  ; 


