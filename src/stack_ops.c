
#include <atmel_start.h>
#include "common.h"
#include "itoa.h"
#include "serial_io.h"
#include <string.h>
#include "stack_ops.h"

int stack[STKSIZE];
int p = 0;

/* push n to top of data stack */
void push(int n) {
  p = (p + 1)& STKMASK;
  TOS = n;
}

/* return top of stack */
int pop(void) {
  int n = TOS;
  p = (p - 1)& STKMASK;
  return n;
}

/* destructively display top of stack, decimal */
void dot(void) {
    int len_pr_strn = 0;
    int popped = pop();
    pr_strn[0] = (uint32_t) "\0";
    input_intgr = popped;
    itoa (input_intgr, pr_strn);
    len_pr_strn = strlen(pr_strn);
    io_write(io, (uint8_t *)pr_strn, len_pr_strn);
    _spc(); // print formatting/spacing
}

/* copy TOS to TOS-1 */
void dup(void) {
    int n = pop();
    push(n); push(n);
}

/* discard top of stack */
void drop(void) {
    pop();
}
void oblit(void) { }
void back(void) { }
void swap(void) { }
void over(void) { }

/* reverse display the whole stack, decimal */
void dotsRp(void) { // dotsR, primitive
    u_dotsR();
}

/* bottom of the stack dot */
void bosDot(void) {
    uBackDotBack();
}

/* display whole stack, decimal */
void dotsC(void) {
    for (int i = 0; i < STKSIZE; i++) dot();
}

void dotsR(void) { // .sr  (newly available to the interpreter)
    dotsC();
}

void dotS(void) { // .s  (in the interpreter)
    dotsRp();
}

void ainsu_rstack(void) {
    rev_coll_stack();
}
