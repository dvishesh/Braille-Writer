/*
 * alib.h
 *
 *  Created on: May 26, 2015
 *      Author: Vishesh
 */

#ifndef ACCLIBRARY_H_
#define ACCLIBRARY_H_

//support header files
#include <stdint.h>

//Public function declarations
void acc1_init (void);
void ReadPulseSource1(void);
uint8_t GetINT_SRC_Status1(void);
uint8_t Get_STATUS1(void);
uint8_t Get_WHOAMI1(void);
uint8_t Get_ZPULSETHRESHOLD1(void);
uint8_t Get_ZPULSE_TMLIMIT1(void);
uint8_t Get_ZPULSE_TMLATENCY1(void);
void acc1_read (int16_t *z);
float acc1_getGs(int16_t *z);



#endif /* ACCLIBRARY_H_ */
