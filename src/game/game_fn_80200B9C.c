typedef unsigned int u32;

extern void *fn_8020080C(void);
extern void *memcpy(void *, const void *, u32);

void fn_80200B9C(void *source)
{
    void *copy = fn_8020080C();

    if (copy != 0) {
        memcpy(copy, source, 0x20);
    }
}
