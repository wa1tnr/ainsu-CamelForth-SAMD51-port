/* nyb_stack.c */
#include "serial_io.h"
#include "common.h"
#include <string.h>
int nyb_stack = 0;
int rbyte_n = 0;
char byte_r;
void ascii_emit_n(void) { }
uint8_t* parsed_low_n(void) { return (uint8_t *) rbyte_n; }
uint8_t* parsed_hi_n(void) { return (uint8_t *) rbyte_n; }
int COUNTER_N = 0;
uint8_t* ndump(void) { // nybble dump 
    uint32_t test_byte = 0xc0ffeeca; // sample int to place into ram 
    return (uint8_t *)test_byte;
}
