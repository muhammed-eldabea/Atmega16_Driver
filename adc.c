/*-----------------------------------------------------------------------------------------------------------------------

 &[FILE NAME]    :->  adc.c

 &[AUTHOR(S)]    :->  Muhammed Eldabea Hashem

 &[DATE CREATED] :->  20 April 2020

 &[DESCRIPTION]  :->  implementation for ADC module in Atmega16

--------------------------------------------------------------------------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------INCLUDES-------------------------------------------------------------*/
#include "adc.h"

/*-------------------------------------------------------------------------Global Variable---------------------------------------------------------*/
void (*ptrTofun)(unsigned char) = (void*)0 ; /* pointer to function this pointer will be used to a callback in ISR ,it need to be {{casting }} */

volatile unsigned char DATA =0 ;
/*---------------------------------------------------------------------Functions Definitions-------------------------------------------------------*/

#if ADC_interruptEnable ==1
ISR(ADC_vect)
{
	if(ptrTofun != (void*)0)
	{
		(*ptrTofun)() ; /*this line  will call a function  as a callback */

	}
}

#endif



void ADC_init(ADC_configuration *ptrTostruct)
{
	/*-------------------------------------------------------------------------------------------------------------------

		[FUNCTION NAME] :ACD_init

		[DESRIPTION] :used to initialize  the ADC module if configure the prescaler ,reference voltage and the Auto trigger source

		[ARGUMENT(S)]  :
		   [IN]  : a pinter to structure that contain the ADC configuration this structure have three members  :
		            1- ADC_Refrence_selection
		            2-ADC_prescaler
		            3-ADC_AutoTriggerSourc


		   [OUT] : void

		[Return]      : void

		-----------------------------------------------------------------------------------------------------------------*/

#if ADC_leftAdjustResult == 1

	ADMUX|=(1<<5) ; /*enable the result left adjustment */
#endif

#if ADC_interruptEnable ==1

	SREG|=(1<<7) ; /*General interrupt bit */
	ADCSRA|=(1<<3) ; /*enable the interrupt bit */

#endif

#if ADC_AutoTriggerEnable==1
	ADCSRA |=(1<<5)  ; /*enable the auto trigger pin */
    SFIOR = (SFIOR   & 0xEF ) | ((ptrTostruct->ADC_AutoTriggerSource    & 0x07)<<5) ; /*configure the Auto trigger source */

#endif
	ADMUX  = (ADMUX  & 0x3f ) |  ((ptrTostruct->ADC_Refrence_selection & 0x03)<<6) ; /*configure the reference voltage */
    ADCSRA = (ADCSRA & 0xf8 ) |  (ptrTostruct->ADC_prescaler           & 0x07)     ; /*configure the pre-scaler */


}




unsigned char ADC_ReadData(unsigned char channel)
{

	/*-------------------------------------------------------------------------------------------------------------------

			[FUNCTION NAME] :ACD_ReadData

			[DESRIPTION] :used to initialize  the ADC module if configure the prescaler ,reference voltage and the Auto trigger source

			[ARGUMENT(S)]  :
			   [IN]  : the channel number


			   [OUT] : the converted value

			[Return]      : the ADC register value that represent the converted value

			-----------------------------------------------------------------------------------------------------------------*/


	ADMUX = (ADMUX & 0xf0 ) |  (channel & 0x0f) ; /*configure the first 4 bit is the channel*/
	ADMUX = (ADMUX & 0xEF ) |  (channel & 0x10) ; /*Configure the  the 5th bit of channel */
	ADCSRA |=(1<<7) ; /*set the enable bit */
	ADCSRA |=(1<<6) ; /*set the Start conversion bit */

#if	ADC_interruptEnable ==1

	ADC_callBAckFunction(GET_data(0)) ;

#elif  ADC_interruptEnable ==0

	while (ADCSRA & (1<<4))  {} /*the ADC will be set when the conversion is completed */

	ADCSRA |= (1<<4) ; /*clear the flag bit by setting it   */

	DATA=ADC ;

#endif




	return DATA ;  /* return the ADC register value that represent the converted value*/
}




void ADC_callBAckFunction (unsigned char (*ptr)(unsigned char))
{
	/*-------------------------------------------------------------------------------------------------------------------

			[FUNCTION NAME] :callBAckFunction

			[DESRIPTION]   :used to make a function take action when ISR is called

			[ARGUMENT(S)]  :
			   [IN]  : pointer to function this function will return a unsigned char and take a unsigned char as input parameter


			   [OUT] : void

			[Return]      : the ADC register value that represent the converted value

			-----------------------------------------------------------------------------------------------------------------*/

	/*any function send to  be called  back will take action in ISR */

	ptrTofun=ptr ; /*we make a Global pointer ptrTofun point to a function */

}

unsigned char   GET_data(unsigned char nothing )
{
	/*-------------------------------------------------------------------------------------------------------------------

				[FUNCTION NAME] :Get_data

				[DESRIPTION]   :read the data from the ADC

				[ARGUMENT(S)]  :
				   [IN]  : void


				   [OUT] : unsigned char DATA its value is equal ADC register value

				[Return]      : void

				-----------------------------------------------------------------------------------------------------------------*/


	DATA=ADC ;

	return 0 ;

}
