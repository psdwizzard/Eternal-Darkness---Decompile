typedef signed short s16;
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXColor {
    u8 r, g, b, a;
} GXColor;

typedef struct ChapterEntry {
    int state;
    int era;
    int nextEra;
    int rune;
    u8 pad10[2];
    u8 flags;
    u8 pad13[5];
    long long playTime;
    u8 pad20[0xC];
    int kind;
    u8 pad30[8];
} ChapterEntry;

typedef struct ChapterMenu {
    u8 pad0[0x28];
    ChapterEntry entries[7];
    u8 order[8];
} ChapterMenu;

typedef struct PositionTable {
    s16 x[8];
} PositionTable;

typedef struct TextBuffer {
    char text[20];
} TextBuffer;

typedef struct CalendarTime {
    int sec;
    int min;
    int hour;
    int mday;
    int mon;
    int year;
    int wday;
    int yday;
    int msec;
    int usec;
} CalendarTime;

typedef struct Panel {
    u8 pad0[0x10];
    int texture;
} Panel;

extern char jumptable_80246E60[];
extern GXColor lbl_802FC5BC[];
extern PositionTable lbl_802397C8;
extern TextBuffer lbl_802397D8;
extern char* lbl_8023B9E4[];
extern u8 lbl_802515D0[];
extern Panel lbl_8030241C;
extern ChapterMenu lbl_80320738;
extern float lbl_80320B30[6];
extern u8 lbl_8064B6C8;
extern u8 lbl_8064B6CA;
extern char lbl_8064B6CC[3];
extern char lbl_8064B6D0[8];
extern char lbl_8064B6D8[8];
extern char lbl_8064B6E0[8];
extern char lbl_8064B6E8[3];
extern GXColor lbl_8064C2AC;
extern GXColor lbl_8064C2B0;
extern GXColor lbl_8064C2BC;
extern GXColor lbl_8064C2C4;
extern void* lbl_8064CA24;
extern int lbl_8064CD80;
extern int lbl_8064CDC8;
extern float lbl_8064CE40;
extern int lbl_8064CE44;
extern const float lbl_8064F010;
extern const float lbl_8064F01C;
extern const GXColor lbl_8064F038;
extern const GXColor lbl_8064F03C;
extern const GXColor lbl_8064F040;
extern const float lbl_8064F044;
extern const float lbl_8064F048;
extern const double lbl_8064F050;
extern const double lbl_8064F058;
extern const float lbl_8064F060;
extern const float lbl_8064F064;
extern const float lbl_8064F068;
extern const float lbl_8064F06C;
extern const float lbl_8064F070;
extern const float lbl_8064F074;

