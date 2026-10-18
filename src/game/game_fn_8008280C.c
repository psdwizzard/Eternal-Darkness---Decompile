typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef union Color {
    u32 word;
    u8 channel[4];
} Color;

typedef struct Effect {
    u32 id;
    u32 owner;
    u32 unknown08;
    u32 velocity;
    u32 acceleration;
    u8 pad14[8];
    Vec3 position;
    Color color;
    u16 field2C;
    u16 field2E;
    u16 field30;
    u16 field32;
    u16 field34;
    u8 field36;
    u8 field37;
    u8 field38;
    u8 pad39[0xF];
    int (*callback)(u32);
    u8 pad4C[0x2C];
} Effect;
typedef struct RuntimeState {
    u8 pad[0x4A4];
    Effect effects[3];
} RuntimeState;
typedef struct GameState {
    u8 pad[0x1E0];
    u8 effectMask[3];
} GameState;

extern GameState lbl_8031CBA0;
extern RuntimeState lbl_8031CD84;
extern int lbl_8064D18C;
extern Color lbl_8064B58C;
extern const Color lbl_8064EAB0;
extern const Color lbl_806519A0;
extern int fn_8008250C(u32);
extern int fn_802019EC(int, int);
extern void *fn_80201814(int);
extern void *fn_80201BC8(void *);
extern void fn_801FD534(u32);
extern void fn_8014CBC0(void *);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern int fn_801E8328(u32, u32);
extern void *fn_8012C62C(u8 *, int, void *, s8 *, void *, int);

void fn_8008280C(int enable)
{
    int variant = 0;
    int i;
    u8 *object;
    void *entry;
    Vec3 position;
    Color color;
    Color start, end, finish;
    switch (lbl_8064D18C) {
    case 0xDA: variant = 1; break;
    case 0x47: variant = 2; break;
    }
    for (i = 0; i < 3; i++) {
        object = 0;
        entry = fn_80201814(fn_802019EC(i + 0x822, lbl_8064D18C));
        if (entry != 0)
            object = fn_80201BC8(entry);
        if (object != 0) {
            if (enable == 1) {
                color = lbl_8064EAB0;
                fn_801FD534(lbl_8031CD84.effects[i].id);
                fn_8014CBC0(&lbl_8031CD84.effects[i]);
                lbl_8031CD84.effects[i].id = 0;
                lbl_8031CD84.effects[i].owner = 0;
                fn_8011F114(&position, (Vec3 *)object);
                lbl_8031CD84.effects[i].position = position;
                lbl_8031CD84.effects[i].color = lbl_8064B58C;
                lbl_8031CD84.effects[i].callback = fn_8008250C;
                lbl_8031CD84.effects[i].field2C = 0;
                lbl_8031CD84.effects[i].field30 = 0;
                lbl_8031CD84.effects[i].field32 = 1;
                lbl_8031CD84.effects[i].velocity = 0;
                lbl_8031CD84.effects[i].acceleration = 0;
                lbl_8031CD84.effects[i].field36 = 25;
                lbl_8031CD84.effects[i].field37 = 0;
                lbl_8031CD84.effects[i].field38 = 5;
                if (lbl_8031CBA0.effectMask[variant] & (1 << i)) {
                    color.channel[3] = 255;
                    fn_801E8328(0x13, (u32)&lbl_8031CD84.effects[i]);
                } else {
                    lbl_8031CD84.effects[i].id = 0;
                }
                finish = color;
                end = lbl_806519A0;
                start = color;
                fn_8012C62C(object, 15, &start, (s8 *)&end, &finish, 4);
            } else if (lbl_8031CD84.effects[i].id != 0) {
                fn_801FD534(lbl_8031CD84.effects[i].id);
                lbl_8031CD84.effects[i].id = 0;
            }
        } else {
            lbl_8031CD84.effects[i].id = 0;
        }
    }
}
