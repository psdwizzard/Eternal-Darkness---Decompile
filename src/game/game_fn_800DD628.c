typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern int fn_800CA2C8(void *);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern void *fn_8011F950(void *);
extern void fn_80128C28();
extern void fn_80128C44();
extern unsigned char *fn_801294DC(void *, int, int, int);
extern void fn_801441C0(int, int, int);
extern void fn_80152838(Vec3 *, Vec3 *, unsigned char);
extern void fn_801593B4(unsigned int);
extern void fn_801A7228(void *);
extern short fn_801A74F8(void *);
extern void fn_801B05E8(int, int, int, int, int, int, int, int);
extern int fn_801E8328(unsigned int, unsigned int);
extern void fn_801F74C8(int, int, int);
extern int fn_80200C10(void *);
extern int fn_80200C20(void *);
extern int fn_80200C28(void *);
extern void *fn_80200C38(void *);
extern unsigned long long fn_8020123C(int, int, int, int);
extern int fn_802019EC(int, int);
extern int fn_80201B44(void);
extern int fn_80201B54(int *);
extern void *fn_80201B94(unsigned char *);
extern void *fn_80201BC8(void *);
extern void fn_80201D14(void *, unsigned char);
extern void fn_80201D1C(void *, unsigned char);
extern void fn_80201D2C(void *, int);
extern void fn_80201D34(void *, int);
extern void fn_80204810(void);
extern int lbl_8064C574;
extern int lbl_8064D18C;
extern float lbl_8064F4F8;

int fn_800DD628(void *object, int phase, void *event, int *result)
{
    Vec3 position;
    Vec3 effectPosition;
    int kind;
    void *runtime;
    int objectId;
    int senderId;
    int targetId;
    void *created;
    int callbackId;
    int stage;

    kind = fn_80200C10(event);
    runtime = fn_80201BC8(object);
    fn_80201B94(object);
    objectId = fn_80201B54(object);
    fn_8011F114(&position, runtime);

    if (phase == 0) {
        if (kind == 1) {
            if (fn_8011F950(runtime) != 0) {
                fn_801294DC(runtime, 0x1B, 0x21, 8);
            }
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
        if (kind == 0x7D) {
            if (result != 0) *result = 1;
            return 1;
        }
        if (kind == 0x3B) {
            targetId = fn_80201B44();
            senderId = fn_80200C20(event);
            if (senderId == targetId && result != 0) {
                *result = 1;
            }
            return 1;
        }
        if (kind == 0xED) {
            fn_8020123C(0xB, fn_80200C20(event), fn_80200C28(event),
                          (int)fn_80200C38(event));
            fn_801A7228(fn_80200C38(event));
            return 1;
        }
        if (kind == 0x3A) {
            fn_8020123C(0x27, fn_80200C20(event), fn_80200C28(event),
                          (int)fn_80200C38(event));
            fn_801A7228(fn_80200C38(event));
            return 1;
        }
        if (kind == 8) {
            lbl_8064C574 = 3;
            fn_801F74C8(0xF, 0, 8);
            fn_801441C0(1, 0, (unsigned short)((2 << lbl_8064C574) + 8));
            created = fn_801294DC(runtime, 0x19, 0x20, 0xA);
            if (created != 0) {
                callbackId = objectId << 8;
                fn_80128C28(created, fn_80204810, callbackId | 6);
                fn_80128C44(created, fn_80204810, callbackId | 7);
                fn_80201D2C(object, 8);
                fn_80201D14(object, 1);
            }
            return 1;
        }
        if (kind == 0x27) {
            if (fn_801A74F8(fn_80200C38(event)) > 0x64) {
                fn_8020123C(8, objectId, objectId, 0);
            } else {
                fn_8020123C(0xB, objectId, objectId, 0);
            }
            return 1;
        }
        if (kind == 0xB) {
            effectPosition = position;
            stage = ++lbl_8064C574;
            if (stage >= 3) {
                fn_8020123C(8, objectId, objectId, 0);
            } else {
                fn_801F74C8(0xF, 0, 1 << stage);
                fn_801441C0(1, 0, (unsigned short)((2 << lbl_8064C574) + 8));
            }
            effectPosition.z += lbl_8064F4F8;
            fn_80152838(&position, &effectPosition, 4);
            if (result != 0) *result = 0x20;
            return 1;
        }
    } else if (phase != 1) {
        if (phase == 8) {
            if (kind == 1) {
                fn_801593B4(0x26);
                fn_801593B4(lbl_8064D18C);
                fn_801B05E8(0x261, 0x64, 4, 1, 0, 5, 0, 0);
                fn_800CA2C8(object);
                fn_8020123C(0x39, objectId, fn_802019EC(0x890, lbl_8064D18C), 0);
                fn_8020123C(0x39, objectId, fn_802019EC(0x891, lbl_8064D18C), 0);
                fn_8020123C(0x39, objectId, fn_802019EC(0x892, lbl_8064D18C), 0);
                return 1;
            }
            if (kind == 6) {
                fn_80201D34(object, 0);
                fn_80201D1C(object, 1);
                fn_801E8328(2, (unsigned int)object);
                return 1;
            }
            if (kind == 7) return 1;
            if (kind == 0x3B) return 1;
            if (kind == 0xB) return 1;
            if (kind == 0x7D) return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
