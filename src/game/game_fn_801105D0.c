typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef struct Color { u8 r, g, b, a; } Color;
typedef struct Vec3f { float x, y, z; } Vec3f;

typedef struct ChapterEntry {
    char *name;
    int place;
    int act;
    int pad[2];
} ChapterEntry;

typedef struct ChapterData {
    u8 textures[0x3D0];
    u8 textureEnd[0x134];
    char *places[326];
    ChapterEntry entries[54];
} ChapterData;

extern ChapterData lbl_8024B6B0[];
extern unsigned int lbl_8024E388[];
extern int lbl_80331738[];
extern const Vec3f lbl_8023A3B0;
extern float lbl_8064B8BC;
extern char lbl_8064B8C0[8];
extern char lbl_8064B8C8[8];
extern char lbl_8064B8D0[8];
extern Color lbl_8064C2A8;
extern int lbl_8064CCF0;
extern int lbl_8064CD04;
extern int lbl_8064CD1C;
extern int lbl_8064CD80;

extern s16 fn_80144A2C(u32, s16, s16, int);
extern void fn_801A852C(unsigned long *, int, u16, unsigned long);
extern void fn_801A85D4(unsigned long *, u16, u16, unsigned long);
extern void fn_801A8974(int, int, int, int, int, int);
extern void fn_801A8D38(int);
extern void fn_801A8F08(s16, s16, s16, s16, int, u16, int);
extern void fn_801A90BC(void *, void *);
extern u32 fn_801E3A34(Color *);
extern void fn_801E3AA4(int);
extern void fn_801E5430(s16, s16);
extern void fn_801E56AC(float, const char *, ...);
extern void fn_801E5AD0(u8);
extern int fn_801E79FC(unsigned int, int);
extern int fn_801E7AD0(unsigned int *, int, int);
extern int fn_801E7B24(unsigned int *, int, int);
extern int fn_801E8D34(int);
extern int fn_801E8D44(int);
extern void fn_801ED3F4(int);
extern int fn_80201B44(void);
extern void *fn_80201814(int);
extern unsigned int fn_8020216C(void *);
extern void fn_8022B970(int, int, int, int);

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

static inline void setTile(Color color, int index, int tile, u32 flags)
{
    fn_801A852C((unsigned long *)&color, index, tile, flags);
}

static inline void setTilePair(Color color, int first, int second, u32 flags)
{
    fn_801A85D4((unsigned long *)&color, first, second, flags);
}

static inline void setTextColor(Color color)
{
    fn_801E3A34(&color);
}

