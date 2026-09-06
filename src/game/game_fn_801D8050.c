typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef float f32;

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct Key {
    u32 word;
    u16 half;
} Key;

typedef struct QueryResult {
    u8 pad00[8];
    Vec3f position;
    u8 pad14[0x14];
} QueryResult;

typedef struct Params {
    u8 pad00[0x14];
    u8 first;
    u8 pad15[0xD];
    u16 x;
    u16 y;
    u16 z;
    u8 pad28[0x10];
    u32 flags;
    u8 pad3C[0x54];
} Params;

extern u32 lbl_80651ED8;
extern u16 lbl_80651EDC;
extern const double lbl_806510D8;
extern void* fn_80201BC8(void*);
extern int fn_8011F598(void*, int, int, int, QueryResult*, int);
extern void fn_801938FC(Params*);
extern int fn_801D38E8(u32);
extern void fn_801D3CAC(int, int, void*);
extern void* fn_80148008(Vec3f*, Key*, Params*, void (*)(void));
extern void fn_801936FC(void);
extern void* fn_80156938(void*);
extern void fn_8017FF1C(void*, int);

void fn_801D8050(void* object, u32 type, const s16* first, const s16* second)
{
    Key key;
    Vec3f position;
    Vec3f first_position;
    Vec3f second_position;
    QueryResult query;
    Params params;
    u8* descriptor;
    int object_type;
    void* effect;

    object = fn_80201BC8(object);
    if (fn_8011F598(object, 0, 1, -1, &query, 1) != -1) {
        key.word = lbl_80651ED8;
        key.half = lbl_80651EDC;
        fn_801938FC(&params);
        descriptor = &params.first;
        *(u16*)(descriptor + 0xE) = (u16)(int)query.position.x;
        *(u16*)(descriptor + 0x10) = (u16)(int)query.position.y;
        *(u16*)(descriptor + 0x12) = (u16)(int)query.position.z;
        *(u32*)(descriptor + 0x24) = 0x4010;
        object_type = fn_801D38E8(type);
        fn_801D3CAC(object_type, 0, descriptor);

        position.x = first[0];
        position.y = first[1];
        position.z = first[2];
        first_position = position;
        effect = fn_80148008(&first_position, &key, &params, fn_801936FC);
        if (effect != 0)
            fn_8017FF1C(fn_80156938(effect), 4);

        position.x = second[0];
        position.y = second[1];
        position.z = second[2];
        second_position = position;
        effect = fn_80148008(&second_position, &key, &params, fn_801936FC);
        if (effect != 0)
            fn_8017FF1C(fn_80156938(effect), 4);
    }
}
