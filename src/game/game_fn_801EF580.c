typedef struct DisplaySize {
    unsigned short field_0;
    unsigned short field_2;
    unsigned short width;
    unsigned short field_6;
    unsigned short height;
} DisplaySize;

extern unsigned int lbl_8064D75C;

extern void fn_8022B94C(float, float, float, float, float, float);
extern void fn_80225FD8(void);

void fn_801EF580(DisplaySize* size)
{
    fn_8022B94C(0.0f, 0.0f, (float)size->width, (float)size->height, 0.0f, 1.0f);
    fn_80225FD8();
    lbl_8064D75C = 0;
}
