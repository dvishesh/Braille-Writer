/* alib.c
 *
 *  Created on: May 26, 2015
 *      Author: Vishesh
 */


/*****************************************************************************
 *   Driver for the MMA8452q Accelerometer
     Reference: acc.c from Baseboard Library
 *
 *   Copyright(C) 2009, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/

/*
 * NOTE: I2C must have been initialized before calling any functions in this
 * file.
 */

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "alib2.h"
#include "macros.h"
#include <stdint.h>

/******************************************************************************
 * Defines and typedefs
 *****************************************************************************/

/******************************************************************************
 * External global variables
 *****************************************************************************/

/******************************************************************************
 * Local variables
 *****************************************************************************/


 // REGISTER READ/WRITE FUNCTIONS

     /*@ Functions sets CTRL_REG1 bits - DATA RATE& ACTIVE/STANDBY MODE ACCESSIBLE FROM HERE
     */


     static void setControlReg1(uint8_t registervalue)
     {
         uint8_t buf[2];

         buf[0] = CTRL_REG1 ;
         buf[1] = registervalue;
         Chip_I2C_MasterSend(I2C2, ACC_I2C_ADDRESS, buf, 2);
     }

     /*@ Functions sets XYZ_DATA_CFG - HIGH PASS FILTER & DYNAMIC g range can be set from here
     */

     static void setXYZ_DATA_CONFG(uint8_t registervalue)
     {
         uint8_t buf[2];

         buf[0] = XYZ_DATA_CFG ;
         buf[1] = registervalue;
         Chip_I2C_MasterSend (I2C2, ACC_I2C_ADDRESS, buf, 2);
     }


     /*@ Functions sets CTRL_REG2 bits - RESET/ SLEEP MODE OR ACTIVE MODE POWER SCHEME / AUTO-SLEEP ENABLE can be accessed from here
     */

     static void setControlReg2(uint8_t registervalue)
     {
         uint8_t buf[2];

         buf[0] = CTRL_REG2 ;
         buf[1] = registervalue;
         Chip_I2C_MasterSend (I2C2, ACC_I2C_ADDRESS, buf, 2);
     }

     /*@ Functions sets CTRL_REG3 bits - Interrupt Polarity (IPOL), and PUSH-PULL/OPEN_DRAIN Pin Mode Config for interrupt ACCESSIBLE FROM HERE
     */

      static void setControlReg3(uint8_t registervalue)
      {
              uint8_t buf[2];

              buf[0] = CTRL_REG3 ;
              buf[1] = registervalue;
              Chip_I2C_MasterSend (I2C2, ACC_I2C_ADDRESS, buf, 2);
       }
      /*@ Functions sets CTRL_REG4 bits - various interrupt enablers accessible from here
      */

      static void setControlReg4(uint8_t registervalue)
      {
              uint8_t buf[2];
              buf[0] = CTRL_REG4 ;
              buf[1] = registervalue;
              Chip_I2C_MasterSend (I2C2, ACC_I2C_ADDRESS, buf, 2);
      }

      /*@ Functions sets CTRL_REG5 bits - various interrupt pin configuration registers accessible from here
      */
      static void setControlReg5(uint8_t registervalue)
      {
              uint8_t buf[2];
              buf[0] = CTRL_REG5 ;
              buf[1] = registervalue;
              Chip_I2C_MasterSend (I2C2, ACC_I2C_ADDRESS, buf, 2);
      }

      static void setPULSE_CONFIG(uint8_t registervalue)
           {
               uint8_t buf[2];

               buf[0] = PULSE_CFG ;
               buf[1] = registervalue;
               Chip_I2C_MasterSend (I2C2, ACC_I2C_ADDRESS, buf, 2);
           }

      static void setPULSE_LPF(uint8_t registervalue)
           {
               uint8_t buf[2];

               buf[0] = HP_FILTER_CUTOFF;
               buf[1] = registervalue;
               Chip_I2C_MasterSend (I2C2, ACC_I2C_ADDRESS, buf, 2);
           }
      static void setZthreshold_CONFG(acc_pulse_zthreshold_t registervalue)
           {
               uint8_t buf[2];

               buf[0] = PULSE_THSZ;
               buf[1] = registervalue;
               Chip_I2C_MasterSend (I2C2, ACC_I2C_ADDRESS, buf, 2);
           }

      static void setPULSE_TMLT(acc_pulse_tmlt_t registervalue)
           {
               uint8_t buf[2];

               buf[0] = PULSE_TMLT;
               buf[1] = registervalue;
               Chip_I2C_MasterSend (I2C2, ACC_I2C_ADDRESS, buf, 2);
           }


      static void setPULSE_LTCY(acc_pulse_latency_t registervalue)
           {
               uint8_t buf[2];

               buf[0] = PULSE_LTCY;
               buf[1] = registervalue;
               Chip_I2C_MasterSend(I2C2, ACC_I2C_ADDRESS, buf, 2);
           }

      static uint8_t getModeControlReg1(void)
          	 {
          	     uint8_t registervalue;
    	  	  	 uint8_t buf[1];

          	     Chip_I2C_MasterCmdRead(I2C2, ACC_I2C_ADDRESS, CTRL_REG1, buf, 1);
          	     registervalue = buf[0];
          	     return registervalue;
          	 }

       static void setmode(acc_mode_t mode)
      {
          uint8_t buf = 0;

          buf = getModeControlReg1();

          buf &= ~(0x01 << 0);
          buf |= ACC_CTRL_REG1_MODE(mode);

          setControlReg1(buf);
      }




 /******************************************************************************
 * Local Functions
 *****************************************************************************/

