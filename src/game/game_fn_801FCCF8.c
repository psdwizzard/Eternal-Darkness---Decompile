typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 lbl_8063E9E0[];
extern void* lbl_8064C3C8;
extern u8* lbl_8064D7C0;
extern float lbl_80651520;

extern u32 fn_80228250(u16, u16, u32, u8, u8);
extern void* fn_8020AD80(void*, u32);
extern void fn_80228474(void*, void*, u16, u16, u32, u32, u32, u8);
extern void fn_80228730(void*, u32, u32, float, float, float, u8, u8, u8);
extern void DCFlushRange(void*, u32);

void fn_801FCCF8(void)
{
    register u8* image;
    register u32 size;
    register u8* texture;
    u32 i;

    if (lbl_8064D7C0 == 0) {
        texture = lbl_8063E9E0;
        size = fn_80228250(16, 16, 1, 0, 0);
        image = fn_8020AD80(lbl_8064C3C8, size);

        for (i = 0; i < 256; i++) {
            u32 offset = ((i & 0x80) >> 2) + ((i & 0x70) >> 4) +
                         ((i & 0xC) << 4) + ((i & 3) << 3);
            image[offset] = i;
        }

        fn_80228474(texture, image, 16, 16, 1, 0, 1, 0);
        fn_80228730(texture, 0, 0, lbl_80651520, lbl_80651520,
                   lbl_80651520, 0, 0, 0);
        DCFlushRange(image, size);
        lbl_8064D7C0 = image;
    }
}