extern int fn_800B194C(void);
extern int fn_800B6908(void);
extern void fn_800B6B00(int);
extern int fn_800B6C00(int);
extern int fn_800B6C88(int);
extern void fn_800B6D10(unsigned int, void*);
extern int fn_800B6E40(int);
extern void sprintf(void*, const char*, ...);
extern void fn_801A85D4(GXColor, u32, u32, u32);
extern void fn_801A872C(int, s16, s16, s16, int, int, GXColor);
extern void fn_801A8974(int, s16, s16, s16, int, int);
extern void fn_801A8C60(int, int, void*, void*);
extern void fn_801A8D38(int);
extern void fn_801A8EDC(void*);
extern void fn_801A8F08(s16, s16, s16, s16, int, int, int);
extern void fn_801E3A34(GXColor);
extern void fn_801E3AA4(int);
extern void fn_801E5448(s16, s16, float, const char*, ...);
extern void fn_801E5594(s16, s16, float, GXColor*, GXColor*, const char*, ...);
extern void fn_801E5AD0(int);
extern void fn_801E8D24(void*);
extern int fn_801E8D34(void*);
extern int fn_801E8D3C(void*);
extern int fn_801E8D44(void*);
extern int fn_801E8D4C(void*);
extern void fn_801ED3F4(int);
extern void fn_801ED5F4(int, int, int, int, int, float);
extern void OSTicksToCalendarTime(long long, CalendarTime*);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void fn_800B6E9C(u8 alpha, int locked)
{
    CalendarTime time;
    TextBuffer buffer;
    PositionTable positions;
    GXColor textColor;
    GXColor selectColor;
    GXColor shadow;
    GXColor color;
    GXColor fadeColor;
    GXColor boxColor;
    GXColor textBoxColor;
    GXColor fallback;
    float* scale;
    float fade;
    float start_frac;
    float end_frac;
    int isAlt;
    int i;
    int first;
    int selected;
    int count;
    int noCursor;
    int nameColor;
    int nextColor;
    int frameColor;
    int innerColor;
    int innerHeight;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    s16 nextX;
    s16 boxW;
    s16 boxH;
    s16 offsetY;
    s16 curX;
    ChapterEntry* entry;
    s16 iconX;
    s16 iconY;
    s16 textX;
    s16 dateY;
    char* strings;

    isAlt = lbl_8064CDC8 == 3;
    strings = jumptable_80246E60;
    first = fn_801E8D3C(lbl_8064CA24);
    fn_801E8D24(lbl_8064CA24);
    selected = fn_801E8D34(lbl_8064CA24);
    count = fn_801E8D4C(lbl_8064CA24);
    noCursor = fn_800B6908();
    x = isAlt ? 0xB8 : 0x93;
    y = isAlt ? 0x11E : 0x110;
    width = isAlt ? 0x15A : 0x15A;
    height = isAlt ? 0x7C : 0x7C;
    nextX = x;
    textColor = lbl_802FC5BC[0];
    selectColor = lbl_802FC5BC[13];
    color = *(isAlt ? &lbl_8064C2B0 : (fallback = lbl_8064F038, &fallback));
    shadow = color;
    positions = lbl_802397C8;
    textColor.a = alpha;
    selectColor.a = alpha;
    color.a = lbl_8064B6C8;
    fn_801A8C60(0xF0, 0x96, &lbl_8064B6C8, &lbl_8064B6CA);
    if (fn_800B194C() != 3) {
        textColor = lbl_802FC5BC[0];
        selectColor = lbl_8064C2B0;
        color = shadow;
    }
    fn_800B6B00(selected);
    fn_801E3AA4(0);
    fn_801E5AD0(0x63);
    if (first > 0) {
        fn_801E5594(x - 0x11, y + 0x1D, lbl_8064F01C, &color, &textColor,
                    lbl_8064B6CC, 6);
    }
    if (first + count <= fn_801E8D44(lbl_8064CA24)) {
        fn_801E5594(x + width + 0xF, y + 0x1D, lbl_8064F01C, &color,
                    &textColor, lbl_8064B6CC, 5);
    }

    for (i = first; i < first + count; i++) {
        scale = &lbl_80320B30[i];
        curX = nextX;
        boxW = lbl_8064F044 * *scale;
        boxH = lbl_8064F048 * *scale;
        entry = &lbl_80320738.entries[lbl_80320738.order[i]];
        offsetY = (0x57 - boxH) >> 1;
        if (i > selected && *scale >= lbl_8064F050 && *scale <= lbl_8064F058) {
            if (isAlt) {
                curX = positions.x[i - first];
            } else {
                curX = positions.x[i - first + 4];
            }
        }

        if (entry->state == 1 && entry->kind == 0x6C && locked == 0) {
            nameColor = isAlt ? fn_800B6C88(entry->era) : fn_800B6C00(entry->era);
            nextColor = isAlt ? fn_800B6C88(entry->nextEra) : fn_800B6C00(entry->nextEra);
            frameColor = isAlt ? 0x5C : 0x3F;
            innerColor = isAlt ? 0x49 : 0x3D;
            innerHeight = isAlt ? 0x4B : 0x40;
            iconX = lbl_8064F060 * *scale + curX;
            iconY = lbl_8064F064 * *scale + (y + offsetY);
            start_frac = (float)(i - first) / (float)count;
            end_frac = (float)(i - first + 1) / (float)count;
            fade = MIN(1.0f, MAX(MIN(end_frac, lbl_8064CE40) / end_frac, 0.0f));

            fn_801A8D38(5);
            fn_801A8EDC(lbl_802515D0);
            if (isAlt) {
                fn_801ED3F4(lbl_8064CD80);
            } else {
                fn_801ED3F4(lbl_8030241C.texture);
            }
            if ((lbl_8064CE44 & 2) && lbl_8064CE40 > start_frac) {
                fadeColor = lbl_8064F03C;
                fadeColor.a = MIN(lbl_8064F068 * fade, lbl_8064F068);
                fn_801A85D4(fadeColor, 0x4A, 0x4A, 0x80000000);
                fn_801A8F08(curX, y + offsetY, curX + boxW, boxH + (y + offsetY), -1, 0, 5);
            }
            boxColor = lbl_8064C2AC;
            if ((lbl_8064CE44 & 2) && lbl_8064CE40 > start_frac) {
                boxColor.a = MAX(lbl_8064F068 - lbl_8064F068 * fade, 0.0f);
            }
            if (entry->era == 0 && entry->nextEra != 0) {
                fn_801A85D4(boxColor, nextColor, frameColor, 0x80000000);
                fn_801A8EDC(strings + 0xA08);
                fn_801A8F08(curX, y + offsetY, curX + boxW, boxH + (y + offsetY), -1, 0, 5);
                fn_801A8EDC(lbl_802515D0);
                fn_801A85D4(boxColor, innerColor, innerHeight, 0x80000000);
                fn_801A8F08(curX, y + offsetY, curX + boxW, boxH + (y + offsetY), -1, 0, 5);
            } else {
                fn_801A85D4(boxColor, nameColor, frameColor, 0x80000000);
                fn_801A8F08(curX, y + offsetY, curX + boxW, boxH + (y + offsetY), -1, 0, 5);
            }
            fn_801E3AA4(0);
            fn_801E5AD0(0x6C);
            textBoxColor = lbl_8064C2AC;
            textX = (float)(curX + boxW) - lbl_8064F06C * *scale;
            if ((lbl_8064CE44 & 2) && lbl_8064CE40 > start_frac) {
                textBoxColor.a = MAX(lbl_8064F068 - lbl_8064F068 * fade, 0.0f);
            }
            fn_801E3A34(textBoxColor);
            switch (entry->rune) {
            case 1:
                fn_801ED5F4(1, 0x422, 1, 0, 0, lbl_8064F070);
                fn_801E5448(textX, iconY, *scale, lbl_8064B6D0);
                fn_801ED5F4(0, 2, 1, 0, 0, lbl_8064F01C);
                break;
            case 2:
                fn_801ED5F4(1, 0x40A, 1, 0, 0, lbl_8064F070);
                fn_801E5448(textX, iconY, *scale, lbl_8064B6D8);
                fn_801ED5F4(0, 2, 1, 0, 0, lbl_8064F01C);
                break;
            case 3:
                fn_801ED5F4(1, 0x412, 1, 0, 0, lbl_8064F070);
                fn_801E5448(textX, iconY, *scale, lbl_8064B6E0);
                fn_801ED5F4(0, 2, 1, 0, 0, lbl_8064F01C);
                break;
            }
            if (entry->flags & 2) {
                fn_801E5448(iconX, iconY, *scale, lbl_8064B6D0);
                iconX = *scale * fn_800B6E40(1) + iconX;
            }
            if (entry->flags & 4) {
                fn_801E5448(iconX, iconY, *scale, lbl_8064B6D8);
                iconX = *scale * fn_800B6E40(2) + iconX;
            }
            if (entry->flags & 8) {
                fn_801E5448(iconX, iconY, *scale, lbl_8064B6E0);
                fn_800B6E40(3);
            }
            if (i == selected && !(lbl_8064CE44 & 2)) {
                dateY = y + height - 0x25;
                buffer = lbl_802397D8;
                OSTicksToCalendarTime(entry->playTime, &time);
                fn_801E5594(x - 5, dateY, lbl_8064F074, &shadow, lbl_802FC5BC,
                            lbl_8064B6E8, lbl_8023B9E4[entry->era]);
                fn_800B6D10(entry->era, buffer.text);
                fn_801E5594(x - 5, dateY + 0x14, lbl_8064F074, &shadow, lbl_802FC5BC,
                            lbl_8064B6E8, buffer.text);
                fn_801E5AD0(0x72);
                fn_801E5594(x + width + 5, dateY, lbl_8064F074, &shadow, lbl_802FC5BC,
                            strings + 0xA18);
                sprintf(buffer.text, strings + 0xA28, time.hour, time.min, time.sec);
                fn_801E5594(x + width + 5, dateY + 0x14, lbl_8064F074, &shadow,
                            lbl_802FC5BC, lbl_8064B6E8, buffer.text);
            }
        } else {
            fn_801A8D38(5);
            fn_801A8EDC(lbl_802515D0);
            if (isAlt) {
                fn_801ED3F4(lbl_8064CD80);
                fn_801A85D4(lbl_8064F040, 0x4A, 0x4A, 0x80000000);
            } else {
                fn_801ED3F4(lbl_8030241C.texture);
                fn_801A85D4(lbl_8064C2AC, 0x3E, 0x3F, 0x80000000);
            }
            fn_801A8F08(curX, y + offsetY, curX + boxW, boxH + (y + offsetY), -1, 0, 5);
            if (noCursor == 0 && i == selected) {
                fn_801E3AA4(0);
                fn_801E5AD0(0x63);
                fn_801E5594(x + (width >> 1), y + height - 0x28, lbl_8064F074,
                            &selectColor, &textColor, strings + 0xA38);
            }
            fn_801E5AD0(0x6C);
        }

        if (i == selected) {
            if (fn_800B194C() == 3) {
                if (isAlt) {
                    fn_801A8974(curX, y + offsetY, boxW, boxH, -1, 3);
                } else {
                    fn_801ED5F4(1, 0x482, 1, 0, 0, lbl_8064F070);
                    fn_801A872C(curX, y + offsetY, boxW, boxH, -1, 3, lbl_8064C2C4);
                    fn_801ED5F4(0, 2, 1, 0, 0, lbl_8064F01C);
                }
            } else if (isAlt) {
                fn_801A872C(curX, y + offsetY, boxW, boxH, -1, 3, lbl_8064C2BC);
            } else {
                fn_801A872C(curX, y + offsetY, boxW, boxH, -1, 3, lbl_8064C2C4);
            }
        }
        nextX += (s16)(boxW + 10);
    }
    fn_801A8D38(5);
}
