typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry20A {
    u32 pad00;
    u32 data04;
    u8 pad08[0xC];
} Entry20A;

typedef struct Entry20B {
    u8 pad00[0x10];
    u32 data10;
} Entry20B;

typedef struct Entry12 {
    u32 pad00;
    u32 data04;
    u8 pad08[4];
} Entry12;

typedef struct Header {
    u8 type;
    u8 pad01[0xB];
    u32 data0C;
    u8 pad10[4];
    u32 data14;
    u8 pad18[4];
    u32 data1C;
    u8 pad20[8];
    u32 data28;
    int count2C;
    Entry20A* data30;
    u16 count34;
    u8 pad36[2];
    Entry20B* data38;
    u16 count3C;
    u8 pad3E[2];
    Entry12* data40;
    u16 count44;
    u8 pad46[2];
    u32 data48;
    u16 count4C;
    u8 pad4E[2];
    u32 data50;
    u16 count54;
    u8 pad56[2];
    u32 data58;
    u32 data5C;
    u8 pad60[4];
    u32 data64;
    u8 pad68[0x18];
} Header;

extern void fn_801E9124(u32*);
extern void fn_80155BB0(const char*, const char*, ...);
extern u32 fn_801EA900(const u8*, void*, u16);
extern u32 fn_801EA600(const u8*, void*);
extern u32 fn_801EA6FC(const u8*, void*);
extern u32 fn_801EA774(const u8*, void*);
extern char lbl_80265B08[];
extern char lbl_80265B2C[];

u32 fn_801E915C(const u8* source, Header* header)
{
    u32 offset = 0;
    int i;
    u32 byte_offset;

    *header = *(const Header*)source;
    offset += sizeof(Header);
    fn_801E9124(&offset);

    if (header->type != 10) {
        fn_80155BB0(lbl_80265B08, lbl_80265B2C, header->type, 10);
    }

    if (header->data0C != 0) {
        u32 size = header->data0C;
        header->data0C = (u32)(source + offset);
        offset += size;
    }
    if (header->data14 != 0) {
        u32 size = header->data14;
        header->data14 = (u32)(source + offset);
        offset += size;
    }
    if (header->data1C != 0) {
        u32 size = header->data1C;
        header->data1C = (u32)(source + offset);
        offset += size;
    }
    if (header->data28 != 0) {
        u32 size = header->data28;
        header->data28 = (u32)(source + offset);
        offset += size;
    }
    if (header->data30 != 0) {
        u32 size = (u32)header->data30;
        header->data30 = (Entry20A*)(source + offset);
        offset += size;
    }

    for (i = 0, byte_offset = 0; i < header->count2C; i++, byte_offset += 0x14) {
        if (header->data30[i].data04 != 0) {
            u32 size = header->data30[i].data04;
            header->data30[i].data04 = (u32)(source + offset);
            offset += size;
        }
    }

    if (header->data38 != 0) {
        u32 size = (u32)header->data38;
        header->data38 = (Entry20B*)(source + offset);
        offset += size;
    }
    for (i = 0, byte_offset = 0; i < header->count34; i++, byte_offset += 0x14) {
        if (header->data38[i].data10 != 0) {
            u32 size = header->data38[i].data10;
            header->data38[i].data10 = (u32)(source + offset);
            offset += size;
        }
    }

    if (header->data40 != 0) {
        u32 size = (u32)header->data40;
        header->data40 = (Entry12*)(source + offset);
        offset += size;
    }
    for (i = 0, byte_offset = 0; i < header->count3C; i++, byte_offset += 0xC) {
        if (header->data40[i].data04 != 0) {
            u32 size = header->data40[i].data04;
            header->data40[i].data04 = (u32)(source + offset);
            offset += size;
        }
    }

    offset += fn_801EA900(source + offset, &header->data48, header->count44);

    if (header->data50 != 0) {
        header->data50 = (u32)(source + offset);
        for (i = 0, byte_offset = 0; i < header->count4C; i++, byte_offset += 4) {
            *(u32*)(header->data50 + byte_offset) = (u32)(source + offset);
            offset += 4;
        }
        for (i = 0, byte_offset = 0; i < header->count4C; i++, byte_offset += 4) {
            offset += fn_801EA600(source + offset, (void*)(header->data50 + byte_offset));
        }
    }

    if (header->data58 != 0) {
        header->data58 = (u32)(source + offset);
        offset += header->count54 * 4;
        for (i = 0, byte_offset = 0; i < header->count54; i++, byte_offset += 4) {
            *(u32*)(header->data58 + byte_offset) = (u32)(source + offset);
            offset += fn_801EA6FC(source + offset, (void*)(header->data58 + byte_offset));
        }
    }

    if (header->data5C != 0) {
        offset += fn_801EA774(source + offset, &header->data5C);
    }
    if (header->data64 != 0) {
        u32 size = header->data64;
        header->data64 = (u32)(source + offset);
        offset += size;
    }
    return offset;
}
