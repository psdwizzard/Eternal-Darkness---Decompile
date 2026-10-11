typedef unsigned int u32;

typedef struct Vec4 {
    float x, y, z, w;
} Vec4;

typedef struct FourWords {
    u32 words[4];
} FourWords;

typedef union Rotation {
    Vec4 vector;
    FourWords words;
} Rotation;

typedef struct Entry {
    int unused;
    void *object;
    unsigned char rest[28];
    u32 active;
    unsigned char tail[4];
} Entry;

typedef struct AxisTable {
    u32 unused[6];
    Vec4 axes[3];
} AxisTable;

extern const AxisTable lbl_8023A298;
extern Entry lbl_80330E88[];
extern Entry lbl_80331098[];

extern void fn_8012CEA4(void *, int, Vec4 *);
extern void fn_80179F48(const Vec4 *, Vec4 *);
extern void fn_8017A34C(const Vec4 *, const Vec4 *, Vec4 *);
extern void fn_80211E1C(Vec4 *, Vec4 *);
extern void fn_8012CDF0(void *, int, FourWords, int);

void fn_8010C220(int index, int axis, float angle)
{
    Vec4 axis0;
    Vec4 axis1;
    Vec4 axis2;
    Vec4 spin;
    Rotation combined;
    Vec4 current;
    Entry *primary;
    Entry *secondary;

    primary = &lbl_80330E88[index];
    axis0 = lbl_8023A298.axes[0];
    axis1 = lbl_8023A298.axes[1];
    axis2 = lbl_8023A298.axes[2];
    fn_8012CEA4(primary->object, 15, &current);

    switch (axis) {
    case 0:
        axis0.w = angle;
        fn_80179F48(&axis0, &spin);
        break;
    case 1:
        axis1.w = angle;
        fn_80179F48(&axis1, &spin);
        break;
    case 2:
        axis2.w = angle;
        fn_80179F48(&axis2, &spin);
        break;
    }

    fn_8017A34C(&spin, &current, &combined.vector);
    fn_80211E1C(&combined.vector, &combined.vector);
    fn_8012CDF0(primary->object, 15, combined.words, 1);

    secondary = &lbl_80331098[index];
    if (secondary->active != 0) {
        fn_8012CEA4(secondary->object, 15, &current);
        fn_8017A34C(&spin, &current, &combined.vector);
        fn_8012CDF0(secondary->object, 15, combined.words, 1);
    }
}
