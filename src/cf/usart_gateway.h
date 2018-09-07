
extern struct io_descriptor *io;

#define timeStamp(t,l) \
    "Fri Sep  7 02:53:11 UTC 2018\n\n", 32

// current target branch:
#define branchStamp(b,l) \
    "On branch progressive_Edits_ac-    ", 35

/*
    "On branch camel_forth_to_stand_alone    ", 40
*/

/*
#define branchStamp(b,l) "master    +CamelForth    ", 25
*/

extern void bold_italics_white(void);
extern void italics(void);
extern void bold_italics(void);
extern void n1uro_italics(void);
extern void fg_white_force_bold(void);
extern void fg_white(void);
extern void fg_yellow(void);
extern void bg_black(void);
extern void bg_blue(void);
extern void bg_red(void);
extern void color_reset(void);
extern void color_bold(void); // experimental
extern void _que(void);
extern void _ok(void);
extern void _bkbar(void); // broken bar
extern void _spc(void);
extern void _cr(void); // line 113
extern void cr(void);
extern void USART_0_example_upper_camelforth(void);
extern void USART_0_example_lower_camelforth(void);
