/*
 * marcos.h
 *
 *  Created on: 6 Jun, 2015
 *      Author: uthesh
 */

#ifndef MACROS_H_
#define MACROS_H_
#include<stdint.h>

/******************************************************************************
 * Defines
 *****************************************************************************/

#define I2C0 0 // I2C0 enum type doesn't work - potential bug
#define I2C1 1
#define I2C2 2

#define ACC_I2C_ADDRESS ACC_I2C_ADDRHIGH //value to be changed for different sensors
//Pin-configurable I2C address modes
#define ACC_I2C_ADDRLOW    (0x1C) //SA0 = 0
#define ACC_I2C_ADDRHIGH    (0x1D) //SA0 = 1 (default)

#define STATUS    		0x00	// R Real time status
#define OUT_X_MSB 		0x01  	// R Output — [7:0] are 8 MSBs of 12-bit sample.
#define OUT_X_LSB 		0x02  	// R Output — [7:4] are 4 LSBs of 12-bit sample.
#define OUT_Y_MSB 		0x03  	// R Output — [7:0] are 8 MSBs of 12-bit sample.
#define OUT_Y_LSB 		0x04  	// R Output — [7:4] are 4 LSBs of 12-bit sample.
#define OUT_Z_MSB 		0x05  	// R Output — [7:0] are 8 MSBs of 12-bit sample.
#define OUT_Z_LSB 		0x06	// R Output — [7:4] are 4 LSBs of 12-bit sample.
//Reserved R      		0x07 — — — Reserved. Read return 0x00.
//Reserved R      		0x08 — — — Reserved. Read return 0x00.
#define SYSMOD    		0x0B	// R Current System Mode
#define INT_SOURCE		0x0C    // R Interrupt status
#define WHO_AM_I		0x0D    // R Device ID (0x2A)
#define XYZ_DATA_CFG	0x0E	// R/W HPF Data Out and Dynamic (g range)

//Range Settings

#define HP_FILTER_CUTOFF	0x0F	// R/W Cutoff frequency is set to 16 Hz @ 800 Hz
#define PL_STATUS			0x10 	// R Landscape/Portrait orientation status
#define PL_CFG				0x11 	// R/W Landscape/Portrait configuration.
#define PL_COUNT			0x12    // R Landscape/Portrait debounce counter
#define PL_BF_ZCOMP			0x13	// R Back-Front, Z-Lock Trip threshold
#define P_L_THS_REG			0x14	// R Portrait to Landscape Trip Angle is 29°
#define FF_MT_CFG			0x15	// R/W Freefall/Motion functional block configuration
#define FF_MT_SRC			0x16    // R Freefall/Motion event source register
#define FF_MT_THS			0x17    // R/W Freefall/Motion threshold register
#define FF_MT_COUNT			0x18	// R/W Freefall/Motion debounce counter

//Reserved R 				0x19 - 0x1C Read return 0x00.

#define TRANSIENT_CFG		0x1D	// R/W Transient functional block configuration
#define TRANSIENT_SRC		0x1E	// R Transient event status register
#define TRANSIENT_THS		0x1F	// R/W Transient event threshold
#define TRANSIENT_COUNT		0x20	// R/W Transient debounce counter
#define PULSE_CFG			0x21	// R/W ELE, Double_XYZ or Single_XYZ
#define PULSE_SRC		    0x22	// R EA, Double_XYZ or Single_XYZ
#define PULSE_THSX			0x23	// R/W X pulse threshold
#define PULSE_THSY			0x24 	// R/W Y pulse threshold
#define PULSE_THSZ			0x25	// R/W Z pulse threshold
#define PULSE_TMLT			0x26	// R/W Time limit for pulse
#define PULSE_LTCY			0x27 	// R/W Latency time for 2nd pulse
#define PULSE_WIND			0x28 	// R/W Window time for 2nd pulse
#define ASLP_COUNT			0x29 	// R/W Counter setting for Auto-SLEEP
#define CTRL_REG1			0x2A 	// R/W Data Rate, ACTIVE Mode
#define CTRL_REG2			0x2B 	// R/W Sleep Enable, OS Modes, RST, ST
#define CTRL_REG3			0x2C 	// R/W Wake from Sleep, IPOL, PP_OD
#define CTRL_REG4			0x2D 	// R/W Interrupt enable register
#define CTRL_REG5			0x2E	// R/W Interrupt pin (INT1/INT2) map
#define OFF_X				0x2F	// R/W X-axis offset adjust
#define OFF_Y				0x30    // R/W Y-axis offset adjust
#define OFF_Z				0x31	// R/W Z-axis offset adjust
//Reserved (do not modify)  0x40 – 7F

// for calculating acceleration in decimal Gs
#define FRAC_2d1 5000
#define FRAC_2d2 2500
#define FRAC_2d3 1250
#define FRAC_2d4 625
#define FRAC_2d5 313
#define FRAC_2d6 156
#define FRAC_2d7 78
#define FRAC_2d8 39
#define FRAC_2d9 20
#define FRAC_2d10 10
#define FRAC_2d11 5
#define FRAC_2d12 2

