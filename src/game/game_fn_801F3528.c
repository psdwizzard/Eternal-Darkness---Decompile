typedef unsigned char u8;
typedef unsigned long u32;

typedef struct Color8 {
    u8 red, green, blue, alpha;
} Color8;

typedef struct ColorF {
    float red, green, blue, alpha;
} ColorF;

extern ColorF lbl_8063C608;
extern u32 lbl_8064D704;

#pragma opt_propagation off
void fn_801F3528(Color8* color)
{
    u8 green = color->green;
    u8 blue = color->blue;
    u8 alpha = color->alpha;
    u8 red = color->red;
    u32 packed = *(u32*)color;

    lbl_8063C608.red = (float)red;
    lbl_8063C608.green = (float)green;
    lbl_8063C608.blue = (float)blue;
    lbl_8063C608.alpha = (float)alpha;
    lbl_8064D704 = packed;
}
#pragma opt_propagation reset
