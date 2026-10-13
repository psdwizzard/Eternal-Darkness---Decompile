#include "src/game/types.h"

extern void *memset(void *, int, unsigned long);
extern void *fn_8022F780(s32 size);
extern void fn_802342DC(void *lookup, u32 n);
extern void fn_8023570C(void *dst, s32 source);
extern void lbl_8064C4D4[];

typedef struct DecoderConfig {
    s32 first;
    s32 second;
    u32 blocksizes;
    u8 pad0C[0x10];
    s32 channels;
    u8 pad20[0x900];
    s32 *books;
} DecoderConfig;

typedef struct Backend {
    u8 pad00[4];
    void *mdct0;
    void *mdct1;
    void *windows;
    u8 pad10[4];
    s32 shift;
    void *maps;
} Backend;

typedef struct DecoderState {
    DecoderConfig *config;
    void *work;
    void *history;
    s32 size;
    s32 half;
    u8 pad14[0x0C];
    s32 zero20;
    s32 zero24;
    u8 pad28[4];
    s32 center;
    u8 pad30[0x18];
    Backend *backend;
} DecoderState;

typedef struct DecoderWrapper {
    u8 pad00[4];
    u32 channels;
    u8 pad08[0x14];
    DecoderConfig *config;
} DecoderWrapper;



typedef struct MapEntry {
    u8 pad00[0x0C];
    s32 mode;
} MapEntry;

typedef struct Mode {
    u8 pad00[8];
    u32 (*func)(void *, void *, s32, void *);
} Mode;

s32 fn_8022FE60(DecoderState *state, DecoderWrapper *wrapper)
{
    Backend *backend;
    s32 i;
    u32 *output;
    u32 *input;
    u32 n;
    DecoderConfig *config = wrapper->config;

    memset(state, 0, 0x4C);
    backend = fn_8022F780(0x1C);
    state->backend = backend;
    state->config = (DecoderConfig *)wrapper;
    n = config->blocksizes;
    i = 0;
    while (n > 1) {
        n >>= 1;
        i++;
    }
    backend->shift = i;
    backend->mdct0 = fn_8022F780(4);
    backend->mdct1 = fn_8022F780(4);
    *(void **)backend->mdct0 = fn_8022F780(0x14);
    *(void **)backend->mdct1 = fn_8022F780(0x14);
    fn_802342DC(*(void **)backend->mdct0, config->first);
    fn_802342DC(*(void **)backend->mdct1, config->second);
    backend->windows = fn_8022F780(config->channels * 0x1C);
    {
        u8 *p = (u8 *)config;
        s32 *dest = backend->windows;
        s32 off = 0;
        for (i = 0; i < config->channels; i++) {
            fn_8023570C((u8 *)dest + off, *(s32 *)(p + 0x920));
            p += 4;
            off += 0x1C;
        }
    }
    state->size = 0xC00;
    state->work = fn_8022F780(wrapper->channels * 4);
    state->history = fn_8022F780(wrapper->channels * 4);
    for (i = 0; i < wrapper->channels; i++)
        ((void **)state->work)[i] = fn_8022F780(state->size * 2);
    state->zero20 = 0;
    state->zero24 = 0;
    state->center = config->second / 2;
    state->half = state->center;
    backend->maps = fn_8022F780(config->blocksizes * 4);
    input = (u32 *)config;
    output = backend->maps;
    for (i = 0; i < config->blocksizes; i++) {
        MapEntry *entry = (MapEntry *)((u8 *)config + input[8] * 4);
        Mode *mode = ((Mode **)lbl_8064C4D4)[entry->mode];
        *output++ = mode->func(state, *(void **)((u8 *)input + 0x20), *(s32 *)((u8 *)entry + 0x220), mode);
        input++;
    }
    return 0;
}
