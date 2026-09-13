typedef unsigned int u32;

typedef struct Triple {
    u32 x;
    u32 y;
    u32 z;
} Triple;

extern void* fn_80201C24();
extern void *fn_80201BC8();
extern u32 fn_80157894(void *);
extern int fn_801261F4(void *);
extern int fn_801E1E38(void);
extern void* fn_8012C62C(void *, int, u32 *, u32 *, u32 *, int);
extern u32 fn_80036D5C(void *);
extern void fn_80120AD0(void *, int, int, int, float, float);
extern u32 lbl_8064F4C0;
extern u32 lbl_8064F4C4;
extern u32 lbl_80651AE0;
extern u32 lbl_80651AE4;
extern u32 lbl_80651AE8;
extern u32 lbl_80651AEC;
extern u32 lbl_80651AF0;
extern u32 lbl_80651AF4;
extern u32 lbl_80651AF8;
extern float lbl_8064F460;
extern float lbl_8064F464;

#pragma opt_common_subs off
void fn_800DBC0C(void *context)
{
    void *state;
    void *object;
    void *saved_context = context;

    state = fn_80201C24(saved_context);
    object = fn_80201BC8(saved_context);

    if ((fn_80157894(state) & 0x10) != 0) {
        fn_801261F4(object);
        if (fn_801E1E38() != 0) {
            Triple value;
            value.x = lbl_8064F4C4;
            value.y = lbl_80651AE0;
            value.z = lbl_8064F4C0;
            fn_8012C62C(object, 15, &value.z, &value.y, &value.x, 4);
        } else {
            Triple value;
            value.x = lbl_80651AEC;
            value.y = lbl_80651AE8;
            value.z = lbl_80651AE4;
            fn_8012C62C(object, 15, &value.z, &value.y, &value.x, 4);
        }
    } else if ((fn_80157894(state) & 8) != 0) {
        Triple value;
        fn_801261F4(object);
        value.x = lbl_80651AF8;
        value.y = lbl_80651AF4;
        value.z = lbl_80651AF0;
        fn_8012C62C(object, 15, &value.z, &value.y, &value.x, 4);
    }

    if ((fn_80036D5C(saved_context) & 0x01000000) != 0) {
        fn_801261F4(object);
        fn_80120AD0(object, 0, 100, 0x20a, lbl_8064F460, lbl_8064F464);
    }
}

#pragma opt_common_subs reset