void fn_801105D0(register int inputActive)
{
    int scroll;
    int current;
    int speed;
    register ChapterData *data;
    register ChapterData *dataHigh;
    register int active;
    int i;
    int index;
    long outer;
    int radius;
    int next;
    s16 y;
    float step;
    float scale;
    float size;
    float t;
    Vec3f sizes;
    ChapterEntry *entry;

    /* ASM: lis/mr/addi preserve the pooled-base initialization and input save;
     * the C pointer initializer inserts an additional register move. */
    asm {
        lis dataHigh, lbl_8024B6B0@ha
        mr active, inputActive
        addi data, dataHigh, lbl_8024B6B0@l
    }
    scroll = fn_80144A2C(0xC0000, 0x1FFF, 8, 0);
    current = fn_801E8D34(lbl_80331738[2]);
    scale = 1.0f;
    sizes = lbl_8023A3B0;
    if (lbl_8064CD1C != -1) {
        scroll = 8;
    }
    if ((scroll > 0 && current == 0) || (scroll < 0 && current == fn_801E8D44(lbl_80331738[2]))) {
        scroll = 0;
    }
    if (scroll == 0) {
        scroll = 3;
    }
    speed = scroll < 0 ? -scroll : scroll;

    if (lbl_8064CD04 > 0) {
        lbl_8064CD04 = 0 > (lbl_8064CD04 -= speed) ? 0 : lbl_8064CD04;
    } else if (lbl_8064CD04 < 0) {
        lbl_8064CD04 += speed;
        lbl_8064CD04 = 0 < lbl_8064CD04 ? 0 : lbl_8064CD04;
    }

    fn_8022B970(0xA0, 0x2D, 0x1A2, 0x166);
    step = 0.01f * speed;
    for (i = -1; i < 2; i++) {
        Color glow = {0xFF, 0xFF, 0xFF, 0x00};
        y = i * 120 + 235;
        size = 1.0f;
        if ((fn_8020216C(fn_80201814(fn_80201B44())) & 0x80000)) {
            index = current + i;
            if (lbl_8064CD04 > 0) {
                next = index - 1;
            } else {
                next = index + 1;
            }
        } else {
            index = fn_801E7B24(lbl_8024E388, 3, current + i);
            if (lbl_8064CD04 > 0) {
                next = fn_801E7B24(lbl_8024E388, 3, current + i - 1);
            } else {
                next = fn_801E7B24(lbl_8024E388, 3, current + i + 1);
            }
        }

        if (active) {
            if (lbl_8064CD04 > 0) {
                glow.a = lbl_8064CD04 * 255 / 120;
                if (i == 0) {
                    size = 1.0f + 0.6f * ABS(lbl_8064CD04 - 60) / 60.0f;
                }
            } else {
                glow.a = -lbl_8064CD04 * 255 / 120;
                if (i == 0) {
                    size = 1.0f + 0.6f * ABS(lbl_8064CD04 + 60) / 60.0f;
                }
            }
            if (i == 0) {
                if (speed > 3) {
                    size = 1.0f;
                }
                if (lbl_8064CD04 < 60 && lbl_8064CD04 > -60) {
                    if (size > lbl_8064B8BC) {
                        t = lbl_8064B8BC + step;
                        lbl_8064B8BC = t < size ? t : size;
                    } else if (size < lbl_8064B8BC) {
                        t = lbl_8064B8BC - step;
                        lbl_8064B8BC = t > size ? t : size;
                    }
                }
                t = lbl_8064B8BC;
                size = t;
                scale = t;
            }
        }
        (&sizes.x)[i + 1] = size;

        if (index >= 0 && index < 54) {
            Color color = lbl_8064C2A8;
            fn_801ED3F4(lbl_8064CD80);
            fn_801A90BC(&data->textures[0], &data->textureEnd[0]);
            if (next == -1) {
                color.a = 255 - glow.a;
            }
            setTile(color, 0, 6, 0x80000000);
            outer = 37.0f * size;
            fn_801A8F08(230 - outer, y - outer, outer + 230, y + outer, -0x7698, 0, 5);
            setTile(lbl_8064C2A8, 0, 0x2D, 0x80000000);
            radius = 32.0f * size;
            fn_801A8F08(230 - radius, y - radius, radius + 230, y + radius, -0x7698, (index + 1) * 4, 5);
            if (next == -1 || next >= 54) {
                setTile(glow, 0, 6, 0x80000000);
                radius = outer;
                fn_801A8F08(230 - radius, y - radius, radius + 230, y + radius, -0x7698, 0, 5);
            }
            if (next >= 0 && next < 54) {
                setTile(glow, 0, 0x2D, 0x80000000);
                fn_801A8F08(230 - radius, y - radius, radius + 230, y + radius, -0x7698, (next + 1) * 4, 5);
            }
            if (i == 0 && active) {
                unsigned int slot = index;
                if (fn_801E7AD0(lbl_8024E388, 3, slot) > 1 ||
                    (fn_8020216C(fn_80201814(fn_80201B44())) & 0x80000)) {
                    if (fn_801E79FC(lbl_8024E388[0], slot) ||
                        (fn_8020216C(fn_80201814(fn_80201B44())) & 0x80000)) {
                        if (fn_801E8D34(lbl_8064CCF0) == 0) {
                            setTilePair(lbl_8064C2A8, 0x4C, 0x4D, 0x80000000);
                        } else {
                            setTilePair(lbl_8064C2A8, 0x4E, 0x4F, 0x80000000);
                        }
                        fn_801A8F08(0x1E4, 0x28, 0x201, 0x5B, -0x7698, 0, 5);
                    }
                    if (fn_801E79FC(lbl_8024E388[1], slot) ||
                        (fn_8020216C(fn_80201814(fn_80201B44())) & 0x80000)) {
                        if (fn_801E8D34(lbl_8064CCF0) == 1) {
                            setTilePair(lbl_8064C2A8, 0x50, 0x51, 0x80000000);
                        } else {
                            setTilePair(lbl_8064C2A8, 0x52, 0x53, 0x80000000);
                        }
                        fn_801A8F08(0x1FF, 0x29, 0x217, 0x58, -0x7698, 0, 5);
                    }
                    if (fn_801E79FC(lbl_8024E388[2], slot) ||
                        (fn_8020216C(fn_80201814(fn_80201B44())) & 0x80000)) {
                        if (fn_801E8D34(lbl_8064CCF0) == 2) {
                            setTilePair(lbl_8064C2A8, 0x54, 0x55, 0x80000000);
                        } else {
                            setTilePair(lbl_8064C2A8, 0x56, 0x57, 0x80000000);
                        }
                        fn_801A8F08(0x215, 0x29, 0x232, 0x5A, -0x7698, 0, 5);
                    }
                }
            }
        }
    }

    if (active) {
        float half = 34.0f * scale;
        float full = 68.0f * scale;
        fn_801A8974(230.0f - half, 235.0f - half, full, 68.0f * scale, -0x7698, 3);
    }
    fn_801A8D38(6);

    {
        float f;
        s16 ty;

        for (i = -2; i < 4; i++) {
            Color text = {0x27, 0x1B, 0x0C, 0xFF};
            ty = i * 120 + 225;
            switch (i) {
            case -1:
                if (lbl_8064CD04 >= 0) {
                    f = 1.0f + 0.6f * lbl_8064CD04 / 240.0f;
                } else {
                    f = 1.0f;
                }
                break;
            case 0:
                if (lbl_8064CD04 >= 0) {
                    f = 1.6f - 0.6f * lbl_8064CD04 / 60.0f;
                } else {
                    f = 1.6f + 0.6f * lbl_8064CD04 / 60.0f;
                }
                break;
            case 1:
                if (lbl_8064CD04 >= 0) {
                    f = 1.0f;
                } else {
                    f = 1.0f - 0.6f * lbl_8064CD04 / 240.0f;
                }
                break;
            default:
                f = 1.0f;
                break;
            }
            if (1.6f < MAX(f, 1.0f)) {
                f = 1.6f;
            } else if (f > 1.0f) {
                /* ASM: b preserves the retail clamp's branch to the merge point;
                 * MWCC folds this empty C arm into the conditional branch. */
                asm { b clampDone }
            } else {
                f = 1.0f;
            }
clampDone:
            t = (f - 1.0f) / 0.6f;
            if (active) {
                text.r = 216.0f * t + 39.0f;
                text.g = 228.0f * t + 27.0f;
                text.b = 12.0f - 12.0f * t;
            }
            index = fn_801E7B24(lbl_8024E388, 3, current + i);
            if ((fn_8020216C(fn_80201814(fn_80201B44())) & 0x80000)) {
                index = current + i;
            }
            if (index >= 0 && index < 54) {
                fn_801E3AA4(1);
                setTextColor(text);
                fn_801E5AD0(0x63);
                fn_801E5430(0x1A0, ty + 2 + lbl_8064CD04);
                fn_8022B970(0xA0, 0x41, 0x1A2, 0x152);
                entry = data->entries;
                entry += index;
                fn_801E56AC(1.1f, entry->name);
                fn_801E5430(0x128, ty - 32 + lbl_8064CD04);
                fn_8022B970(0xA0, 0x41, 0x1A2, 0x152);
                fn_801E5AD0(0x6E);
                {
                    char **places = data->places;
                    places += entry->place;
                    fn_801E56AC(0.9f, *places);
                }
                fn_801E5430(0x1C2, ty - 32 + lbl_8064CD04);
                fn_8022B970(0xA0, 0x41, 0x1A2, 0x152);
                if (entry->act != -1) {
                    fn_801E56AC(0.9f, lbl_8064B8C0, entry->act);
                }
            }
        }
    }

    fn_8022B970(0, 0, 0x280, 0x1E0);
    fn_801E3AA4(0);
    fn_801E5AD0(0x63);
    {
        Color arrow = {0xC8, 0xC8, 0x00, 0xFF};
        setTextColor(arrow);
    }
    if (active) {
        if (current != 0) {
            fn_801E5430(0x190, 0x37);
            fn_801E56AC(1.0f, lbl_8064B8C8);
        }
        if (current < fn_801E8D44(lbl_80331738[2])) {
            fn_801E5430(0x190, 0x195);
            fn_801E56AC(1.0f, lbl_8064B8D0);
        }
    }
}
