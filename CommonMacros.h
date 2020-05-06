/*
 * CommonMacros.h
 *
 *  Created on: 19 Apr 2020
 *      Author: Muhammed Eldabea Hashem
 */

#ifndef COMMONMACROS_H_
#define COMMONMACROS_H_

#define SETBIT(REG,BIT)       ( REG = REG|(1<<BIT))
#define CLEARBIT(REG,BIT)     ( REG = REG & (~(1<<BIT)))
#define ToggleBIT(REG,BIT)    ( REG = REG ^ (1<<BIT))
#define CHECKifSET(REG,BIT)   ( REG | (1<<BIT))
#define CHECKifClear(REG,BIT) (~( REG | (1<<BIT)))




#endif /* COMMONMACROS_H_ */
