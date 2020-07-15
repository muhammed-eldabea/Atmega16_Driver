/*
 * 		[file name]   : spi.h
 *  	[Created on]  : Jul 7, 2020
 *      [Author]      : Muhammed Eldabea Hashem
 *      [Description] : Function declarations and configuration used
 *
 */



#ifndef SPI_H_
#define SPI_H_


/*==========================> INCLUDES <===============================*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

/*=========================> Definitions <=============================*/
#define SPI_Enable_inteerupt  0
#define SPI_LSB_DataOrder     0



/*=========================> Enumerations <============================*/
typedef enum {
	/*  configuration for the operation mode slelct */
	SPI_Slave_select,SPI_Master_select
}SPI_OperationMODE;

typedef enum {
	/*  configuration of the clock polarity
	 *  the idle state of the SPI          */
	Spi_CLP_RisingleadingFallingTrailling,Spi_CLP_FallingleadingRisingTrailling
}SPI_clockPolarity;

typedef enum {
	/*  configuration for the clock phase */
	/*  Data sampled on rising edge and shifted out on the falling edge
	 *  or */
	Spi_CLP_sampleleadingsetupTrailling,Spi_CLP_setupleadingsampleTrailling
}SPI_clockPhase;
typedef enum {
	/*  configuration for the pre-scaler values that will be used
	 *  to enable the double speed mode choose any configuration
	 *  with 2X title */

SPI_FoscBY4,SPI_FoscBY16,SPI_FoscBY64,SPI_FoscBY128,
SPI_FoscBY2_2xspeed,SPI_FoscBY8_2xspeed,SPI_FoscBY32_2xspeed,
SPI_FoscBY64_2xspeed

}SPI_FreqPreScaler;


/*=====================> Structure and Unions <========================*/

typedef struct {

	/*------------------------------------------------------------------
		[Structure Name]  :  SPI_configuration
		[Description]     :  select the configuration that will used in
							 like operation mode clock polarity,
							 clock phase , pre-scaler value
	--------------------------------------------------------------------*/

	/* master or slave selection*/
	unsigned char SPI_MAsterSlaveSelect ;
	 /* idle state of the SCK
	  *  when this bit written
	  *   to zero the SCK is low in idle */
	unsigned char SPI_ClockPolarity ;
	/*clock phase describe the data is sampled in the first or last
	 * of the clock , the data will synch with rising/falling edge  */
	unsigned char SPI_ClockPhase ;
	/*Frequency pre-scaler configuration */
	unsigned char SPI_preScaler ;
}SPI_configuration ;



/*=====================> Function Declarations <========================*/





#endif /* SPI_H_ */
