typedef unsigned char u8;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Entry { int value; int kind; int pad8; } Entry;
typedef struct EntryList { int count; Entry* entries; } EntryList;
typedef struct State { u8 pad0[0x90]; void* field90; } State;

extern void *fn_80201B8C(void*);
extern void* fn_80201B94(void*);
extern void fn_8011F114(Vec3*, void*);
extern void fn_80128EE4(void*);
extern void* fn_80201C48(void*);
extern void* fn_80201B54(void*);
extern void *fn_80201814(void*);
extern void *fn_80201BC8(void*);
extern void *fn_801294DC(void *, int, int, int);
extern void* fn_801A717C(void);
extern void* fn_80072354(void*);
extern void fn_801A7460(void*, int);
extern void fn_801A74A0(void*, void*);
extern void fn_801A74A8(void*, void*);
extern void fn_801A74C8(void*, int);
extern void fn_801A7560(void*, int);
extern void fn_801A7538(void*, int);
extern void fn_801A7518(void*, int);
extern void fn_801A7550(void*, int);
extern void fn_801A7558(void*, int);
extern void fn_801A764C(void*, Vec3*);
extern void fn_801A7598(void*, int);
extern void fn_801292E0(void*, int*, Entry**);
extern void fn_801287C4(void*, void (*)(void), void*, int);
extern void* fn_80201C2C(void*);
extern void* fn_80205288(void*);
extern void* fn_80201C24(void);
extern void fn_801A7680(void*, void*);
extern void fn_801A7478(void*, void*);
extern void fn_80129334(void*, int, int*, int);
extern void fn_80128C28();
extern void fn_80128C44(void*, void*, void*);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_8003B8A0(void);
extern void fn_8003BD48(void);
extern void fn_800C3ADC(void);
extern void fn_80204230(void);
extern void fn_802042A4(void);
extern char lbl_8031D790[];

int fn_800A7A68(void* context, void* object)
{
    State* state = fn_80201B8C(context);
    void* actor = fn_80201B94(context);
    Vec3 copy;
    Vec3 position;
    Vec3 targetPosition;
    void* target;
    void* targetObject;
    void* owner;
    void* found;
    void* effect;
    EntryList list;
    int index;
    int callbackIndex;
    int first;

    fn_8011F114(&position, object);
    copy = position;
    fn_80128EE4(object);
    target = fn_80201C48(actor);
    owner = ((void*)fn_80201B54(context));
    targetObject = fn_80201814(target);
    if (targetObject != 0) {
        {
            void* targetData = fn_80201BC8(targetObject);
            fn_8011F114(&targetPosition, targetData);
        }
        found = fn_801294DC(object, 4, 0, 6);
        if (found != 0) {
            effect = fn_801A717C();
            first = 1;
            actor = fn_80072354(state->field90);
            fn_801A7460(effect, 4);
            fn_801A74A0(effect, owner);
            fn_801A74A8(effect, target);
            fn_801A74C8(effect, 1);
            fn_801A7560(effect, 0x8244);
            index = 0;
            fn_801A7538(effect, *((u8*)actor + (((unsigned)index >> 28) & 8) + 0x2B));
            fn_801A7518(effect, 5);
            fn_801A7550(effect, 12);
            fn_801A7558(effect, 7);
            fn_801A764C(effect, &copy);
            fn_801A7598(effect, 450);
            fn_801292E0(object, &list.count, &list.entries);
            for (index = 0; index < list.count; index++) {
                Entry* entry = &list.entries[index];
                int callback;
                if (entry->kind != 1) continue;
                callback = entry->value >> 17;
                if (first) {
                    fn_801287C4(found, fn_8003B8A0, effect, callback);
                    first = 0;
                    if (fn_80201C2C(context) != 0 && fn_80205288(context) != 0) {
                        fn_801A7680(effect, fn_80201C24());
                        fn_801A7478(effect, lbl_8031D790);
                        fn_80129334(object, 1, &callbackIndex, -1);
                        fn_801287C4(found, fn_800C3ADC, effect, callbackIndex - 1);
                    }
                } else {
                    fn_801287C4(found, fn_8003BD48, effect, callback);
                }
            }
            fn_80128C28(found, fn_80204230, effect);
            fn_80128C44(found, fn_802042A4, effect);
            fn_80201D2C(context, 6);
            fn_80201D14(context, 1);
            return 1;
        }
    }
    return 0;
}
