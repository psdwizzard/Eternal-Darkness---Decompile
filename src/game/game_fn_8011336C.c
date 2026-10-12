typedef unsigned int u32;
typedef unsigned char u8;
typedef short s16;

typedef struct Vec3 { float x, y, z; } Vec3;

typedef struct CodecPoint {
    s16 x;
    s16 y;
} CodecPoint;

typedef struct CodecPath {
    CodecPoint points[7];
} CodecPath;

typedef struct CodecSlot {
    int min;
    int cur;
    int max;
    void *model;
    char pad10[0x2C - 0x10];
} CodecSlot;

typedef struct TaskDesc {
    char pad0[0x2C];
    void *unk2C;
} TaskDesc;

extern const CodecPath lbl_8023A3C0[3];
extern const u32 lbl_8023A444[];
extern TaskDesc lbl_8024DE38;
extern u32 lbl_80331748[];
extern CodecSlot lbl_803317F8[];
extern int lbl_80331A08[];
extern void *lbl_8064C504;
extern u8 lbl_8064CD28;
extern int lbl_8064CD2C;
extern int lbl_8064CD44;
extern u32 lbl_8064CD4C;
extern u32 lbl_8064CD50;
extern u32 lbl_8064CD54;
extern u8 lbl_8064CD64;
extern u32 lbl_8064CD68;
extern int lbl_8064CD6C;

extern void fn_80111F2C(int, unsigned int);
extern int fn_80112230(int);
extern int fn_80112258(int);
extern unsigned int fn_80113CF8(unsigned int);
extern int fn_80113E48(unsigned int);
extern void fn_80113F54(unsigned int);
extern void fn_80117AE0(s16, s16, int, int);
extern void fn_8011F0E8(void *, Vec3 *);
extern int fn_801A98F4(int, int);
extern void *fn_801E6CA0(void *, int, int, int, int);
extern int fn_801E75A4(u32, int);
extern void fn_801E8B24(int, int, int);
extern int fn_801E8D24(int);
extern int fn_801E8D34(int);
extern int fn_801E8D3C(int);
extern void fn_801F69F0(int *, Vec3 *, int);
extern int fn_80201B44();
extern void *fn_80201814();
extern unsigned int fn_8020216C(void);

