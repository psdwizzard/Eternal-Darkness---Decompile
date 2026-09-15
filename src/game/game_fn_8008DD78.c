extern void fn_8011F114();
extern int fn_80201B54();
extern void* fn_80201B94();
extern void *fn_80201B8C();
extern int fn_80201C48(void*);
extern void *fn_80201814();
#define FN_80201E78_RETURN void
#define FN_80201E78_PARAMETERS void*, void*
extern FN_80201E78_RETURN fn_80201E78(FN_80201E78_PARAMETERS);extern void fn_80204180(void*, void*);
extern void *fn_801294DC(void *, int, int, int);
extern void* fn_80072354(void*);
extern void* fn_801A717C(void*);
extern void fn_801A7460(void*, int);
extern void fn_801A74A0(void*, int);
extern void fn_801A74A8(void*, int);
extern void fn_801A74C8(void*, int);
extern void fn_801A7560(void*, int);
extern void fn_800CF6AC(void*, void*, void*, void*, int, int);
extern void fn_801A7550(void*, int);
extern void fn_801A7558(void*, int);
extern void fn_801A764C(void*, void*);
extern void fn_801287C4(void*, void*, void*, int);
extern void fn_80128C28();
extern void fn_80128C44(void*, void*, void*);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_8003B8A0(void);
extern void fn_8008DBA8(void);
extern void fn_800DEA88(void);
extern void fn_8008DD24(void);
extern void fn_802042A4(void);

typedef struct Vec8008DD78 { float x, y, z; } Vec8008DD78;
typedef struct Data8008DD78 {
    unsigned char pad0[0x90];
    void* value90;
} Data8008DD78;

/* NonMatching: behavior-complete honest C. Size, instruction scheduling, and
 * all 38 relocation sites align; the remaining differences are register
 * allocation for the object, data/value, and effect live ranges. */
int fn_8008DD78(void* object, void* resource)
{
    Vec8008DD78 position;
    Vec8008DD78 target_position;
    void* actor;
    void* created;
    void* target;
    Data8008DD78* value;
    void* data;
    int callback;
    int owner;
    int target_id;

    fn_8011F114(&position);
    owner = fn_80201B54(object);
    data = fn_80201B94(object);
    value = fn_80201B8C(object);
    target_id = fn_80201C48(data);
    target = fn_80201814(target_id);
    if (target != 0)
        fn_80201E78(&target_position, target);
    fn_80204180(object, target);
    if (target != 0) {
        created = fn_801294DC(resource, 4, 0, 6);
        if (created != 0) {
            resource = fn_80072354(value->value90);
            actor = fn_801A717C(resource);
            fn_801A7460(actor, 4);
            fn_801A74A0(actor, owner);
            fn_801A74A8(actor, target_id);
            fn_801A74C8(actor, 1);
            fn_801A7560(actor, 132);
            fn_800CF6AC(object, resource, value, actor, 1, 5);
            fn_801A7550(actor, 12);
            fn_801A7558(actor, 7);
            fn_801A764C(actor, &position);
            fn_801287C4(created, fn_8003B8A0, actor, 25);
            callback = 26;
            do {
                fn_801287C4(created, fn_8008DBA8, actor, callback);
                callback++;
            } while (callback < 35);
            fn_801287C4(created, fn_800DEA88, actor, 15);
            fn_80128C28(created, fn_8008DD24, actor);
            fn_80128C44(created, fn_802042A4, actor);
            fn_80201D2C(object, 6);
            fn_80201D14(object, 1);
            return 1;
        }
    }
    return 0;
}
