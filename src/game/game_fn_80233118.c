#include "src/game/types.h"

typedef struct Data {
    u8 pad0[0x10];
    s32 dCount;
    s32 aCount;
    s32 bCount;
} Data;

typedef struct Source {
    u8 pad0[4];
    u32 channels;
    u8 pad8[0x14];
    Data *data;
} Source;

typedef struct Mapping {
    s32 submaps;
    s32 chmuxlist[256];
    s32 floorsubmap[16];
    s32 residuesubmap[16];
    s32 timesubmap[16];
    u8 pad4C4[8];
    s32 couplingSteps;
    s32 couplingMag[256];
    s32 couplingAng[256];
} Mapping;

extern s32 fn_8022E868(void *, s32);
extern void *fn_8022F780(s32);
extern void *memset(void *, int, unsigned long);

static inline s32 ilog2(u32 v) {
    s32 n = 0;
    while (v > 1) {
        v >>= 1;
        n++;
    }
    return n;
}

Mapping *fn_80233118(Source *source, void *stream) {
    Mapping *map = fn_8022F780(sizeof(Mapping));
    Data *data = source->data;
    s32 i;

    memset(map, 0, sizeof(Mapping));

    if (fn_8022E868(stream, 1) != 0) {
        map->submaps = fn_8022E868(stream, 4) + 1;
    } else {
        map->submaps = 1;
    }

    if (fn_8022E868(stream, 1) != 0) {
        map->couplingSteps = fn_8022E868(stream, 8) + 1;
        for (i = 0; i < map->couplingSteps; i++) {
            s32 mag;
            s32 ang;
            mag = fn_8022E868(stream, ilog2(source->channels));
            map->couplingMag[i] = mag;
            ang = fn_8022E868(stream, ilog2(source->channels));
            map->couplingAng[i] = ang;
            if (mag < 0 || ang < 0 || mag == ang || mag >= (s32)source->channels ||
                ang >= (s32)source->channels) {
                goto error;
            }
        }
    }

    if (fn_8022E868(stream, 2) > 0) {
        goto error;
    }

    if (map->submaps > 1) {
        for (i = 0; i < (s32)source->channels; i++) {
            map->chmuxlist[i] = fn_8022E868(stream, 4);
            if (map->chmuxlist[i] >= map->submaps) {
                goto error;
            }
        }
    }

    for (i = 0; i < map->submaps; i++) {
        map->floorsubmap[i] = fn_8022E868(stream, 8);
        if (map->floorsubmap[i] >= data->dCount) {
            goto error;
        }
        map->residuesubmap[i] = fn_8022E868(stream, 8);
        if (map->residuesubmap[i] >= data->aCount) {
            goto error;
        }
        map->timesubmap[i] = fn_8022E868(stream, 8);
        if (map->timesubmap[i] >= data->bCount) {
            goto error;
        }
    }
    return map;

error:
    if (map != 0) {
        memset(map, 0, sizeof(Mapping));
    }
    return 0;
}
