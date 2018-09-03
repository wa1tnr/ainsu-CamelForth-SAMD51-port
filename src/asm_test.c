/* asm_test.c */
void asm_test(void) {
    for (volatile int i=1; i<2; i++) { // trick compiler not to optimize out
        asm("nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;");
    }
}
