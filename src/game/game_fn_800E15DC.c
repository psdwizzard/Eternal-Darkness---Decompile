typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct ObjectInfo {
    char pad_00[0x78];
    int *state;
} ObjectInfo;

typedef struct Object80201D34 Object80201D34;
typedef struct Object80201D1C Object80201D1C;
typedef struct Object80201D2C Object80201D2C;
typedef struct Object80201D14 Object80201D14;

extern int fn_80200C10(int *);
extern int fn_80200C20(int *);
extern int fn_80201B54(int *);
extern void *fn_80201BC8(void *);
extern void *fn_80201B94(unsigned char *);
extern void *fn_80201B8C(unsigned char *);
extern int fn_80201B44(void);
extern void fn_8020104C(int, int, int, int, float);
extern unsigned long long fn_8020123C(int, int, int, int);
extern void fn_801E7974(unsigned char *, unsigned int);
extern int fn_802066E0(void *, unsigned int);
extern void fn_8016ADF0(short, short, short);
extern void fn_8016B400(int, void *, void *);
extern int fn_801E8328(unsigned int, unsigned int);
extern void fn_80201D34(Object80201D34 *, int);
extern void fn_80201D1C(Object80201D1C *, unsigned char);
extern void fn_80201D2C(Object80201D2C *, int);
extern void fn_80201D14(Object80201D14 *, unsigned char);
extern void fn_80201E78(void *, void *);
extern int fn_801AC9F4(unsigned short, unsigned char, Vec3 *, unsigned char);
extern int fn_800E1C9C(void *);
extern void fn_800E1AA8(void *);
extern void *fn_8011FB4C(void *);
extern int fn_800E1B40(void *, void *);
extern void fn_800E19CC(void *);
extern void fn_800E1DB0(void *);
extern void *lbl_8064C4E0;
extern int lbl_8064D18C;
extern float lbl_8064F618;

int fn_800E15DC(void *object, int state, void *event, int *value)
{
    int kind = fn_80200C10(event);
    int object_id = fn_80201B54(object);
    void *resource = fn_80201BC8(object);
    int *data;

    fn_80201B94(object);
    data = ((ObjectInfo *)fn_80201B8C(object))->state;

    if (state == 0) {
        if (kind == 1) {
            fn_8020104C(0xD5, object_id, object_id, 0, lbl_8064F618);
            return 1;
        }
        if (kind == 0x39) {
            fn_801E7974(lbl_8064C4E0, 0xE1);
            if (lbl_8064D18C == 0x99 &&
                fn_802066E0((void *)fn_80201B44(), 0x36793917) != 0) {
                fn_8016ADF0(0x31B, 0, -1);
                fn_8016B400(0x31B, 0, 0);
            }
            fn_801E8328(2, (unsigned int)object);
            fn_80201D34(object, 0);
            fn_80201D1C(object, 1);
            return 1;
        }
        if (kind == 0x97) {
            Vec3 sound_position;
            Vec3 position;
            fn_80201E78(&position, object);
            sound_position = position;
            fn_801AC9F4(0x64, 0x64, &sound_position, 2);
            return 1;
        }
        if (kind == 0xD5) {
            *data = fn_800E1C9C(object);
            fn_80201D2C(object, 0x26);
            fn_80201D14(object, 1);
            return 1;
        }
    } else if (state == 0x26) {
        if (kind == 0x3E) {
            fn_800E1AA8(object);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
        if (kind == 3) {
            if (lbl_8064D18C == (int)fn_8011FB4C(resource)) {
                fn_800E1AA8(object);
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
            return 1;
        }
    } else if (state == 1) {
        if (kind == 1) {
            return 1;
        }
        if (kind == 0x3B) {
            int active = fn_80201B44();
            int target = fn_80200C20(event);
            if (target == active && value != 0) {
                *value = 1;
            }
            return 1;
        }
        if (kind == 0xEF) {
            if (value != 0) {
                *value = 0;
            }
            return 1;
        }
        if (kind == 0xB) {
            if (fn_800E1B40(object, event) != 0) {
                fn_800E19CC(object);
            } else if (value != 0) {
                *value = 0x29;
            }
            return 1;
        }
        if (kind == 3) {
            fn_800E1DB0(object);
            return 1;
        }
    } else if (state == 0xB) {
        if (kind == 1) {
            return 1;
        }
        if (kind == 0x3D) {
            fn_8020123C(0x39, object_id, object_id, 0);
            return 1;
        }
        if (kind == 0x3B) {
            return 1;
        }
        if (kind == 0xEF) {
            return 1;
        }
        if (kind == 0xB) {
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
