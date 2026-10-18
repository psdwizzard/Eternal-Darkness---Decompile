#include "src/game/types.h"

typedef struct Data {
    u8 pad0[0x320];
    s32 aTypes[64];
    void *aObjects[64];
    s32 bTypes[64];
    void *bObjects[64];
    s32 cTypes[64];
    void *cObjects[64];
} Data;

typedef struct Handler Handler;
struct Handler {
    void *method0;
    void *method4;
    void *(*create)(void *, void *, void *);
};

typedef struct Source {
    u8 pad0[4];
    s32 value;
    u8 pad8[0x14];
    Data *data;
} Source;

typedef struct Layout {
    s32 count;
    u8 pad4[0x400];
    s32 aIndex[16];
    s32 bIndex[16];
    s32 cIndex[16];
} Layout;

typedef struct Instance {
    void *owner;
    Layout *layout;
    void **aInstances;
    void **bInstances;
    void **cInstances;
    u8 pad14[8];
    Handler **aHandlers;
    Handler **bHandlers;
    Handler **cHandlers;
    s32 value;
    u8 pad2C[4];
} Instance;

extern void *fn_8022F780(s32);
extern Handler *_time_P[];
extern Handler *_floor_P[];
extern Handler *_residue_P[];

Instance *mapping0_look(Source **ctx, void *owner, Layout *layout) {
    Layout *cursor;
    s32 i;
    Instance *inst;
    Data *data;
    Source *source;

    source = *ctx;
    data = source->data;
    inst = fn_8022F780(sizeof(Instance));
    inst->layout = layout;
    inst->owner = owner;
    inst->aInstances = fn_8022F780(layout->count * 4);
    inst->bInstances = fn_8022F780(layout->count * 4);
    inst->cInstances = fn_8022F780(layout->count * 4);
    inst->aHandlers = fn_8022F780(layout->count * 4);
    inst->bHandlers = fn_8022F780(layout->count * 4);
    inst->cHandlers = fn_8022F780(layout->count * 4);
    cursor = layout;
    for (i = 0; i < layout->count; i++) {
        s32 a = cursor->aIndex[0];
        s32 b = cursor->bIndex[0];
        s32 c = cursor->cIndex[0];
        inst->aHandlers[i] = _time_P[data->aTypes[a]];
        inst->aInstances[i] = inst->aHandlers[i]->create(ctx, owner, data->aObjects[a]);
        inst->bHandlers[i] = _floor_P[data->bTypes[b]];
        inst->bInstances[i] = inst->bHandlers[i]->create(ctx, owner, data->bObjects[b]);
        inst->cHandlers[i] = _residue_P[data->cTypes[c]];
        inst->cInstances[i] = inst->cHandlers[i]->create(ctx, owner, data->cObjects[c]);
        cursor = (Layout *)((char *)cursor + 4);
    }
    inst->value = source->value;
    return inst;
}
