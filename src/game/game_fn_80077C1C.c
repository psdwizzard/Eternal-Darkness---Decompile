typedef unsigned int u32;
typedef int s32;

typedef struct Vec3_77C1C {
    u32 x, y, z;
} Vec3_77C1C;

extern void *fn_80036D38(void);
extern s32 fn_80200C20(s32);
extern s32 fn_80201B54(void *);
extern u32 fn_80201814(s32);
extern s32 fn_80201BC8(void);
extern s32 fn_801294DC(void *, s32, s32, s32, s32, s32);
extern float fn_8012B750(s32);
extern void fn_8017A12C(float *, float, float);
extern void fn_80129BA4(s32, float, float);
extern void fn_8012B690(s32, void *, void *);
extern s32 fn_8011F130(void *);
extern void fn_80211A6C(const void *, s32, void *);
extern float fn_80211B08(void *);
extern void fn_80211AAC(void *, void *);
extern void fn_80211A90(void *, void *, float);
extern void fn_80128B8C(void *, void *);
extern void fn_80129FD0(void *, s32, s32);
extern void fn_80128C28(s32, void *, s32);
extern void fn_80128C44(s32, void *, s32);
extern void fn_80201D2C(void *, s32);
extern void fn_80201D14(void *, s32);
extern void fn_80204810(void);
extern u32 lbl_802391C4[3];
extern float lbl_8064E870;
extern float lbl_8064E874;
extern float lbl_8064E8D8;
extern float lbl_8064E8F0;
extern float lbl_8064E8F4;

void fn_80077C1C(void *context, void *object, s32 event, u32 *result)
{
    void *work = fn_80036D38();
    s32 resource = fn_80200C20(event);
    s32 actor = fn_80201B54(context);
    s32 attachment;
    s32 created;
    float angle;
    float difference;
    Vec3_77C1C color;
    Vec3_77C1C direction;

    if (fn_80201814(resource) != 0)
        attachment = fn_80201BC8();
    else
        attachment = 0;

    color.x = lbl_802391C4[0];
    color.y = lbl_802391C4[1];
    color.z = lbl_802391C4[2];
    created = fn_801294DC(object, 0x7D, 0x120, 8,
                         (s32)lbl_802391C4[1], (s32)lbl_802391C4[0]);
    if (created != 0) {
        *(s32 *)((char *)work + 0x48) = resource;
        angle = lbl_8064E8D8 + fn_8012B750(attachment);
        fn_8017A12C(&difference, fn_8012B750((s32)object), angle);
        if (difference < lbl_8064E870)
            difference = -difference;
        if (difference > lbl_8064E874)
            fn_80129BA4(created, angle, lbl_8064E8F0);
        fn_8012B690(attachment, &color, &color);
        fn_80211A6C(&color, fn_8011F130(object), &direction);
        angle = fn_80211B08(&direction);
        fn_80211AAC(&direction, &direction);
        fn_80211A90(&direction, &direction, angle / lbl_8064E8F4);
        fn_80128B8C(object, &direction);
        fn_80129FD0(object, 0x240000, 1);
        fn_80128C28(created, fn_80204810, (actor << 8) | 0x6C);
        fn_80128C44(created, fn_80204810, (actor << 8) | 7);
        fn_80201D2C(context, 0x34);
        fn_80201D14(context, 1);
        if (result != 0)
            *result = 1;
    } else if (result != 0) {
        *result = 0;
    }
}
