typedef signed char s8;
typedef signed int s32;
typedef unsigned int u32;

typedef struct RuntimeObject {
    unsigned char data[0x10A];
    s8 active;
} RuntimeObject;

typedef struct ObjectState {
    s32 unused;
    RuntimeObject **installed;
} ObjectState;

extern void *fn_80201BC8();
extern void *fn_80201B8C();
extern int fn_80201B54();
extern void fn_8011F114();
extern int fn_80200C20(s32 event);
extern u32 fn_80036D5C(void *object);
extern s32 fn_80066D04(void *object, s32 index);
extern void *fn_801294DC(void *, int, int, int);
extern s32 fn_800683E4(void *action, s32 object_id);
extern void fn_80128C28();
extern void fn_80067BAC(void *object);
extern void fn_80201D34(void *object, s32 value);
extern void fn_80201D1C(void *object, s32 value);

s32 fn_80068290(void *object, s32 event, s32 *result)
{
    RuntimeObject **installed;
    void *state;
    s32 owner_id;
    unsigned char local[8];

    state = fn_80201BC8(object);
    installed = ((ObjectState *)fn_80201B8C(object))->installed;
    owner_id = fn_80201B54(object);
    fn_8011F114(local, state);
    fn_80200C20(event);

    if ((fn_80036D5C(object) & 0x80) != 0) {
        if (result != 0) {
            *result = 0;
        }
        return 0;
    }

    if (fn_80066D04(object, 0) != 0 && installed != 0 && *installed != 0 &&
        (*installed)->active == 0) {
        void *action = fn_801294DC(state, 0x2B, 0x24, 10);
        if (action != 0) {
            fn_80128C28(action, (void *)fn_800683E4, owner_id);
            fn_80067BAC(object);
            fn_80201D34(object, 0x1C);
            fn_80201D1C(object, 1);
            if (result != 0) {
                *result = 1;
            }
            return 1;
        }
        if (result != 0) {
            *result = 0;
        }
        return 0;
    }

    if (result != 0) {
        *result = 0;
    }
    return 0;
}
