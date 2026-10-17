typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec4 { float x, y, z, w; } Vec4;
typedef struct FourWords { u32 words[4]; } FourWords;
typedef union Rotation { Vec4 vector; FourWords words; } Rotation;

typedef struct ClockState {
    u8 pad[0x120];
    s16 hour[2];   /* 0x120 */
    s16 minute[2]; /* 0x124 */
} ClockState;

enum { CLOCK_MINUTE_INDEX = 0x124 / sizeof(s16) };

typedef struct ClockCursor {
    s16 *minute;
} ClockCursor;

typedef struct ClockObjects {
    u8 pad[0x41C];
    u8 *hands[2][2]; /* 0x41C */
} ClockObjects;

typedef struct ClockConstants {
    u8 pad[0x224];
    Vec3 hourAxis;   /* 0x224 */
    Vec3 minuteAxis; /* 0x230 */
    Vec3 chimeAxis;  /* 0x23C */
} ClockConstants;

extern ClockState lbl_8031CBA0;
extern ClockObjects lbl_8031CD84;
extern ClockConstants lbl_80239208;
extern int lbl_8064D18C;
extern const float lbl_8064EAA0;
extern const float lbl_8064EAA4;
extern const float lbl_8064EAA8;
extern const float lbl_8064EAAC;

extern int fn_8011E310(int, int, int, int, int, int, int);
extern void fn_8017A244(const Vec3 *, Vec4 *, float);
extern void fn_8012CDF0(u8 *, int, FourWords, int);
extern int fn_801A98F4(int, void *);
extern void fn_80081FF8(int, int);
extern void fn_8007D744(int);
extern void fn_80144C40(void);

static inline int clockIndex(void)
{
    return lbl_8064D18C != 0x4E;
}

void fn_8008210C(int delta, u32 silent)
{
    ClockConstants *constants = &lbl_80239208;
    int alt = clockIndex();
    ClockCursor cursor;
    s16 old;
    int crossed = 0;
    Rotation rotation;
    Vec3 axis;
    Rotation rotation2;
    Vec3 axis2;
    Rotation rotation3;
    Vec3 axis3;

    /* Begin at the selected clock column, then advance to its minute field. */
    cursor.minute = (s16 *)((u8 *)&lbl_8031CBA0 + alt * 2);
    old = cursor.minute[CLOCK_MINUTE_INDEX];
    *(cursor.minute += CLOCK_MINUTE_INDEX) = old + delta;
    if (silent == 0) {
        fn_8011E310(6, 0x37, 0, 0, 0x32, 0, 0);
    }

    if (*cursor.minute >= 600) {
        *cursor.minute -= 600;
        lbl_8031CBA0.hour[alt]++;
        if (lbl_8031CBA0.hour[alt] >= 12) {
            lbl_8031CBA0.hour[alt] = 0;
        }
    } else if (*cursor.minute < 0) {
        *cursor.minute += 600;
        lbl_8031CBA0.hour[alt]--;
        if (lbl_8031CBA0.hour[alt] < 0) {
            lbl_8031CBA0.hour[alt] = 11;
        }
    }

    axis = constants->hourAxis;
    fn_8017A244(&axis, &rotation.vector,
                lbl_8064EAA0 * (*cursor.minute / lbl_8064EAA4));
    fn_8012CDF0(lbl_8031CD84.hands[alt][1], 15, rotation.words, 0);

    axis2 = constants->minuteAxis;
    fn_8017A244(&axis2, &rotation2.vector,
                lbl_8064EAA0 * ((*cursor.minute + lbl_8031CBA0.hour[alt] * 600) / lbl_8064EAA8));
    fn_8012CDF0(lbl_8031CD84.hands[alt][0], 15, rotation2.words, 0);

    if ((s16)delta > 0) {
        if (old + (s16)delta > (old / 30 + 1) * 30 - 1) {
            crossed = 1;
        }
    } else if (old + (s16)delta < (old / 30) * 30) {
        crossed = 1;
    }

    if (((s16)delta < 0 ? -(s16)delta : (s16)delta) > 3) {
        if (crossed) {
            fn_801A98F4(0x144, (void *)0x32);
        }
    } else if (lbl_8031CBA0.hour[alt] == 3 && *cursor.minute >= 340 &&
               *cursor.minute <= 346) {
        axis3 = constants->chimeAxis;
        fn_8017A244(&axis3, &rotation3.vector, lbl_8064EAAC);
        fn_8012CDF0(lbl_8031CD84.hands[alt][1], 15, rotation3.words, 0);
        if ((s16)delta != 0) {
            fn_801A98F4(0x280, (void *)0x64);
            fn_80081FF8(0, 0);
        }
    } else if (crossed) {
        fn_801A98F4(0x144, (void *)0x32);
    }

    fn_8007D744(8);
    fn_80144C40();
}
