typedef unsigned short u16;

typedef struct Animation {
    u16 flags;
    unsigned char pad_2[0x10E];
} Animation;

void fn_801F60FC(u16 count, Animation* animation)
{
    u16 i;

    for (i = 0; i < count; i++, animation++) {
        animation->flags ^= 0x10;
    }
}
