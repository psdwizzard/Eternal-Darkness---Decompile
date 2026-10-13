/* fn_8022C53C (0x8022C53C, 300 bytes): TPLBind (Dolphin SDK texPalette.c). */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;

typedef struct TPLHeader {
    u16 height;
    u16 width;
    u32 format;
    char *data;
    u32 wrapS;
    u32 wrapT;
    u32 minFilter;
    u32 magFilter;
    f32 LODBias;
    u8 edgeLODEnable;
    u8 minLOD;
    u8 maxLOD;
    u8 unpacked;
} TPLHeader;

typedef struct TPLClutHeader {
    u16 numEntries;
    u8 unpacked;
    u8 pad8;
    u32 format;
    char *data;
} TPLClutHeader;

typedef struct TPLDescriptor {
    TPLHeader *textureHeader;
    TPLClutHeader *CLUTHeader;
} TPLDescriptor;

typedef struct TPLPalette {
    u32 versionNumber;
    u32 numDescriptors;
    TPLDescriptor *descriptorArray;
} TPLPalette;

extern void fn_8020C5D0(const char *, int, const char *, ...); /* OSPanic */
extern char lbl_802FF718[]; /* "texPalette.c" */
extern char lbl_802FF728[];

void fn_8022C53C(TPLPalette *pal) {
    u16 i;

    if (pal->versionNumber != 2142000) {
        fn_8020C5D0(lbl_802FF718, 0x53, lbl_802FF728);
    }

    pal->descriptorArray = (TPLDescriptor *)((u32)pal->descriptorArray + (u32)pal);

    for (i = 0; i < pal->numDescriptors; i++) {
        if (pal->descriptorArray[i].textureHeader) {
            pal->descriptorArray[i].textureHeader =
                (TPLHeader *)((u32)pal + (u32)pal->descriptorArray[i].textureHeader);
            if (!pal->descriptorArray[i].textureHeader->unpacked) {
                pal->descriptorArray[i].textureHeader->data =
                    (char *)((u32)pal + (u32)pal->descriptorArray[i].textureHeader->data);
                pal->descriptorArray[i].textureHeader->unpacked = 1;
            }
        }
        if (pal->descriptorArray[i].CLUTHeader) {
            pal->descriptorArray[i].CLUTHeader =
                (TPLClutHeader *)((u32)pal + (u32)pal->descriptorArray[i].CLUTHeader);
            if (!pal->descriptorArray[i].CLUTHeader->unpacked) {
                pal->descriptorArray[i].CLUTHeader->data =
                    (char *)((u32)pal + (u32)pal->descriptorArray[i].CLUTHeader->data);
                pal->descriptorArray[i].CLUTHeader->unpacked = 1;
            }
        }
    }
}
