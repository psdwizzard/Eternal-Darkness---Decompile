#include "src/game/types.h"

typedef struct Entry {
    s32 flags;
    s32 kind;
    s32 index;
    s32 target;
} Entry;

typedef struct Data {
    u8 pad0[8];
    s32 entryCount;
    s32 dCount;
    s32 aCount;
    s32 bCount;
    s32 cCount;
    s32 objectCount;
    Entry *entries[64];
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
    void *(*read)(void *, void *, Handler *);
};

typedef struct Source {
    u8 pad[0x1c];
    Data *data;
} Source;

extern s32 fn_8022E868(void *, s32);
extern void *fn_8022F780(s32);
extern s32 fn_802307F8(void *, void *);
extern void fn_802326F8(Source *);
extern void fn_800F8BAC(const char *, const char *, s32);
extern Handler *lbl_8064C4C8[];
extern Handler *lbl_8064C4CC[];
extern Handler *lbl_80300160[];
extern Handler *lbl_8064C4D4[];
extern const char lbl_806517EC;
extern const char lbl_806517F0;

s32 fn_80232078(Source *source, void *stream) {
    Data *data;

    if (source->data == 0) {
        return -0x81;
    }
    data = source->data;

    {
        Data *objectCursor;
        s32 i;
        data->objectCount = fn_8022E868(stream, 8) + 1;
        objectCursor = data;
        for (i = 0; i < data->objectCount; i++) {
            objectCursor->objects[0] = fn_8022F780(0x34);
            if (fn_802307F8(stream, objectCursor->objects[0]) != 0) goto error;
            objectCursor = (Data *)((char *)objectCursor + 4);
        }
    }

    {
        Handler *handler;
        Handler **handlers;
        s32 type;
        Data *cursor;
        s32 i;
        data->aCount = fn_8022E868(stream, 6) + 1;
        cursor = data;
        handlers = lbl_8064C4C8;
        for (i = 0; i < data->aCount; i++) {
            cursor->aTypes[0] = fn_8022E868(stream, 0x10);
            type = cursor->aTypes[0];
            if (type < 0 || type >= 1) goto error;
            handler = handlers[type];
            cursor->aObjects[0] = handler->read(source, stream, handler);
            if (cursor->aObjects[0] == 0) goto error;
            cursor = (Data *)((char *)cursor + 4);
        }
    }

    {
        s32 i;
        s32 type;
        Data *cursor;
        Handler **handlers;
        Handler *handler;
        data->bCount = fn_8022E868(stream, 6) + 1;
        cursor = data;
        handlers = lbl_8064C4CC;
        for (i = 0; i < data->bCount; i++) {
            cursor->bTypes[0] = fn_8022E868(stream, 0x10);
            type = cursor->bTypes[0];
            if (type < 0 || type >= 2) goto error;
            handler = handlers[type];
            cursor->bObjects[0] = handler->read(source, stream, handler);
            if (cursor->bObjects[0] == 0) goto error;
            cursor = (Data *)((char *)cursor + 4);
        }
    }

    {
        s32 i;
        s32 type;
        Data *cursor;
        Handler **handlers;
        Handler *handler;
        data->cCount = fn_8022E868(stream, 6) + 1;
        cursor = data;
        handlers = lbl_80300160;
        for (i = 0; i < data->cCount; i++) {
            cursor->cTypes[0] = fn_8022E868(stream, 0x10);
            type = cursor->cTypes[0];
            if (type < 0 || type >= 3) goto error;
            handler = handlers[type];
            cursor->cObjects[0] = handler->read(source, stream, handler);
            if (cursor->cObjects[0] == 0) goto error;
            cursor = (Data *)((char *)cursor + 4);
        }
    }

    {
        s32 i;
        s32 type;
        Data *cursor;
        Handler **handlers;
        Handler *handler;
        data->dCount = fn_8022E868(stream, 6) + 1;
        cursor = data;
        handlers = lbl_8064C4D4;
        for (i = 0; i < data->dCount; i++) {
            cursor->dTypes[0] = fn_8022E868(stream, 0x10);
            type = cursor->dTypes[0];
            if (type < 0 || type >= 1) goto error;
            handler = handlers[type];
            cursor->dObjects[0] = handler->read(source, stream, handler);
            if (cursor->dObjects[0] == 0) goto error;
            cursor = (Data *)((char *)cursor + 4);
        }
    }

    {
        s32 i;
        Data *cursor;
        data->entryCount = fn_8022E868(stream, 6) + 1;
        cursor = data;
        for (i = 0; i < data->entryCount; i++) {
            cursor->entries[0] = fn_8022F780(0x10);
            cursor->entries[0]->flags = fn_8022E868(stream, 1);
            cursor->entries[0]->kind = fn_8022E868(stream, 0x10);
            cursor->entries[0]->index = fn_8022E868(stream, 0x10);
            cursor->entries[0]->target = fn_8022E868(stream, 8);
            if (cursor->entries[0]->kind >= 1) goto error;
            if (cursor->entries[0]->index >= 1) goto error;
            if (cursor->entries[0]->target >= data->dCount) goto error;
            cursor = (Data *)((char *)cursor + 4);
        }
    }

    if (fn_8022E868(stream, 1) != 1) goto error;
    return 0;

error:
    fn_800F8BAC(&lbl_806517EC, &lbl_806517F0, 0x12d);
    fn_802326F8(source);
    return -0x85;
}
