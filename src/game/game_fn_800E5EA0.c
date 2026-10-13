typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec3i { int x, y, z; } Vec3i;
typedef union Vec3Storage { Vec3 position; Vec3i words; } Vec3Storage;
typedef struct ActorInfo { u8 pad[0x94]; int state; } ActorInfo;

extern void *lbl_8064C4E4;
extern u32 *lbl_8064C4E0;
extern float lbl_8064F740, lbl_8064F744;
extern u32 lbl_8064F754, lbl_8064F758, lbl_8064F75C, lbl_8064F760;
extern u32 lbl_8064F764, lbl_8064F768, lbl_8064F76C;
extern float lbl_8064F770;
extern u32 lbl_80651B50, lbl_80651B54;

extern void fn_8011F114(Vec3 *, Vec3 *);
extern void *fn_8011F130(void *);
extern ActorInfo *fn_80201B8C(void *);
extern void *fn_80201BC8(void *);
extern void *fn_80200C38(void **);
extern u32 fn_801A7498(void *);
extern u32 fn_801A74C0(void *);
extern void *fn_80201814(int);
extern void *fn_80205288(void *);
extern void *fn_8012C62C(u8 *, int, void *, s8 *, void *, int);
extern void fn_8020104C(int, int, int, int, float);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern int fn_800460EC(void);
extern int fn_80201B44(void);
extern int fn_801D9924(int);
extern int fn_801E79FC(u32 *, u32);
extern void fn_8016B400(int, void *, void *);
extern void fn_80211A6C(Vec3 *, Vec3 *, Vec3 *);
extern void fn_80211AAC(Vec3 *, Vec3 *);
extern void fn_800337C8(Vec3 *, const Vec3 *, int, void *, int, int);
extern void fn_80120AD0(void *, const void *, u16, u32, float, float);
extern void fn_800E50AC(Vec3i *, int *);

void fn_800E5EA0(int owner, void *object, int skip, int unused, void **event)
{
    Vec3 direction;
    Vec3 position;
    Vec3 ownerPosition;
    Vec3Storage effectPosition2;
    Vec3Storage effectPosition3;
    Vec3Storage effectPosition1;
    u32 color1, end1, start1;
    u32 color2, end2, start2;
    int value2, value3, value1;
    ActorInfo *actor;
    void *room;
    void *eventObject;
    int runEffect = 1;
    int extraFrames = 0;
    int kind;

    fn_8011F114(&ownerPosition, (Vec3 *)lbl_8064C4E4);
    direction = ownerPosition;
    actor = fn_80201B8C(object);
    room = fn_80201BC8(object);
    fn_8011F114(&position, (Vec3 *)room);
    fn_8011F130(room);
    eventObject = fn_80200C38(event);
    fn_80205288(fn_80201814(fn_801A7498(eventObject)));

    if ((fn_801A74C0(eventObject) >> 16) & 1) {
        kind = ((fn_801A74C0(eventObject) >> 20) & 1) * 3;
        if (kind == 0) {
            kind = (fn_801A74C0(eventObject) >> 18) & 2;
        }
        if (kind == 0) {
            kind = (fn_801A74C0(eventObject) >> 18) & 1;
        }
        switch (kind) {
        case 2:
            extraFrames = 30;
            /* Fall through: both variants use the same effect setup. */
        case 1:
            start1 = lbl_8064F758;
            end1 = lbl_80651B50;
            color1 = lbl_8064F754;
            fn_8012C62C(room, 15, &color1, (s8 *)&end1, &start1, 4);
            fn_8020104C(0x8C, owner, owner, 0, (float)(extraFrames + 30));
            break;
        case 3:
            fn_80201D2C(object, 8);
            fn_80201D14(object, 1);
            break;
        }
    } else if (skip == 0) {
        if (fn_800460EC() == 0) {
            if (fn_801D9924(fn_80201B44()) == 0) {
                start2 = lbl_8064F760;
                end2 = lbl_80651B54;
                color2 = lbl_8064F75C;
                fn_8012C62C(room, 15, &color2, (s8 *)&end2, &start2, 4);
                fn_8020104C(0x7A, owner, owner, 0, lbl_8064F770);
                fn_80201D2C(object, 0x70);
                fn_80201D14(object, 1);
                if (fn_801E79FC(lbl_8064C4E0, 0xA3)) {
                    switch (actor->state) {
                    case 2: fn_8016B400(0xAEB, 0, 0); break;
                    case 3: fn_8016B400(0xAEC, 0, 0); break;
                    case 1: fn_8016B400(0xAEA, 0, 0); break;
                    }
                } else {
                    switch (actor->state) {
                    case 2: fn_8016B400(0x16F, 0, 0); break;
                    case 3: fn_8016B400(0x1E7, 0, 0); break;
                    case 1: fn_8016B400(0x16C, 0, 0); break;
                    }
                }
            }
        }
    } else {
        runEffect = 0;
    }

    if (runEffect) {
        direction.z = position.z;
        fn_80211A6C(&direction, &position, &direction);
        fn_80211AAC(&direction, &direction);
        fn_800337C8(&position, &direction, actor->state, 0, 300, 1);
        switch (actor->state) {
        case 2:
            fn_80120AD0(room, 0, 100, 10, lbl_8064F740, lbl_8064F744);
            value2 = lbl_8064F764;
            effectPosition2.position = position;
            fn_800E50AC(&effectPosition2.words, &value2);
            break;
        case 3:
            fn_80120AD0(room, 0, 100, 18, lbl_8064F740, lbl_8064F744);
            value3 = lbl_8064F768;
            effectPosition3.position = position;
            fn_800E50AC(&effectPosition3.words, &value3);
            break;
        case 1:
            fn_80120AD0(room, 0, 100, 34, lbl_8064F740, lbl_8064F744);
            value1 = lbl_8064F76C;
            effectPosition1.position = position;
            fn_800E50AC(&effectPosition1.words, &value1);
            break;
        }
    }
}
