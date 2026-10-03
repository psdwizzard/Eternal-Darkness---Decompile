typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;

typedef struct FontDescriptor {
    u8 reserved[4];
    s8 height;
    u8 widths[256];
} FontDescriptor;

extern void* lbl_8064D568;
extern u32 lbl_8064D584;

static void* fonts[10] = {0};
static u32 indices[10] = {0};
static FontDescriptor* descriptors[10] = {0};

int fn_801E5BD8(FontDescriptor* descriptor)
{
    u32 index = lbl_8064D584;

    if (index < 10) {
        if (descriptor != 0) {
            descriptors[index] = descriptor;
            indices[index] = index;
            fonts[index] = lbl_8064D568;
            if (index == 2) {
                descriptors[2]->widths['A'] -= 5;
                descriptors[2]->widths['C'] -= 2;
                descriptors[2]->widths['E'] -= 3;
                descriptors[2]->widths['H'] -= 6;
                descriptors[2]->widths['K'] -= 6;
                descriptors[2]->widths['L'] -= 8;
                descriptors[2]->widths['M'] -= 6;
                descriptors[2]->widths['P'] -= 7;
                descriptors[2]->widths['Q'] -= 5;
                descriptors[2]->widths['R'] -= 6;
                descriptors[2]->widths['T'] -= 7;
                descriptors[2]->widths['W'] -= 4;
                descriptors[2]->widths['Y'] -= 8;
            }
        }
        lbl_8064D584++;
        return 1;
    }
    return 0;
}
