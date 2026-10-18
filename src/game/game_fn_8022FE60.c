#include "src/game/types.h"

extern void *memset(void *, int, unsigned long);
extern void *fn_8022F780(s32 size);
typedef struct MdctLookup MdctLookup;
typedef struct DecodeAux DecodeAux;
typedef struct StaticCodebook StaticCodebook;
typedef struct Codebook {
    s32 dim;
    s32 entries;
    StaticCodebook *c;
    float *valuelist;
    s32 *codelist;
    DecodeAux *decode_tree;
    s32 dec_maxlength;
} Codebook;
extern void mdct_init(MdctLookup *lookup, s32 n);
extern s32 vorbis_book_init_decode(Codebook *dst, StaticCodebook *source);
typedef struct MapEntry {
    u8 pad00[0x0C];
    s32 mode;
} MapEntry;

typedef struct DecoderConfig {
    s32 first;
    s32 second;
    s32 modes;
    u8 pad0C[0x10];
    s32 book_count;
    MapEntry *mode_param[64];
    s32 map_type[64];
    void *map_param[64];
    u8 pad320[0x600];
    StaticCodebook *books[256];
} DecoderConfig;

typedef struct Backend {
    u8 pad00[4];
    MdctLookup **mdct0;
    MdctLookup **mdct1;
    Codebook *codebooks;
    u8 pad10[4];
    s32 shift;
    void **maps;
} Backend;

typedef struct DecoderWrapper DecoderWrapper;

typedef struct DecoderState {
    DecoderWrapper *config;
    s16 **work;
    s16 **history;
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

struct DecoderWrapper {
    u8 pad00[4];
    s32 channels;
    u8 pad08[0x14];
    DecoderConfig *config;
};


typedef struct Mode {
    u8 pad00[8];
    void *(*func)(DecoderState *, MapEntry *, void *);
} Mode;
extern Mode *_mapping_P[];

/* Initialize the Vorbis synthesis transforms, codebooks, PCM and mappings. */
s32 _vds_shared_init(register DecoderState *state_arg, register DecoderWrapper *wrapper_arg)
{
    Backend *backend;
    register DecoderConfig *config;
    register DecoderWrapper *wrapper;
    register DecoderState *state;
    register DecoderConfig *book_cursor;
    register s32 book_offset;
    u32 n;
    register s32 bits;
    /* ASM: or (mr) retains register copies; C emits addi with zero. */
    asm {
        or wrapper, wrapper_arg, wrapper_arg
        or state, state_arg, state_arg
    }
    config = wrapper_arg->config;

    memset(state_arg, 0, 0x4C);
    backend = fn_8022F780(0x1C);
    /* ASM: li initializes the bit count before the state stores;
     * C schedules it between them. */
    asm { li bits, 0 }
    state->backend = backend;
    state->config = wrapper;
    {
        n = config->modes;
        while (n > 1) {
            n >>= 1;
            bits++;
        }
        backend->shift = bits;
    }
    backend->mdct0 = fn_8022F780(4);
    backend->mdct1 = fn_8022F780(4);
    *backend->mdct0 = fn_8022F780(0x14);
    *backend->mdct1 = fn_8022F780(0x14);
    mdct_init(*backend->mdct0, config->first);
    mdct_init(*backend->mdct1, config->second);
    backend->codebooks = fn_8022F780(config->book_count * 0x1C);
    {
        s32 i;
        /* ASM: or (mr) preserves the book_cursor copy instead of addi with zero. */
        asm { or book_cursor, config, config }
        i = 0;
        book_offset = 0;
        for (; i < config->book_count; i++) {
            vorbis_book_init_decode((Codebook *)((u8 *)backend->codebooks + book_offset),
                        book_cursor->books[0]);
            book_cursor = (DecoderConfig *)((u8 *)book_cursor + 4);
            book_offset += 0x1C;
        }
    }
    state->size = 0xC00;
    state->work = fn_8022F780(wrapper->channels * 4);
    state->history = fn_8022F780(wrapper->channels * 4);
    {
        s32 i;
        for (i = 0; i < wrapper->channels; i++)
            state->work[i] = fn_8022F780(state->size * 2);
    }
    state->zero20 = 0;
    state->zero24 = 0;
    {
        register s32 half;
        register u32 blocksize = config->second;
        half = blocksize >> 31;
        /* ASM: add preserves the sign-first operand order; C commutes it. */
        asm { add half, half, blocksize }
        state->center = half >> 1;
    }
    state->half = state->center;
    {
        register s32 i;
        register DecoderConfig *cursor;
        register s32 offset;
        register Mode **handlers;
        register u32 table_hi;
        void *maps = fn_8022F780(config->modes * 4);
        /* ASM: li/lis preserve initialization before the allocation is stored;
         * C hoists the loop zero and table base into a different order. */
        asm {
            li i, 0
            lis table_hi, _mapping_P@ha
        }
        backend->maps = maps;
        /* ASM: or/ori/addi retain the cursor and offset dependencies and
         * table-base order. C folds the copies into immediate assignments;
         * ori also prevents this compiler from folding the offset move. */
        asm {
            or cursor, config, config
            ori offset, i, 0
            addi handlers, table_hi, _mapping_P@l
        }
        for (; i < config->modes; i++) {
            MapEntry *entry = cursor->mode_param[0];
            *(void **)((u8 *)backend->maps + offset) = handlers[config->map_type[entry->mode]]->func(
                state, entry, config->map_param[entry->mode]);
            cursor = (DecoderConfig *)((u8 *)cursor + 4);
            offset += 4;
        }
    }
    return 0;
}
