typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3f {
    float x, y, z;
} Vec3f;

extern void fn_8014B738(void);
extern void* fn_80149D98(void (*)(void));
extern void fn_80149D64(void*);
extern void fn_80181F5C(void*);
extern void fn_80182014(void);
extern unsigned int rand(void);
#define rand() ((int)rand())
extern void* memcpy(void*, const void*, u32);
extern int fn_801E8328();

void fn_80152A88(Vec3f* position, Vec3f* target, u16 kind, u8 mode)
{
    u8 key[8];
    u8* instance;
    u8* work;

    instance = fn_80149D98(fn_8014B738);
    if (instance != 0) {
        fn_80149D64(instance);
        work = instance + 8;
        instance[0x1328] = mode;
        fn_80181F5C(work);
        *(signed char*)(work + 3) = -5;
        *(u16*)(work + 4) = kind;
        work[0] = 30;
        work[1] = 4;
        *(u16*)(work + 6) = (rand() & 3) + 5;
        *(u16*)(work + 8) = *(u16*)(work + 6);
        work[0x14] = 4;
        *(u32*)(work + 0x18) = 0;
        *(u32*)(work + 0x1C) = 0;
        *(void (**)(void))(work + 0x90) = fn_80182014;
        *(Vec3f*)(work + 0x98) = *position;
        *(s16*)(key + 0) = target->x - position->x;
        *(s16*)(key + 2) = target->y - position->y;
        *(s16*)(key + 4) = target->z - position->z;
        memcpy(work + 0xA4, key, 6);
        *(u32*)(work + 0x94) = 0;
        work[0xAA] = mode;
        fn_801E8328(0x10, work);
    }
}
