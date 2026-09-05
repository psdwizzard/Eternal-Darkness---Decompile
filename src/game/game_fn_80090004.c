typedef unsigned char u8;
typedef struct SceneEntry {
    int mode;
    void* value;
    short unused0;
    short unused1;
    short unused2;
    short amount;
} SceneEntry;

#define SCENE_VALUE_AT(value_column, scene, row, column)                   \
    (*(void**)((value_column) + (scene) * sizeof(SceneEntry) * 8 +        \
               (row) * sizeof(SceneEntry) * 4 +                          \
               (column) * sizeof(SceneEntry)))

extern SceneEntry lbl_8031D3F8[][2][4];
extern int lbl_8064C560;
extern int lbl_8064C564;
extern int lbl_8064C578;
extern const float lbl_8064EC24;

extern void* fn_8008F224(void*, int, int);
extern void *fn_80201814(void *);
extern void *fn_80201B8C(void *);
extern int fn_80201B44(void);
extern void fn_801ACACC(int, int, void*, int);
extern void fn_800DE4D8(void*, int);
extern void *fn_80201BC8(void *);
extern unsigned int fn_8011FA8C(void*, int, int);
extern int fn_80036D5C(void*);
extern void fn_80036DA4(void*, int);
extern int fn_80201EB8(void *);
extern void fn_80201D34(void*, int);
extern void fn_80201D1C(void*, int);
extern void fn_8008F860(void*);
extern void fn_800BD2DC(void*, void*);
extern void fn_8011FB54(void*, void*);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_80201138(int, void*, int, int, int, float);
extern void fn_8020104C(int, void*, void*, int, float);

void fn_80090004(void* object, void* actor, void* target, void* unused4,
                 void* unused5, void* unused6, void* unused7, void* unused8,
                 void* resource)
{
    u8* value_column = (u8*)&lbl_8031D3F8[0][0][0].value;
    void* state;
    void* owner = fn_8008F224(
        SCENE_VALUE_AT(value_column, lbl_8064C578, lbl_8064C560, lbl_8064C564),
        1, 1);
    int next;

    state = fn_80201814(owner);
    fn_80201B8C(state);
    fn_801ACACC(0xC1, 0x4B, ((void*)fn_80201B44()), 0x82);
    fn_800DE4D8(owner, 2);
    fn_8011FA8C(fn_80201BC8(state), 0, 0x02000000);
    fn_80036DA4(state, fn_80036D5C(state) | 0x80000);
    lbl_8064C564 = 0;
    next = lbl_8064C560 + 1;
    lbl_8064C560 = next;
    if (next >= 2 || lbl_8031D3F8[lbl_8064C578][next][0].mode == 0) {
        fn_80201EB8(object);
        if (lbl_8064C578 == 2) {
            fn_80201D34(object, 9);
            fn_80201D1C(object, 1);
        } else {
            fn_8008F860(target);
            fn_800BD2DC(object, resource);
            fn_8011FB54(actor, (void*)0xEF);
            fn_80201D2C(object, 0x39);
            fn_80201D14(object, 1);
            fn_80201138(23, object, 0x39, 0x49, 0, lbl_8064EC24);
        }
    } else {
        short amount = lbl_8031D3F8[lbl_8064C578][next][0].amount;
        fn_8008F860(target);
        fn_8020104C(23, target, target, -1, (float)amount);
        fn_8011FB54(actor, SCENE_VALUE_AT(value_column, lbl_8064C578,
                                         lbl_8064C560, lbl_8064C564));
    }
}

#undef SCENE_VALUE_AT
