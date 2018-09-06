// Thu Sep  6 03:55:27 UTC 2018
// On branch camel_forth_to_stand_alone

#include <atmel_start.h>
// #include "pins.h"
// #include "clock_gen_OE.h"
#include "usart_gateway.h"

int main(void)
{
    /* Initializes MCU, drivers and middleware */
    atmel_start_init();
    SystemInit();
    // 8 MHz CPU
    // pins_setup(); // initialize GPIO D13 PA17

    // clock_gen_oe(); // clock generator 0 output enable

    USART_0_example_upper_camelforth(); // atmel start USART driver

    /* Replace with your application code */
    USART_0_example_lower_camelforth();

    while (1) {
    }
}
