typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct ObjectState {
    u8 pad[0x6c];
    void (*update)(void *);
    u8 pad70[4];
    struct ObjectState *child;
} ObjectState;
typedef struct GameState {
    u8 pad0[0x18];
    u8 active; /* 0x18 */
    u8 pad19[0x1];
    u8 submode; /* 0x1A */
    u8 pad1B[0x39];
    float angle1; /* 0x54 */
    u8 pad58[0x2C];
    float angle2; /* 0x84 */
    u8 pad88[0x30];
    float angle3; /* 0xB8 */
    u8 padBC[0xD0];
    Vec3 position; /* 0x18C */
    Vec3 target; /* 0x198 */
    Vec3 direction; /* 0x1A4 */
    u8 pad1B0[0xC];
    int positionInitialized; /* 0x1BC */
    float selectionAngle; /* 0x1C0 */
    u8 pad1C4[0x7];
    s8 screen; /* 0x1CB */
    s8 selectionState; /* 0x1CC */
    s8 selectedItem; /* 0x1CD */
    s8 selections[18]; /* 0x1CE */
    u8 runeFlags[3]; /* 0x1E0 */
    u8 pad1E3[0x1];
} GameState;
typedef struct CameraPair { Vec3 first, second; u8 tail[8]; } CameraPair;
typedef struct ModelGroup {
    u8 pad[0x94]; void *primary, *secondary; u8 tail[0x1c];
} ModelGroup;
typedef struct MenuState {
    void *model; /* 0x0 */
    u8 pad4[8];
    CameraPair cameras[3];
    ModelGroup groups[5];
    void *model404; /* 0x404 */
    int value408; /* 0x408 */
    int value40C; /* 0x40C */
    int value410; /* 0x410 */
    int value414; /* 0x414 */
    int counter; /* 0x418 */
    void *pair[2][2]; /* 0x41C */
    s8 selectedGroup; /* 0x42C */
    u8 pad42D[0x3];
    void *model430; /* 0x430 */
    ObjectState * object; /* 0x434 */
    int value438; /* 0x438 */
    int value43C; /* 0x43C */
    int value440; /* 0x440 */
    u8 pad444[0x53];
    u8 flag497; /* 0x497 */
    void *text[3]; /* 0x498 */
    u8 pad4A4[0x16C];
    void *range; /* 0x610 */
    void *models[5]; /* 0x614 */
    u32 mask; /* 0x628 */
    int firstBit; /* 0x62C */
} MenuState;
typedef struct Entry { char pad[0x1C]; unsigned int flags; } Entry;

extern GameState lbl_8031CBA0;
extern MenuState lbl_8031CD84;
extern Entry *lbl_8064C8E8;
extern void *lbl_8064C8EC;
extern u8 *lbl_8064C4E0;

extern void fn_80144C40(void);
extern void fn_80144680(Entry *entry);
extern void fn_8016B400(int id, void *context, void *value);
extern int fn_801A98F4(int index, void *object);
extern void fn_801E5FB0(void *object);
extern void fn_801E7974(unsigned char *bits, unsigned int index);

void fn_80084168(void)
{
    if (lbl_8064C8E8 != 0) {
        /* Direct indexing lets MWCC fold the groups offset into both loads.
         * A local ModelGroup pointer emits an extra addi of 0x6C and loads
         * at 0x94/0x98 instead of the retail 0x100/0x104. */
        if (lbl_8031CD84.groups[lbl_8031CD84.selectedGroup].primary &&
            lbl_8031CD84.groups[lbl_8031CD84.selectedGroup].secondary) {
            fn_801A98F4(0x2B2, (void *)100);
        }
        fn_80144C40();
        fn_80144680(lbl_8064C8E8);
        lbl_8031CBA0.screen = -1;
        lbl_8064C8E8 = 0;
        fn_801E5FB0(lbl_8064C8EC);
        lbl_8064C8EC = 0;
        lbl_8031CD84.selectedGroup = -1;
        fn_8016B400(0x574, 0, 0);
        lbl_8031CD84.groups[0].primary = 0;
        lbl_8031CD84.groups[0].secondary = 0;
        lbl_8031CD84.groups[1].primary = 0;
        lbl_8031CD84.groups[1].secondary = 0;
        lbl_8031CD84.groups[2].primary = 0;
        lbl_8031CD84.groups[2].secondary = 0;
        lbl_8031CD84.groups[3].primary = 0;
        lbl_8031CD84.groups[3].secondary = 0;
        lbl_8031CD84.groups[4].primary = 0;
        lbl_8031CD84.groups[4].secondary = 0;
        fn_801E7974(lbl_8064C4E0, 0x112);
    }
}
