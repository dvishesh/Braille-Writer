/*
 * alib.h
 *
 *  Created on: May 26, 2015
 *      Author: Vishesh
 */

#ifndef ACCLIBRARY_H_
#define ACCLIBRARY_H_
#include <stdint.h>

//Public function declarations
void acc_init (void);
void ReadPulseSource(void);
uint8_t GetINT_SRC_Status(void);
uint8_t Get_STATUS(void);
uint8_t Get_WHOAMI(void);
uint8_t Get_ZPULSETHRESHOLD(void);
uint8_t Get_ZPULSE_TMLIMIT(void);
uint8_t Get_ZPULSE_TMLATENCY(void);
void acc_read (int16_t *z);
float acc_getGs(int16_t *z);



#endif /* ACCLIBRARY_H_ */
