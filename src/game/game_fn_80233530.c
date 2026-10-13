#include "src/game/types.h"

typedef struct Handler {
    void *method0;
    void *method4;
    void *(*create)(void *, void *, void *);
    void *methodC;
    void *method10;
    void (*free)(void *);
} Handler;

typedef struct Layout {
    s32 count;
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

/* Release each submap's three lookup objects through their handlers. */
void fn_80233530(Instance *inst) {
    s32 offset;
    s32 i;

    if (inst != 0) {
        for (i = 0, offset = 0; i < inst->layout->count; offset += 4, i++) {
            (*(Handler **)((char *)inst->aHandlers + offset))->free(
                *(void **)((char *)inst->aInstances + offset));
            (*(Handler **)((char *)inst->bHandlers + offset))->free(
                *(void **)((char *)inst->bInstances + offset));
            (*(Handler **)((char *)inst->cHandlers + offset))->free(
                *(void **)((char *)inst->cInstances + offset));
        }
    }
}
