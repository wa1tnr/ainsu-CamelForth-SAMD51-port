#include "itoacf.h"

void itoa_write(void) { // int to ascii, with write (printf substitute)

    int len_pr_strn = 0;   // DECLARE LENGTH VARIABLE
    int popped             // DECLARE DATA INPUT VARIABLE
                = *psp++ ; // AND POPULATE IT FROM THE STACK

//  pr_strn[0] = (uint32_t) "\0"; // ZERO INIT GLOBAL STRING

//  extern char print_string[stack_buffer_length];

    print_string[0] = (uint32_t) "\0"; // ZERO INIT GLOBAL STRING

    input_integer = popped; // COPY DATA INTO GLOBAL
    cmf_itoa(input_integer, print_string); // SCAN

    len_pr_strn = strlen(print_string); // LENGTH OF OUTPUT
    io_write(io, (uint8_t *)print_string, len_pr_strn); // WRITE OUTPUT TO USART
    _spc(); // print formatting/spacing

}


/*
void itoacfp(void) { // int to ascii, with write (printf substitute)
    int len_pr_strn = 0;
    // int popped = pop();
    int popped = *psp++ ;
    pr_strn[0] = (uint32_t) "\0";
    input_integer = popped;
    cmf_itoa(input_integer, pr_strn);
    len_pr_strn = strlen(pr_strn);
    io_write(io, (uint8_t *)pr_strn, len_pr_strn);
    _spc(); // print formatting/spacing
}
*/
