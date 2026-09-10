extern unsigned char lbl_8023B7D8[];
extern unsigned char lbl_8063C6B8[];
extern float lbl_80651460;
extern float lbl_80651464;
extern float lbl_8064D7A0;

extern void fn_801F7034(void*, int);
extern void fn_801F8994(void*, float);
extern void fn_801F8620(void*, void*);
extern void fn_801FA410(int);

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

void* fn_801F7AF8(void)
{
    unsigned char* base = lbl_8063C6B8;
    unsigned char* first = base + 0x660;
    unsigned char* second;
    unsigned char* third;
    Vec3 values = *(Vec3*)lbl_8023B7D8;

    first += 0x550;
    fn_801F7034(first, 1);

    second = base;
    second += 0x550;
    fn_801F7034(second, 1);

    *(void**)(base + 0x660 + 0x5C4) = second;
    third = base + 0xCC0;
    *(Vec3*)(base + 0x598) = values;
    *(Vec3*)(base + 0x660 + 0x598) = values;

    fn_801F8994(first, *(float*)(third + 0x34));
    fn_801F8994(second, *(float*)(third + 0x34));
    fn_801F8620(second, base + 0xD48);
    fn_801FA410(10);

    lbl_8064D7A0 = lbl_80651464;
    *(float*)(base + 0x660 + 0x580) = lbl_80651460;
    *(float*)(base + 0x580) = lbl_80651460;
    return first;
}