/******************************************************************************
* Public Functions
*****************************************************************************/


     void acc2_init (void)
     {

       // set to standby mode for register configuration
    	 setControlReg1	( ACC_CTRL_REG1_MODE(ACC_MODE_STANDBY));

    	 setXYZ_DATA_CONFG(ACC_GDYNAMIC(EIGHTG_RANGE));
       //Self Test Mode: for testing purposes
         setControlReg2 ( ACC_CTRL_REG2_SELFTEST(ACC_SELFTEST_DISABLE));

         /* Note: Enabling FLAGLATCH for testing purposes: PULSE_SRC needs to be read by handler to clear.*/
         setPULSE_CONFIG( (ACC_PULSECFG_EVENTLATCH(FLAGLATCH_ENABLE)|ACC_PULSECFG_ZSINGLEPULSE(EVENTFLAG_ENABLE)) );

         setPULSE_LPF   (  ACC_PULSELPFMODE(PULSE_LPF_ENABLE));

         setZthreshold_CONFG(SEVENG); //Setting Interrupt Threshold value
         setPULSE_TMLT(TMLY_TWENTYMS); //Setting time between exceeding threshold and returning below threshold
         setPULSE_LTCY(TMLY_TWOHUNDREDMS); //Time delay between two interrupts - INT Flag is automatically reset after this delay if ELE Flag Latch is disabled

         setControlReg3 ( ACC_CTRL_REG3_INTPOLARITY(INT_ACTIVE_HIGH)); // Setting Interrupt Polarity: Rising or Falling Edge

         setControlReg5	( ACC_CTRL_REG5_INTCFGPULSE(PIN1)); // Selecting Breakout board Interrupt Pin

         setControlReg4	( ACC_CTRL_REG4_INTENPULSE(INTIMP_DISABLE));

         // set to active mode for use
         setmode(ACC_CTRL_REG1_MODE(ACC_MODE_ACTIVE));

     }

     void ReadPulseSource2(void)
     {
    	 uint8_t buf[1];
    	 buf[0] = 0;

    	 Chip_I2C_MasterCmdRead(I2C2, ACC_I2C_ADDRESS, PULSE_SRC, buf, 1);
     }

     uint8_t GetINT_SRC_Status2(void)
     {
    	 uint8_t buf[1];
    	 buf[0] = 0;

    	 Chip_I2C_MasterCmdRead(I2C2, ACC_I2C_ADDRESS, INT_SOURCE, buf, 1);
    	 return buf[0];

     }


     uint8_t Get_STATUS2(void)
     {
    	 uint8_t buf[1];
    	 buf[0] = 0;

    	 Chip_I2C_MasterCmdRead(I2C2, ACC_I2C_ADDRESS, STATUS, buf, 1);
         return buf[0];
     }

     uint8_t Get_WHOAMI2(void)
        {
       	 uint8_t buf[1];
       	buf[0] = 0;

       	 Chip_I2C_MasterCmdRead(I2C2, ACC_I2C_ADDRESS, WHO_AM_I, buf, 1);
            return buf[0];
        }

     uint8_t Get_ZPULSETHRESHOLD2(void)
             {
            	 uint8_t buf[1];
            	buf[0] = 0;

            	 Chip_I2C_MasterCmdRead(I2C2, ACC_I2C_ADDRESS, PULSE_THSZ , buf, 1);
                 return buf[0];
             }

     uint8_t Get_ZPULSE_TMLIMIT2(void)
             {
            	 uint8_t buf[1];
            	buf[0] = 0;

            	 Chip_I2C_MasterCmdRead(I2C2, ACC_I2C_ADDRESS, PULSE_TMLT , buf, 1);
                 return buf[0];
             }

     uint8_t Get_ZPULSE_TMLATENCY2(void)
             {
            	 uint8_t buf[1];
            	buf[0] = 0;

            	 Chip_I2C_MasterCmdRead(I2C2, ACC_I2C_ADDRESS, PULSE_LTCY , buf, 1);
                 return buf[0];
             }

     void acc2_read (int16_t *z)
     {
        uint8_t zvalue_hi[1];
        uint8_t zvalue_low[1];
        uint16_t temp;

        zvalue_hi[0] = 0;
        zvalue_low[0] = 0;
    	// wait for ready flag

        while(((Get_STATUS()>>2)& 0x01) == 0) //ZDR>>2 (STATUS REGISTER}
        {

        }

        Chip_I2C_MasterCmdRead(I2C2, ACC_I2C_ADDRESS, OUT_Z_MSB , zvalue_hi, 1);
        Chip_I2C_MasterCmdRead(I2C2, ACC_I2C_ADDRESS, OUT_Z_LSB , zvalue_low, 1);

        temp = (zvalue_hi[0]<<8)| zvalue_low[0];

        *z = temp;

     }

     float acc2_getGs(int16_t *z)
     {

    	 //ALGORITHM FOR TWO'S COMPLEMENT TO SIGNED G REPRESENTATION

    	 int sign = 0;
    	 int16_t temp = *z;
    	 int8_t zvalue_hi[1];
    	 int8_t zvalue_low[1];
    	 int8_t temp_int;
    	 int8_t temp_fraction;
    	 int8_t value_Byte;
    	 int result;
    	 float decimalvalue;

    	 //Spliting into MSB and LSB bytes
    	 zvalue_hi[0] = temp>>8;
    	 zvalue_low[0] = (temp& 0xFF);

    	//Determine sign and implement 2s complement to unsigned binary coversion

    	 if (zvalue_hi[0] > 0x7F) // test case to see if number is negative
    	 {
    	 sign = -1.0;
    	 temp = ~(temp) + 1;
    	 // updating MSB and LSB bytes with unsigned binary values
    	 zvalue_hi[0] = temp>>8;
    	 zvalue_low[0] = (temp& 0xFF);
    	 }
    	 else
    	 sign = 1;


    	 //Determine integer value FOR 8G MODE - MSB byte: bits 6,5,4
    	 temp_int = zvalue_hi[0] << 1; //eliminate the signed bit 7
    	 temp_int = temp_int >>5; //eliminate the fractional bits

    	 //determine fractional bits
    	 temp_fraction = zvalue_hi[0] << 4; //eliminate the signed and integer bits
    	 temp_fraction = temp_fraction >> 4; // Setting MSB byte bits 3,2,1,0 as most significant fractional bits

    	 // testing for bits 3-0 of MSB & bits 7-2 of LSB for 8G mode to determine fractional value
    	 result = 0;

    	 // testing for bits 3-0 of MSB
    	 value_Byte = temp_fraction;
    	 if (value_Byte>>3 & 0x01 == 1)
    	 result += FRAC_2d1;
    	 if (value_Byte>>2 &0x01 == 1)
    	 result += FRAC_2d2;
    	 if (value_Byte>>1 &0x01 == 1)
    	 result += FRAC_2d3;
    	 if (value_Byte>>0 &0x01 == 1)
    	 result += FRAC_2d4;

    	 //testing for bits 7-2 of LSB
    	 value_Byte = zvalue_low[0];
    	 if ((value_Byte>>7 & 0x01) == 1)
    	 result += FRAC_2d5;
    	 if ((value_Byte>>6 &0x01) == 1)
    	 result += FRAC_2d6;
    	 if ((value_Byte>>5 &0x01) == 1)
    	 result += FRAC_2d7;
    	 if (value_Byte>>4 &0x01 == 1)
    	 result += FRAC_2d8;
    	 if (value_Byte>>3 &0x01 == 1)
    	 result += FRAC_2d9;
    	 if (value_Byte>>2 &0x01 == 1)
    	 result += FRAC_2d10;

    	 //perform necessary type conversions here if required
    	 decimalvalue = (float)result/10000; //integer result/ 10000 to get 4 decimal places
    	 temp_int = temp_int * sign; //get signed integer value
    	 decimalvalue += temp_int; // get signed decimal value

    	 return decimalvalue;

     }


