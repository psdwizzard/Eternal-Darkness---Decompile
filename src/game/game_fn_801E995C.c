typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Entry14 {
    u8 pad00[0x34]; u32 data34; u8 pad38[4]; u32 data3C;
    u8 pad40[0x2C]; s16 type6C; u8 pad6E[6];
} Entry14;
typedef struct Entry44 {
    u8 pad00[4]; Vec3 center; float radius; u8 pad14[0x14];
    u16 count28; u8 pad2A[2]; u16* indices; u8 pad30[8];
} Entry44;
typedef struct Entry5C { u8 pad00[0x28]; u32 data28; } Entry5C;
typedef struct Entry64 { u8 pad00[6]; u8 count06; u8 pad07; u32* data08; } Entry64;

typedef struct ModelHeader {
    s8 type; u8 pad01; u16 count02; u32 data04;
    u16 count08; u8 pad0A[2]; u32 data0C;
    u16 count10; u8 pad12[2]; Entry14* data14;
    u8 pad18[4]; u32 data1C;
    u16 count20; u8 pad22[2]; u32 data24; u32 data28;
    u8 pad2C[4]; u32 data30; u8 pad34[4]; u32 data38;
    u16 count3C; u8 pad3E[2]; u32 data40; Entry44* data44;
    u8 pad48[4]; s16* vertices; u8 pad50[4]; u32 data54;
    u16 count58; u8 pad5A[2]; Entry5C* data5C;
    u16 count60; u8 pad62[2]; Entry64* data64;
    u8 pad68[4]; u32 data6C; u8 pad70[8];
} ModelHeader;

extern void fn_801E9124(u32*);
extern void fn_80155BB0(const char*, const char*, ...);
extern u32 fn_801EA900(const u8*, void*, u16);
extern void fn_80211A90(Vec3*, const Vec3*, float);
extern u32 fn_80178F14(s32, s32, s32, s32, s32, s32);
extern char lbl_80265CB8[];
extern char lbl_80265CDC[];
extern const float lbl_806512A8;
extern const float lbl_806512AC;
extern const float lbl_806512B0;

#define RELOCATE(field) do { \
    u32 size = (u32)(field); \
    if (size != 0) { \
        *(u32*)&(field) = (u32)(source + offset); \
        offset += size; \
    } \
} while (0)

u32 fn_801E995C(const u8* source, ModelHeader* header)
{
    u32 offset = 0;
    int i;
    u32 byte_offset;

    *header = *(const ModelHeader*)source;
    offset += sizeof(ModelHeader);
    fn_801E9124(&offset);
    if (header->type != 15) {
        fn_80155BB0(lbl_80265CB8, lbl_80265CDC, header->type, 15);
    }

    RELOCATE(header->data04);
    for (i = 0, byte_offset = 0; i < header->count02; i++, byte_offset += 0x78) {
        RELOCATE(*(u32*)((u8*)header->data04 + byte_offset + 0x64));
        RELOCATE(*(u32*)((u8*)header->data04 + byte_offset + 0x6C));
        RELOCATE(*(u32*)((u8*)header->data04 + byte_offset + 0x74));
    }
    RELOCATE(header->data0C);
    for (i = 0, byte_offset = 0; i < header->count08; i++, byte_offset += 0x78) {
        RELOCATE(*(u32*)((u8*)header->data0C + byte_offset + 0x64));
        RELOCATE(*(u32*)((u8*)header->data0C + byte_offset + 0x6C));
        RELOCATE(*(u32*)((u8*)header->data0C + byte_offset + 0x74));
    }
    RELOCATE(header->data14);
    for (i = 0, byte_offset = 0; i < header->count10; i++, byte_offset += 0x74) {
        if (((Entry14*)((u8*)header->data14 + byte_offset))->type6C == 2) {
            RELOCATE(((Entry14*)((u8*)header->data14 + byte_offset))->data34);
            RELOCATE(((Entry14*)((u8*)header->data14 + byte_offset))->data3C);
        }
    }
    RELOCATE(header->data24);
    offset += fn_801EA900(source + offset, &header->data28, header->count20);
    RELOCATE(header->data30);
    RELOCATE(header->data38);
    RELOCATE(header->data40);
    offset += fn_801EA900(source + offset, &header->data44, header->count3C);
    RELOCATE(header->vertices);

    for (i = 0; i < header->count3C; i++) {
        Entry44* entry = &header->data44[i];
        s16* vertices = header->vertices;
        int count = entry->count28;
        int j;
        float maximum = lbl_806512A8;
        entry->center.x = maximum;
        entry->center.y = maximum;
        entry->center.z = maximum;
        for (j = 0; j < count; j++) {
            entry->center.x += vertices[entry->indices[j] * 3];
            entry->center.y += vertices[entry->indices[j] * 3 + 1];
            entry->center.z += vertices[entry->indices[j] * 3 + 2];
        }
        fn_80211A90(&entry->center, &entry->center,
                    lbl_806512AC / (float)count);
        for (j = 0; j < count; j++) {
            s16* vertex = vertices + entry->indices[j] * 3;
            float distance = (float)fn_80178F14((s32)entry->center.x,
                                                (s32)entry->center.y,
                                                (s32)entry->center.z,
                                                vertex[0], vertex[1], vertex[2]);
            if (distance > maximum) maximum = distance;
        }
        entry->radius = lbl_806512B0 * (float)maximum;
    }

    RELOCATE(header->data1C);
    RELOCATE(header->data54);
    RELOCATE(header->data5C);
    for (i = 0, byte_offset = 0; i < header->count58; i++, byte_offset += 0x2C) {
        RELOCATE(*(u32*)((u8*)header->data5C + byte_offset + 0x28));
    }
    RELOCATE(header->data64);
    for (i = 0; i < header->count60; i++) RELOCATE(header->data64[i].data08);
    for (i = 0; i < header->count60; i++) {
        Entry64* entry = &header->data64[i];
        int j;
        for (j = 0; j < entry->count06; j++) {
            entry->data08[j] = (u32)&header->data64[entry->data08[j]];
        }
    }
    RELOCATE(header->data6C);
    return offset;
}
