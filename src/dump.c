/* dump.c */
#include "serial_io.h"
// #include "common.h"
#include "stack_ops.h"
#include <string.h>
#define LBOUND 0x1e70+0x100 // add 0x100 through the stack mechanism, later
// uint32_t  rbyte = 0;
// char      byte_r;
// void new_ascii_emit(void) { }
// uint8_t* parsed_low(void) { return (uint8_t *) rbyte; }
// uint8_t* parsed_hi(void) { return (uint8_t *) rbyte; }
// uint8_t* cdump(void) { int adptr = 0; return (uint8_t *)adptr; }
