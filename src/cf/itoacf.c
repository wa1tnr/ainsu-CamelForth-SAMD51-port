#include "itoacf.h"

void itoacf(void) { // int to ascii, with write (printf substitute)
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
