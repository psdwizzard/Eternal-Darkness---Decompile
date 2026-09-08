typedef struct DisplaySize {
    unsigned short field_0;
    unsigned short field_2;
    unsigned short width;
    unsigned short field_6;
    unsigned short height;
} DisplaySize;

extern float lbl_80651348;
extern float lbl_8065134C;
extern unsigned int lbl_8064D75C;

extern void fn_8022B94C(float, float, float, float, float, float);
extern void fn_80225FD8(void);

void fn_801EF580(DisplaySize* size)
{
    fn_8022B94C(lbl_80651348, lbl_80651348, (float)size->width,
                (float)size->height, lbl_80651348, lbl_8065134C);
    fn_80225FD8();
    lbl_8064D75C = 0;
}
