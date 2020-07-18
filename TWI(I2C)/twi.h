/*
 * 		[file name]   : twi.h
 *  	[Created on]  : Jul 15, 2020
 *      [Author]      : Muhammed Eldabea Hashem
 *      [Description] : Function declarations and configuration used
 *
 */

#ifndef TWI_H_
#define TWI_H_


/*==========================> INCLUDES <===============================*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

/*=========================> Definitions <=============================*/

#define TWI_Interrupt_Enable  0

#define TWI_ General_Call_Recognition  0
// start has been sent
#define TW_START         0x08
// repeated start
#define TW_REP_START     0x10
// Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_W_ACK  0x18
// Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40
// Master transmit data and ACK has been received from Slave.
#define TW_MT_DATA_ACK   0x28
// Master received data and send ACK to slave
#define TW_MR_DATA_ACK   0x50
// Master received data but doesn't send ACK to slave
#define TW_MR_DATA_NACK  0x58


/*=========================> Enumerations <============================*/
typedef enum {
	/*configuration for the pre-scaler value */
	TWI_preScalerBY_1,TWI_preScalerBY_2,TWI_preScalerBY_16,TWI_preScalerBY_64
};

/*=====================> Structure and Unions <========================*/
typedef struct {
	/*****************************************************************
	 *  [struct name] : TWI_Configuration
	 *  [Description] : have the main configuration that will be used
	 *  				in the TWI module configuration like
	 *  				TWBR register value and pre-scaler value
	 *****************************************************************/
	unsigned char TWI_BitRate_value ;
	unsigned char TWI_PreScaler ;
	unsigned char TWI_AddressRegister ;
}TWI_Configuration;

/*============================> Macros <===============================*/
#define BIT_IS_CLEAR(REG,BIT)  (!(REG &(1<<BIT)))

/*=====================> Function Declarations <========================*/

void TWI_init(TWI_Configuration *ptr) ;
void TWI_start(void) ;
void TWI_stop(void) ;
void TWI_write(unsigned char  data) ;
unsigned char  TWI_readWithACK(void) ;
unsigned char TWI_readWithNACK(void) ;
unsigned char TWI_getStatus(void) ;

#endif /* TWI_H_ */
