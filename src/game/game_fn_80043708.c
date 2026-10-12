typedef unsigned char u8;
typedef unsigned int u32;

typedef struct ResourcePath {
    char text[12];
} ResourcePath;

typedef struct GameState {
    int unknown[2];
    int mode;
} GameState;

typedef struct Table Table;

extern ResourcePath lbl_80238E08;
extern GameState lbl_803003C8;
extern Table lbl_803064C0;
extern u8 *lbl_8064C4E0;
extern Table *lbl_8064C500;
extern int lbl_8064D18C;

extern void fn_801E7974(u8 *bits, u32 index);
extern int fn_801E79FC(u32 *set, u32 index);
extern int fn_8015D458(void *owner, int *result, void *callback);
extern void fn_801E85A8(Table *table);

void fn_80043708(int index)
{
    ResourcePath path = lbl_80238E08;

    if (lbl_803003C8.mode == 0 && lbl_8064D18C == 100) {
        fn_801E7974(lbl_8064C4E0, 0x313);
    }
    if (index == 16) {
        index = 0;
    }
    if (index == 0 && fn_801E79FC((u32 *)lbl_8064C4E0, 0x313) != 0) {
        index = 12;
    }
    if (index == 19) {
        path.text[5] = index / 10 + '0';
        path.text[6] = '6';
    } else {
        path.text[5] = index / 10 + '0';
        path.text[6] = index % 10 + '0';
    }
    lbl_8064C500 = &lbl_803064C0;
    fn_8015D458(&path, (int *)&lbl_803064C0, (void *)0x9000);
    fn_801E85A8(lbl_8064C500);
}