// CTRL REGISTER 1 USER-INPUT OPTIONS
#define ACC_CTRL_REG1_MODE(m) ((m) << 0) //m has a range of 0-1

// CTRL REGISTER 2 USER-INPUT OPTIONS
#define ACC_CTRL_REG2_SELFTEST(st) ((st) << 7) //st has a range of 0-1

// CTRL REGISTER 3 USER-INPUT OPTIONS
#define ACC_CTRL_REG3_INTPOLARITY(ipol) ((ipol) << 1) //st has a range of 0-1

// CTRL REGISTER 4 USER-INPUT OPTIONS
#define ACC_CTRL_REG4_INTENPULSE(p) ((p) << 3) //p has a range of 0-1

// CTRL REGISTER 5 USER-INPUT OPTIONS
#define ACC_CTRL_REG5_INTCFGPULSE(pin) ((pin) << 3) //pin has a range of 0-1

// XYZ_DATA CONFG USER-INPUT OPTIONS
#define ACC_GDYNAMIC(g) ((g) << 0) //pin has a range of 0-2
//#define ACC_HPF_OUT(hpf)((hpf) << 3) // pin has a range of 0-1 : Not required for now

// PULSE_CONFG SETTINGS
#define ACC_PULSECFG_ZSINGLEPULSE(zspefe)((zspefe)<<3) //range is 0-1
#define ACC_PULSECFG_EVENTLATCH(ele)((ele)<<6)         //range is 0-1
// PULSE

//HF-FILTER-CUTOFF USER OPTIONS: FOR PULSE INTERRUPT CONFIG: Pulse_HPF_BYP & Pulse_LPF-Enable
#define ACC_PULSELPFMODE(lpf)((lpf) << 3)

/******************************************************************************
 * Typedef
 *****************************************************************************/
typedef enum
{
    ACC_MODE_STANDBY,
    ACC_MODE_ACTIVE,
} acc_mode_t;

typedef enum
{
    ACC_SELFTEST_DISABLE,
    ACC_SELFTEST_ENABLE,
} acc_selftest_t;

typedef enum
{
    INT_ACTIVE_LOW,
    INT_ACTIVE_HIGH,
} acc_intpolarity_t;

typedef enum
{
    INTIMP_DISABLE,
    INTIMP_ENABLE,
} acc_intenimpulse_t;

typedef enum
{
    PIN2,
    PIN1,
} acc_intcfgpulse_t;

typedef enum
{
    TWOG_RANGE,
    FOURG_RANGE,
	EIGHTG_RANGE,
} acc_gsetting_t;
/*
typedef enum
{
    HPF_DISABLE,
    HPF_ENABLE,
} acc_hpfenable_t; */

typedef enum
{
    EVENTFLAG_DISABLE,
    EVENTFLAG_ENABLE,
} acc_zsinglepulse_t;

typedef enum
{
    FLAGLATCH_DISABLE,
    FLAGLATCH_ENABLE,
} acc_pulseflaglatch_t;

typedef enum
{
    PULSE_LPF_DISABLE,
    PULSE_LPF_ENABLE,
} acc_pulselpf_t;

// can define more if required for testing: sensitivity is 0.063g per count
typedef enum
{
    TWOG = 0x20, // Sensitivity: 2g/0.063 = 32 = 0x20
    THREEG = 0x30,
	FOURG = 0x40,
	FIVEG = 0x4F,
	SIXG= 0x5F,
	SEVENG = 0x6F,
	EIGHTG = 0x7F,
} acc_pulse_zthreshold_t;

typedef enum
{
    TMLT_FIVEMS = 0x02, // Sensitivity: 2.5ms per step count For Normal Mode 800Hz sampling rate: same for PULS_WIN
	TMLT_TENMS = 0x04,
	TMLT_FIFTEENMG = 0x06,
	TMLT_TWENTYMS = 0x08,
	TMLT_TWENTYFIVEMS= 0x0A,
	TMLT_THIRTYMS = 0x0C,
	TMLT_FORTYMS = 0x10,
	TMLT_FIFTYMS = 0x14,
} acc_pulse_tmlt_t;


typedef enum
{
    TMLY_FIVEMS = 0x02, // Sensitivity: 2.5ms per step count For Normal Mode 800Hz sampling rate: same for PULS_WIN
	TMLY_TENMS = 0x04,
	TMLY_FIFTEENMS = 0x06,
	TMLY_TWENTYMS = 0x08,
	TMLY_TWENTYFIVEMS= 0x0A,
	TMLY_THIRTYMS = 0x0C,
	TMLY_FORTYMS = 0x10,
	TMLY_FIFTYMS = 0x14,
	TMLY_HUNDREDMS = 0x28,
	TMLY_TWOHUNDREDMS = 0x50,
	TMLY_THREEHUNDREDMS = 0x78,
} acc_pulse_latency_t;



#endif /* MACROS_H_ */

