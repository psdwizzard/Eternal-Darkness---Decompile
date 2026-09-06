typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Object { u8 bytes[0x1000]; } Object;
typedef union SpawnHeader { u8 bytes[144]; double align; } SpawnHeader;
typedef struct SpawnInfo { u8 bytes[172]; } SpawnInfo;
typedef struct Pair { u32 first, second; } Pair;

extern int lbl_8064D18C;
extern void fn_80196578(void*);
extern void fn_8018F81C(void*, u8);
extern u32 fn_801D3944(u32);
extern int fn_801D38E8(u32);
extern void fn_801966E0(void);
extern void* fn_80147EC4(void*);

void fn_801D7998(s16* first, s16* second, Object* object)
{
    SpawnHeader header;
    SpawnInfo info;
    Pair pair;
    int type;

    if (object != 0 && *(int*)(object->bytes + 8) == lbl_8064D18C) {
        fn_80196578(&header);
        *(s16*)(header.bytes + 4) = -1;
        *(s16*)(header.bytes + 6) = 20;
        *(s16*)(header.bytes + 8) = 21;
        fn_8018F81C(&header, 4);
        *(s16*)(header.bytes + 0x30) = 15;
        header.bytes[0x29] = 8;
        header.bytes[0x2A] = 4;

        pair.first = fn_801D3944(*(u32*)(object->bytes + 4));
        pair.second = pair.first;
        ((u8*)&pair)[7] = 90;
        ((u8*)&pair)[3] = 120;

        switch (fn_801D38E8(*(u32*)(object->bytes + 4))) {
        case 1: type = 0x20; break;
        case 2: type = 8; break;
        case 3: type = 0x10; break;
        case 4: type = 0x40; break;
        case 0: type = 0x100; break;
        }

        *(u32*)(header.bytes + 0x14) = pair.second;
        *(u32*)(header.bytes + 0x18) = pair.first;
        header.bytes[0x21] = 9;
        header.bytes[0x24] = 3;
        *(u16*)(header.bytes + 0x1E) = (u16)type;
        header.bytes[0x2C] |= 0x80;
        header.bytes[0x2B] = 0;

        *(s16*)(header.bytes + 0x68) = first[0];
        *(s16*)(header.bytes + 0x6A) = first[1];
        *(s16*)(header.bytes + 0x6C) = first[2] + 400;
        *(s16*)(header.bytes + 0x6E) = first[0];
        *(s16*)(header.bytes + 0x70) = first[1];
        *(s16*)(header.bytes + 0x72) = first[2];
        *(s16*)(header.bytes + 0x74) = second[0];
        *(s16*)(header.bytes + 0x76) = second[1];
        *(s16*)(header.bytes + 0x78) = second[2];
        *(s16*)(header.bytes + 0x7A) = second[0];
        *(s16*)(header.bytes + 0x7C) = second[1];
        *(s16*)(header.bytes + 0x7E) = second[2] + 400;

        *(SpawnHeader*)info.bytes = header;
        *(void**)(info.bytes + 0x90) = fn_801966E0;
        info.bytes[0xAA] = 4;
        fn_80147EC4(&info);
    }
}
