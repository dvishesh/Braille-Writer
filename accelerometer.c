/*
===============================================================================
 Name        : accelerometer.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>
// TODO: insert other include files here
#include "alib.h"
#include "alib1.h"
#include "alib2.h"


// TODO: insert other definitions and declarations here
#define SPEED_100KHz 100000

//global variables
volatile static int braillematrix[6] = {0}; //initializing matrix to 0

static void i2c_app_init(I2C_ID_T id, int speed);
void gpioint_init(void);
static void i2c_set_mode(I2C_ID_T id, int polling);

int main(void) {

#if defined (__USE_LPCOPEN)
#if !defined(NO_BOARD_LIB)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif

    // TODO: insert code here
    i2c_app_init(I2C0, SPEED_100KHz);
    i2c_app_init(I2C1, SPEED_100KHz);
    i2c_app_init(I2C2, SPEED_100KHz);
    //acc_init ();
    acc1_init ();
    acc2_init ();
    Chip_GPIO_Init(LPC_GPIO);
    Chip_GPIOINT_Init(LPC_GPIOINT);
    gpioint_init();


   // Force the counter to be placed into memory
   // volatile static int i = 0 ;

    static int16_t z1=0;
    static int16_t z2=0;
    static int16_t z3=0;

    float acc_Gvalue1 = 0.0;
    float acc_Gvalue2 = 0.0;
    float acc_Gvalue3 = 0.0;

    int8_t whoami1=0;
    int8_t whoami2=0;
    int8_t whoami3=0;

    uint8_t threshold_value1;
    uint8_t threshold_value2;
    uint8_t threshold_value3;

    uint8_t time_limit1 = 0;
    uint8_t time_limit2 = 0;
    uint8_t time_limit3 = 0;

    uint8_t time_latency1 = 0;
    uint8_t time_latency2 = 0;
    uint8_t time_latency3 = 0;

    while(1)
        {
    	//Checking interrupt settings
    	threshold_value1= Get_ZPULSETHRESHOLD();
    	threshold_value2= Get_ZPULSETHRESHOLD1();
    	threshold_value3= Get_ZPULSETHRESHOLD2();

    	time_limit1 = Get_ZPULSE_TMLIMIT();
    	time_limit2 = Get_ZPULSE_TMLIMIT1();
    	time_limit3 = Get_ZPULSE_TMLIMIT2();


    	time_latency1 = Get_ZPULSE_TMLATENCY();
    	time_latency2 = Get_ZPULSE_TMLATENCY1();
    	time_latency3 = Get_ZPULSE_TMLATENCY2();




        //acc_read(&z1);//reads 14 bit data: accelerometer in self-test mode
        acc1_read(&z2);
        acc2_read(&z3);


        //acc_Gvalue1 = acc_getGs(&z1);
        acc_Gvalue2 = acc1_getGs(&z2);
        acc_Gvalue3 = acc2_getGs(&z3);
    	}

        return 0 ;
}

    static void i2c_app_init(I2C_ID_T id, int speed)
    {
    	Board_I2C_Init(id);
    	/* Initialize I2C */
    	Chip_I2C_Init(id);
    	Chip_I2C_SetClockRate(id, speed);

    	// Set default mode to polling Note: Event Handling may be important in implementing I2C interface
    	i2c_set_mode(id, 1);
    }

    void gpioint_init(void)
    {

    	/* Configure GPIO interrupt pin as input */
    	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 24);

    	/* Configure the GPIO interrupt */
    	Chip_GPIOINT_SetIntRising(LPC_GPIOINT, 0, 1 << 24);

    	/* Enable interrupt in the NVIC */
    	NVIC_ClearPendingIRQ(EINT3_IRQn);
    	NVIC_EnableIRQ(EINT3_IRQn);
    }


    void EINT3_IRQHandler(void)
    {
    	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, 0, 1 << 24);
    	//braillematrix[0] = (braillematrix[0] == 0? 1 : 0);
    	Board_LED_Toggle(0);
    	ReadPulseSource(); //to clear INT1: can be disabled if ELE FLAG_LATCH is disabled
    }

    static void i2c_set_mode(I2C_ID_T id, int polling)
    {
    	if(!polling) {
    		Chip_I2C_SetMasterEventHandler(id, Chip_I2C_EventHandler);
    		if(id==I2C0)
    			{NVIC_EnableIRQ(I2C0_IRQn);}
    		if(id==I2C1)
    			{NVIC_EnableIRQ(I2C1_IRQn);}
    		if(id==I2C2)
    			{NVIC_EnableIRQ(I2C2_IRQn);}
    	} else {

    		if(id==I2C0)
    			{NVIC_DisableIRQ(I2C0_IRQn);}
    		if(id==I2C1)
    		    {NVIC_DisableIRQ(I2C1_IRQn);}
    		if(id==I2C2)
    		    {NVIC_DisableIRQ(I2C2_IRQn);}
    		Chip_I2C_SetMasterEventHandler(id, Chip_I2C_EventHandlerPolling);
    	}
    }
