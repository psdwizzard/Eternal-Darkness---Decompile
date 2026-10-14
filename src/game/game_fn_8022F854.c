/* Initialize and clear a memory region. */

extern void *memset(void *dest, int value, unsigned long size);

extern void * volatile lbl_8064DC1C;
extern volatile unsigned int lbl_8064DC18;
extern void * volatile lbl_8064DC14;
extern volatile unsigned int lbl_8064DC10;
extern volatile unsigned int lbl_8064DC08;

void fn_8022F854(void *base, unsigned int size) {
    lbl_8064DC1C = base;
    lbl_8064DC18 = size;
    lbl_8064DC14 = base;
    lbl_8064DC10 = size;
    lbl_8064DC08 = size;
    memset(base, 0, size);
}
