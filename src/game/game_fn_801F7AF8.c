extern unsigned char lbl_8023B7D8[];
typedef struct ObjectState {
    unsigned char data[0x660];
} ObjectState;

extern ObjectState lbl_8063C6B8[];
extern float lbl_80651460;
extern float lbl_80651464;
extern float lbl_8064D7A0;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern void fn_801F7034(void*, int);
extern void fn_801F8994(void*, const Vec3*, float);
extern void fn_801F8620(void);
extern void fn_801FA410(int);

/* NonMatching: behavior-complete reconstruction. GC/1.3 emits 264 bytes
 * instead of 268, folds the first object and field offsets, and rematerializes
 * lbl_8063C6B8 after calls instead of retaining base/first/second/third in
 * r31/r29/r30/r28 as retail does. */
void* fn_801F7AF8(void)
{
    ObjectState* base = lbl_8063C6B8;
    unsigned char* first = base[1].data;
    unsigned char* second;
    unsigned char* third;
    Vec3 values = *(Vec3*)lbl_8023B7D8;

    first += 0x550;
    fn_801F7034(first, 1);

    second = base[0].data;
    second += 0x550;
    fn_801F7034(second, 1);

    *(void**)(base[1].data + 0x5C4) = second;
    third = base[2].data;
    *(Vec3*)(base[0].data + 0x598) = values;
    *(Vec3*)(base[1].data + 0x598) = values;

    fn_801F8994(first, (Vec3*)third, *(float*)(third + 0x34));
    fn_801F8994(second, (Vec3*)(base[2].data + 0x88), *(float*)(third + 0x34));
    fn_801F8620();
    fn_801FA410(10);

    lbl_8064D7A0 = lbl_80651464;
    *(float*)(base[1].data + 0x580) = lbl_80651460;
    *(float*)(base[0].data + 0x580) = lbl_80651460;
    return first;
}
