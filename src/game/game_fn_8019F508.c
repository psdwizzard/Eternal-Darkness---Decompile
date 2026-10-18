typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;

extern int fn_8018F0A0(void);
extern int rand(void);

void fn_8019F508(u8* object, u8* config)
{
    u16 lower;
    int random;
    int range;

    if (fn_8018F0A0()) {
        lower = *(u16*)(config + 0x16);
        random = rand();
        range = *(u16*)(config + 0x14) - lower;
        *(u16*)(object + 0x8C) = *(s16*)(object + 0x14) - lower - random % range;
    } else {
        lower = *(u16*)(config + 0x16);
        random = rand();
        range = *(u16*)(config + 0x14) - lower;
        *(u16*)(object + 0x8C) = *(s16*)(object + 0x14) + lower + random % range;
    }
}
