typedef unsigned char u8;
typedef unsigned int u32;

extern void* memcpy(void* destination, const void* source, unsigned long size);
extern void DCFlushRangeNoSync(void* address, u32 size);
extern void ICInvalidateRange(void* address, u32 size);
extern u8 __OSSystemCallVectorStart[];
extern u8 __OSSystemCallVectorEnd[];

void __OSInitSystemCall(void) {
    register void* vector;
    register const u8* start;
    register const u8* end;
    register void* destination;

    /* ASM: lis/addi materialize the vector and its source bounds after
     * the prologue; C hoists and reorders these independent addresses. */
    asm {
        lis r5, 0x8000
        lis r4, __OSSystemCallVectorStart@ha
        lis r3, __OSSystemCallVectorEnd@ha
        addi vector, r5, 0xC00
        addi end, r3, __OSSystemCallVectorEnd@l
        addi start, r4, __OSSystemCallVectorStart@l
    }
    /* ASM: or (mr) copies the vector address; C emits addi with zero. */
    asm { or destination, vector, vector }
    memcpy(destination, start, end - start);
    DCFlushRangeNoSync(vector, 0x100);
    /* ASM: sync completes the cache flush; C has no hardware barrier operation. */
    asm { sync }
    ICInvalidateRange(vector, 0x100);
}
