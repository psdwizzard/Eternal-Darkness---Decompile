typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct ShortVec3 {
    short x;
    short y;
    short z;
} ShortVec3;

extern int lbl_8064D18C;
extern void* lbl_8064C4E4;

extern void fn_801AC980(int, int);
extern void fn_8011F114(Vec3*, void*);
extern void fn_801F68B0(Vec3*);
extern void fn_80179B64(Vec3*, ShortVec3*);
extern void fn_8013CCEC(Vec3*, Vec3*, ShortVec3*, int, int);
extern void fn_80211A6C(Vec3*, Vec3*, Vec3*);
extern float fn_80211B08(Vec3*);
extern int fn_801AC908(int, Vec3*, int);
extern int fn_8015E4E8(void);
extern int fn_801AC8AC(int, int, int, Vec3*);

int fn_8019FAB8(u8* object)
{
    Vec3 candidate;
    Vec3 base;
    Vec3 direction;
    Vec3 loop_position;
    Vec3 position;
    Vec3 fallback_position;
    ShortVec3 points[4];
    float best_distance;
    int outer;
    int inner;
    u8* source;
    ShortVec3* point_base;
    int count;

    count = *(u16*)(object + 0x90);
    if (lbl_8064D18C != *(int*)(object + 0x38)) {
        *(u16*)(object + 0x22) = 8;
        fn_801AC980(*(int*)(object + 0x94), 1);
        goto done;
    }

    if (lbl_8064C4E4 != 0) {
        fn_8011F114(&position, lbl_8064C4E4);
        source = (u8*)&position;
    } else {
        fn_801F68B0(&fallback_position);
        source = (u8*)&fallback_position;
    }
    base = *(Vec3*)source;

    point_base = points;
    for (inner = 0; inner < 4; inner++) {
        fn_80179B64((Vec3*)(*(u8**)(object + 0x8C) + inner * 0xC + 0xC), point_base + inner);
    }
    fn_8013CCEC(&candidate, &base, points, 4, 1);
    fn_80211A6C(&candidate, &base, &direction);
    best_distance = fn_80211B08(&direction);

    for (outer = 1; outer < count; outer++) {
        for (inner = 0; inner < 4; inner++) {
            fn_80179B64((Vec3*)(*(u8**)(object + 0x8C) + outer * 0x3C + inner * 0xC + 0xC), point_base + inner);
        }
        fn_8013CCEC(&loop_position, &base, points, 4, 1);
        fn_80211A6C(&loop_position, &base, &direction);
        {
            float distance = fn_80211B08(&direction);
            if (distance < best_distance) {
                candidate = loop_position;
                best_distance = distance;
            }
        }
    }

    if (fn_801AC908(*(int*)(object + 0x94), &candidate, 0xFF) == 0 &&
        fn_8015E4E8() == 0) {
        *(int*)(object + 0x94) = fn_801AC8AC(0x4B, 0x64, 0x3E8, &candidate);
    }
    (*(u16*)(object + 0xA))++;
done:
    return 0;
}
