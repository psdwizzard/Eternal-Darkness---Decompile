typedef unsigned int u32;
typedef unsigned short u16;

typedef struct Entry {
    u32 clear;
    unsigned char pad4[0x114];
    u32 source;
    u32 size;
    u32 unknown;
    u32 state;
} Entry;

typedef struct Header {
    unsigned char pad0[0x14];
    u16 count;
    unsigned char pad16[2];
    u32 entries;
} Header;

extern u32 lbl_8064C7DC;
extern void* fn_80138A6C(u32, void*);
extern u32 fn_8015E7A0(void);
extern u32 fn_8015E7C8(u32);
extern void fn_8015D7D4(u32, void*, void*, u32, int);
extern void* memcpy(void*, const void*, u32);

Header* fn_80139B1C(unsigned char* base, int unused, u32* offset, void* alloc_arg,
                    void* source_base, int mode)
{
    Header* result;
    Header* header;
    u32 header_size;
    u32 total;
    u32 checkpoint;
    int i;

    header = (Header*)(base + *offset);
    header_size = header->count * 0x128 + 0x48;
    result = fn_80138A6C(header_size, alloc_arg);
    total = 0;
    checkpoint = fn_8015E7A0();
    memcpy(result, header, header_size);
    header = result;
    result->entries = (u32)result + result->entries;
    result = (Header*)result->entries;
    for (i = 0; i < header->count; i++, result = (Header*)((Entry*)result + 1)) {
        u32 size = (((Entry*)result)->size + 31) & ~31;
        u32 position = fn_8015E7C8(size);
        total += size;
        if (checkpoint <= position) {
            u32 source = ((Entry*)result)->source;
            fn_8015D7D4(position, source_base,
                        (unsigned char*)source + *offset, size, mode);
        }
        ((Entry*)result)->source = position;
        ((Entry*)result)->clear = 0;
        ((Entry*)result)->state = 0;
    }
    lbl_8064C7DC += total;
    return header;
}
