typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Entry80104980 Entry80104980;
typedef struct BlockCursor BlockCursor;

typedef struct Work80104980 {
    int index;
    int *current;
    u16 *start;
    int *end;
    u16 value0;
    u16 value1;
    u8 byte14;
} Work80104980;

extern void IpicBlockDec(u8 *, u8 *, int, BlockCursor *, u16 *);

void IpicLineDec(register Entry80104980 *entries, register int *output, register int width,
                  register Work80104980 *work, register int columns)
{
    u16 *current;
    register int remaining;
    register Work80104980 *cursor;
    register int rowWidth;
    register int *destination;
    register Entry80104980 *sourceEntries;
    register Entry80104980 *callEntries;
    register int *callOutput;
    register int callWidth;
    register Work80104980 *callCursor;
    register u16 value;

    /* ASM: mr and addi keep the retail setup order and addi copies;
     * C turns the copies into mr instructions. */
    asm {
        mr cursor, work
        addi sourceEntries, entries, 0
        addi destination, output, 0
        addi rowWidth, width, 0
    }
    remaining = columns - 1;
    /* ASM: lwz and mr keep the initial load and the saved cursor live;
     * C loads through the incoming argument instead of the saved cursor. */
    asm {
        lwz work, 8(work)
        mr cursor, cursor
    }
    cursor->value0 = *(u16 *)work;
    cursor->byte14 = *(u8 *)cursor->start;

    while (remaining > 0) {
        /* ASM: lhz keeps the halfword load before argument setup;
         * C schedules the load after the copies. */
        asm { lhz value, 16(cursor) }
        /* ASM: addi copies the first two arguments before the halfword store;
         * C emits mr and moves them later. */
        asm {
            addi callEntries, sourceEntries, 0
            addi callOutput, destination, 0
        }
        cursor->value1 = value;
        /* ASM: addi copies the next two arguments after the halfword store;
         * C emits mr and moves them later. */
        asm {
            addi callWidth, rowWidth, 0
            addi callCursor, cursor, 0
        }
        current = cursor->start + 1;
        cursor->start = current;
        cursor->value0 = *current;
        IpicBlockDec((u8 *)callEntries, (u8 *)callOutput, callWidth,
                    (BlockCursor *)callCursor, current);
        destination++;
        remaining--;
    }

    /* ASM: lhz keeps the final halfword load before argument setup;
     * C schedules the load after the copies. */
    asm { lhz value, 16(cursor) }
    /* ASM: addi copies the first two final arguments before the store;
     * C emits mr and moves them later. */
    asm {
        addi callEntries, sourceEntries, 0
        addi callOutput, destination, 0
    }
    cursor->value1 = value;
    /* ASM: addi copies the next two final arguments after the store;
     * C emits mr and moves them later. */
    asm {
        addi callWidth, rowWidth, 0
        addi callCursor, cursor, 0
    }
    current = cursor->start;
    cursor->start = current + 3;
    IpicBlockDec((u8 *)callEntries, (u8 *)callOutput, callWidth,
                (BlockCursor *)callCursor, current);
    cursor->current++;
    cursor->end++;
}
