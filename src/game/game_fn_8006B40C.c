typedef signed int s32;

typedef struct Descriptor {
    s32 words[5];
} Descriptor;

extern Descriptor lbl_802390A0;
extern void *lbl_8064C8D0;
extern void fn_8006BE84(void *object, s32 value);
extern void fn_8006BEE4(void *object, void *callback);
extern void fn_8006BEF4(void *object, Descriptor *descriptor);

void fn_8006B40C(void)
{
    Descriptor descriptor;
    void *object;

    descriptor = lbl_802390A0;
    object = lbl_8064C8D0;

    fn_8006BE84(object, -1);
    fn_8006BEE4(object, 0);
    fn_8006BEF4(object, &descriptor);
}
