typedef int s32;

typedef struct ResidueLook ResidueLook;
typedef struct LevelTable LevelTable;

extern s32 **fn_80234D70(void *vb, ResidueLook *look, float **in, s32 ch,
                       s32 (*classify)(float *, s32, ResidueLook *, s32, s32));
extern int fn_80234E9C(float *in, s32 n, LevelTable **tablep, s32 count, s32 value);

/* Compact active channels before classifying their residue partitions. */
s32 **fn_80234890(void *vb, ResidueLook *look, register float **in, s32 *nonzero, s32 ch)
{
    s32 i;
    register float **channel;
    register s32 used = 0;
    /* ASM: mr and li retain the source pointer and destination byte offset
     * in registers; C strength reduction changes the indexed stores. */
    asm {
        mr channel, in
        li r8, 0
    }
    for (i = 0; i < ch; i++) {
        if (*nonzero) {
            register float *samples = *channel;
            used++;
            /* ASM: stwx and addi retain the indexed destination addressing
             * that C strength reduction replaces with a moving pointer. */
            asm {
                stwx samples, in, r8
                addi r8, r8, 4
            }
        }
        nonzero++;
        channel++;
    }
    if (used) {
        register s32 count;
        register s32 (*classify)(float *, s32, ResidueLook *, s32, s32);
        /* ASM: lis, addi and mr form the callback and channel arguments
         * together; a C call changes the final register move to addi. */
        asm {
            lis count, fn_80234E9C@ha
            addi classify, count, fn_80234E9C@l
            mr count, used
        }
        return fn_80234D70(vb, look, in, count, classify);
    }
    return 0;
}
