typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ModelHeader {
    s8 type;
    unsigned char pad01;
    u16 count04;
    u32 data04;
    u16 count08;
    unsigned char pad0A[2];
    u32 data0C;
    u16 count10;
    unsigned char pad12[2];
    u32 data14;
    unsigned char pad18[8];
    u16 count20;
    unsigned char pad22[2];
    u32 data24;
    unsigned char pad28[8];
    u32 data30;
    unsigned char pad34[4];
    u32 data38;
    u16 count3C;
    unsigned char pad3E[2];
    u32 data40;
    unsigned char pad44[4];
    u32 data48;
    u32 data4C;
    unsigned char pad50[40];
} ModelHeader;

extern void fn_801E9124(u32*);
extern void fn_80155BB0(const char*, const char*, ...);
extern char lbl_80265CB8[];
extern char lbl_80265CDC[];

static void relocate_block(const unsigned char* source, u32* offset, u32* field)
{
    u32 size = *field;
    if (size != 0) {
        *field = (u32)(source + *offset);
        *offset += size;
    }
}

u32 fn_801E995C(const unsigned char* source, ModelHeader* header)
{
    u32 offset = 0;
    u32 i;

    *header = *(const ModelHeader*)source;
    offset += sizeof(ModelHeader);
    fn_801E9124(&offset);
    if (header->type != 15) {
        fn_80155BB0(lbl_80265CB8, lbl_80265CDC, header->type, 15);
    }

    relocate_block(source, &offset, &header->data04);
    for (i = 0; i < header->count04; i++) {
        unsigned char* entry = (unsigned char*)header->data04 + i * 0x78;
        relocate_block(source, &offset, (u32*)(entry + 0x64));
        relocate_block(source, &offset, (u32*)(entry + 0x6C));
        relocate_block(source, &offset, (u32*)(entry + 0x74));
    }
    relocate_block(source, &offset, &header->data0C);
    for (i = 0; i < header->count08; i++) {
        unsigned char* entry = (unsigned char*)header->data0C + i * 0x78;
        relocate_block(source, &offset, (u32*)(entry + 0x64));
        relocate_block(source, &offset, (u32*)(entry + 0x6C));
        relocate_block(source, &offset, (u32*)(entry + 0x74));
    }
    relocate_block(source, &offset, &header->data14);
    relocate_block(source, &offset, &header->data24);
    relocate_block(source, &offset, &header->data30);
    relocate_block(source, &offset, &header->data38);
    relocate_block(source, &offset, &header->data40);
    relocate_block(source, &offset, &header->data48);
    relocate_block(source, &offset, &header->data4C);
    return offset;
}
