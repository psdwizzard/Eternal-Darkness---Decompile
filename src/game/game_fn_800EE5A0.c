typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct MovieState {
    u8 pad[0x150];
    int start_time;
} MovieState;
typedef struct GameState {
    u8 pad[0x1DA];
    u8 scene;
} GameState;

extern GameState lbl_8030F540;
extern char lbl_803282E0[], lbl_80328360[];
extern MovieState lbl_805DB280;
extern int lbl_8064CBEC, lbl_8064CBF4, lbl_8064CBF8, lbl_8064CBFC;
extern u32 lbl_8064CC00[2];
extern int lbl_8064CC08, lbl_8064CC0C[2];
extern MovieState* lbl_8064CC14;
extern u32 lbl_8064CC18[2], lbl_8064D71C[2];
extern int lbl_8064CC20;

extern void* fn_801397F8(u32*, int, int, int);
extern void fn_80237D2C(int);
extern int fn_801358B4(int);
extern void fn_80046B68(void);
extern void fn_800ED93C(int);
extern void fn_801EB194(int);
extern void fn_80108C24(void*);
extern void fn_800EEB44(void);
extern void fn_80109B24(void*, u32, u32);
extern int DVDConvertPathToEntrynum(char*);
extern int fn_801098C0(void*, void*);
extern u32 fn_80135748(u32*);
extern u32 fn_80109574(void*);
extern void* fn_8015AA0C(void);
extern void fn_8012BD4C(void);
extern void* memset(void*, int, unsigned long);
extern int fn_80109424(void*, u32);
extern void fn_801093CC(void*);
extern u16 fn_8010940C(void*);
extern u16 fn_801093F4(void*);
extern void fn_801F5598(void*);
extern void fn_801F53E8(int);
extern void fn_800ED9DC(void*, void*);
extern void fn_800EDA88(void);
extern void fn_800ED9D8(void);
extern void fn_801093E4(void*, void*);
extern void fn_801093D4(void*, void*);
extern void fn_801093C4(void*);
extern int fn_80109790(void*, u8);
extern int fn_80236D30(void);
extern int fn_801B09DC(int*);
extern void fn_802367B0(char*, int);
extern void fn_80236A1C(void);
extern int fn_802365D4(void);

void fn_800EE5A0(void)
{
    int timer_size;
    u32 arena_size;
    u32 pool_size;
    char* arena;
    u32 buffers;
    u32 size;
    int time;
    u32 frame_size;

    arena = fn_801397F8(&arena_size, 2, 2, 1);
    arena = arena + arena_size - 0x180000;
    lbl_8064CC0C[0] = -2;
    lbl_8064CC0C[1] = -2;
    lbl_8064CBF4 = 3;
    lbl_8064CC08 = 0;
    fn_80237D2C(1);
    fn_801358B4(0);
    fn_80046B68();
    lbl_8064CBEC = 0;
    if (lbl_8030F540.scene != 0x25 && lbl_8030F540.scene != 0x26 && lbl_8030F540.scene != 0x27) {
        fn_800ED93C(0);
        fn_801EB194(1);
    }
    fn_80108C24(arena);
    fn_800EEB44();
    lbl_8064CC18[0] = lbl_8064D71C[0];
    lbl_8064CC18[1] = lbl_8064D71C[1];
    lbl_8064CC14 = &lbl_805DB280;
    fn_80109B24(&lbl_805DB280, (u32)lbl_8064CC18, 2);
    if (DVDConvertPathToEntrynum(lbl_803282E0) == -1) {
        lbl_8064CC20 = 0;
        return;
    }
    if ((u32)fn_801098C0(lbl_803282E0, lbl_8064CC14) == 0) {
        lbl_8064CC20 = 1;
        buffers = fn_80135748(&pool_size);
        size = fn_80109574(lbl_8064CC14);
        arena = fn_8015AA0C();
        fn_8012BD4C();
        memset(arena, 0, (size + 31) & ~31);
        fn_80109424(lbl_8064CC14, (u32)arena);
        fn_801093CC(fn_800ED93C);
        lbl_8064CBFC = fn_8010940C(lbl_8064CC14);
        lbl_8064CBF8 = fn_801093F4(lbl_8064CC14);
        lbl_8064CC00[0] = buffers;
        frame_size = lbl_8064CBFC * lbl_8064CBF8 * 4;
        lbl_8064CC00[1] = buffers + frame_size;
        if (lbl_8030F540.scene == 0x25 || lbl_8030F540.scene == 0x26 || lbl_8030F540.scene == 0x27) {
            fn_801F5598((void*)(lbl_8064CC00[1] + frame_size));
            fn_801F53E8(250);
        }
        fn_801093E4(lbl_8064CC14, fn_800ED9DC);
        fn_801093D4(lbl_8064CC14, fn_800EDA88);
        fn_801093C4(fn_800ED9D8);
        fn_80109790(lbl_8064CC14, 1);
        lbl_8064CC14->start_time = 0;
        if (fn_80236D30() == 0) {
            if (DVDConvertPathToEntrynum(lbl_80328360) != -1) {
                fn_802367B0(lbl_80328360, fn_801B09DC(&timer_size));
                fn_80236A1C();
            }
        } else {
            time = fn_802365D4();
            lbl_8064CC14->start_time = fn_802365D4();
            if (lbl_8030F540.scene == 0x25 || lbl_8030F540.scene == 0x26 || lbl_8030F540.scene == 0x27) {
                lbl_8064CC14->start_time += 0xB96 - time;
            } else if (lbl_8030F540.scene == 0x11) {
                lbl_8064CC14->start_time += 0x638 - time;
            } else if ((u8)(lbl_8030F540.scene - 0x2D) <= 1 || lbl_8030F540.scene == 0x2F) {
                lbl_8064CC14->start_time += 0x912 - time;
            } else if ((u8)(lbl_8030F540.scene - 0x3C) <= 1 || lbl_8030F540.scene == 0x3E) {
                lbl_8064CC14->start_time += 0x9B0 - time;
            }
        }
    } else {
        lbl_8064CC20 = 0;
    }
}
