// Thu Aug 30 20:51:14 UTC 2018
// On branch xKM_converser_d51-pp-

/* stack_ops.c */

/* from Shattuck's Tiny interpreter,
   similar to myforth's Standalone Interpreter
   This example code is in the public domain */

/* Data stack for parameter passing
   This "stack" is circular,
   like a Green Arrays F18A data stack,
   so overflow and underflow are not possible
   Number of items must be a power of 2 */

#include <atmel_start.h>
#include "common.h"
#include "itoa.h"
#include "serial_io.h"
#include <string.h>
#include "stack_ops.h"

// const int STKSIZE = 8;
// #define STKSIZE 8

// const int STKMASK = 7;
// #define STKMASK 7

int stack[STKSIZE];
int p = 0;

/* TOS is Top Of Stack */
// #define TOS stack[p]

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

/* obliterate drop - remove trace of TOS */
void oblit(void) {
    pop();
    push(0); // any value to oblit is fine
    back();
    pop();
    pop();
}

/* recover dropped stack item */
void back(void) {
    for (int i = 1; i < STKSIZE; i++) drop();
}

/* exchange top two stack items */
void swap(void) {
    int a;
    int b;
    a = pop();
    b = pop();
    push(a);
    push(b);
}

/* copy second on stack to top */
void over(void) {
    int a;
    int b;
    a = pop();
    b = pop();
    push(b);
    push(a);
    push(b);
}

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
    // dotsRp();
}

void dotS(void) { // .s  (in the interpreter)
    // dotsC();
    dotsRp();
}

void ainsu_rstack(void) {
    rev_coll_stack();
}

/*

  30 August 2018:

  THIS IS NOW OUTDATED.  SEE EARLIER CODE for correct context.

  Specifically, dotS() itself was changed, so the context (in
  which the below was writen) is now wrong.

  1. move the code here to stack_ops.c - or to a good
     place for that code, if it's not stack related.

     ex.

     The code from the dotS word is copied here to stack_ops.c:

         // display whole stack, decimal

         // NAMED(_dotS, ".s");
         void dotS(void) {
             for (int i = 0; i < STKSIZE; i++) dot();
         }

      This code was formerly held by dict.c before it was
      moved to stack_ops.c - the old copy is held there as
      a comment (for a while) and is then removed entirely,
      once proper program function is confirmed.

   2. Move it's NAMED macro applier into the correct .h file:

         // flashDict.h
         #include "dict_common.h"
         NAMED(_drop, "drop");
         NAMED(_back, "back");
         NAMED(_swap, "swap");
         NAMED(_dotS, ".s");

      For the time being, flashDict.h is the only correct file to
      hold these NAMED macro appliers (the macro is the original
      #define NAMED creation; the word 'applier' is used here to
      indicate a single 'creation' with many 'appliers'.

   3. Place a prototype in the corresponding .h file to where the
      main code went.  Use stack_ops.h in this example, since the
      main code for the dotS word was stored in stack_ops.c (after
      having moved it).

         // stack_ops.h
         .
         .
         extern void back(void);
         extern void swap(void);
         extern void dotS(void);

   4. (Obviously) update the dictionary with a new entry, as well:

      // dict.c

      // table of names and function addresses in flash

      const entry dictionary[] = {
          { _nop,       nop    },
          { _dott,      dott   },
          { _drop,      drop   },
          { _back,      back   },
          { _swap,      swap   },

          { _dotS,      dotS   },   <<== NEW

          { _nopp,      nopp   },
      };

*/
