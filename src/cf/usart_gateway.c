// Fri Sep  7 02:10:29 UTC 2018
// On branch progressive_Edits_ab-

/* wa1tnr - September, 2018 LGPL v2.1 */

// Thu Sep  6 03:55:27 UTC 2018
// On branch camel_forth_to_stand_alone

#include "driver_init.h"
#include "getKey_cf.h" // SAMD51 dependency for now (06 SEP 2018)

extern void camelforth(void); // pivotal - do not omit!

struct io_descriptor *io;

void usart_sync_get_desc(void) {
    usart_sync_get_io_descriptor(&USART_0, &io);
}

void usart_sync_enbl(void) {
    usart_sync_enable(&USART_0);
}

void bg_black(void)   { // background black
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\064\060", 2); // 40 - blue black
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

void bg_red(void)    { // background red
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\064\061", 2); // 41 - red bg
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

void bg_blue(void)   { // background blue
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\064\064", 2); // 44 - blue bg
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

void color_reset(void) {  // reset color
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\060", 1);     // 0
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

void color_bold(void) {
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\061", 1);     // 1
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

void fg_white_force_bold(void) {
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\060", 1);     // 0
    io_write(io, (uint8_t *)"\073", 1);     // ;  semicolon
    io_write(io, (uint8_t *)"\061", 1);     // 1
    io_write(io, (uint8_t *)"\073", 1);     // ;  semicolon
    io_write(io, (uint8_t *)"\063\067", 2); // 37 - white  fg
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

void fg_white(void) {
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\063\067", 2); // 37 - white  fg
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

void fg_magenta(void) {
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\063\065", 2); // 35 - yellow fg
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

void bold_italics_white(void) { // specify ^[[1;03;37m
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\061", 1);     // 1 // bold flag?
    io_write(io, (uint8_t *)"\073", 1);     // ;  semicolon
    io_write(io, (uint8_t *)"\060\063", 2); // 03 - some name for this one
    io_write(io, (uint8_t *)"\073", 1);     // ;  semicolon
    io_write(io, (uint8_t *)"\063\067", 2); // 37 - white  fg
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

void italics(void) {
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\060\063", 2); // 03 - some name for this one
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

void bold_italics(void) {
    color_bold();
    italics();
}

void n1uro_italics(void) {
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\060\063", 2); // 03 - some name for this one
    io_write(io, (uint8_t *)"\073", 1);     // ;  semicolon
    io_write(io, (uint8_t *)"\063\066", 2); // 36 - cyan maybe thunderstorm comin'
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

/* italics - NOTES

   2^1 probably raises italics.
   2^0 when set raises bold.

    io_write(io, (uint8_t *)
    io_write(io, (uint8_t *)
*/

/* SOURCE string: "   [03;36m " */

void fg_yellow(void) { // foreground yellow
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\063\063", 2); // 33 - yellow fg
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

uint8_t *buf;

void _spc(void) {
    io_write(io, (uint8_t *) " ",         1);
}

void _que(void) {
    io_write(io, (uint8_t *) "? ",         1);
    _spc();
}

void _ok(void) {
    // if (crlfstate == -1) {
        io_write(io, (uint8_t *) " ok\r\n", 5); // echo TODO \r\n on some terminals
        // crlfstate = 0;
    // }
}

#define HAS_FILTER_AINSU
#undef HAS_FILTER_AINSU
#ifdef HAS_FILTER_AINSU
void filter(void) {

    /* stanza -- control H */
    if ((uint8_t) *buf == 8) { // Control H
        io_write(io, (uint8_t *) "\010",  1);
        io_write(io, (uint8_t *) " ",  1);
        return;
    }

    /* stanza -- rubout */
    if ((uint8_t) *buf == 127) { // Control H
        io_write(io, (uint8_t *) "\010",  1);
        io_write(io, (uint8_t *) " ",  1);
        io_write(io, (uint8_t *) "\010",  1); // rubout needs to travel to the left here
        return;
    }

    /* stanza -- CR */
    if ((uint8_t) *buf == 13) { // CR or 0x0d
        io_write(io, (uint8_t *) "\015",  1); // 0x0d
        io_write(io, (uint8_t *) "\012",  1); // 0x0a // your terminal may want differently
        return;
    }
}
#endif // #ifdef HAS_FILTER_AINSU

void _bkbar(void) {
    io_write(io, (uint8_t *) "|",         1);
}

void _cr(void) {
    io_write(io, (uint8_t *) "\r\n",         2);
}

void cr(void) {
    _cr();
}

void USART_0_example_upper_camelforth(void) {
    usart_sync_get_desc();
    usart_sync_enbl();
    _cr();
}

/*
void dispatcher_simple_int(void) {
    if (number() == 911) { // help
        io_write(io, (uint8_t *) "\r\n\r\n     911 - help\r\n",  21);
        io_write(io, (uint8_t *) "     211 - reboot (warm)\r\n",  26);
    }
    if (number() == 211) _warm();
}
*/

void USART_0_example_lower_camelforth(void) {
    _cr();

    io_write(io, (uint8_t *)
        "Program is configured for 38400 bps speed.\n",              43);
    io_write(io, (uint8_t *)
        "Target MCU board is Adafruit Metro M4 Express.\n",          47);

    color_reset();
    io_write(io, (uint8_t *)
        "UART pins TX and RX used with CP2104 bridge.\n",            45);

    io_write(io, (uint8_t *) branchStamp(t,l));
    io_write(io, (uint8_t *) timeStamp(t,l));


    bg_blue();
    fg_white();
    bg_red();
    io_write(io, (uint8_t *)  "  ainsuForth MTX  ",  18);
    color_reset();
    io_write(io, (uint8_t *)  "\n\n",                 2);
    color_reset();

    bg_black();
    bg_black();

    fg_yellow(); // color it!


    while(-1) { // endless loop
        camelforth(); // right here is where CamelForth is invoked!
        io_write(io, (uint8_t *) "\n", 1);
        italics();
        fg_magenta();
        io_write(io, (uint8_t *) "USART_0_example_lower_camelforth() .. completes.\n", 49); // is alive
        color_reset(); // no italics
        io_write(io, (uint8_t *) "\n", 1);
    }
}
