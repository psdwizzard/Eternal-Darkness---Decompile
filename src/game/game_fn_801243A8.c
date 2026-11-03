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

static inline void loadWeight(register const float* source)
{
    /* ASM: psq_l loads both weight lanes; scalar C cannot load a float pair. */
    asm { psq_l f2, 0(source), 0, 0 }
}

void fn_801243A8(SkinModel* model)
{
    s32 i;
    SkinGroup* group = model->groups;
    register f32* out = lbl_804F3650[0].m;
    f32 one = lbl_80650114;
    f32 weightPair[2];

/* Paired-single operations keep both matrix elements in each FPR. */
/* ASM: psq_l loads two float lanes, which scalar C cannot express. */
#define LOAD_PAIR(value, source, offset) asm { psq_l value, offset(source), 0, 0 }
/* ASM: psq_st stores both float lanes, which scalar C cannot express. */
#define STORE_PAIR(value, destination, offset) asm { psq_st value, offset(destination), 0, 0 }
/* ASM: ps_muls0 scales both lanes; C has no paired-single arithmetic. */
#define SCALE_PAIR(result, value, scale) asm { ps_muls0 result, value, scale }
/* ASM: ps_madds0 fuses both lane operations; scalar C cannot express this. */
#define ADD_PAIR(sum, value, scale) asm { ps_madds0 sum, value, scale, sum }

    /* f17-f24 hold the eight accumulated pairs. The odd scratch registers
     * hold source pairs, and loadWeight supplies the replicated weight in f2. */

    for (i = 0; i < model->count; i++) {
        s32 n;
        SkinWeight* w = &model->weights[group->first];
        f32 wt = w->weight;
        register f32* src = lbl_804F02F0[w->matrix].m;

        n = group->count - 2;

        if (one == wt) {
            LOAD_PAIR(f17, src, 0);
            LOAD_PAIR(f18, src, 8);
            LOAD_PAIR(f19, src, 16);
            LOAD_PAIR(f20, src, 24);
            LOAD_PAIR(f21, src, 32);
            LOAD_PAIR(f22, src, 40);
            LOAD_PAIR(f23, src, 48);
            LOAD_PAIR(f24, src, 56);
        } else {
            weightPair[0] = wt;
            weightPair[1] = wt;
            LOAD_PAIR(f0, src, 0);
            loadWeight(weightPair);
            SCALE_PAIR(f17, f0, f2);
            LOAD_PAIR(f3, src, 8);
            SCALE_PAIR(f18, f3, f2);
            LOAD_PAIR(f5, src, 16);
            SCALE_PAIR(f19, f5, f2);
            LOAD_PAIR(f7, src, 24);
            SCALE_PAIR(f20, f7, f2);
            LOAD_PAIR(f9, src, 32);
            SCALE_PAIR(f21, f9, f2);
            LOAD_PAIR(f11, src, 40);
            SCALE_PAIR(f22, f11, f2);
            LOAD_PAIR(f13, src, 48);
            SCALE_PAIR(f23, f13, f2);
            LOAD_PAIR(f15, src, 56);
            SCALE_PAIR(f24, f15, f2);
        }
        w++;
        if (group->count > 1) {
            do {
                wt = w->weight;
                src = lbl_804F02F0[w->matrix].m;
                weightPair[0] = wt;
                weightPair[1] = wt;
                LOAD_PAIR(f0, src, 0);
                loadWeight(weightPair);
                LOAD_PAIR(f3, src, 8);
                LOAD_PAIR(f5, src, 16);
                ADD_PAIR(f17, f0, f2);
                LOAD_PAIR(f7, src, 24);
                ADD_PAIR(f18, f3, f2);
                LOAD_PAIR(f9, src, 32);
                ADD_PAIR(f19, f5, f2);
                LOAD_PAIR(f11, src, 40);
                ADD_PAIR(f20, f7, f2);
                LOAD_PAIR(f13, src, 48);
                ADD_PAIR(f21, f9, f2);
                LOAD_PAIR(f15, src, 56);
                ADD_PAIR(f22, f11, f2);
                ADD_PAIR(f23, f13, f2);
                ADD_PAIR(f24, f15, f2);
                w++;
            } while (n-- != 0);
        }
        STORE_PAIR(f17, out, 0);
        STORE_PAIR(f18, out, 8);
        STORE_PAIR(f19, out, 16);
        STORE_PAIR(f20, out, 24);
        STORE_PAIR(f21, out, 32);
        STORE_PAIR(f22, out, 40);
        STORE_PAIR(f23, out, 48);
        STORE_PAIR(f24, out, 56);
        out += 12;
        group++;
    }
    DCFlushRange(lbl_804F3650, model->count * sizeof(Mtx34));
}

#undef LOAD_PAIR
#undef STORE_PAIR
#undef SCALE_PAIR
#undef ADD_PAIR
