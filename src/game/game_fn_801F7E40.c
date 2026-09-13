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
    void* value;
    unsigned int index;
    Vec3 init;
    Vec3 position;
    Vec3 adjusted;
    Vec3 source;
    Vec3 a;

    if (input != 0) {
        fn_8011F114(&init);
        value = fn_8011F7D8(input);
        index = fn_8011F134(input);
        if (index == 0xFFFF) {
            fn_80127F90(input, 0, &lbl_802FC6FC);
        } else {
            fn_80127F90(input, index, &lbl_802FC6FC);
        }
    } else if (lbl_8064C4E4 != 0) {
        source = lbl_8023B7F0;
        fn_8012B690(lbl_8064C4E4, &source, &a);
        value = fn_8011F7D8(lbl_8064C4E4);
        index = fn_8011F134(lbl_8064C4E4);
        if (index == 0xFFFF) {
            fn_80127F90(lbl_8064C4E4, 0, &position);
        } else {
            fn_80127F90(lbl_8064C4E4, index, &position);
        }
        lbl_802FC6FC = a;
        lbl_802FC6FC.z = position.z;
    }

    fn_80211A90(value, &adjusted, amount);
    fn_80211A48(&lbl_802FC6FC, &adjusted, output);
}
