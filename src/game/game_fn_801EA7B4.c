typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Header {
    u8 type;
    u8 pad001[0x117];
    u32 dataSize;
    u32 data;
} Header;

extern u32 fn_801E971C(const u8*, void*);
extern u32 fn_801E9564(const u8*, void*);
extern u32 fn_801E915C(const u8*, void*);
extern u32 fn_801E995C(const u8*, void*);
extern u32 fn_801E914C(u32);
extern void fn_801E9124(u32*);
extern void fn_80155BB0(const char*, const char*, ...);
extern char lbl_80265D0C[];
extern char lbl_80265D24[];

u32 fn_801EA7B4(const u8* source, Header* header)
{
    u32 offset = 0;
    u32 previous;

    *header = *(const Header*)source;
    offset += sizeof(Header);
    if (header->type != 0x17) {
        fn_80155BB0(lbl_80265D0C, lbl_80265D24, header->type, 0x17);
    }
    offset += fn_801E971C(source + offset, (u8*)header + 4);
    offset += fn_801E9564(source + offset, (u8*)header + 0x10);
    offset += fn_801E915C(source + offset, (u8*)header + 0x20);
    offset += fn_801E995C(source + offset, (u8*)header + 0xA0);
    if (header->dataSize != 0) {
        previous = fn_801E914C(0x20);
        fn_801E9124(&offset);
        header->data = (u32)(source + offset);
        offset += header->dataSize;
        fn_801E914C(previous);
    }
    return offset;
}
