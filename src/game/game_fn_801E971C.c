typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Header {
    u16 type;
    u8 pad02[6];
    u32 data08;
} Header;

extern void fn_801E9124(u32*);
extern void fn_80155BB0(const char*, const char*, ...);
extern char lbl_80265BD8[];
extern char lbl_80265C00[];

u32 fn_801E971C(const u8* source, Header* header)
{
    u32 offset = 0;

    *header = *(const Header*)source;
    offset += sizeof(Header);
    fn_801E9124(&offset);
    if (header->type != 0xC) {
        fn_80155BB0(lbl_80265BD8, lbl_80265C00, header->type, 0xC);
    }
    if (header->data08 != 0) {
        u32 size = header->data08;
        header->data08 = (u32)(source + offset);
        offset += size;
    }
    return offset;
}
