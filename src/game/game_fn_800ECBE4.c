typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Color {
    u8 r, g, b, a;
} Color;

typedef struct Point {
    s16 x, y, z;
} Point;

typedef struct Node {
    Point pos;
    u8 linkCount;
    Point** links;
} Node;

typedef struct NodeTable {
    u8 pad[0x60];
    u16 count;
    Node* nodes;
} NodeTable;

extern s16 lbl_802FC53C[];
extern Color lbl_802FC5BC[];

extern NodeTable* fn_8015C390(int);
extern void fn_801ED468(int);
extern void fn_80226D28(int);
extern void fn_801ED118(void);
extern int fn_801EDA7C(s16*, int, int, void*);
extern void fn_801ECF50(u32);
extern void fn_801ECD74(Color*);
extern void fn_80226AB4(int, int, u16);
extern void fn_800ED6F8(float, float, float);
extern void fn_800ED6F4(void);

/* Draws every node of a table as line segments to each of its links. */
void fn_800ECBE4(int kind, u8 colorIndex, u8 alpha)
{
    NodeTable* table;
    Color color;
    Color line;
    int i;
    u8 j;
    Node* node;
    Point* link;
    int total;

    table = fn_8015C390(kind);
    if (table != 0) {
        total = 0;
        fn_801ED468(0x1B);
        fn_80226D28(0);
        fn_801ED118();
        fn_801EDA7C(lbl_802FC53C, 0, 0x2BF, 0);
        fn_801ECF50(4);
        color = lbl_802FC5BC[colorIndex];
        color.a = alpha;
        line = color;
        fn_801ECD74(&line);

        for (i = 0; i < table->count; i++) {
            total += table->nodes[i].linkCount;
        }
        fn_80226AB4(0xA8, 3, total * 2);

        for (i = 0; i < table->count; i++) {
            node = &table->nodes[i];
            for (j = 0; j < node->linkCount; j++) {
                fn_800ED6F8(node->pos.x, node->pos.y, node->pos.z);
                link = node->links[j];
                fn_800ED6F8(link->x, link->y, link->z);
            }
        }
        fn_800ED6F4();
    }
}
