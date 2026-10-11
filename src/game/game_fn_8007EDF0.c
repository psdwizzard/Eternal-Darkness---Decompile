typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Basis { Vec3 axes[3]; } Basis;
typedef struct IconState {
    float angles[2];
    u8 padding[0x2c];
} IconState;
typedef struct GameState {
    float parameters[2];
    u32 resources[3];
    u16 duration, sound;
    u8 active;
    s8 selected;
    u8 padding1a[2];
    IconState icons[5];
    u8 padding120[0xa4];
    int timer;
    s16 timerCount;
    u8 padding1ca;
    s8 screen;
    s8 selectionState, selectedItem;
    s8 selections[18];
    u8 runeFlags[3];
    u8 padding1e3;
} GameState;
/* Five 0xb8-byte records follow the menu object header. */
typedef struct MenuEntry {
    IconState *state;
    u8 padding04[0x24];
    Vec3 direction, up;
    Basis basis;
    Vec3 axis, targetAxis;
    int facing;
    u8 padding80[0xc];
    float angles[2];
    u8 padding94[8];
    int position[2], size[2];
    s16 start[2], end[2];
    s8 type, selected;
    u8 paddingb6[2];
} MenuEntry;
typedef struct ResourceId { u32 id, flags; } ResourceId;
typedef struct MenuState {
    u8 padding00[0x6c];
    MenuEntry entries[5];
    u8 padding404[0x28];
    s8 selectedGroup;
    u8 padding42d[0x17];
    ResourceId resources[5];
    int counters[7];
    u8 symbols[7], symbolCount;
    u8 padding490[0x17c];
    int counter;
    u8 padding610[0x24];
} MenuState;
typedef struct MenuConstants {
    Vec3 padding[4];
    Vec3 axes[6];
    Vec3 directions[5];
    Vec3 up[5];
    Basis bases[5];
} MenuConstants;

extern GameState lbl_8031CBA0;
extern MenuState lbl_8031CD84;
extern const MenuConstants lbl_80239208;
extern char lbl_80244870[];
extern int lbl_8064C900;
extern float lbl_8064D7A0;
extern const float lbl_8064EA14, lbl_8064EA30, lbl_8064EA34, lbl_8064EA38;
extern void fn_8007D848(int);
extern void fn_8007EC28(void);
extern void fn_80211AAC(const Vec3 *, Vec3 *);
extern u32 fn_801E741C(const char *);
extern u32 fn_800FBFB0(void);
extern void *memset(void *, int, unsigned long);

/* Initialize the menu's icon transforms, selection state and resource IDs.
 * The three scalar accesses through the byte layout preserve MWCC's original
 * address coalescing and register allocation. */
