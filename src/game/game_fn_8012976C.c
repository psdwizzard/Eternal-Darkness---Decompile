typedef unsigned char u8;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Owner {
    Vec3 position;
    u8 pad0C[0x34];
    u8* effects;
} Owner;

extern u8* fn_80128E30(void*);
extern int fn_80129C2C(void*, u8*, int, int, int);
extern void fn_80129CE8(void*, u8*, int, int, int);
extern void fn_801299DC(u8*, Vec3*);
extern void fn_80129BA4(u8*, float, float);
extern void fn_80129DE0(void*, u8*, int, int);

u8* fn_8012976C(Owner* owner, int kind, int flags, Vec3* position, float scale)
{
    u8* entry = fn_80128E30(owner);
    if (fn_80129C2C(owner, entry, kind, flags, 5)) {
        u8* resource = *(u8**)(entry + 0xB8);
        if (resource != 0) {
            owner->effects[0x884] = resource[0xD];
        }
        fn_80129CE8(owner, entry, kind, flags, 5);
        fn_801299DC(entry, position);
        *(Vec3*)(entry + 0xD8) = owner->position;
        if ((*(int*)(entry + 0xF4) & 0x40) == 0) {
            fn_80129BA4(entry, 0.0f, scale);
        }
        fn_80129DE0(owner, entry, !(flags & 0x10000), 1);
    } else {
        entry = 0;
    }
    return entry;
}
