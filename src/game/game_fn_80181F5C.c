typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern unsigned int rand(void);

void fn_80181F5C(u8* effect)
{
    effect[0] = 15;
    effect[1] = 16;
    effect[2] = 240;
    *(s8*)(effect + 3) = -4;
    *(u16*)(effect + 4) = 52;
    *(u16*)(effect + 6) = (rand() & 7) + 1;
    *(u16*)(effect + 8) = *(u16*)(effect + 6);
    effect[0x14] = 8;
    *(int*)(effect + 0x18) = 1;
    *(int*)(effect + 0x1C) = 1;
}
