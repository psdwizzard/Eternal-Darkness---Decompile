/* Build the residue decoder's stage books and partition decode map. */
#include "src/game/types.h"

typedef struct ResidueCodebook {
    s32 dim;
    u8 pad04[0x18];
} ResidueCodebook;

typedef struct ResidueSetup {
    u8 pad00[0x0C];
    ResidueCodebook *books;
} ResidueSetup;

typedef struct ResidueState {
    u8 pad00[0x48];
    ResidueSetup *setup;
} ResidueState;

typedef struct ResidueMode {
    u8 pad00[0x0C];
    s32 mapping;
} ResidueMode;

typedef struct ResidueInfo {
    s32 begin;
    s32 end;
    s32 grouping;
    s32 partitions;
    s32 groupbook;
    u32 secondstages[64];
    s32 booklist[256];
} ResidueInfo;

typedef struct ResidueLook {
    ResidueInfo *info;
    s32 mapping;
    s32 parts;
    s32 stages;
    ResidueCodebook *fullbooks;
    ResidueCodebook *phrasebook;
    ResidueCodebook ***partbooks;
    s32 partvals;
    s32 **decodemap;
    u8 pad24[0x0C];
    s32 thresholds[17];
} ResidueLook;

extern void *fn_8022F780(s32 size);
/* The retail wrapper forwards both floating-point arguments to pow. */
extern double pow();
extern double rint(double value);

ResidueLook *res0_look(ResidueState *state, ResidueMode *mode, ResidueInfo *info) {
    s32 i;
    s32 samples;
    s32 acc;
    ResidueSetup *setup;
    s32 j;
    s32 dim;
    s32 maxstage;
    ResidueLook *look;

    look = fn_8022F780(sizeof(ResidueLook));
    setup = state->setup;
    acc = 0;
    maxstage = 0;

    look->info = info;
    look->mapping = mode->mapping;
    look->parts = info->partitions;
    look->fullbooks = setup->books;
    look->phrasebook = setup->books + info->groupbook;
    dim = look->phrasebook->dim;
    look->partbooks = fn_8022F780(look->parts * sizeof(*look->partbooks));

    /* The packed book list advances only for stages whose bits are set. */
    for (j = 0; j < look->parts; j++) {
        u32 mask = info->secondstages[j];
        s32 stages = 0;
        while (mask) {
            mask >>= 1;
            stages++;
        }
        if (stages) {
            if (stages > maxstage) maxstage = stages;
            look->partbooks[j] = fn_8022F780(stages * sizeof(**look->partbooks));
            for (i = 0; i < stages; i++) {
                if (info->secondstages[j] & (1U << i)) {
                    s32 book = *(s32 *)((u8 *)info->booklist + acc);
                    acc += sizeof(*info->booklist);
                    look->partbooks[j][i] = setup->books + book;
                }
            }
        }
    }
    look->partvals = rint(pow((float)look->parts, (float)dim));
    look->stages = maxstage;
    look->decodemap = fn_8022F780(look->partvals * sizeof(*look->decodemap));
    /* Expand each partition value into base-parts digits. */
    for (j = 0; j < look->partvals; j++) {
        s32 val = j;
        s32 mult = look->partvals / look->parts;
        look->decodemap[j] = fn_8022F780(dim * sizeof(**look->decodemap));
        i = 0;
        if (dim > 0) {
            /* Process eight dimensions per block, then the remaining digits. */
            if (dim > 8) {
                s32 blocks = (u32)(dim - 8 + 7) >> 3;
                do {
                    s32 index = i;
                    i += 8;
                    {
                        s32 parts = look->parts;
                        s32 deco = val / mult;
                        look->decodemap[j][index + 0] = deco;
                        val -= deco * mult;
                        mult /= parts;
                    }
                    {
                        s32 parts = look->parts;
                        s32 deco = val / mult;
                        look->decodemap[j][index + 1] = deco;
                        val -= deco * mult;
                        mult /= parts;
                    }
                    {
                        s32 parts = look->parts;
                        s32 deco = val / mult;
                        look->decodemap[j][index + 2] = deco;
                        val -= deco * mult;
                        mult /= parts;
                    }
                    {
                        s32 parts = look->parts;
                        s32 deco = val / mult;
                        look->decodemap[j][index + 3] = deco;
                        val -= deco * mult;
                        mult /= parts;
                    }
                    {
                        s32 parts = look->parts;
                        s32 deco = val / mult;
                        look->decodemap[j][index + 4] = deco;
                        val -= deco * mult;
                        mult /= parts;
                    }
                    {
                        s32 parts = look->parts;
                        s32 deco = val / mult;
                        look->decodemap[j][index + 5] = deco;
                        val -= deco * mult;
                        mult /= parts;
                    }
                    {
                        s32 parts = look->parts;
                        s32 deco = val / mult;
                        look->decodemap[j][index + 6] = deco;
                        val -= deco * mult;
                        mult /= parts;
                    }
                    {
                        s32 parts = look->parts;
                        s32 deco = val / mult;
                        look->decodemap[j][index + 7] = deco;
                        val -= deco * mult;
                        mult /= parts;
                    }
                } while (--blocks > 0);
            }
            if (i < dim) {
                s32 remaining = dim - i;
                do {
                    s32 parts = look->parts;
                    s32 deco = val / mult;
                    look->decodemap[j][i] = deco;
                    val -= deco * mult;
                    mult /= parts;
                    i++;
                } while (--remaining > 0);
            }
        }
    }
    samples = (info->end - info->begin) / info->grouping;
    {
        s32 count = 2;
        i = 0;
        do {
            s32 index = i;
            i += 8;
            look->thresholds[index + 0] = samples * (index + 1) / 16;
            look->thresholds[index + 1] = samples * (index + 2) / 16;
            look->thresholds[index + 2] = samples * (index + 3) / 16;
            look->thresholds[index + 3] = samples * (index + 4) / 16;
            look->thresholds[index + 4] = samples * (index + 5) / 16;
            look->thresholds[index + 5] = samples * (index + 6) / 16;
            look->thresholds[index + 6] = samples * (index + 7) / 16;
            look->thresholds[index + 7] = samples * (index + 8) / 16;
        } while (--count > 0);
    }
    look->thresholds[i] = 9999999;
    return look;
}
