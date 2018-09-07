// Wed Aug 22 18:00:54 UTC 2018
/* wa1tnr - August, 2018 LGPL v2.1 */

// On branch KM_converser_aa-
//     On branch xKM_converser_aa-br-bb-

#include <atmel_start.h>
// #include "common.h"
// #include "driver_examples.h"
// #include "serial_io.h"
#include "usart_gateway.h"

char ch[0]; // holds an 8-bit keystroke
int read_ln = 0; // how many chars were read

/* Terminal Input Buffer for interpreter */
// char tib[maxtib];

void _USART_read(void) { // hardware implementation-dependent keystroke reader
    // getKey:
    // io_read(io,  (uint8_t *)tib, 1); // 1  is length
    read_ln = io_read(io,  (uint8_t *)ch, 1); // 1  is length
}

void getKey(void) { // hardware-independent wrapper
    _USART_read();
}

void queryKey(void) {
    _USART_read();
}
