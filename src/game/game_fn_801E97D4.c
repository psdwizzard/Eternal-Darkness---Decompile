typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Header {
    u32 type;
    u8 pad04[4];
    u32 data08;
    u8 pad0C[4];
    u32 data10;
    u8 pad14[4];
    u32 data18;
    u8 pad1C[4];
    u32 data20;
    u8 pad24[4];
    u32 data28;
} Header;

extern void fn_801E9124(u32*);
extern void fn_80155BB0(const char*, const char*, ...);
extern char lbl_80265C44[];
extern char lbl_80265C68[];

u32 fn_801E97D4(const u8* source, Header* header)
{
    u32 offset = 0;

    *header = *(const Header*)source;
    offset += sizeof(Header);
    fn_801E9124(&offset);
    if (header->type != 0x2C) {
        fn_80155BB0(lbl_80265C44, lbl_80265C68, 0x2C, header->type);
    }
    if (header->data08 != 0) {
        u32 size = header->data08;
        header->data08 = (u32)(source + offset);
        offset += size;
    }
    if (header->data10 != 0) {
        u32 size = header->data10;
        header->data10 = (u32)(source + offset);
        offset += size;
    }
    if (header->data18 != 0) {
        u32 size = header->data18;
        header->data18 = (u32)(source + offset);
        offset += size;
    }
    if (header->data20 != 0) {
        u32 size = header->data20;
        header->data20 = (u32)(source + offset);
        offset += size;
    }
    if (header->data28 != 0) {
        u32 size = header->data28;
        header->data28 = (u32)(source + offset);
        offset += size;
    }
    return offset;
}
