typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry80202C00 {
    char pad[0x2C];
    u32 type;
    char pad2[0x38];
    u32 flags;
    char pad3[8];
} Entry80202C00;

typedef struct List80202C00 {
    char pad[0xB0];
    u16 count;
    char pad2[2];
    Entry80202C00 *entries;
} List80202C00;

extern void *lbl_8064C4E0;
extern int lbl_8064D18C;

extern int fn_801E79FC(void *object, int value);
extern void fn_801E79A0(void *object, int value);
extern void fn_801E7974(void *object, int value);
extern List80202C00 *fn_8015C28C(int value);
extern void *fn_802019EC(int first, int second);
extern void fn_80201D2C(void *object, int value);
extern void fn_80201D14(void *object, int value);
extern unsigned long long fn_8020123C(int kind, void *target, void *value,
                                     int flags);

void fn_80202C00(int object, int event, void *target)
{
    if (fn_801E79FC(lbl_8064C4E0, 0x145) == 0) {
        if (event == 0x9C || event == 0x9D) {
            List80202C00 *list = fn_8015C28C(2);
            int found = 0;
            void *resource = fn_802019EC(0x145, 0x128);
            int i;

            for (i = 0; i < list->count; i++) {
                Entry80202C00 *entry = &list->entries[i];
                if (entry->type == 0xE98A39BB && (entry->flags & 1))
                    found = 1;
            }

            if (found != 0) {
                fn_80201D2C(target, 0xD);
                fn_80201D14(target, 1);
            } else {
                fn_801E79A0(lbl_8064C4E0, 0x143);
                fn_801E79A0(lbl_8064C4E0, 0x142);
                fn_801E79A0(lbl_8064C4E0, 0x2BC);
                fn_80201D2C(target, 0xE);
                fn_80201D14(target, 1);
                fn_8020123C(0xF0, resource, resource, 0);
            }
        }
    } else {
        if (event == 0x9C) {
            fn_80201D2C(target, 0xE);
            fn_80201D14(target, 1);
        }
        if (event == 0x9D) {
            fn_80201D2C(target, 0xE);
            fn_80201D14(target, 1);
        }
    }

    if (lbl_8064D18C == 0x9B &&
        fn_801E79FC(lbl_8064C4E0, 0x225) == 0 &&
        fn_801E79FC(lbl_8064C4E0, 0x155) == 1) {
        int expected = (int)fn_802019EC(0x109, 0x9B);
        fn_802019EC(0x27B, 0x9B);
        if (object == expected) {
            if (fn_801E79FC(lbl_8064C4E0, 0x27C) == 1) {
                fn_80201D2C(target, 0xD);
                fn_80201D14(target, 1);
                fn_801E7974(lbl_8064C4E0, 0x14);
            } else {
                fn_80201D2C(target, 0xE);
                fn_80201D14(target, 1);
                fn_801E79A0(lbl_8064C4E0, 0x14);
            }
        }
    }
}
