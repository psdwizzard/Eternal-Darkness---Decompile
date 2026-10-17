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
typedef struct Marker {
    const short* position;
    unsigned char pad04[0x32];
    unsigned char id;
    unsigned char pad37;
} Marker;
typedef struct Owner Owner;
typedef struct Entry80201814 Entry80201814;
typedef struct RuntimeState RuntimeState;
typedef struct Object80201D34 Object80201D34;
typedef struct Object80201D1C Object80201D1C;
typedef struct Object80201D2C Object80201D2C;
typedef struct Object80201D14 Object80201D14;
typedef struct Vec3f { float x, y, z; } Vec3f;

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
extern void fn_8020104C(int, int, int, int, float);
extern void* fn_8011FB4C(void*);
extern void fn_8011FB54(void*, void*);
extern void fn_800DE468(int);
extern void fn_800DD314(void*, int, u8, int);
extern void* fn_8008F224(int, int, int);
extern Entry80201814* fn_80201814(int);
extern Marker* fn_800BC100(const short*, Vec3*, int*, unsigned int,
                            int*, int*, Vec3*);
extern void fn_800BCCC4(const short*, Vec3f*);
extern void fn_8011F0E8(Vec3*, Vec3*);
extern void fn_80048708(Vec3*);
extern int fn_800DE298(void*);
extern int fn_801261F4(Owner*);
extern void fn_800DFD54(int, void*, void*, void*);
extern void* fn_80036D5C(void*);
extern void fn_80036DA4(void*, void*);
extern void fn_80201D34(Object80201D34*, int);
extern void fn_80201D1C(Object80201D1C*, u8);
extern int fn_800BD2DC(int*, RuntimeState*);
extern void fn_80201D2C(Object80201D2C*, int);
extern void fn_80201D14(Object80201D14*, u8);
extern void fn_80201138(int, void*, int, int, int, float);
extern void fn_8008F5B4(void*, void*, void*, void*, int*, void*, void*,
                        Runtime*, void*, void*);
extern int fn_80201B64(int*);
extern int fn_80201B6C(int*);
extern int fn_80201B5C(int*);
extern int fn_80201B7C(int*);
extern void fn_8012B344(void*);
extern int fn_80090204(void*);
extern void fn_8016B400(int, void*, void*);

void fn_8008FB9C(void* object, void* actor, int target, Vec3 position,
                 int* link, void* state, void* extra, Runtime* runtime,
                 void* resource)
{
    u8* amount_column;
    u8* value_column;
    void* current;
    void* value;

    lbl_8064C564++;
    fn_8008F860((void*)target);
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
            void* owner = fn_8008F224((int)lbl_8064D18C, 0, 0);
            if (fn_80201814((int)owner) != 0) {
                Vec3 destination;
                int id = lbl_8031D3F8[lbl_8064C578][lbl_8064C560][lbl_8064C564].id;
                Marker* marker = fn_800BC100(0, 0, &id, 16, 0, 0, 0);
                fn_800BCCC4(marker->position, (Vec3f*)&destination);
                fn_8011F0E8(actor, &destination);
                fn_80048708(actor);
                if (fn_800DE298(object)) {
                    fn_801261F4(actor);
                    fn_800DFD54(1, object, actor, 0);
                }
                fn_80036DA4(object, (void*)((int)fn_80036D5C(object) | 0x2100000));
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
                    fn_8008F860((void*)target);
                    fn_80201138(23, object, 0x39, 0x49, 0, lbl_8064EC44);
                } else {
                    lbl_8064C564 = 1;
                    fn_8008F860((void*)target);
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
            Vec3 copied;
            copied = position;
            fn_8008F5B4(object, actor, (void*)target, &copied, link, state, extra,
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
