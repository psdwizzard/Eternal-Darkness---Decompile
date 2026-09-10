typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern void* lbl_8064C4E4;
extern Vec3 lbl_8023B7F0;
extern Vec3 lbl_802FC6FC;

extern void fn_8011F114(void*);
extern void* fn_8011F7D8(void*);
extern unsigned int fn_8011F134(void*);
extern void fn_80127F90(void*, unsigned int, Vec3*);
extern void fn_8012B690(void*, Vec3*, Vec3*);
extern void fn_80211A90(void*, Vec3*, float);
extern void fn_80211A48(Vec3*, Vec3*, Vec3*);

void fn_801F7E40(Vec3* output, void* input, float amount)
{
    Vec3 a;
    Vec3 b;
    Vec3 c;
    void* value;
    unsigned int index;

    if (input != 0) {
        fn_8011F114(&c);
        value = fn_8011F7D8(input);
        index = fn_8011F134(input);
        if (index == 0xFFFF) {
            fn_80127F90(input, 0, &lbl_802FC6FC);
        } else {
            fn_80127F90(input, index, &lbl_802FC6FC);
        }
    } else if (lbl_8064C4E4 != 0) {
        b = lbl_8023B7F0;
        fn_8012B690(lbl_8064C4E4, &b, &a);
        value = fn_8011F7D8(lbl_8064C4E4);
        index = fn_8011F134(lbl_8064C4E4);
        if (index == 0xFFFF) {
            fn_80127F90(lbl_8064C4E4, 0, &c);
        } else {
            fn_80127F90(lbl_8064C4E4, index, &c);
        }
        lbl_802FC6FC = a;
        lbl_802FC6FC.z = c.z;
    }

    fn_80211A90(value, &b, amount);
    fn_80211A48(&lbl_802FC6FC, &b, output);
}
