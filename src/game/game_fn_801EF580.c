typedef struct DisplaySize {
    unsigned short field_0;
    unsigned short field_2;
    unsigned short width;
    unsigned short field_6;
    unsigned short height;
} DisplaySize;

extern unsigned int lbl_8064D75C;

extern void GXSetViewport(float, float, float, float, float, float);
extern void GXInvalidateVtxCache(void);

void fn_801EF580(DisplaySize* size)
{
    GXSetViewport(0.0f, 0.0f, (float)size->width, (float)size->height, 0.0f, 1.0f);
    GXInvalidateVtxCache();
    lbl_8064D75C = 0;
}
