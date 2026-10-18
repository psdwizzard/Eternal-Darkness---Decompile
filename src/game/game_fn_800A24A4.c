typedef unsigned char u8;

typedef struct Vec3i800A24A4 {
    int x;
    int y;
    int z;
} Vec3i800A24A4;

typedef struct SourceVtable800A24A4 {
    u8 pad000[0x2C];
    int (*callback)(void*, void*, void*);
} SourceVtable800A24A4;

typedef struct Source800A24A4 {
    SourceVtable800A24A4* vtable;
    u8 pad004[4];
    int countdown;
} Source800A24A4;

extern void *fn_80201B8C();
extern void fn_8011F114();
extern int fn_80201B54();
extern void* fn_80201B94();
extern void* fn_80201C48(void);
extern void *fn_80201814();
extern int fn_802045AC(void*, Vec3i800A24A4*);
extern u8 fn_80204578(void*, Vec3i800A24A4*);
extern void PSVECSubtract();
extern int fn_800A4F44(Vec3i800A24A4*, float);
extern float lbl_8064EE80;

int fn_800A24A4(void* object, void* context, Source800A24A4* source, void* value)
{
    Vec3i800A24A4 first;
    Vec3i800A24A4 second;
    Vec3i800A24A4 delta;
    int result = 0;
    void* active;

    fn_80201B8C(object);
    fn_8011F114(&first, context);
    ((void*)fn_80201B54(object));
    fn_80201B94(object);
    fn_80201C48();
    active = fn_80201814();
    if (source->countdown > 0) {
        source->countdown--;
    }
    fn_802045AC(object, &second);
    if (source->countdown <= 0 && active != 0 && fn_80204578(object, &second)) {
        PSVECSubtract(&first, &second, &delta);
        if (fn_800A4F44(&delta, lbl_8064EE80) <= 0) {
            result = source->vtable->callback(object, context, value);
        }
    }
    return result;
}
