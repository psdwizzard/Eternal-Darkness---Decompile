typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Shape {
    u8 data[0x3c];
} Shape;

typedef struct Hit {
    u8 data[0x18];
} Hit;

extern u8 lbl_8063D378[];
extern float lbl_80650110;
extern float lbl_80650138;
extern float lbl_80650180;
extern s32 lbl_8064D738;
extern u8 lbl_804F3650[];

extern float fn_8017968C(void*, void*);
extern s32 fn_80126050(void*);
extern void fn_80120B58(void*);
extern void fn_801248FC(void*);
extern void fn_80124180(void*, s32);
extern void fn_801243A8(void*);
extern s32 fn_80130998(u16, float);
extern void* fn_80120744(void*, s32, float);
extern void* fn_801208AC(void*, s32, float);
extern void fn_80124A40(void*, void*, u32*, u32*);
extern void fn_80125300(void*, void*, u32, u32, void*, void*, void*, s32,
                       s32, float);
extern s32 fn_8011F134(void*);
extern void fn_80127F90(void*, s32, Vec3*);
extern void* fn_8012AB2C(void*);
extern void fn_8013F3C0(Shape*, Vec3*, Vec3*, float);
extern void* fn_8013FBE4(void*, Shape*, Hit*, s32, s32);
extern void DCFlushRange(void*, u32);

#define U8(p, o) (*(u8*)((u8*)(p) + (o)))
#define U16(p, o) (*(u16*)((u8*)(p) + (o)))
#define U32(p, o) (*(u32*)((u8*)(p) + (o)))
#define F32(p, o) (*(float*)((u8*)(p) + (o)))

void fn_80124DBC(void* owner)
{
    void* table = (void*)U32(owner, 0x3C);
    float scale = fn_8017968C(owner, lbl_8063D378);
    float frame = F32(owner, 0x2AC);
    s32 first_count;
    s32 second_count;
    u32 first;
    u32 second;
    s32 triple;
    Vec3 position;
    Vec3 lowered;
    Shape shape;
    Hit hit;
    void* collision;

    if (U32(owner, 0x2A0) == 0) {
        return;
    }
    if (lbl_80650110 == frame) {
        return;
    }
    if (!fn_80126050(owner)) {
        return;
    }

    if (U32(owner, 0x254) & 0x10000000) {
        U32((void*)U32(owner, 0x2A0), 0) &= ~4;
    } else {
        U32((void*)U32(owner, 0x2A0), 0) &= ~4;
    }
    fn_80120B58(owner);
    if (U8(owner, 0x2DE) != 0) {
        if (U8(owner, 0x2DE) < U8(owner, 0x2DF))
            U8(owner, 0x2DE) = 0;
        else
            U8(owner, 0x2DE) -= U8(owner, 0x2DF);
    }

    if ((U32(owner, 0x254) & 0x80000) == 0)
        return;

    fn_801248FC(owner);
    fn_80124180(owner, 0);
    fn_801243A8(table);
    first_count = fn_80130998(U16(table, 0x1E), frame);
    second_count = fn_80130998(U16(table, 0x1E), frame);
    triple = U32(owner, 0x254) & 0x400000;
    if (triple)
        second_count *= 3;

    *(void**)((u8*)owner + 0x164 + lbl_8064D738 * 4) =
        fn_80120744(owner, first_count, frame);
    *(void**)((u8*)owner + 0x16C + lbl_8064D738 * 4) =
        fn_801208AC(owner, second_count, frame);

    if (*(void**)((u8*)owner + 0x164 + lbl_8064D738 * 4) != 0 &&
        *(void**)((u8*)owner + 0x16C + lbl_8064D738 * 4) != 0) {
        fn_80124A40(owner, table, &first, &second);
        fn_80125300(owner, table, first, second,
                    *(void**)((u8*)owner + 0x164 + lbl_8064D738 * 4),
                    *(void**)((u8*)owner + 0x16C + lbl_8064D738 * 4),
                    lbl_804F3650, first_count,
                    triple, scale);
    } else {
        U32(owner, 0x254) &= ~0x80000;
        *(void**)((u8*)owner + 0x164 + lbl_8064D738 * 4) = 0;
        *(void**)((u8*)owner + 0x16C + lbl_8064D738 * 4) = 0;
    }

    DCFlushRange(*(void**)((u8*)owner + 0x164 + lbl_8064D738 * 4),
                 first_count * 6);
    DCFlushRange(*(void**)((u8*)owner + 0x16C + lbl_8064D738 * 4),
                 second_count * 6);

    if (U16(owner, 0x2D0) & 0x2000) {
        s32 index = fn_8011F134(owner);
        if (index == 0xFFFF) {
            fn_80127F90(owner, 0, &position);
        } else {
            fn_80127F90(owner, index, &position);
        }

        collision = fn_8012AB2C(owner);
        lowered = position;
        lowered.z -= lbl_80650180;
        fn_8013F3C0(&shape, &position, &lowered, lbl_80650138);
        if (collision != 0) {
            if (fn_8013FBE4(collision, &shape, &hit, 0, 0) != 0) {
                F32(owner, 0x14) = *(float*)((u8*)&hit + 8);
                U32(owner, 0x254) |= 0x100;
            } else {
                U32(owner, 0x254) &= ~0x100;
            }
        } else {
            F32(owner, 0x14) = F32(owner, 8);
        }
    }
}
