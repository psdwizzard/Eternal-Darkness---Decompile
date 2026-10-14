/* Reset and clear the memory region. */

extern void *memset(void *dest, int value, unsigned long size);

extern void * volatile lbl_8064DC1C;
extern volatile unsigned int lbl_8064DC18;
extern void * volatile lbl_8064DC14;
extern volatile unsigned int lbl_8064DC10;

void fn_8022F890(void) {
    void *base = lbl_8064DC1C;
    unsigned int size = lbl_8064DC18;

    lbl_8064DC14 = base;
    lbl_8064DC10 = size;
    memset(base, 0, size);
}
