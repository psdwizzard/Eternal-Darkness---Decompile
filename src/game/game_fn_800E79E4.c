typedef int s32;

extern float lbl_8064F7E8;

extern s32 fn_80200C10(void *);
extern s32 fn_80200C20(void *);
extern int fn_80201B44();
extern s32 fn_80201B54(void *);
extern void *fn_80201BC8();
extern void *fn_80201B94();
extern void fn_80201DD8(void *, int);
extern unsigned int fn_8011FA8C(void *, int, int);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_80201D34(void *, int);
extern void fn_80201D1C(void *, int);
extern int fn_801E8328();
extern void fn_800C8394(void *, int);
extern void fn_800C8434(void *);
extern void fn_800E8634(int, void *);
extern void fn_800E840C(void *);
extern void fn_800E7FA4(void *);
extern void fn_800C80E8(void *, int, int);
extern void fn_800E7F70(void *);
extern void fn_800E801C(void *, void *);
extern void fn_800E8384(int, void *);
extern void fn_801A977C(void *, int);
extern s32 fn_800E7964(void *);
extern int fn_800E8130(void *);
extern void fn_8020104C(int, int, int, int, float);
extern unsigned long long fn_8020123C();

int fn_800E79E4(void *object, int state, void *event, s32 *result)
{
    s32 kind = fn_80200C10(event);
    s32 owner = fn_80201B54(object);
    void *runtime = fn_80201BC8(object);
    void *link = fn_80201B94(object);

    if (state == 0) {
        if (kind == 1) {
            fn_80201DD8(link, fn_80201B44());
            fn_8011FA8C(runtime, 0, 0x8C0);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        } else if (kind == 0x39) {
            fn_801E8328(2, object);
            fn_80201D34(object, 0);
            fn_80201D1C(object, 1);
            return 1;
        } else if (kind == 0x13) {
            fn_80201D2C(object, 0xE);
            fn_80201D14(object, 1);
            return 1;
        } else if (kind == 0x11) {
            fn_800C8394(runtime, -5);
            return 1;
        } else if (kind == 0x10) {
            fn_800C8434(runtime);
            return 1;
        }
    } else if (state == 1) {
        if (kind == 1) {
            return 1;
        } else if (kind == 0x12) {
            fn_800E8634(0, object);
            return 1;
        } else if (kind == 0xD7) {
            fn_800E840C(object);
            return 1;
        } else if (kind == 0x3B) {
            if (result != 0) {
                *result = 0;
            }
            return 1;
        } else if (kind == 0xEF) {
            if (result != 0) {
                *result = 0;
            }
            return 1;
        } else if (kind == 0x3E) {
            fn_800E7FA4(object);
            return 1;
        } else if (kind == 3) {
            fn_800C80E8(object, 0x13, 1);
            return 1;
        } else if (kind == 0xB) {
            return 1;
        }
    } else if (state == 0xF) {
        if (kind == 1) {
            fn_800E7F70(object);
            return 1;
        } else if (kind == 0xB) {
            fn_800E801C(object, event);
            fn_800E8384(0, object);
            fn_801A977C(runtime, 0x13);
            if (result != 0) {
                *result = 0x29;
            }
            return 1;
        } else if (kind == 0x27) {
            return 1;
        } else if (kind == 0x3B) {
            s32 value = fn_800E7964(event);
            if (result != 0) {
                *result = value;
            }
            return 1;
        } else if (kind == 0xEF) {
            if (result != 0) {
                *result = 1;
            }
            return 1;
        } else if (kind == 3) {
            fn_800C80E8(object, 0x13, 1);
            return 1;
        } else if (kind == 0x12) {
            return 1;
        } else if (kind == 0xD7) {
            return 1;
        }
    } else if (state == 6) {
        if (kind == 1) {
            fn_800E7F70(object);
            return 1;
        } else if (kind == 0xB) {
            fn_800E801C(object, event);
            fn_800E8384(0, object);
            fn_801A977C(runtime, 0x13);
            if (result != 0) {
                *result = 0x29;
            }
            return 1;
        } else if (kind == 0x27) {
            return 1;
        } else if (kind == 0xC9) {
            s32 source = fn_80200C20(event);
            if (source == owner) {
                if (fn_800E8130(object) != 0) {
                    fn_8020104C(0xC9, owner, owner, 0, lbl_8064F7E8);
                }
            }
            return 1;
        } else if (kind == 0x3B) {
            s32 value = fn_800E7964(event);
            if (result != 0) {
                *result = value;
            }
            return 1;
        } else if (kind == 0xEF) {
            if (result != 0) {
                *result = 1;
            }
            return 1;
        } else if (kind == 3) {
            fn_800C80E8(object, 0x13, 1);
            return 1;
        } else if (kind == 2) {
            return 1;
        }
    } else if (state == 0x10) {
        if (kind == 1) {
            return 1;
        } else if (kind == 0x3B) {
            if (result != 0) {
                *result = 0;
            }
            return 1;
        } else if (kind == 0xEF) {
            if (result != 0) {
                *result = 0;
            }
            return 1;
        } else if (kind == 0x3D) {
            fn_8020123C(0x39, owner, owner, 0);
            return 1;
        } else if (kind == 3) {
            fn_8011FA8C(runtime, 0x40000, 0);
            return 1;
        } else if (kind == 0xB) {
            return 1;
        } else if (kind == 0x13) {
            return 1;
        } else if (kind == 0x10) {
            return 1;
        }
    } else if (state == 0xE) {
        if (kind == 1) {
            return 1;
        } else if (kind == 0x3D) {
            fn_8020123C(0x39, owner, owner, 0);
            return 1;
        } else if (kind == 0x13) {
            return 1;
        } else if (kind == 0x10) {
            return 1;
        } else if (kind == 0xB) {
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
