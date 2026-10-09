typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec4 { float x, y, z, w; } Vec4;
typedef struct FourWords { u32 words[4]; } FourWords;
typedef union Rotation { Vec4 vector; FourWords words; } Rotation;
typedef struct Entry { char pad[0x1C]; unsigned int flags; } Entry;

typedef struct GameState {
    u8 pad0[0x1CB];
    s8 screen; /* 0x1CB */
} GameState;

typedef struct MenuState {
    u8 pad0[0x404];
    u8 *model404; /* 0x404 */
    int value408; /* 0x408 */
    int value40C; /* 0x40C */
    int value410; /* 0x410 */
    int value414; /* 0x414 */
} MenuState;

/* Declared exactly as defined in game_data_80239408.c / game_data_80239414.c.
 * They are read here as a whole Vec3 (a plain word-wise struct copy); the
 * volatile qualifier is not needed for this function's codegen. */
extern const volatile float lbl_80239408[3];
extern const volatile float lbl_80239414[3];
extern GameState lbl_8031CBA0;
extern MenuState lbl_8031CD84;
extern u8 *lbl_8064C4E0;
extern Entry *lbl_8064C8E8;
extern void *lbl_8064C8EC;
extern float lbl_8064EA14, lbl_8064EA94, lbl_8064EA98;

extern void fn_8007D744(int);
extern void fn_8012CDF0(u8 *, int, FourWords, int);
extern void fn_8012CEA4(u8 *, int, Vec4 *);
extern void fn_8012CF08(u8 *, int, Vec4, Vec4, int, int, float);
extern void fn_80144680(Entry *);
extern void fn_80144C40(void);
extern void fn_8016B400(int, void *, void *);
extern void fn_8017A244(const Vec3 *, Vec4 *, float);
extern void fn_8017A71C(Vec4 *);
extern int fn_8017A750(const Vec4 *, const Vec4 *);
extern int fn_801A98F4(int, void *);
extern void fn_801E5FB0(void *);
extern void fn_801E7974(u8 *, u32);

void fn_800818B8(short mode)
{
    Rotation rotation;
    Vec3 openAxis;
    Vec4 target;
    Vec3 closeAxis;
    Vec4 start;
    Vec4 current;

    switch (mode) {
    case 1:
        openAxis = *(const Vec3 *)lbl_80239408;
        fn_8017A244(&openAxis,&rotation.vector, lbl_8064EA14);
        fn_8012CDF0(lbl_8031CD84.model404, 8, rotation.words, 0);
        fn_80144680(lbl_8064C8E8);
        lbl_8031CBA0.screen = -1;
        lbl_8064C8E8 = 0;
        fn_801E5FB0(lbl_8064C8EC);
        lbl_8064C8EC = 0;
        fn_8016B400(0x355, 0, 0);
        break;
    case 0:
        if (lbl_8031CD84.value408 == 2 &&
            lbl_8031CD84.value40C < 5 && lbl_8031CD84.value40C > -5 &&
            lbl_8031CD84.value410 > 50 && lbl_8031CD84.value410 < 60) {
            fn_801A98F4(0xF2, (void *)100);
            fn_80144680(lbl_8064C8E8);
            lbl_8031CBA0.screen = -1;
            lbl_8064C8E8 = 0;
            fn_801E5FB0(lbl_8064C8EC);
            lbl_8064C8EC = 0;
            fn_801E7974(lbl_8064C4E0, 0xAD);
            fn_8016B400(0x355, 0, 0);
        } else {
            fn_801A98F4(0xF3, (void *)100);
        }
        break;
    default:
        closeAxis = *(const Vec3 *)lbl_80239414;
        fn_8012CEA4(lbl_8031CD84.model404, 8, &current);
        fn_8017A244(&closeAxis, &target, lbl_8064EA94);
        start = current;
        if (lbl_8031CD84.value410 == 0) {
            fn_8017A244(&closeAxis,&start, -lbl_8064EA98);
        }
        if (fn_8017A750(&start, &target)) {
            fn_8017A71C(&target);
        }
        fn_8012CF08(lbl_8031CD84.model404, 8, start, target, 0, 2, lbl_8064EA98);
        fn_801A98F4(0xF4, (void *)100);
        lbl_8031CD84.value408 = 0;
        lbl_8031CD84.value40C = 0;
        lbl_8031CD84.value410 = 0;
        lbl_8031CD84.value414 = 2;
        fn_8007D744(1);
        break;
    }
    fn_80144C40();
}
