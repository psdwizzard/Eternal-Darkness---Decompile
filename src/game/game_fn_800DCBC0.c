typedef unsigned short u16;

typedef struct LinkedObject {
    unsigned char pad[8];
    u16 kind;
} LinkedObject;

extern int fn_80200C10(void *);
extern int fn_80200C38();
extern void *fn_80201BC8(void *);
extern void *fn_80201C24(void *);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_80201D34(void *, int);
extern void fn_80201D1C(void *, int);
extern void fn_8012B324(void);
extern void fn_801E8328(int, void *);
extern void fn_800DB9B0(void *);
extern void fn_800DB62C(void *);
extern void fn_800DBB24(void *, void *);
extern void *fn_8011FE4C(void);
extern void fn_8011FAEC(void);
extern int fn_80128EAC(void *);
extern int fn_8011FCE4(void *);
extern void *fn_80042748(void *, u16);
extern LinkedObject *fn_8004279C(void *);
extern void fn_8011FC38(void *, int, int);
extern int fn_8012A100(void *, int);
extern int fn_801290D0(void *);
extern int fn_8012915C(void *);
extern int fn_8011EB04(void *);
extern int fn_80127208(void *);
extern void fn_801291F0(void *, int, int);
extern void *fn_801294DC(void *, int, int, int);
extern int fn_80129748(void *);
extern void fn_801296F8(void *, int);
extern u16 fn_80157994(void);
extern void fn_80124664(void *, int, int, float);
extern float lbl_8064F460;
extern float lbl_8064F464;

int fn_800DCBC0(void *context, int phase, void *message, int *handled)
{
    int kind = fn_80200C10(message);
    void *object = fn_80201BC8(context);

    if (phase == 0) {
        if (kind == 1) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 240) {
            int value = fn_80200C38(message);
            fn_80201D34(context, value);
            fn_80201D1C(context, 1);
            if (handled != 0)
                *handled = 1;
            return 1;
        }
        if (kind == 61)
            return 1;
        if (kind == 62)
            return 1;
        if (kind == 57) {
            fn_8012B324();
            fn_80201D34(context, 0);
            fn_80201D1C(context, 1);
            fn_801E8328(2, context);
            return 1;
        }
    } else if (phase == 1) {
        if (kind == 190) {
            fn_800DB9B0(context);
            fn_800DB62C(context);
            return 1;
        }
        if (kind == 75) {
            fn_800DBB24(context, message);
            return 1;
        }
        if (kind == 3) {
            int source_model;
            int object_model;
            int source_kind;
            int object_kind;
            int existing;

            /* The message is no longer needed; reuse it for the source object. */
            message = fn_8011FE4C();
            fn_8011FAEC();
            source_model = fn_80128EAC(message);
            object_model = fn_80128EAC(object);
            source_kind = fn_8011FCE4(message);
            object_kind = fn_8011FCE4(object);

            if (object_kind != source_kind) {
                if (fn_80042748(object, (u16)source_kind) != 0) {
                    object_kind = source_kind;
                    fn_8011FC38(object, source_kind, 0);
                } else if (fn_80042748(object, 0) != 0) {
                    object_kind = 0;
                    fn_8011FC38(object, 0, 0);
                } else {
                    LinkedObject *linked = fn_8004279C(object);
                    if (linked != 0) {
                        object_kind = linked->kind;
                        fn_8011FC38(object, object_kind, 0);
                    }
                }
            }

            existing = fn_8012A100(object, 15);
            if (object_kind == source_kind) {
                int other = fn_8012A100(object, source_model);
                int object_flag = fn_801290D0(object) & 2;
                int source_flag = fn_801290D0(message) & 2;
                int different = source_flag != object_flag;

                fn_8012915C(object);
                fn_8012915C(message);
                if ((object_model != source_model || different) && other != 0 &&
                    fn_8011EB04(message) != 101 &&
                    fn_8011EB04(message) != 121 &&
                    fn_8011EB04(message) != 122 &&
                    fn_8011EB04(message) != 120) {
                    /* Dispatch is complete; reuse kind for the transition flags. */
                    kind = 0x30;
                    if (fn_8012915C(message) == 0)
                        kind = 0x10030;
                    if (different)
                        kind |= fn_801290D0(message) & 2;
                    if (fn_80127208(message) == 0)
                        kind |= 0x20000;
                    fn_801294DC(object, source_model, kind, 9);
                } else if (existing != 0 && object_model != source_model) {
                    fn_801291F0(object, 15, 3);
                    fn_801294DC(object, 15, 0x30, 9);
                }
            } else if (existing != 0) {
                fn_801291F0(object, 15, 3);
                fn_801294DC(object, 15, 0x30, 9);
            }

            fn_801296F8(object, fn_80129748(message));
            if (fn_8011EB04(object) == 112) {
                fn_80201C24(context);
                if (fn_80157994() != 0)
                    fn_80124664(object, 26, 8, lbl_8064F460);
                else
                    fn_80124664(object, 26, 8, lbl_8064F464);
            }
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
