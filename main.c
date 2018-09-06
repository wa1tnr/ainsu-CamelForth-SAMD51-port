// Wed Aug 29 04:49:35 UTC 2018
// On branch xKM_converser_d51-nn-

#include <atmel_start.h>
#include "pins.h"
#include "dump.h"
#include "nyb_stack.h"
#include "clock_gen_OE.h"
#include "common.h"
#include "itoa.h"
#include "stack_ops.h"
#include "usart_gateway.h"
#include "forth.h"

/*
void delays(void) { // delay some
    for (volatile int i=(3*21040); i>0; i--) {
    }
}
*/

/*
void blink_two(void) {
    PORT->Group[PORTA].OUTCLR.reg  = (uint32_t)(1 << 17); // PA17 //  0 13 pinwrite  // D13
    for (int blinks=2; blinks >0; blinks--) {
        PORT->Group[PORTA].OUTTGL.reg  = (uint32_t)(1 << 17); // PA17 //    13 pintoggle // D13
        delays();
    }
}
*/

/*
void ldelays(void) {
    for (int ie=7; ie >0; ie--) {
        delays();
    }
}
*/

void blink_awhile(void) {

    for (int iter=5; iter >0; iter--) {
/*
        blink_two();
*/
    }
}

int main(void)
{
    // rram, q, i
    uint8_t* rram = 0;
    int q = 0;


    int xec =  0; // false - no,  do not exec

    /* Initializes MCU, drivers and middleware */
    atmel_start_init();
    SystemInit();
    // 8 MHz CPU
    pins_setup(); // initialize GPIO D13 PA17

    clock_gen_oe(); // clock generator 0 output enable

    // USART_0_example_upper(); // initialize

    USART_0_example_upper_camelforth(); // atmel start USART driver

#define LOCAL_AINSU_OFFSET 8304 // 8304  $2070

    if (xec != 0) {
        push(LOCAL_AINSU_OFFSET);



        for (int jk =   0x7; jk > 0; jk--) { // 7 lines
            rram = cdump(); // dump.c
            push(((uint32_t)rram) + 16); // address of the most recent line dumped
        }

        q = (int)rram;
        if (q > 2)  q = 2;
        if (q < 1)  q = 2;
        for (volatile int i=-1; i<q; i++) {
/*
            blink_two();
*/

        }

    } // fi xec

    /* Replace with your application code */


    _cr(); // examples/driver_examples.c


    USART_0_example_lower();

    while (1) {
        toggle_d11();
    }
}
