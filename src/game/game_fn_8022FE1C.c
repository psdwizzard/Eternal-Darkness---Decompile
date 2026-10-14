#include "src/game/types.h"

typedef struct DecoderConfig DecoderConfig;
typedef struct DecoderWrapper DecoderWrapper;
typedef struct Backend Backend;

typedef struct DecoderState {
    DecoderConfig *config;
    void *work;
    void *history;
    s32 size;
    s32 half;
    s32 pcm_read;
    u8 pad18[8];
    s32 zero20;
    s32 zero24;
    u8 pad28[4];
    s32 center;
    s32 granulepos;
    s32 sequence;
    u8 pad38[0x10];
    Backend *backend;
} DecoderState;

/* Keep the non-prototype declaration compatible with the two-argument
 * definition while preserving the original call's unused mode argument. */
extern s32 fn_8022FE60();

s32 fn_8022FE1C(DecoderState *state, DecoderWrapper *wrapper)
{
    fn_8022FE60(state, wrapper, 0);
    state->pcm_read = -1;
    state->granulepos = -1;
    state->sequence = -1;
    return 0;
}
