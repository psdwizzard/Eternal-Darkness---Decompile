typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 { u32 x, y, z; } Vec3;
typedef struct Coord3 { short x, y, z; } Coord3;
typedef struct EffectDesc { u8 bytes[0x98]; } EffectDesc;
typedef struct EffectWork { u8 bytes[0x90]; } EffectWork;

extern int lbl_8064D18C;
extern u32 lbl_80650600;
extern u16 lbl_80650604;
extern int fn_8015C9F0(void);
extern void fn_80149E28(void*);
extern void fn_801A1A04(EffectDesc*);
extern void* fn_80154CB4(Vec3*, short*, EffectDesc*, float);
extern unsigned int rand(void);
#define rand() ((int)rand())
extern void* fn_80154D24(Vec3*, void*, EffectWork*);

void fn_80154B6C(void* object)
{
    EffectDesc desc;
    EffectWork effect;
    Coord3 position;
    u16 delay;

    if (*(int*)((char*)object + 0x1324) != lbl_8064D18C || fn_8015C9F0() == 1) {
        fn_80149E28(object);
        return;
    }

    if (*(u8*)((char*)object + 0x26) == 0) {
        fn_801A1A04(&desc);
        desc.bytes[0x19] = *(u8*)((char*)object + 0x25);
        fn_80154CB4((Vec3*)((char*)object + 0xC),
                    (short*)((char*)object + 0x18), &desc,
                    *(float*)((char*)object + 8));
        if (*(u8*)((char*)object + 0x24)) {
            delay = *(u16*)((char*)object + 0x20) +
                    rand() % *(u16*)((char*)object + 0x22);
        } else {
            delay = (rand() & 0xFFF) + 1;
        }
        *(u16*)((char*)object + 0x1E) = delay;
        *(u8*)((char*)object + 0x26) = 1;
    }

    delay = *(u16*)((char*)object + 0x1E);
    if (delay == 0) {
        *(u32*)&position = lbl_80650600;
        *(u16*)((char*)&position + 4) = lbl_80650604;
        fn_80154D24((Vec3*)((char*)object + 0xC), &position, &effect);
        if (*(u8*)((char*)object + 0x24)) {
            delay = *(u16*)((char*)object + 0x20) +
                    rand() % *(u16*)((char*)object + 0x22);
        } else {
            delay = (rand() & 0xFFF) + 60;
        }
        *(u16*)((char*)object + 0x1E) = delay;
    } else {
        *(u16*)((char*)object + 0x1E) = delay - 1;
    }
}
