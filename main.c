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

/* */ /* */ /* */ /* */

int main(void)
{
    /* Initializes MCU, drivers and middleware */
    atmel_start_init();
    SystemInit();
    // 8 MHz CPU
    pins_setup(); // initialize GPIO D13 PA17

    clock_gen_oe(); // clock generator 0 output enable

    // USART_0_example_upper(); // initialize
    USART_0_example_upper_camelforth(); // atmel start USART driver

    /* Replace with your application code */
    USART_0_example_lower();

    while (1) {
    }
}
