typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec4 { float x, y, z, w; } Vec4;
typedef struct FourWords { u32 words[4]; } FourWords;
typedef union Rotation { Vec4 vector; FourWords words; } Rotation;
typedef struct GameState {
    float zAngle;
    u8 pad04[0x16];
    u8 submode;
} GameState;
typedef struct MenuState { u8 *model; u8 pad04[0x630]; } MenuState;

extern Vec3 lbl_802393E4;
extern GameState lbl_8031CBA0;
extern MenuState lbl_8031CD84;
extern float lbl_8064EA7C, lbl_8064EA80;
extern u32 fn_80144710(u32, int, int);
extern u32 fn_8014549C(int, float);
extern void fn_8017A244(const Vec3 *, Vec4 *, float);
extern void fn_8012CDF0(u8 *, int, FourWords, int);
extern void fn_80080B7C(void);
extern void fn_8007D744(int);
extern void fn_80144C40(void);

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void fn_80080D14(short delta)
{
    if ((!fn_80144710(0x30000, 1, 0) &&
         !fn_80144710(0x20000000, 1, 0)) ||
        (fn_8014549C(0, lbl_8064EA7C) & 0x30000)) {
        Rotation rotation;
        Vec3 axis = lbl_802393E4;

        if (delta != 0)
            lbl_8031CBA0.submode = 0;
        lbl_8031CBA0.zAngle += (float)delta / lbl_8064EA80;
        /* Clamp the model rotation to its permitted range. */
        lbl_8031CBA0.zAngle = MIN(0.675398f,
                                 MAX(lbl_8031CBA0.zAngle, -0.674601f));
        fn_8017A244(&axis, &rotation.vector, lbl_8031CBA0.zAngle);
        fn_8012CDF0(lbl_8031CD84.model, 15, rotation.words, 0);
        fn_80080B7C();
        fn_8007D744(0);
        fn_80144C40();
    }
}
