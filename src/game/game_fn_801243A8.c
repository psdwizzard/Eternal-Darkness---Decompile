typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;

typedef struct SkinWeight {
    f32 weight;
    u16 matrix;
    u16 pad;
} SkinWeight;

typedef struct SkinGroup {
    u16 count;
    u16 first;
} SkinGroup;

typedef struct SkinModel {
    u8 pad00[0xA];
    u16 count;
    u8 pad0C[0x20];
    SkinGroup* groups;
    u8 pad30[0x1C];
    SkinWeight* weights;
} SkinModel;

/* 3x4 matrices; the blend reads/writes 16 floats (8 float pairs) per matrix,
 * spilling one row into the following entry, which is later overwritten. */
typedef struct Mtx34 {
    f32 m[12];
} Mtx34;

extern Mtx34 lbl_804F02F0[];
extern Mtx34 lbl_804F3650[];
extern f32 lbl_80650114;

extern void DCFlushRange(void*, u32);

/* Paired values stay in floating-point registers from load to store. */
static inline float loadPair0(register const f32* source)
{
    register float value;
    /* ASM: psq_l loads two float lanes; C has no paired-single type. */
    asm { psq_l value, 0(source), 0, 0 }
    return value;
}

static inline float loadPair1(register const f32* source)
{
    register float value;
    /* ASM: psq_l loads two float lanes; C has no paired-single type. */
    asm { psq_l value, 8(source), 0, 0 }
    return value;
}

static inline float loadPair2(register const f32* source)
{
    register float value;
    /* ASM: psq_l loads two float lanes; C has no paired-single type. */
    asm { psq_l value, 16(source), 0, 0 }
    return value;
}

static inline float loadPair3(register const f32* source)
{
    register float value;
    /* ASM: psq_l loads two float lanes; C has no paired-single type. */
    asm { psq_l value, 24(source), 0, 0 }
    return value;
}

static inline float loadPair4(register const f32* source)
{
    register float value;
    /* ASM: psq_l loads two float lanes; C has no paired-single type. */
    asm { psq_l value, 32(source), 0, 0 }
    return value;
}

static inline float loadPair5(register const f32* source)
{
    register float value;
    /* ASM: psq_l loads two float lanes; C has no paired-single type. */
    asm { psq_l value, 40(source), 0, 0 }
    return value;
}

static inline float loadPair6(register const f32* source)
{
    register float value;
    /* ASM: psq_l loads two float lanes; C has no paired-single type. */
    asm { psq_l value, 48(source), 0, 0 }
    return value;
}

static inline float loadPair7(register const f32* source)
{
    register float value;
    /* ASM: psq_l loads two float lanes; C has no paired-single type. */
    asm { psq_l value, 56(source), 0, 0 }
    return value;
}

static inline float scalePair(register float value, register float scale)
{
    register float result;
    /* ASM: ps_muls0 scales both lanes by lane zero, unavailable in C. */
    asm { ps_muls0 result, value, scale }
    return result;
}

static inline float addScaledPair(register float value, register float scale, register float sum)
{
    /* ASM: ps_madds0 performs a fused multiply-add on both float lanes. */
    asm { ps_madds0 sum, value, scale, sum }
    return sum;
}

static inline void storePair0(register f32* destination, register float value)
{
    /* ASM: psq_st stores both float lanes; scalar C cannot retain lane one. */
    asm { psq_st value, 0(destination), 0, 0 }
}

static inline void storePair1(register f32* destination, register float value)
{
    /* ASM: psq_st stores both float lanes; scalar C cannot retain lane one. */
    asm { psq_st value, 8(destination), 0, 0 }
}

static inline void storePair2(register f32* destination, register float value)
{
    /* ASM: psq_st stores both float lanes; scalar C cannot retain lane one. */
    asm { psq_st value, 16(destination), 0, 0 }
}

static inline void storePair3(register f32* destination, register float value)
{
    /* ASM: psq_st stores both float lanes; scalar C cannot retain lane one. */
    asm { psq_st value, 24(destination), 0, 0 }
}

static inline void storePair4(register f32* destination, register float value)
{
    /* ASM: ps_mr and psq_st copy and store both lanes through the paired
     * scratch register; C has no operation preserving both float lanes. */
    asm {
        ps_mr f15, value
        psq_st f15, 32(destination), 0, 0
    }
}

void fn_801243A8(SkinModel* model)
{
    s32 i;
    SkinGroup* group = model->groups;
    f32* out = lbl_804F3650[0].m;
    f32 one = lbl_80650114;
    register float a0, a1, a2, a3, a4, a5, a6, a7;
    f32 weightPair[2];

    for (i = 0; i < model->count; i++) {
        s32 n = group->count - 2;
        SkinWeight* w = &model->weights[group->first];
        f32 wt = w->weight;
        f32* src = lbl_804F02F0[w->matrix].m;
        register float scale;
        register float b0;

        if (one == wt) {
            a0 = loadPair0(src);
            a1 = loadPair1(src);
            a2 = loadPair2(src);
            a3 = loadPair3(src);
            a4 = loadPair4(src);
            a5 = loadPair5(src);
            a6 = loadPair6(src);
            a7 = loadPair7(src);
        } else {
            weightPair[0] = wt;
            weightPair[1] = wt;
            b0 = loadPair0(src);
            scale = loadPair0(weightPair);
            a0 = scalePair(b0, scale);
            a1 = scalePair(loadPair1(src), scale);
            a2 = scalePair(loadPair2(src), scale);
            a3 = scalePair(loadPair3(src), scale);
            a4 = scalePair(loadPair4(src), scale);
            a5 = scalePair(loadPair5(src), scale);
            a6 = scalePair(loadPair6(src), scale);
            a7 = scalePair(loadPair7(src), scale);
        }
        w++;
        if (group->count > 1) {
            do {
                wt = w->weight;
                src = lbl_804F02F0[w->matrix].m;
                weightPair[0] = wt;
                weightPair[1] = wt;
                b0 = loadPair0(src);
            scale = loadPair0(weightPair);
                a0 = addScaledPair(b0, scale, a0);
                a1 = addScaledPair(loadPair1(src), scale, a1);
                a2 = addScaledPair(loadPair2(src), scale, a2);
                a3 = addScaledPair(loadPair3(src), scale, a3);
                a4 = addScaledPair(loadPair4(src), scale, a4);
                a5 = addScaledPair(loadPair5(src), scale, a5);
                a6 = addScaledPair(loadPair6(src), scale, a6);
                a7 = addScaledPair(loadPair7(src), scale, a7);
                w++;
            } while (n-- != 0);
        }
        storePair0(out, a0);
        storePair1(out, a1);
        storePair2(out, a2);
        storePair3(out, a3);
        storePair4(out, a4);
        storePair0(out + 10, a5);
        storePair0(out + 12, a6);
        storePair0(out + 14, a7);
        out += 12;
        group++;
    }
    DCFlushRange(lbl_804F3650, model->count * sizeof(Mtx34));
}
