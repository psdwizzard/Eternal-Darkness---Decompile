typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Header {
    u32 field00;
    u32 field04;
    u32 field08;
    u16 field0C;
    u16 field0E;
    u32 field10;
    u32 field14;
} Header;

extern u32 fn_80125664(void*, int);
extern u32 fn_80125788(void*);
extern void fn_80139E18(void);

u32 fn_801EA6FC(Header* header)
{
    header->field04 = fn_80125664((u8*)header + header->field04, 0);
    header->field00 = fn_80125788((u8*)header + header->field00);
    if (header->field0E != 0) {
        fn_80139E18();
        header->field10 = (u32)((u8*)header + header->field10);
        header->field14 = (u32)((u8*)header + header->field14);
    }
    return header->field08;
}
