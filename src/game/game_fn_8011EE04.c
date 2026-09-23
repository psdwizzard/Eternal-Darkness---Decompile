typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/*
 * Honest reconstruction of the object initializer. It preserves the retail
 * call order, random bounds, transform setup, 24-entry state initialization,
 * and type-205 special case. The scalar constants live in read-only .sdata2;
 * const qualification is required for MWCC to schedule their loads correctly.
 * Remaining work is vector-copy scheduling and conversion-constant identity.
 */

extern float fn_80140E58(void);
extern u16 fn_80140E68(void);
extern void* fn_8011FDF0(void);
extern void fn_80128754(void*, int);
extern void fn_801287B0(void*, int);
extern void fn_8011F890(void*, float, float, float);
extern void fn_80179F48(void*, void*);
extern void fn_8011FE5C(void*, int);
extern void fn_8011FB44(void*, int);
extern void fn_80128C50(void*);
extern void fn_8012260C(void*);
extern int fn_801261F4(void*);
extern void fn_80120AD0(void*, const void*, u16, u32, float, float);
extern const u32 lbl_8023A680[4];
extern u8 lbl_8024EDD4[];
extern const float lbl_80650068;
extern const float lbl_8065006C;
extern const float lbl_80650070;
extern const float lbl_80650074;

void* fn_8011EE04(void* parent, float x, float y, float z)
{
    u8* object;
    float bound;
    float sample;
    int i;
    u8* entry;

    bound = fn_80140E58();
    object = fn_8011FDF0();
    *(void**)(object + 60) = parent;
    *(float*)(object + 0) = x;
    *(float*)(object + 4) = y;
    *(float*)(object + 8) = z;
    object[734] = 0;
    object[735] = 0;
    fn_80128754(object, -2);
    fn_801287B0(object, -1);

    if (parent != 0) {
        sample = fn_80140E58();
        if (*(float*)((u8*)parent + 248) > sample) {
            sample = *(float*)((u8*)parent + 248);
        } else {
            sample = fn_80140E58();
        }
        bound = sample;
    }
    *(float*)(object + 624) = bound;
    *(float*)(object + 628) = bound;

    sample = (float)fn_80140E68();
    if (bound > sample) {
        sample = bound;
    } else {
        sample = (float)fn_80140E68();
    }
    *(u16*)(object + 712) = (u16)sample;

    {
        u32 first = lbl_8023A680[0];
        u32 second = lbl_8023A680[1];
        *(u32*)(object + 12) = first;
        *(u32*)(object + 16) = second;
        *(u32*)(object + 20) = lbl_8023A680[2];
    }
    fn_8011F890(object, lbl_80650068, lbl_80650068, lbl_8065006C);
    sample = lbl_80650068;
    *(float*)(object + 612) = sample;
    *(float*)(object + 616) = sample;
    *(float*)(object + 620) = *(float*)(object + 628);
    *(float*)(object + 632) = lbl_80650070;
    *(u32*)(object + 600) = 0x10000;
    fn_80179F48(lbl_8024EDD4, object + 44);

    *(void**)(object + 372) = object;
    entry = object;
    for (i = 0; i < 24; i++) {
        *(u16*)(entry + 384) = 1;
        *(u32*)(entry + 380) = 0;
        entry += 8;
    }

    *(int*)(object + 660) = -1;
    fn_8011FE5C(object, 15);
    *(float*)(object + 684) = lbl_80650070;
    fn_8011FB44(object, 0x10000);
    *(u32*)(object + 376) = 0;
    *(u32*)(object + 608) = 0;
    fn_80128C50(object + 68);
    object[730] = 0;
    sample = lbl_80650074;
    object[731] = 5;
    object[732] = 18;
    object[733] = 150;
    *(float*)(object + 636) = sample;
    *(float*)(object + 640) = sample;
    *(u16*)(object + 722) = 0;
    fn_8012260C(object);
    if (*(int*)(object + 580) == 205) {
        fn_801261F4(object);
        fn_80120AD0(object, 0, 100, 522, lbl_80650070, lbl_80650068);
    }
    return object;
}
