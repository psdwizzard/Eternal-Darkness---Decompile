extern void *fn_8022F780(int size);
extern void *memcpy(void *destination, const void *source, unsigned int size);

/* Allocate and copy the fixed-size configuration. */
void *fn_80233614(const void *source) {
    void *copy = fn_8022F780(0xCD0);
    return memcpy(copy, source, 0xCD0);
}
