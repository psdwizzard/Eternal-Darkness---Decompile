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

extern s32 oggpack_read(void *, s32);
extern void *fn_8022F780(s32);
extern s32 vorbis_staticbook_unpack(void *, void *);
extern void vorbis_info_clear(Source *);
extern void __assertion_failed(const char *, const char *, s32);
extern Handler *_time_P[];
extern Handler *_floor_P[];
extern Handler *_residue_P[];
extern Handler *_mapping_P[];
extern const char lbl_806517EC;
extern const char lbl_806517F0;

s32 _vorbis_unpack_books(Source *source, void *stream) {
    Data *data;

    if (source->data == 0) {
        return -0x81;
    }
    data = source->data;

    {
        Data *objectCursor;
        s32 i;
        data->objectCount = oggpack_read(stream, 8) + 1;
        objectCursor = data;
        for (i = 0; i < data->objectCount; i++) {
            objectCursor->objects[0] = fn_8022F780(0x34);
            if (vorbis_staticbook_unpack(stream, objectCursor->objects[0]) != 0) goto error;
            objectCursor = (Data *)((char *)objectCursor + 4);
        }
    }

    {
        Handler *handler;
        Handler **handlers;
        s32 type;
        Data *cursor;
        s32 i;
        data->aCount = oggpack_read(stream, 6) + 1;
        cursor = data;
        handlers = _time_P;
        for (i = 0; i < data->aCount; i++) {
            cursor->aTypes[0] = oggpack_read(stream, 0x10);
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
        data->bCount = oggpack_read(stream, 6) + 1;
        cursor = data;
        handlers = _floor_P;
        for (i = 0; i < data->bCount; i++) {
            cursor->bTypes[0] = oggpack_read(stream, 0x10);
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
        data->cCount = oggpack_read(stream, 6) + 1;
        cursor = data;
        handlers = _residue_P;
        for (i = 0; i < data->cCount; i++) {
            cursor->cTypes[0] = oggpack_read(stream, 0x10);
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
        data->dCount = oggpack_read(stream, 6) + 1;
        cursor = data;
        handlers = _mapping_P;
        for (i = 0; i < data->dCount; i++) {
            cursor->dTypes[0] = oggpack_read(stream, 0x10);
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
        data->entryCount = oggpack_read(stream, 6) + 1;
        cursor = data;
        for (i = 0; i < data->entryCount; i++) {
            cursor->entries[0] = fn_8022F780(0x10);
            cursor->entries[0]->flags = oggpack_read(stream, 1);
            cursor->entries[0]->kind = oggpack_read(stream, 0x10);
            cursor->entries[0]->index = oggpack_read(stream, 0x10);
            cursor->entries[0]->target = oggpack_read(stream, 8);
            if (cursor->entries[0]->kind >= 1) goto error;
            if (cursor->entries[0]->index >= 1) goto error;
            if (cursor->entries[0]->target >= data->dCount) goto error;
            cursor = (Data *)((char *)cursor + 4);
        }
    }

    if (oggpack_read(stream, 1) != 1) goto error;
    return 0;

error:
    __assertion_failed(&lbl_806517EC, &lbl_806517F0, 0x12d);
    vorbis_info_clear(source);
    return -0x85;
}