void fn_8011336C(int unused, int event)
{
    int idx;
    CodecSlot *slot;
    u32 *rows;
    u32 row;
    u32 i;
    u32 count;
    float t;
    Vec3 world;
    int pos[3];

    if (event != 1) {
        return;
    }

    switch (lbl_8064CD44) {
    case 16:
        if (lbl_8064CD6C >= 0 && lbl_8064CD2C == 0) {
            lbl_8064CD44 = 0x11;
            lbl_8064CD54 = 1;
            lbl_8064CD64 = 0;
            lbl_8064CD68 = 0;
        }
        break;
    case 17:
        rows = &lbl_80331748[26];
        row = rows[lbl_8064CD6C];
        count = (row & 0xF) * 2 + 3;
        if (lbl_8064CD64 <= 0xFA) {
            if (lbl_8064CD68 < count) {
                lbl_8064CD64 += 5;
            } else {
                lbl_8064CD64 += 15;
                if (lbl_8064CD64 < 15) {
                    lbl_8064CD64 = 0xFF;
                }
            }
        } else if (lbl_8064CD68 <= count) {
            if (lbl_8064CD68 < count) {
                fn_801A98F4(0x108, 100);
                fn_80117AE0(lbl_8023A3C0[rows[lbl_8064CD6C] & 0xF].points[lbl_8064CD68].x,
                            lbl_8023A3C0[rows[lbl_8064CD6C] & 0xF].points[lbl_8064CD68].y,
                            lbl_8064CD68 + 1, 1);
            }
            lbl_8064CD64 = 0;
            lbl_8064CD68++;
        } else if (lbl_8064CD68 == count + 1) {
            lbl_8064CD50 = row;
            lbl_8064CD68++;
            fn_80111F2C(1, row);
        }
        break;
    case 7:
    case 20:
        idx = fn_801E8D24(lbl_80331A08[5]) * 3 + fn_801E8D34(lbl_80331A08[4]);
        slot = &lbl_803317F8[idx];
        slot->cur -= 5;
        if (slot->cur <= slot->max) {
            int item = idx + fn_801E8D3C(lbl_80331A08[5]) * 3;
            slot->cur = slot->max;
            lbl_8064CD44++;
            if ((lbl_80331748[item + 2] & 0x08000000) ||
                (fn_80201B44(), fn_80201814(), fn_8020216C() & 0x4000)) {
                lbl_8024DE38.unk2C = fn_801E6CA0(lbl_8064C504, 6, lbl_8023A444[item], 0, 1);
            } else {
                lbl_8024DE38.unk2C = fn_801E6CA0(lbl_8064C504, 6, 0x2D, 0, 1);
            }
        }
        t = (float)(slot->max - slot->cur) / (float)(slot->max - slot->min);
        pos[0] = (int)(t * (float)(fn_80112230(idx) - 0x140)) + 0x140;
        pos[1] = (int)(t * (float)(fn_80112258(idx) - 0xA5)) + 0xA5;
        pos[2] = slot->cur;
        fn_801F69F0(pos, &world, 0);
        fn_8011F0E8(slot->model, &world);
        break;
    case 9:
    case 22:
        idx = fn_801E8D24(lbl_80331A08[5]) * 3 + fn_801E8D34(lbl_80331A08[4]);
        slot = &lbl_803317F8[idx];
        slot->cur += 5;
        if (slot->cur >= slot->min) {
            slot->cur = slot->min;
            if (lbl_8064CD44 == 9) {
                lbl_8064CD44 = 6;
            } else if (lbl_8064CD6C >= 0) {
                lbl_8064CD44 = 0x17;
                lbl_8024DE38.unk2C = fn_801E6CA0(lbl_8064C504, 0xF, 0x1A, 0, 1);
                fn_801E8B24(lbl_80331A08[6], 1, 0);
            } else {
                lbl_8064CD44 = 6;
                fn_801E8B24(lbl_80331A08[6], 2, 0);
            }
        }
        t = (float)(slot->max - slot->cur) / (float)(slot->max - slot->min);
        pos[0] = (int)(t * (float)(fn_80112230(idx) - 0x140)) + 0x140;
        pos[1] = (int)(t * (float)(fn_80112258(idx) - 0xA5)) + 0xA5;
        pos[2] = slot->cur;
        fn_801F69F0(pos, &world, 0);
        fn_8011F0E8(slot->model, &world);
        break;
    case 3:
        count = (lbl_8064CD50 & 0xF) * 2 + 3;
        if (lbl_8064CD54 > count) {
            lbl_8064CD28 += 15;
        } else if (lbl_8064CD28 < 0x4B) {
            lbl_8064CD28 += 5;
        }
        if (lbl_8064CD28 == 0xFF) {
            lbl_8064CD50 &= ~(0xF << (lbl_8064CD54 * 4));
            lbl_8064CD50 |= fn_801E75A4(lbl_8064CD4C & 0x3FF0, fn_801E8D34(lbl_80331A08[3]))
                            << (lbl_8064CD54 * 4);
            if (lbl_8064CD54 > count) {
                unsigned int sound = fn_80113CF8(lbl_8064CD50);
                if (fn_80113E48(sound) != -1) {
                    fn_80113F54(sound | 0x04000000);
                    fn_80111F2C(1, lbl_8064CD50);
                } else {
                    for (i = 0; i < count; i++) {
                        fn_80117AE0(lbl_8023A3C0[lbl_8064CD50 & 0xF].points[i].x,
                                    lbl_8023A3C0[lbl_8064CD50 & 0xF].points[i].y, i + 1, 0);
                    }
                }
                lbl_8064CD44 = 4;
            }
        }
        break;
    }
}
