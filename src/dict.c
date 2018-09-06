// Fri Aug 31 01:48:14 UTC 2018
// On branch xKM_converser_d51-pp-

/* dict.c */

// previous:
// Thu Aug 30 20:51:14 UTC 2018
// On branch xKM_converser_d51-pp-

// Tue Aug 28 23:24:03 UTC 2018
// On branch xKM_converser_d51-kk-

#include "dict.h"
#include <string.h>
// #include "common.h"
// #include "getKey.h"
#include "serial_io.h"
#include "stack_ops.h"
#include "math.h"
#include "flashDict.h"
#include "warm.h"
// #include "dump.h"
#include "ascii_art.h"
#include "emit.h"
#include "fmacros.h" // forth macros
#include "programs.h"
#include "asm_test.h"

extern void camelforth(void);

int linelen = LLENGTH; // = 28

/* buffer required for strings read from flash */
// char namebuf[maxtib];

uint8_t* adrs_ram = 0;

/* demo ascii art */
NAMED(_aart, "aart");
void aart(void) {
    forth_ascii();
}

/* destructively display top of stack, decimal */
NAMED(_dott, ".");
void dott(void) {
    dot();
}

// const char x[]=y
const char _nop[2]=" \0";
void nop(void) { }

NAMED(_nopp, "nop");  // swapped _name with _nop
void nopp(void) { }

void help(void) {
    asm_test(); // test of almost empty asm function with multiple nop
    io_write(io, (uint8_t *) "    type 'words' instead of 'help'.\r\n\r\n",   39);
    io_write(io, (uint8_t *) "    8304 16 dump              \r\n\r\n",        34);
    io_write(io, (uint8_t *) "    1 2 3 4 5 6 7 64  prog_a    \r\n\r\n",      36);

    io_write(io, (uint8_t *) "    sram starts at        0x20000000\r\n",      38);
    io_write(io, (uint8_t *) "                           536870912  decimal.\r\n", 48);
    io_write(io, (uint8_t *) "    536870912  12288  dump ",                   27);
    io_write(io, (uint8_t *) "    will dump all of sram \r\n",                28);
    io_write(io, (uint8_t *) "\r\n\r\n    test of asm here as well. \r\n\r\n",        38);
}
                           // 123456789012345678901234567890123456789012345678901234567890
/*
     sram starts at        0x20000000  seven zero's or twenty million
                            536870912  decimal.
*/

/*
void dump(void) { // ( adrs lines --  )
    int popped = pop();
    for (int i= popped; i > 0; i--) {
        // adrs_ram = cdump();
        push(((uint32_t)adrs_ram) + 16); // address of the most recent line dumped
    }
}
*/

void words(void); // forward declaration // 28 Aug 22:35 UTC

/* look in stack_ops.c - for example - to find the
   definitions of most of the earliest dictionary
   entries referred to in the table found below. */

/* table of names and function addresses in flash */
// extern const entry dictionary[];
const entry dictionary[] = {
    { _nopp,      nopp   }, // just switched these 28 Aug 23:10 UTC
//  { _plus,      plus   },
//  { _emit,      emit   },
    { _cr_n,      cr     },
    { _dott,      dott   },
    { _dup,       dup    },
    { _drop,      drop   },
//  { _oblit,     oblit  },
//  { _back,      back   },
//  { _swap,      swap   },
//  { _over,      over   },
    { _dotS,      dotS   },
//  { _dotsR,     dotsR  },
//  { _multiply,  multiply },
//  { _subtract,  subtract },
//  { _add,       add    },
//  { _dump,      dump   },
    { _words,     words  },
    { _help,      help   },
    { _bosDot,    bosDot },
//  { _prog_a,    prog_a },
//  { _ainsu_rstack,    ainsu_rstack },
    { _aart,      aart   },
    { _camelforth,   camelforth },
    { _warm_,     _warm  },
    { _nop,       nop    }, // just switched these 28 Aug 23:10 UTC
};

/* Number of words in the dictionary */
const int entries = sizeof dictionary / sizeof dictionary[0];

/* Find a word in the dictionary, returning its position */
int locate(void) {
  for (int i = entries - 1; i >= 0; i--) {
    // strcpy(namebuf, dictionary[i].name);
    // if (!strcmp(tib, namebuf)) return i;
  }
  return LOCATE_BOUNDS_ERR ; // return 0;
}

/* Display all words in dictionary */
void words(void) { // 28 Aug 20:05 UTC
    int count_ln = 0; // count of line's length
    for (int i = entries - 2; i >= 0; i--) { // entries - 2 mask the 'nop' word which is a space
        // strcpy(namebuf, dictionary[i].name);
        // count_ln = count_ln + strlen(namebuf) + 1 ; // how long this line is, so far
        // io_write(io, (uint8_t *)namebuf, strlen(namebuf));
        _spc();
        if (count_ln > linelen) { // exceeded
            count_ln = 0; // reset
            _cr(); // newline
        }
    }
}
