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

extern s32 oggpack_read(void *, s32);
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

Mapping *mapping0_unpack(Source *source, void *stream) {
    Mapping *map = fn_8022F780(sizeof(Mapping));
    Data *data = source->data;
    s32 i;

    memset(map, 0, sizeof(Mapping));

    if (oggpack_read(stream, 1) != 0) {
        map->submaps = oggpack_read(stream, 4) + 1;
    } else {
        map->submaps = 1;
    }

    if (oggpack_read(stream, 1) != 0) {
        map->couplingSteps = oggpack_read(stream, 8) + 1;
        for (i = 0; i < map->couplingSteps; i++) {
            s32 mag;
            s32 ang;
            mag = oggpack_read(stream, ilog2(source->channels));
            map->couplingMag[i] = mag;
            ang = oggpack_read(stream, ilog2(source->channels));
            map->couplingAng[i] = ang;
            if (mag < 0 || ang < 0 || mag == ang || mag >= (s32)source->channels ||
                ang >= (s32)source->channels) {
                goto error;
            }
        }
    }

    if (oggpack_read(stream, 2) > 0) {
        goto error;
    }

    if (map->submaps > 1) {
        for (i = 0; i < (s32)source->channels; i++) {
            map->chmuxlist[i] = oggpack_read(stream, 4);
            if (map->chmuxlist[i] >= map->submaps) {
                goto error;
            }
        }
    }

    for (i = 0; i < map->submaps; i++) {
        map->floorsubmap[i] = oggpack_read(stream, 8);
        if (map->floorsubmap[i] >= data->dCount) {
            goto error;
        }
        map->residuesubmap[i] = oggpack_read(stream, 8);
        if (map->residuesubmap[i] >= data->aCount) {
            goto error;
        }
        map->timesubmap[i] = oggpack_read(stream, 8);
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
