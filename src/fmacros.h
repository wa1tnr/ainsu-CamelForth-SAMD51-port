/* fmacros.h */

#define uBackDotBack() \
    back(); \
    dot(); \
    back();

#define u_dotsR() \
    for (int i = 8; i > 0; i--) { \
        uBackDotBack() \
    }

#define bk_bk_dr() \
    back(); \
    back(); \
    drop();

#define swdr() \
    swap(); \
    drop();

#define swdr_four() \
    for (int mi = 4; mi > 0; mi--) { \
        swap(); drop();  \
    }

#define drp_four() \
    for (int mj = 4; mj > 0; mj--) { \
        drop();  \
    }

#define swdr_three() \
    for (int mk = 3; mk > 0; mk--) { \
        swap(); drop();  \
    }

#define bkbkdr_three() \
    for (int mk = 3; mk > 0; mk--) { \
        bk_bk_dr(); \
    }

#define rev_coll_stack() \
    swdr_four();    \
    swdr_four();    \
    drop();         \
    swdr_four()     \
    swap();         \
    drp_four()      \
    swdr_four()     \
    drp_four()      \
    swdr_three()    \
    bkbkdr_three()  \
    swdr();         \
    swap();         \
    bk_bk_dr();     \
    swap();


/* from: dump.c

 40 void new_ascii_emit(void) {
 44     rbyte = rbyte + 0x30; // normalize (in ASCII) for 0-9
 56     io_write(io, (uint8_t *) char_r, 1);
 57 }
*/

/* u_emit - cpp macro for emit() */
// ( n -- )

#define u_emit() \
    uint32_t  rbyte = 0; \
    int       char_r   =  '0'; \
    char      *cbyte; \
    rbyte = pop(); \
    cbyte = (char*) &rbyte; \
    int df = (uint32_t) cbyte; \
    char *dfbyte = (char*) df; \
    char_r = (int)dfbyte; \
    io_write(io, (uint8_t *) char_r, 1);


#define next_char_prog_a() \
    back(); back();   swap();  drop();  plus();    emit();

#define reload_prog_a() \
    drop(); back();    back(); back(); \
    swap(); drop();    swap(); drop();

#define print_reloaded_buffer_prog_a() \
    for (int i = 7; i > 0; i--) { \
        emit(); \
    } \
    drop(); \
    cr(); cr();

// expects 1 2 3 4 5 6 7 and some value - 64 here -- on the stack
// emits first four characters - program is capable to emit an
// additional three chars (seven total).

// Call next_char_prog_a() as required.
#define fmac_prog_a()                                           \
                                       ainsu_rstack();   back();      \
                      swap();           plus();    emit();      \
    back(); back();   swap();           plus();    emit();      \
    back(); back();   swap();  drop();  plus();    emit();      \
    next_char_prog_a();            \
    next_char_prog_a();            \
    next_char_prog_a();            \
    next_char_prog_a();            \
    cr(); \
    reload_prog_a();               \
    print_reloaded_buffer_prog_a() \
    print_reloaded_buffer_prog_a() \
    print_reloaded_buffer_prog_a()

/*

\ nice working program - without responses

  1 2 3 4   5 6 7  64        rstack back  .s
               swap          plus   emit  .s
  back back    swap          plus   emit  .s

  back back    swap drop     plus   emit  .s
  back back    swap drop     plus   emit  .s
  back back    swap drop     plus   emit  .s
  back back    swap drop     plus   emit  .s

  back back    swap drop     plus   emit  .s

  drop back    back back                  .s
  swap drop    swap drop                  .s

  emit A   emit B   emit C   emit D   cr
  emit E   emit F   emit G   drop         .s

  emit A   emit B   emit C   emit D   cr
  emit E   emit F   emit G   drop         .s

  emit A   emit B   emit C   emit D   cr
  emit E   emit F   emit G   drop

\ loads the stack with ints 1-7
\ and a seed (offset) value for ASCII (65 - 1 = 64)
\ 65 is ascii 'A'  (66 is 'B' and so on)

\ prints them in sequence
\ reuses them when it gets to the end

\ wastes possibly the least amount of stack space
\ possible, given the initial 'additive' method
\ to populate the stack with a sequence of ASCII
\ characters.

*/

#define uback back();

#define backfour() \
    uback uback uback uback

/* end fmacros.h */
