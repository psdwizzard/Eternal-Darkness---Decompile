typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Entry80104980 {
    u8 pad00[4];
    u16 *data;
    u16 columns;
    u16 rows;
    u16 stride;
    u8 pad0E[0x1A];
    u16 width;
    u8 pad2A[0xE];
} Entry80104980;

typedef struct Work80104980 {
    int index;
    int *current;
    u16 *start;
    int *end;
    u16 value0;
    u16 value1;
    u8 byte14;
} Work80104980;

extern void fn_80104980(Entry80104980 *, int *, int, Work80104980 *, int);

void fn_80104A54(register Entry80104980 *entries, int index, register int *output)
{
    Work80104980 work;
    register Entry80104980 *entry;
    register u16 **data;
    register int row;
    register int outputStride;
    register int width;
    register int columns;

    entry = &entries[index];
    /* ASM: addi keeps the data-field address live across the decoder call;
     * MWCC otherwise folds it into both loads, unlike the retail code. */
    asm { addi data, entry, 4 }
    {
        register int rawWidth = entry->width;

        columns = entry->columns;

        {
            register int stride = entry->stride;
            register u16 *initial;
            register int callWidth;
            register int *callOutput;
            register int callColumns;
            /* ASM: mr and addi keep the distinct width copy and retail move
             * encoding, which the compiler coalesces or replaces with mr. */
            asm {
                mr width, rawWidth
                addi callWidth, width, 0
            }
            work.index = index;
            /* ASM: slwi keeps stride scaling before argument setup; C schedules
             * this independent calculation after the argument copies. */
            asm { slwi stride, stride, 1 }
            /* ASM: addi preserves the output copy; MWCC emits mr for C copies. */
            asm { addi callOutput, output, 0 }
            /* ASM: lwz retains the data load between the retail argument copies;
             * the compiler delays the equivalent C field access. */
            asm { lwz initial, 4(entry) }
            /* ASM: addi preserves the column copy; MWCC emits mr for C copies. */
            asm { addi callColumns, columns, 0 }
            /* ASM: slwi keeps the output stride calculation at its retail position;
             * C schedules it with the other pointer arithmetic. */
            asm { slwi outputStride, rawWidth, 2 }
            work.current = (int *)initial;
            work.start = initial;
            work.end = (int *)((u8 *)initial + stride);
            fn_80104980(entries, callOutput, callWidth, &work, callColumns);
        }
    }
    output = (int *)((u8 *)output + outputStride);
    work.current = (int *)*data;

    row = entry->rows - 2;
    while (row > 0) {
        {
            register Entry80104980 *callEntries;
            register int *callOutput;
            register int callWidth;
            register int callColumns;
            /* ASM: addi preserves the retail argument-copy encoding;
             * MWCC emits mr for equivalent C pointer and integer copies. */
            asm {
                addi callEntries, entries, 0
                addi callOutput, output, 0
                addi callWidth, width, 0
                addi callColumns, columns, 0
            }
            fn_80104980(callEntries, callOutput, callWidth, &work, callColumns);
        }
        output = (int *)((u8 *)output + outputStride);
        row--;
    }

    work.end = (int *)work.start;
    {
        register Entry80104980 *callEntries;
        register int *callOutput;
        register int callWidth;
        register int callColumns;
        /* ASM: addi preserves the retail argument-copy encoding;
         * MWCC emits mr for equivalent C pointer and integer copies. */
        asm {
            addi callEntries, entries, 0
            addi callOutput, output, 0
            addi callWidth, width, 0
            addi callColumns, columns, 0
        }
        fn_80104980(callEntries, callOutput, callWidth, &work, callColumns);
    }
}
