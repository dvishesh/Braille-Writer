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
void acc2_init (void);
void ReadPulseSource2(void);
uint8_t GetINT_SRC_Status2(void);
uint8_t Get_STATUS2(void);
uint8_t Get_WHOAMI2(void);
uint8_t Get_ZPULSETHRESHOLD2(void);
uint8_t Get_ZPULSE_TMLIMIT2(void);
uint8_t Get_ZPULSE_TMLATENCY2(void);
void acc2_read (int16_t *z);
float acc2_getGs(int16_t *z);



#endif /* ACCLIBRARY_H_ */
