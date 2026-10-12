/* Dispatch events for the object's current action state. */
typedef unsigned char u8;
typedef unsigned int u32;

/* Opaque types used by the runtime and object accessors. */
typedef struct Object Object;
typedef struct Object80201DD8 Object80201DD8;
typedef struct Object80201D2C Object80201D2C;
typedef struct Object80201D14 Object80201D14;
typedef struct Object80201D1C Object80201D1C;
typedef struct Object80201D34 Object80201D34;

extern int fn_80200C10(int *event);
extern void *fn_80200C38(void **event);
extern int fn_80201B54(int *object);
extern void *fn_80201BC8(void *object);
extern void *fn_80201B94(u8 *object);
extern int fn_80201B44(void);
extern int fn_8011EB04(Object *runtime);
extern void fn_80201DD8(Object80201DD8 *relation, void *value);
extern u32 fn_8011FA8C(void *runtime, u32 clear, u32 set);
extern u32 fn_8011FABC(void *runtime, u32 clear, u32 set);
extern void fn_80201D2C(Object80201D2C *object, int state);
extern void fn_80201D14(Object80201D14 *object, u8 value);
extern void fn_80201D1C(Object80201D1C *object, u8 value);
extern void fn_80201D34(Object80201D34 *object, int value);
extern int fn_801E8328(u32 kind, u32 object);
extern void fn_800C8394(void *runtime, u8 alpha);
extern void fn_800C8434(void *runtime);
extern void fn_800C81E0(void *object);
extern int fn_800C77B4(int unused, void *object);
extern int fn_800C77FC(int unused, void *object);
extern int fn_800C78C4(int unused, void *object);
extern void fn_800C80E8(void *object, int first, int second);
extern void fn_800C76DC(void *object);
extern void fn_800C7540(void *object);
extern void fn_800C82F0(void *object);
extern void fn_800C7E40(void *object);
extern void fn_800C7DCC(void *object);
extern void fn_800C7B74(void *object);
extern void fn_800C7C0C(void *object);
extern void fn_800C7AEC(void *object);
extern void fn_800C7A54(void *object);
extern void fn_8020104C(int kind, int source, int target, int value, float delay);
extern float lbl_8064F210;

/* The dispatch body matches retail. The existing compiler settings emit
 * _savegpr_25/_restgpr_25 in place of the retail stmw/lmw pair. */
int fn_800C7030(void *object, int state, void *event)
{
    int kind;
    int identifier;
    register Object *runtime;
    Object80201DD8 *relation;

    kind = fn_80200C10(event);
    identifier = fn_80201B54(object);
    runtime = fn_80201BC8(object);
    fn_8011EB04(runtime);
    relation = fn_80201B94(object);

    if (state == 0) {
        if (kind == 1) {
            int current_identifier = fn_80201B44();
            fn_8011EB04(runtime);
            fn_80201DD8(relation, (void *)current_identifier);
            fn_8011FA8C(runtime, 0xC0, 0x802);
            fn_8011FABC(runtime, 0, 0x200);
            fn_80201D2C(object, 0x26);
            fn_80201D14(object, 1);
            return 1;
        } else if (kind == 0x39) {
            fn_801E8328(2, (u32)object);
            fn_80201D34(object, 0);
            fn_80201D1C(object, 1);
            return 1;
        } else if (kind == 0x13) {
            fn_8011FA8C(runtime, 0x20000000, 0);
            fn_80201D2C(object, 0xE);
            fn_80201D14(object, 1);
            return 1;
        } else if (kind == 0x11) {
            /* ASM: mr/li/bl pass the retail sign-extended alpha byte;
             * the function takes u8, so C canonicalizes -5 to 251. */
            asm {
                mr r3, runtime
                li r4, -5
                bl fn_800C8394
            }
            return 1;
        } else if (kind == 0x10) {
            fn_800C8434(runtime);
            return 1;
        }
    } else if (state == 0x26) {
        if (kind == 1) {
            int current_identifier = fn_80201B44();
            fn_80201DD8(relation, (void *)current_identifier);
            return 1;
        } else if (kind == 0x12) {
            fn_800C81E0(object);
            return 1;
        } else if (kind == 0xD7) {
            fn_800C81E0(object);
            return 1;
        } else if (kind == 0xE4) {
            fn_800C77B4(0, object);
            return 1;
        } else if (kind == 3) {
            int target = fn_80201B44();
            if (target != 0 && target != -1) {
                fn_80201DD8(relation, (void *)target);
                fn_800C80E8(object, 1, 0xF);
            }
            return 1;
        } else if (kind == 0xE3) {
            return 1;
        }
    } else if (state == 1) {
        if (kind == 1) {
            int current_identifier = fn_80201B44();
            fn_80201DD8(relation, (void *)current_identifier);
            return 1;
        } else if (kind == 0x12) {
            fn_800C81E0(object);
            return 1;
        } else if (kind == 0xE3) {
            fn_800C77FC(0, object);
            return 1;
        } else if (kind == 0xD7) {
            void *target = fn_80200C38(event);
            fn_80201DD8(relation, target);
            fn_80201D2C(object, 6);
            fn_80201D14(object, 1);
            return 1;
        } else if (kind == 3) {
            fn_800C76DC(object);
            fn_800C80E8(object, 1, 0xF);
            fn_800C7540(object);
            return 1;
        }
    } else if (state == 6) {
        if (kind == 1) {
            fn_800C82F0(object);
            return 1;
        } else if (kind == 0xD8) {
            fn_80201D2C(object, 0x12);
            fn_80201D14(object, 1);
            return 1;
        } else if (kind == 0x3E) {
            fn_800C77B4(0, object);
            return 1;
        } else if (kind == 0xC) {
            fn_800C78C4(0, object);
            return 1;
        } else if (kind == 3) {
            fn_800C80E8(object, 1, 0xF);
            fn_800C7E40(object);
            return 1;
        } else if (kind == 0xE3) {
            return 1;
        } else if (kind == 2) {
            return 1;
        }
    } else if (state == 0x12) {
        if (kind == 1) {
            fn_800C7DCC(object);
            return 1;
        } else if (kind == 0x25) {
            fn_8020104C(0xDD, identifier, identifier, 0, lbl_8064F210);
            return 1;
        } else if (kind == 0xDD) {
            fn_800C7B74(object);
            return 1;
        } else if (kind == 0x24) {
            fn_80201D2C(object, 0x10);
            fn_80201D14(object, 1);
            return 1;
        } else if (kind == 3) {
            fn_800C7C0C(object);
            return 1;
        } else if (kind == 0xE3) {
            return 1;
        }
    } else if (state == 0x10) {
        if (kind == 1) {
            fn_800C7AEC(object);
            return 1;
        } else if (kind == 3) {
            fn_800C7A54(object);
            return 1;
        } else if (kind == 0xDD) {
            return 1;
        } else if (kind == 0xE3) {
            return 1;
        }
    } else if (state == 0xE) {
        if (kind == 1) {
            return 1;
        } else if (kind == 0xDD) {
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
