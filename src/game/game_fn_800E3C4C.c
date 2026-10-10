/* fn_800E3C4C (0x800E3C4C, 708 bytes): event handler dispatch by state/event id. */

extern int fn_80200C10(void *);
extern int fn_80200C20(void *);
extern int fn_80200C38(void *);
extern int fn_80201B44(void);
extern int fn_80201B54(void *);
extern void *fn_80201BC8(void *);
extern void fn_80201D14(void *, int);
extern void fn_80201D2C(void *, int);
extern unsigned int fn_8011FA8C(void *, int, int);
extern void fn_800E3F10(void *, int, void *, int *);
extern void fn_800E41FC(void *);
extern void fn_800E428C(void *, int);
extern void fn_800E42E8(void *, int);
extern void fn_800E4458(void *);
extern int fn_800E4520(int, int);

int fn_800E3C4C(void *object, int state, void *event, int *result) {
    int id;
    void *runtime;

    id = fn_80200C10(event);
    fn_80201B54(object);
    runtime = fn_80201BC8(object);

    if (state == 0) {
        if (id == 1) {
            fn_800E4458(object);
            return 1;
        }
    } else if (state == 1) {
        if (id == 1) {
            fn_800E428C(runtime, 0x1B);
            return 1;
        } else if (id == 0x12) {
            fn_800E42E8(object, fn_80200C38(event));
            return 1;
        } else if (id == 0x14) {
            fn_80201D2C(object, 0xE);
            fn_80201D14(object, 1);
            return 1;
        } else if (id == 0x3B) {
            if (fn_80200C20(event) == fn_80201B44() && result != 0) {
                *result = 1;
            }
            return 1;
        } else if (id == 0xEF) {
            if (result != 0) {
                *result = 0;
            }
            return 1;
        } else if (id == 0xB) {
            fn_800E3F10(object, state, event, result);
            return 1;
        }
    } else if (state == 0xF) {
        if (id == 1) {
            fn_800E428C(runtime, 0x1A);
            return 1;
        } else if (id == 0x17) {
            fn_800E41FC(object);
            return 1;
        } else if (id == 0x3E) {
            fn_800E41FC(object);
            return 1;
        } else if (id == 0x14) {
            fn_80201D2C(object, 0xE);
            fn_80201D14(object, 1);
            return 1;
        } else if (id == 3) {
            return 1;
        } else if (id == 0x3B) {
            return 1;
        } else if (id == 0xEF) {
            return 1;
        } else if (id == 0xB) {
            return 1;
        }
    } else if (state == 0xE) {
        if (id == 1) {
            fn_800E4520(0, 0);
            fn_800E428C(runtime, 0x1A);
            return 1;
        } else if (id == 0x3E) {
            fn_800E41FC(object);
            return 1;
        } else if (id == 3) {
            fn_8011FA8C(runtime, 0x40000, 0);
            return 1;
        } else if (id == 0x14) {
            return 1;
        } else if (id == 0x3B) {
            return 1;
        } else if (id == 0xEF) {
            return 1;
        } else if (id == 0xB) {
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
