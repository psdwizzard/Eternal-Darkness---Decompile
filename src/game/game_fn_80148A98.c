typedef unsigned char u8;
typedef unsigned short u16;

typedef struct InstanceList InstanceList;

extern void* memset(void*, int, unsigned long);
extern void fn_80184740(u8*);
extern void* fn_801848AC(void*, void*, void*);
extern void fn_80148BCC(InstanceList*, void*, void*);
extern void fn_80148E04(void*, void*);
extern void fn_80185000(u8*, u16);

typedef struct EffectCallbacks {
    u8 pad[0x90];
    void* (*create)(void*, void*, void*);
    void (*initialize)(u8*);
    void (*update)(void*, void*);
    void* unknown;
    void (*attach)(InstanceList*, void*, void*);
    void (*set_value)(u8*, u16);
    u8 padA8[0x14];
    u8 kind;
} EffectCallbacks;

typedef struct EffectInstances {
    u8 count;
    u8 pad[0x87];
    void* instances[16];
} EffectInstances;

void fn_80148A98(EffectCallbacks* effect, EffectInstances* list)
{
    effect->create = fn_801848AC;
    effect->initialize = fn_80184740;
    effect->update = fn_80148E04;
    effect->unknown = 0;
    effect->attach = fn_80148BCC;
    effect->set_value = fn_80185000;
    effect->kind = 1;
    list->count = 16;
    memset(list->instances, 0, sizeof(list->instances));
}
