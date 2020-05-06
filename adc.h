/*--------------------------------------------------------------------------------------------------------------

 &[FILE NAME]    :adc.h

 &[AUTHOR(S)]    : Muhammed Eldabea Hashem

 &[DATE CREATED] : 20 April 2020

 &[DESCRIPTION]  :  definitions and configuration used foe ADC module in Atmega16

------------------------------------------------------------------------------------------------------------------*/
#ifndef ADC_H_
#define ADC_H_


/*---------------------------------------> INCLUDES <---------------------------------------*/
#include "micro_config.h"

/*-------------------------------> Definitions and configuration <---------------------------*/

/* to use any of next configuration just set it */

#define ADC_leftAdjustResult   0        /*enable it will left write the result of conversion  */
#define ADC_AutoTriggerEnable  0        /* The ADC will start a conversion on a positive edge of the selected trigger signal */
#define ADC_HighSpeedMode      0        /*This mode enables higher conversion rate at the expense of higher power consumption*/
#define ADC_interruptEnable    0        /*set this macro will enable the interrupt of ADC */


/*----------------------------------------> Enums <-----------------------------------------*/


typedef enum
{
	           /* -> using these configuration u could chose the reverence voltage by with you could make conversion <- */

	AREF_withInternal_Vref_off,
	AVCC_withExternalCapacitorAtVref,
	ADC_Reserved,
	internal2_56Voltag_Ref
}Refrence_selection_bit;


typedef enum
{
	    /* -> these configuration are used to chose the channel that we will deal with
        	  and the gain by which signal is multiplied when we use a Differential mode
         	  in case of Differential mode naming -->> tow Positive_inpute>>negative_input>>gain <-- */

	ADC0,ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,
	ADC0_to_ADC0_withGain10x,ADC1_to_ADC0_withGain10x,
	ADC0_to_ADC0_withGain200x,ADC1_to_ADC0_withGain200x,
	ADC2_to_ADC2_withGain10x,ADC3_to_ADC2_withGain10x,
	ADC2_to_ADC2_withGain200x,ADC3_to_ADC2_withGain200x ,
	ADC0_to_ADC1_withGain1x,ADC1_to_ADC1_withGain1x , ADC2_to_ADC1_withGain1x,
	ADC3_to_ADC1_withGain1x,ADC4_to_ADC1_withGain1x,ADC5_to_ADC1_withGain1x,
	ADC6_to_ADC1_withGain1x,ADC7_to_ADC1_withGain1x,ADC0_to_ADC2_withGain1x ,
	ADC1_to_ADC2_withGain1x,ADC2_to_ADC2_withGain1x,ADC3_to_ADC2_withGain1x,
	ADC4_to_ADC2_withGain1x,ADC5_to_ADC2_withGain1x,vBG_ADC,GND_ADC
}Analog_channel_andGainSelection;


typedef enum
{
	/*chose the auto trigger source for the ADC >> it will be enabled depending on an event  */

	ADC_Trigger_free_runningMode,ADC_Trigger_AnalogeComparator ,ADC_Trigger_ExternalInterrupt_request,
	ADC_Trigger_Timer0CompareMatch,ADC_Trigger_Timer0OverFlow,ADC_Trigger_Timer1CompareMatchB,
	ADC_Trigger_Timer1OverFlow ,ADC_Trigger_TimerCaptureEvent,ADC_NOTrgigger

}AutoTriggerSource;


typedef enum
{
	/*note that ADC work in a frequency between 50KH to 200KH so we should use a <pre>-scaler to divide the natural frequency */
	ADC_preScalerBY2,ADC_preScalerBy2,ADC_preScalerBY4,ADC_preScalerBY8,
	ADC_preScalerBY16,ADC_preScalerBY32,ADC_preScalerBY64,ADC_preScalerBY128

}ADC_preScaler;


/*--------------------------------> Structure and Unions <----------------------------------*/

typedef struct
{
	/*this structure contain the configuration for the ADC like the Voltage reference  and the <pre>-scaler that we will use  */

	unsigned char ADC_Refrence_selection ;  /*used to configure the reference voltage */
	unsigned char ADC_prescaler ;           /*used to configure the <pre>-scaler value */
    unsigned char ADC_AutoTriggerSource;    /*chose the Auto trigger Source  chose "ADC_NOTrgigger" if you don't enable Auto trigger */

}ADC_configuration ;



/*--------------------------------> Function Declarations <--------------------------------*/

void ADC_init(ADC_configuration *ptrTostruct) ;
unsigned char ADC_ReadData(unsigned char channel) ;
void ADC_callBAckFunction (unsigned char (*ptr)(unsigned char)) ;
unsigned char   GET_data(unsigned char nothing ) ;








/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif /* ADC_H_ */
