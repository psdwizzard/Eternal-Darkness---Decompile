/* fn_800E3C4C (0x800E3C4C, 708 bytes): event handler dispatch by state/event id. */

typedef struct Object80201D14 Object80201D14;
typedef struct Object80201D2C Object80201D2C;

extern int fn_80200C10(int *);
extern int fn_80200C20(int *);
extern void *fn_80200C38(void **);
extern int fn_80201B44(void);
extern int fn_80201B54(int *);
extern void *fn_80201BC8(void *);
extern void fn_80201D14(Object80201D14 *, unsigned char);
extern void fn_80201D2C(Object80201D2C *, int);
extern unsigned int fn_8011FA8C(void *, unsigned int, unsigned int);
extern void fn_800E3F10(int *, void *, void **);
extern void fn_800E41FC(int);
extern void fn_800E428C(void *, int);
extern void fn_800E42E8(int, int);
extern void fn_800E4458(int);
extern int fn_800E4520(void);

int fn_800E3C4C(register int *object, register int state, register int *event, register int *result) {
    int id;
    void *runtime;

    id = fn_80200C10(event);
    fn_80201B54(object);
    runtime = fn_80201BC8(object);

    if (state == 0) {
        if (id == 1) {
            fn_800E4458((int)object);
            return 1;
        }
    } else if (state == 1) {
        if (id == 1) {
            fn_800E428C(runtime, 0x1B);
            return 1;
        } else if (id == 0x12) {
            fn_800E42E8((int)object, (int)fn_80200C38((void **)event));
            return 1;
        } else if (id == 0x14) {
            fn_80201D2C((Object80201D2C *)object, 0xE);
            fn_80201D14((Object80201D14 *)object, 1);
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
            /* ASM: mr r3-r6; bl -- retail forwards all four arguments
               (result last, in r6) to fn_800E3F10, but its definition takes
               only three parameters, so a C call cannot load r6 after r5. */
            asm {
                mr r3, object
                mr r4, state
                mr r5, event
                mr r6, result
                bl fn_800E3F10
            }
            return 1;
        }
    } else if (state == 0xF) {
        if (id == 1) {
            fn_800E428C(runtime, 0x1A);
            return 1;
        } else if (id == 0x17) {
            fn_800E41FC((int)object);
            return 1;
        } else if (id == 0x3E) {
            fn_800E41FC((int)object);
            return 1;
        } else if (id == 0x14) {
            fn_80201D2C((Object80201D2C *)object, 0xE);
            fn_80201D14((Object80201D14 *)object, 1);
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
            /* ASM: li r3,0; li r4,0 -- retail zeroes r3/r4 before calling
               fn_800E4520, whose definition takes no parameters, so no C
               arguments would load them. */
            asm {
                li r3, 0
                li r4, 0
            }
            fn_800E4520();
            fn_800E428C(runtime, 0x1A);
            return 1;
        } else if (id == 0x3E) {
            fn_800E41FC((int)object);
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
