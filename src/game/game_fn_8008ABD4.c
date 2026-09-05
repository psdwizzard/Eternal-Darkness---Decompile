typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Info {
    u8 pad48[0x48];
    void* field48;
    u8 pad4C[0x3C];
    void* field88;
    void* field8C;
    u8 pad90[4];
    int type94;
} Info;

typedef struct Data8C {
    u8 pad[0x14E];
    u16 timer;
} Data8C;

extern void *fn_80201BC8();
extern void *fn_80201B8C();
extern int fn_80201B54();
extern unsigned int fn_8015C910(void);
extern int fn_80204180(void*, void*);
extern void *fn_801294DC(void *, int, int, int);
extern void* fn_801A717C(void);
extern void fn_801A7460(void*, int);
extern void fn_801A74A0(void*, void*);
extern void fn_801A74A8(void*, void*);
extern void fn_801A74C8(void*, int);
extern void fn_801A7560(void*, int);
extern void fn_801A7550(void*, int);
extern void fn_801A7558(void*, int);
extern void fn_801A7538(void*, int);
extern void fn_801A7518(void*, int);
extern void* fn_8011F130(void*);
extern void fn_801A764C(void*, void*);
extern void fn_801287C4(void*, void*, void*, int);
extern void fn_80128C28();
extern void fn_80128C44(void*, void*, void*);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern unsigned int fn_800FBFB0(void);
#define fn_800FBFB0() ((int)fn_800FBFB0())
extern void fn_8008AE40(void);
extern void fn_8008C7A0(void);
extern void fn_802042A4(void);

int fn_8008ABD4(void* object, void* other, int unused, int forced)
{
    void* objectPosition;
    void* otherPosition;
    Info* info;
    void* owner;
    void* otherOwner;
    void* effect;
    void* config;
    int distance;

    if (object == 0 || other == 0)
        goto fail;
    objectPosition = fn_80201BC8(object);
    otherPosition = fn_80201BC8(other);
    if (objectPosition == 0 || otherPosition == 0)
        goto fail;
    info = ((Info*)fn_80201B8C(object));
    owner = ((void*)fn_80201B54(object));
    otherOwner = other != 0 ? ((void*)fn_80201B54(other)) : 0;
    if (fn_8015C910() != 0)
        return 0;
    distance = fn_80204180(object, other);
    if (!forced && distance > 500)
        goto fail;
    effect = fn_801294DC(objectPosition, 4, 0, 6);
    if (effect == 0)
        goto fail;
    config = fn_801A717C();
    fn_801A7460(config, 4);
    fn_801A74A0(config, owner);
    fn_801A74A8(config, otherOwner);
    fn_801A74C8(config, 1);
    fn_801A7560(config, 0x84);
    fn_801A7550(config, 0xC);
    fn_801A7558(config, 7);
    fn_801A764C(config, fn_8011F130(objectPosition));
    if (forced) {
        fn_801A7538(config, 1);
        fn_801A7518(config, 0x7FFE);
    } else {
        switch (info->type94) {
        case 1:
            fn_801A7538(config, 1);
            fn_801A7518(config, 10);
            break;
        case 2:
            fn_801A7538(config, 5);
            fn_801A7518(config, 25);
            break;
        case 3:
            fn_801A7538(config, 3);
            fn_801A7518(config, 25);
            break;
        }
    }
    fn_801287C4(effect, fn_8008AE40, config, 4);
    fn_80128C28(effect, fn_8008C7A0, config);
    fn_80128C44(effect, fn_802042A4, config);
    fn_80201D2C(object, 6);
    fn_80201D14(object, 1);
    ((Data8C*)info->field8C)->timer = (fn_800FBFB0() & 0x7F) + 600;
    *((u8*)info->field48 + 4) = 1;
    return 1;
fail:
    return 0;
}