void fn_8007EDF0(void)
{
    const MenuConstants *constants = &lbl_80239208;
    char *names = lbl_80244870;

    fn_8007D848(-1);
    memset(&lbl_8031CBA0, 0, sizeof(GameState));
    memset(&lbl_8031CD84, 0, sizeof(MenuState));

    lbl_8031CBA0.screen = -1;
    {
        int i;
        for (i = 0; i < 18; i++) {
            lbl_8031CBA0.selections[i] = -1;
        }
    }
    lbl_8031CBA0.parameters[0] = lbl_8064EA30;
    lbl_8031CBA0.parameters[1] = lbl_8064EA34;
    lbl_8031CBA0.selected = -1;
    lbl_8031CBA0.runeFlags[0] = 6;
    lbl_8031CBA0.runeFlags[1] = 5;
    lbl_8031CBA0.runeFlags[2] = 7;
    lbl_8064D7A0 = lbl_8064EA14;
    lbl_8031CBA0.resources[0] = 0x58d;
    lbl_8031CBA0.resources[1] = 0x58c;
    lbl_8031CBA0.resources[2] = 0x636;
    lbl_8031CD84.entries[0].state = &lbl_8031CBA0.icons[0];
    lbl_8031CD84.entries[0].selected = -1;
    lbl_8031CD84.entries[1].state = &lbl_8031CBA0.icons[1];
    lbl_8031CD84.entries[1].selected = -1;
    lbl_8031CD84.entries[2].state = &lbl_8031CBA0.icons[2];
    lbl_8031CD84.entries[2].selected = -1;
    lbl_8031CD84.entries[3].state = &lbl_8031CBA0.icons[3];
    lbl_8031CD84.entries[3].selected = -1;
    lbl_8031CD84.entries[4].state = &lbl_8031CBA0.icons[4];
    lbl_8031CD84.entries[0].type = 18;
    lbl_8031CD84.entries[1].type = 18;
    lbl_8031CD84.entries[2].type = 18;
    *(s8 *)((u8 *)&lbl_8031CD84 + 0x401) = -1; /* entries[4].selected */
    lbl_8031CD84.entries[3].type = 10;
    lbl_8031CD84.entries[4].type = 10;

    lbl_8031CD84.entries[0].end[0] = 450;
    lbl_8031CD84.entries[0].end[1] = 300;
    lbl_8031CD84.entries[0].start[0] = 450;
    lbl_8031CD84.entries[0].start[1] = 236;
    lbl_8031CD84.entries[1].end[0] = 520;
    lbl_8031CD84.entries[1].end[1] = 370;
    lbl_8031CD84.entries[1].start[0] = 520;
    lbl_8031CD84.entries[1].start[1] = 306;
    lbl_8031CD84.entries[2].end[0] = 520;
    lbl_8031CD84.entries[2].end[1] = 370;
    lbl_8031CD84.entries[2].start[0] = 520;
    lbl_8031CD84.entries[2].start[1] = 306;
    lbl_8031CD84.entries[3].end[0] = 520;
    lbl_8031CD84.entries[3].end[1] = 370;
    lbl_8031CD84.entries[3].start[0] = 520;
    lbl_8031CD84.entries[3].start[1] = 306;
    lbl_8031CD84.entries[4].end[0] = 520;
    lbl_8031CD84.entries[4].end[1] = 370;
    lbl_8031CD84.entries[4].start[0] = 520;
    lbl_8031CD84.entries[4].start[1] = 306;
    *(float *)((u8 *)&lbl_8031CBA0 + 0x1c) = lbl_8064EA14; /* icons[0].angles[0] */
    lbl_8031CBA0.icons[0].angles[1] = lbl_8064EA14;

    lbl_8031CD84.entries[1].size[0] = 0x3200;
    lbl_8031CD84.entries[1].size[1] = 0x3200;
    lbl_8031CD84.entries[1].position[0] = 0xc800;
    lbl_8031CD84.entries[1].position[1] = 0x9600;
    lbl_8031CD84.entries[2].size[0] = 0xf000;
    lbl_8031CD84.entries[2].size[1] = 0x3200;
    lbl_8031CD84.entries[2].position[0] = 0x11300;
    lbl_8031CD84.entries[2].position[1] = 0x8c00;
    lbl_8031CD84.entries[3].size[0] = 0x3200;
    lbl_8031CD84.entries[3].size[1] = 0x3200;
    lbl_8031CD84.entries[3].position[0] = 0x9600;
    lbl_8031CD84.entries[3].position[1] = 0xc800;
    lbl_8031CD84.entries[1].angles[0] = lbl_8064EA14;
    *(float *)((u8 *)&lbl_8031CD84 + 0x1b4) = lbl_8064EA38; /* entries[1].angles[1] */
    lbl_8031CD84.entries[2].angles[0] = lbl_8064EA38;
    lbl_8031CD84.entries[2].angles[1] = lbl_8064EA14;
    lbl_8031CD84.entries[3].angles[0] = lbl_8064EA38;
    lbl_8031CD84.entries[3].angles[1] = lbl_8064EA14;
    lbl_8031CD84.entries[1].axis = constants->axes[0];
    lbl_8031CD84.entries[1].targetAxis = constants->axes[1];
    lbl_8031CD84.entries[2].axis = constants->axes[2];
    lbl_8031CD84.entries[2].targetAxis = constants->axes[3];
    lbl_8031CD84.entries[3].axis = constants->axes[4];
    lbl_8031CD84.entries[3].targetAxis = constants->axes[5];

    lbl_8031CD84.entries[0].direction = constants->directions[0];
    lbl_8031CD84.entries[1].direction = constants->directions[1];
    lbl_8031CD84.entries[2].direction = constants->directions[2];
    lbl_8031CD84.entries[3].direction = constants->directions[3];
    lbl_8031CD84.entries[4].direction = constants->directions[4];
    lbl_8031CD84.entries[0].up = constants->up[0];
    lbl_8031CD84.entries[1].up = constants->up[1];
    lbl_8031CD84.entries[2].up = constants->up[2];
    lbl_8031CD84.entries[3].up = constants->up[3];
    lbl_8031CD84.entries[4].up = constants->up[4];
    lbl_8031CD84.entries[0].facing = 1;
    lbl_8031CD84.entries[1].facing = 1;
    lbl_8031CD84.entries[2].facing = -1;
    lbl_8031CD84.entries[3].facing = 1;
    lbl_8031CD84.entries[4].facing = 1;

    fn_80211AAC(&lbl_8031CD84.entries[0].direction, &lbl_8031CD84.entries[0].direction);
    fn_80211AAC(&lbl_8031CD84.entries[1].direction, &lbl_8031CD84.entries[1].direction);
    fn_80211AAC(&lbl_8031CD84.entries[2].direction, &lbl_8031CD84.entries[2].direction);
    fn_80211AAC(&lbl_8031CD84.entries[3].direction, &lbl_8031CD84.entries[3].direction);
    fn_80211AAC(&lbl_8031CD84.entries[4].direction, &lbl_8031CD84.entries[4].direction);
    fn_80211AAC(&lbl_8031CD84.entries[0].up, &lbl_8031CD84.entries[0].up);
    fn_80211AAC(&lbl_8031CD84.entries[1].up, &lbl_8031CD84.entries[1].up);
    fn_80211AAC(&lbl_8031CD84.entries[2].up, &lbl_8031CD84.entries[2].up);
    fn_80211AAC(&lbl_8031CD84.entries[3].up, &lbl_8031CD84.entries[3].up);
    fn_80211AAC(&lbl_8031CD84.entries[4].up, &lbl_8031CD84.entries[4].up);

    lbl_8031CD84.entries[0].basis = constants->bases[0];
    lbl_8031CD84.entries[1].basis = constants->bases[1];
    lbl_8031CD84.entries[2].basis = constants->bases[2];
    lbl_8031CD84.entries[3].basis = constants->bases[3];
    lbl_8031CD84.entries[4].basis = constants->bases[4];
    lbl_8031CD84.selectedGroup = -1;
    fn_8007EC28();

    lbl_8031CD84.resources[0].id = fn_801E741C(names + 0x62c);
    lbl_8031CD84.resources[1].id = fn_801E741C(names + 0x63c);
    lbl_8031CD84.resources[2].id = fn_801E741C(names + 0x64c);
    lbl_8031CD84.resources[3].id = fn_801E741C(names + 0x65c);
    lbl_8031CD84.resources[4].id = fn_801E741C(names + 0x65c);
    lbl_8031CBA0.timer = (int)fn_800FBFB0() % 1000 + 700;
    lbl_8031CBA0.timerCount = 0;
    lbl_8031CD84.counter = 0;
    lbl_8064C900 = 10800;
    lbl_8031CD84.counters[0] = 0;
    lbl_8031CD84.symbols[0] = 9;
    lbl_8031CD84.counters[1] = 0;
    lbl_8031CD84.symbols[1] = 10;
    lbl_8031CD84.counters[2] = 0;
    lbl_8031CD84.symbols[2] = 11;
    lbl_8031CD84.counters[3] = 0;
    lbl_8031CD84.symbols[3] = 12;
    lbl_8031CD84.counters[4] = 0;
    lbl_8031CD84.symbols[4] = 13;
    lbl_8031CD84.counters[5] = 0;
    lbl_8031CD84.symbols[5] = 14;
    lbl_8031CD84.counters[6] = 0;
    lbl_8031CD84.symbols[6] = 15;
    lbl_8031CD84.symbolCount = 0;
    lbl_8031CBA0.duration = 10800;
    lbl_8031CBA0.sound = 0xffff;
}
