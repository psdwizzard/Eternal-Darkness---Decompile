typedef unsigned char u8;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

typedef struct Node {
    void *object;
} Node;

typedef struct Entry {
    void *object;
    Node *links[12];
    unsigned char flags;
    unsigned char linkCount;
    unsigned char tail[2];
} Entry;

extern void fn_800BCCC4(void *, Vec3 *);
extern void fn_800ED4BC(Vec3 *, int, const char *, ...);
extern void fn_800EBA80(int, Vec3 *, Color *, int, float);
extern void fn_801E7CBC(Vec3, Vec3, Vec3, Vec3, Color);

extern Color lbl_802FC5BC[];
extern Node *lbl_80320C60[];
extern char lbl_8064B6F0[8];
extern char lbl_8064B6F8[4];
extern Entry *lbl_8064CA74;
extern float lbl_8064F0CC;
extern Color lbl_8064F0D0;
extern Color lbl_8064F0D4;
extern Color lbl_8064F0D8;
extern float lbl_8064F0DC;
extern float lbl_8064F0E0;
extern float lbl_8064F0E4;

static inline void drawMarker(Vec3 *pos, Color color)
{
    fn_800EBA80(1, pos, &color, 0x7F, lbl_8064F0E4);
}

void fn_800BC888(int showLabels, int showLinks, int showPath, int showIndices)
{
    Vec3 pos;
    Vec3 top;
    Vec3 linkPos;
    Vec3 linkTop;
    Vec3 prev;
    Vec3 curTop;
    Vec3 prevTop;
    Vec3 cur;
    int i;
    int j;
    float height;

    if (showLabels || showLinks || showIndices) {
        for (i = 0; lbl_8064CA74[i].object != 0 && i < 500; i++) {
            fn_800BCCC4(lbl_8064CA74[i].object, &pos);
            if (showIndices) {
                pos.z += showLabels ? lbl_8064F0DC : lbl_8064F0E0;
                fn_800ED4BC(&pos, 3, lbl_8064B6F0, i, lbl_8064B6F8, lbl_8064B6F8);
                pos.z -= showLabels ? lbl_8064F0DC : lbl_8064F0E0;
            }
            if (showLabels) {
                drawMarker(&pos, lbl_802FC5BC[3]);
            }
            if (showLinks) {
                top = pos;
                top.z += lbl_8064F0CC;
                for (j = 0; j < lbl_8064CA74[i].linkCount; j++) {
                    Node *link = lbl_8064CA74[i].links[j];
                    if (link != 0 && link->object != 0) {
                        fn_800BCCC4(link->object, &linkPos);
                        linkTop = linkPos;
                        linkTop.z += lbl_8064F0CC;
                        fn_801E7CBC(pos, top, linkTop, linkPos, lbl_8064F0D0);
                    }
                }
            }
        }
    }

    if (showPath && lbl_80320C60[0] != 0 && lbl_80320C60[0]->object != 0) {
        fn_800BCCC4(lbl_80320C60[0]->object, &prev);
        height = lbl_8064F0CC;
        for (i = 1; lbl_80320C60[i] != 0 && i < 100; i++) {
            prevTop = prev;
            prevTop.z += height;
            if (lbl_80320C60[i]->object != 0) {
                fn_800BCCC4(lbl_80320C60[i]->object, &cur);
                curTop = cur;
                curTop.z += lbl_8064F0CC;
                drawMarker(&cur, lbl_802FC5BC[3]);
                fn_801E7CBC(prev, prevTop, curTop, cur, lbl_8064F0D4);
                fn_801E7CBC(cur, curTop, prevTop, prev, lbl_8064F0D8);
                prev = cur;
            }
        }
    }
}
