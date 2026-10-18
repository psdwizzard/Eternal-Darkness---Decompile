typedef unsigned char u8;
typedef signed int s32;

#pragma use_lmw_stmw on

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct OwnerData {
    u8 pad[0x90];
    void* range;
} OwnerData;

extern unsigned int rand(void);
#define rand() ((int)rand())
extern void *fn_80201B8C();
extern void* fn_80201B94();
extern void *fn_80201BC8();
extern void fn_800360B0(void*, void*);
extern void* fn_80201C48(void*);
extern void* fn_80072354(void*);
extern void fn_8011F114();
extern void *fn_80201814();

/* NonMatching: honest reconstruction of the randomized range selector. */
s32 fn_8008A808(void* object, s32 enabled)
{
    register OwnerData* owner;
    register void* secondary;
    register void* resource;
    register s32 random;
    register s32 result;
    unsigned short status;
    Vec3 position;
    void* selection;

    random = rand() % 100;
    result = -1;
    owner = ((OwnerData*)fn_80201B8C(object));
    secondary = fn_80201B94(object);
    resource = fn_80201BC8(object);
    fn_800360B0(object, &status);
    selection = fn_80201C48(secondary);
    fn_80072354(owner->range);
    fn_8011F114(&position, resource);
    fn_80201814(selection);
    if (random <= 100 && enabled != 0)
        result = 4;
    return result;
}
