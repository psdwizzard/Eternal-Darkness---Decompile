typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Object {
    u8 bytes[0xFF6];
} Object;

extern int lbl_8064D18C;
extern const float lbl_80651178;

extern void fn_801FE22C(void*);
extern void fn_801B05B0(int, int);
extern void fn_801DAD68(void*);
extern int fn_801CEB2C(u32);
extern void* fn_801DA3B0(u32, u32, void*, u8, void*, u8, void**, void**,
                         void**, void**);
extern u16 fn_801DA058(u32);
extern void* fn_800CD458(void*, u32, u16, void*, void*, void*, void*);
extern int fn_80201B54(void*);
extern void fn_8020104C(int, int, int, int, float);
extern void fn_801FE934(void*, int);

void fn_801DADDC(Object* object)
{
    register unsigned long object_r = (unsigned long)object;
    if (*(int*)(((Object*)object_r)->bytes + 8) != lbl_8064D18C ||
        (((Object*)object_r)->bytes[0xFF0] & 1) != 0) {
        fn_801FE22C(*(void**)(((Object*)object_r)->bytes + 0x44));
        if (*(int*)(((Object*)object_r)->bytes + 0x10) != -1)
            fn_801B05B0(*(int*)(((Object*)object_r)->bytes + 0x10), 10);
        fn_801DAD68((void*)object_r);
    } else {
        switch (*(u16*)(((Object*)object_r)->bytes + 0xFF4)) {
        case 0: {
            void* owner;
            void* output_a;
            void* output_b;
            void* output_c;
            void* output_d;
            owner = *(void**)(((Object*)object_r)->bytes + 0xBC);

            *(void**)(((Object*)object_r)->bytes + 0xC8) =
                fn_801DA3B0(*(u32*)(((Object*)object_r)->bytes + 8),
                             *(u32*)(((Object*)object_r)->bytes + 4),
                             ((Object*)object_r)->bytes + 0x38,
                             (u8)fn_801CEB2C(*(u32*)(((Object*)object_r)->bytes + 4)),
                             owner, ((Object*)object_r)->bytes[0xC4], &output_a, &output_b,
                             &output_d, &output_c);
            * (u32*)output_c = fn_80201B54(
                fn_800CD458(owner, *(u32*)(((Object*)object_r)->bytes + 4),
                            fn_801DA058(*(u32*)(((Object*)object_r)->bytes + 4)),
                            output_a, output_b, output_d,
                            *(void**)(((Object*)object_r)->bytes + 0xC8)));
            fn_8020104C(0x5C, *(u32*)output_c, *(u32*)output_c, 0,
                        lbl_80651178);
            fn_801FE934(*(void**)(((Object*)object_r)->bytes + 0x44), 10);
            break;
        }
        case 0x8C:
            if (*(void (**)(Object*, u32))(((Object*)object_r)->bytes + 0x28) != 0)
                (*(void (**)(Object*, u32))(((Object*)object_r)->bytes + 0x28))(
                    (Object*)object_r,
                    *(u32*)(((Object*)object_r)->bytes + 0x2C));
            fn_801DAD68((void*)object_r);
            break;
        }
    }
}
