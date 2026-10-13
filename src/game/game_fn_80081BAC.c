typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec4 { float x, y, z, w; } Vec4;
typedef struct FourWords { u32 words[4]; } FourWords;
typedef union Rotation { Vec4 vector; FourWords words; } Rotation;

typedef struct MenuState {
    u8 pad[0x404];
    u8 *model;
    int stage;
    int error;
    int position;
    int turns;
    int frame;
} MenuState;

extern MenuState lbl_8031CD84;
extern u32 *lbl_8064C4E0;
extern const volatile float lbl_80239420[4][3];
extern float lbl_8064EA0C, lbl_8064EA9C;
extern void fn_8007D744(int);
extern void fn_80144C40(void);
extern void fn_8017A244(const Vec3 *, Vec4 *, float);
extern void fn_8012CDF0(u8 *, int, FourWords, int);
extern int fn_801E79FC(u32 *, u32);
extern int fn_801A98F4(int, void *);

static inline int minimum(int value, int limit)
{
    return limit < value ? limit : value;
}

static inline int maximum(int value, int limit)
{
    return limit > value ? limit : value;
}

void fn_80081BAC(short input)
{
    Rotation rotation;
    Vec3 axis;
    int speed;
    short direction;
    int clicked = 0;

    if (input > 0) {
        speed = input;
        direction = 1;
    } else {
        direction = -1;
        speed = -input;
    }
    if (speed == 6) {
        speed--;
    }
    if (lbl_8031CD84.frame % (6 - speed) == 0) {
        lbl_8031CD84.position += direction;
        if (lbl_8031CD84.position > 99) {
            lbl_8031CD84.position = 0;
            lbl_8031CD84.turns++;
            lbl_8031CD84.turns = lbl_8031CD84.turns <= 1 ? lbl_8031CD84.turns : 1;
            if (lbl_8031CD84.turns >= 2) {
                lbl_8031CD84.turns = 2;
                lbl_8031CD84.error = 0;
            }
        } else if (lbl_8031CD84.position < 0) {
            lbl_8031CD84.position = 99;
            lbl_8031CD84.turns--;
            lbl_8031CD84.turns = lbl_8031CD84.turns >= -1 ? lbl_8031CD84.turns : -1;
        }

        switch (lbl_8031CD84.stage) {
        case 0:
            if (lbl_8031CD84.error > -5) {
                if (lbl_8031CD84.turns > 2 || lbl_8031CD84.turns < 0) {
                    lbl_8031CD84.error = -6;
                } else if (lbl_8031CD84.turns == 2) {
                    lbl_8031CD84.error += direction;
                    lbl_8031CD84.error = minimum(lbl_8031CD84.error, 0);
                    if (lbl_8031CD84.position == 42) {
                        if (fn_801E79FC(lbl_8064C4E0, 0xA6)) {
                            clicked = 1;
                            fn_801A98F4(0xEF, (void *)100);
                        }
                        lbl_8031CD84.stage++;
                        lbl_8031CD84.error = 0;
                        lbl_8031CD84.turns = 0;
                    }
                } else {
                    lbl_8031CD84.error += direction;
                    lbl_8031CD84.error = minimum(lbl_8031CD84.error, 0);
                }
            }
            break;
        case 1:
            if (lbl_8031CD84.error < 5) {
                if (lbl_8031CD84.turns > 0 || lbl_8031CD84.turns < -1) {
                    lbl_8031CD84.error = 6;
                } else if (lbl_8031CD84.turns == -1) {
                    lbl_8031CD84.error += direction;
                    lbl_8031CD84.error = maximum(lbl_8031CD84.error, 0);
                    if (lbl_8031CD84.position == 20) {
                        if (fn_801E79FC(lbl_8064C4E0, 0xA6)) {
                            clicked = 1;
                            fn_801A98F4(0xEF, (void *)100);
                        }
                        lbl_8031CD84.stage++;
                        lbl_8031CD84.error = 0;
                        lbl_8031CD84.turns = 0;
                    }
                } else {
                    lbl_8031CD84.error += direction;
                    lbl_8031CD84.error = maximum(lbl_8031CD84.error, 0);
                }
            }
            break;
        case 2:
            if (lbl_8031CD84.error > -5 && lbl_8031CD84.error < 5) {
                if (lbl_8031CD84.turns != 0) {
                    lbl_8031CD84.error = -6;
                } else {
                    lbl_8031CD84.error += direction;
                    if (lbl_8031CD84.position < 55) {
                        lbl_8031CD84.error = minimum(lbl_8031CD84.error, 0);
                    } else {
                        lbl_8031CD84.error = maximum(lbl_8031CD84.error, 0);
                    }
                    if (lbl_8031CD84.position == 55 && fn_801E79FC(lbl_8064C4E0, 0xA6)) {
                        clicked = 1;
                        fn_801A98F4(0xEF, (void *)100);
                    }
                }
            }
            break;
        }
        if (!clicked) {
            fn_801A98F4(0xF0, (void *)100);
        }
        axis = *(const Vec3 *)lbl_80239420;
        fn_8017A244(&axis, &rotation.vector, lbl_8064EA0C * ((float)lbl_8031CD84.position / lbl_8064EA9C));
        fn_8012CDF0(lbl_8031CD84.model, 8, rotation.words, 0);
    }
    fn_8007D744(1);
    fn_80144C40();
    lbl_8031CD84.frame++;
}
