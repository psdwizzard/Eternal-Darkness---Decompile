typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef float f32;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef union {
    u8 bytes[144];
    double alignment;
    struct {
        u8 prefix[40];
        u8 body[104];
    } layout;
} SpawnHeader;

typedef struct {
    u8 bytes[172];
} SpawnInfo;

typedef struct {
    s32 first;
    s32 second;
} ValuePair;

typedef struct {
    char invalid_count[52];
    f32 colour[3];
    f32 origin[3];
    char missing_marker[25];
} MarkerDiagnostics;

MarkerDiagnostics lbl_8023CBC8 = {
    "\nInvalid Num of Markers! Expecting %i, and got %i",
    { 0.2f, 0.2f, 0.2f },
    { 0.0f, 0.0f, 0.0f },
    "Could not find marker %u"
};
extern const f32 lbl_8064DCF4;
extern const f32 lbl_8064DE70;
extern const f32 lbl_8064DE74;
extern double lbl_8064DE68;
extern s32 lbl_8064D1BC;
extern s32 lbl_8064D18C;

extern double fn_8016A694(void*, int);
extern int fn_8016A598(void*);
extern void fn_80163BB4(void*, const char*, ...);
extern void fn_8016A830(void*, double);
extern unsigned int fn_800F5C54(double);
extern void fn_80196578(void*);
extern void fn_8018F81C(void*, u8);
extern void* fn_801D3974(int);
extern int fn_8015C4A4(void*, int);
extern Vec3s* fn_80158ABC(int, int, void*);
extern void fn_80211AAC(f32*, f32*);
extern void* fn_80147EC4(void*);
extern void fn_801964E8(void*, s32, s32);
extern void fn_801978F8(void*, u16);
extern void* fn_80142A70(u8, Vec3s*, s16, u32, void*, void*, void*, int);
extern int fn_8014B8D0(void*, void*);
extern void* fn_801966E0(void*, int, int);
extern void fn_8014BA14(Vec3s, Vec3s, u32, void*);


static inline void* CreateTriggerRing(Vec3s* endpoints, s32 width, void* owner,
                                      s32 user_value)
{
    return fn_80142A70(2, endpoints, width, lbl_8064D18C, 0,
                       (void*)fn_8014BA14, owner, user_value);
}

s32 fn_80017FF8(void* script)
{
    void* id;
    SpawnHeader header;
    u8* body;
    SpawnInfo info;
    Vec3s endpoints[2];
    f32 direction[3];
    ValuePair values;
    s32 kind;
    s32 mode;
    s32 user_value;
    s32 flags;
    s32 handle;
    s32 width;
    f32 min_z;
    f32 max_z;
    f32 best_low;
    f32 best_high;
    s32 count;
    s32 i;

    handle = -1;
    count = (s32)fn_8016A694(script, 1);
    if (fn_8016A598(script) != count + 4) {
        fn_80163BB4(script, lbl_8023CBC8.invalid_count, count + 4,
                    fn_8016A598(script));
        fn_8016A830(script, lbl_8064DE68);
        return 1;
    }

    flags = 0;
    body = header.layout.body;
    kind = (s32)fn_8016A694(script, 2);
    mode = (s32)fn_8016A694(script, 3);
    user_value = (s32)fn_8016A694(script, 4);

    fn_80196578(&header);
    *(s16*)&header.bytes[4] = -1;
    fn_8018F81C(&header, (u8)count);

    *(u16*)&header.bytes[48] = 15;
    header.bytes[41] = 9;
    header.bytes[42] = (u8)count;
    if (lbl_8064D1BC == 0x89C || lbl_8064D1BC == 0xADE ||
        lbl_8064D1BC == 0x33D || lbl_8064D1BC == 0x395) {
        *(u16*)&header.bytes[28] = 100;
    }
    header.bytes[40] = 0;

    values.second = values.first = (s32)fn_801D3974(kind);
    ((u8*)&values.second)[3] = 60;
    ((u8*)&values.first)[3] = 150;

    switch (kind) {
    case 1:
        flags = 0x20;
        break;
    case 2:
        flags = 0x08;
        break;
    case 3:
        flags = 0x10;
        break;
    case 4:
        flags = 0x40;
        break;
    case 0:
        flags = 0x100;
        break;
    }

    *(s32*)&header.bytes[20] = values.second;
    *(s32*)&header.bytes[24] = values.first;
    header.bytes[33] = 9;
    header.bytes[36] = 3;
    *(u16*)&header.bytes[30] = (u16)flags;
    header.bytes[44] |= 0x81;
    header.bytes[43] = 0;

    endpoints[0] = *fn_80158ABC(fn_8015C4A4((void*)fn_800F5C54(fn_8016A694(script, 5)), 2), 2, 0);
    endpoints[1] = *fn_80158ABC(fn_8015C4A4((void*)fn_800F5C54(fn_8016A694(script, 7)), 2), 2, 0);
    direction[0] = (f32)(endpoints[1].x - endpoints[0].x);
    direction[1] = (f32)(endpoints[1].y - endpoints[0].y);
    direction[2] = lbl_8064DCF4;
    fn_80211AAC(direction, direction);

    min_z = (f32)endpoints[0].z;
    max_z = (f32)endpoints[0].z;
    best_low = lbl_8064DE70;
    best_high = lbl_8064DE74;
    for (i = 0; i < count; i++) {
        Vec3s* point;
        f32 distance;

        point = fn_80158ABC(
            fn_8015C4A4((void*)fn_800F5C54(fn_8016A694(script, i + 5)), 2),
            2, 0);
        distance = direction[0] * point->x +
                   direction[1] * point->y +
                   direction[2] * point->z;
        if ((f32)point->z < min_z) {
            min_z = point->z;
        }
        if ((f32)point->z > max_z) {
            max_z = point->z;
        }
        if (distance > best_high) {
            best_high = distance;
            endpoints[1] = *point;
        }
        if (distance < best_low) {
            best_low = distance;
            endpoints[0] = *point;
        }
        *(Vec3s*)&body[64] = *point;
        body += 6;
    }

    *(SpawnHeader*)&info = header;
    *(void**)&info.bytes[144] = (void*)fn_801966E0;
    info.bytes[170] = 0x84;
    if (fn_80147EC4(&info) != 0) {
        void* object = *(void**)&info.bytes[148];

        fn_801964E8(object, 1, 0);
        fn_801978F8(object, 0);
        endpoints[0].z = (s16)min_z;
        endpoints[1].z = (s16)min_z;
        width = (s16)(max_z - min_z);
        if (mode != 0) {
            id = CreateTriggerRing(endpoints, width, object, user_value);
        } else {
            id = fn_80142A70(2, endpoints, width, lbl_8064D18C, 0, 0, 0,
                             user_value);
        }
        handle = fn_8014B8D0(object, id);
    }

    fn_8016A830(script, (double)handle);
    return 1;
}
