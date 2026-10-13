typedef unsigned char u8;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct SceneEntry {
    int mode;
    void* value;
    short id;
    short unused0;
    short unused1;
    short amount;
} SceneEntry;
typedef struct Wrapper { void* object; } Wrapper;
typedef struct Runtime { unsigned char pad[0x8C]; void* resource; } Runtime;

#define SCENE_FIELD_AT(type, column, scene, row, index)                   \
    (*(type*)((column) + (scene) * sizeof(SceneEntry) * 8 +              \
              (row) * sizeof(SceneEntry) * 4 +                          \
              (index) * sizeof(SceneEntry)))

extern SceneEntry lbl_8031D3F8[][2][4];
extern int lbl_8064C560;
extern int lbl_8064C564;
extern int lbl_8064C578;
extern void* lbl_8064D18C;
extern const float lbl_8064EC44;

extern void fn_8008F860(void*);
extern void fn_8020104C(int, void*, void*, int, float);
extern void* fn_8011FB4C(void*);
extern void fn_8011FB54(void*, void*);
extern void fn_800DE468(int);
extern void fn_800DD314(void*, int, int, int);
extern void* fn_8008F224(void*, int, int);
extern void* fn_80201814();
extern Wrapper* fn_800BC100(int, int, int*, int, int, int, int);
extern void fn_800BCCC4(void*, Vec3*);
extern void fn_8011F0E8(void*, Vec3*);
extern void fn_80048708(void*);
extern int fn_800DE298(void*);
extern int fn_801261F4(void*);
extern void fn_800DFD54(int, void*, void*, int);
extern int fn_80036D5C(void*);
extern void fn_80036DA4(void*, int);
extern void fn_80201D34(void*, int);
extern void fn_80201D1C(void*, int);
extern void fn_800BD2DC(void*, void*);
extern void fn_80201D2C(void*, int);
extern void fn_80201D14(void*, int);
extern void fn_80201138(int, void*, int, int, int, float);
extern void fn_8008F5B4(void*, void*, void*, Vec3*, int*, void*, void*,
                        Runtime*, void*, void*);
extern void fn_80201B64(void*);
extern void fn_80201B6C(void*);
extern void fn_80201B5C(void*);
extern void fn_80201B7C(void*);
extern void fn_8012B344(void*);
extern void fn_80090204(void*);
extern void fn_8016B400(int, void*, int);

void fn_8008FB9C(void* object, void* actor, void* target, Vec3* position,
                 int* link, void* state, void* extra, Runtime* runtime,
                 void* resource)
{
    u8* amount_column;
    u8* value_column;
    void* current;
    void* value;

    lbl_8064C564++;
    fn_8008F860(target);
    amount_column = (u8*)&lbl_8031D3F8[0][0][0].amount;
    fn_8020104C(23, target, target, -1,
                (float)SCENE_FIELD_AT(short, amount_column, lbl_8064C578,
                                      lbl_8064C560, lbl_8064C564));
    current = fn_8011FB4C(actor);
    value_column = (u8*)&lbl_8031D3F8[0][0][0].value;
    value = SCENE_FIELD_AT(void*, value_column, lbl_8064C578, lbl_8064C560,
                           lbl_8064C564);
    fn_8011FB54(actor, value);
    fn_800DE468((int)current == (int)lbl_8064D18C ||
                (int)value == (int)lbl_8064D18C);

    if ((int)value == (int)lbl_8064D18C) {
        fn_800DD314(object, 15, 255, 0);
        if (lbl_8031D3F8[lbl_8064C578][lbl_8064C560][lbl_8064C564].mode == 1) {
            void* owner = fn_8008F224(lbl_8064D18C, 0, 0);
            if (fn_80201814() != 0) {
                Vec3 destination;
                int id = lbl_8031D3F8[lbl_8064C578][lbl_8064C560][lbl_8064C564].id;
                Wrapper* wrapper = fn_800BC100(0, 0, &id, 16, 0, 0, 0);
                fn_800BCCC4(wrapper->object, &destination);
                fn_8011F0E8(actor, &destination);
                fn_80048708(actor);
                if (fn_800DE298(object)) {
                    fn_801261F4(actor);
                    fn_800DFD54(1, object, actor, 0);
                }
                fn_80036DA4(object, fn_80036D5C(object) | 0x2100000);
                link[5] = (int)owner;
                fn_80201D34(object, 9);
                fn_80201D1C(object, 1);
            } else {
                int next;
                lbl_8064C564 = 0;
                next = lbl_8064C560 + 1;
                lbl_8064C560 = next;
                if (next >= 2 || lbl_8031D3F8[lbl_8064C578][next][0].mode == 0) {
                    link[5] = 0;
                    fn_800BD2DC(object, resource);
                    fn_8011FB54(actor, (void*)0xEF);
                    fn_80201D2C(object, 0x39);
                    fn_80201D14(object, 1);
                    fn_8008F860(target);
                    fn_80201138(23, object, 0x39, 0x49, 0, lbl_8064EC44);
                } else {
                    lbl_8064C564 = 1;
                    fn_8008F860(target);
                    fn_8020104C(23, target, target, -1,
                                (float)SCENE_FIELD_AT(short, amount_column,
                                                      lbl_8064C578, lbl_8064C560,
                                                      lbl_8064C564));
                    fn_8011FB54(actor,
                                SCENE_FIELD_AT(void*, value_column, lbl_8064C578,
                                               lbl_8064C560, lbl_8064C564));
                }
            }
        } else {
            Vec3 copied = *position;
            fn_8008F5B4(object, actor, target, &copied, link, state, extra,
                        runtime, resource, lbl_8064D18C);
        }
    } else if (lbl_8031D3F8[lbl_8064C578][lbl_8064C560][lbl_8064C564].mode == 1) {
        fn_80201B64(object);
        fn_80201B6C(object);
        fn_80201B5C(object);
        fn_80201B7C(object);
        fn_801261F4(actor);
        fn_8012B344(actor);
        fn_80090204(object);
        fn_8016B400(0x49F, value, 0);
    }
}

#undef SCENE_FIELD_AT
