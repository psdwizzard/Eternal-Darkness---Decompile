#include "src/game/types.h"

/* libvorbis vorbis_info_clear-style teardown of the codec setup:
 * free each floor/residue/mapping param through its type's handler,
 * then free the codebooks. Mirrors the unpack in fn_80232078. */

typedef struct Data {
    u8 pad0[8];
    s32 entryCount;
    s32 dCount;
    s32 aCount;
    s32 bCount;
    s32 cCount;
    s32 objectCount;
    void *entries[64];
    s32 dTypes[64];
    void *dObjects[64];
    s32 aTypes[64];
    void *aObjects[64];
    s32 bTypes[64];
    void *bObjects[64];
    s32 cTypes[64];
    void *cObjects[64];
    void *objects[256];
} Data;

typedef struct Handler Handler;
struct Handler {
    void *method0;
    void *read;
    void *method8;
    void *methodC;
    void (*free)(void *, Handler *);
};

typedef struct Source {
    u8 pad[0x1c];
    Data *data;
} Source;

extern void fn_802357B4(void *);
extern Handler *lbl_8064C4CC[];
extern Handler *lbl_80300160[];
extern Handler *lbl_8064C4D4[];

void fn_802326F8(Source *source) {
    Data *data = source->data;
    Handler **handlers;
    Handler *handler;
    s32 i;
    Data *cursor;

    if (data == 0) {
        return;
    }

    cursor = data;
    handlers = lbl_8064C4D4;
    for (i = 0; i < data->dCount; i++) {
        handler = handlers[cursor->dTypes[0]];
        handler->free(cursor->dObjects[0], handler);
        cursor = (Data *)((char *)cursor + 4);
    }

    cursor = data;
    handlers = lbl_8064C4CC;
    for (i = 0; i < data->bCount; i++) {
        handler = handlers[cursor->bTypes[0]];
        handler->free(cursor->bObjects[0], handler);
        cursor = (Data *)((char *)cursor + 4);
    }

    cursor = data;
    handlers = lbl_80300160;
    for (i = 0; i < data->cCount; i++) {
        handler = handlers[cursor->cTypes[0]];
        handler->free(cursor->cObjects[0], handler);
        cursor = (Data *)((char *)cursor + 4);
    }

    {
        s32 j;
        Data *book;

        book = data;
        for (j = 0; j < data->objectCount; j++) {
            if (book->objects[0] != 0) {
                fn_802357B4(book->objects[0]);
            }
            book = (Data *)((char *)book + 4);
        }
    }
}
