typedef unsigned int u32;
typedef unsigned char u8;

typedef struct GameState {
    int key;
    int previous;
    int room;
} GameState;
typedef struct Table Table;

extern GameState lbl_803003C8;

extern Table *lbl_8064C520;
extern Table *lbl_8064C528;
extern Table *lbl_8064C52C;
extern int lbl_8064C5BC;
extern int lbl_8064D18C;
extern float lbl_8064F010;
extern char lbl_80246F70[];
extern char lbl_8063CD18[];

extern void fn_80007EC0(int, int, u32);
extern void fn_80024B74(int);
extern void fn_80042974(void);
extern void fn_800429E8(void);
extern void fn_800AD238(int, int);
extern int fn_800AD430(void);
extern void fn_800AFE30(void);
extern void fn_8012B954(u8 *);
extern void *fn_80138A6C(u32, int);
extern void fn_80138E9C(void);
extern void fn_80159440(int, u32);
extern u32 fn_801E741C(const char *);
extern void *fn_801E86A0(Table *, u32);
extern u32 fn_801E88E4(Table *);
extern int fn_801FA198(void *, void *, int, int, int, int, int, int, void *);
extern void fn_80200EAC(int, int, int, int, float);

void fn_800B0414(int action, int flags, int update, int cameraMode, int cameraParam)
{
    int size;
    u32 i;
    void *entry;
    u32 j;
    void *other;
    u32 loadFlags;

    if (lbl_803003C8.room == 13) {
        size = fn_800AD430();
        fn_800AD238((int)fn_80138A6C(size, 0), size);
    }

    for (i = 0; i < fn_801E88E4(lbl_8064C52C); i++) {
        entry = fn_801E86A0(lbl_8064C52C, i);
        if (entry != 0) {
            for (j = 0; j < i; j++) {
                if (fn_801E86A0(lbl_8064C52C, j) == entry) {
                    break;
                }
            }
            if (j == i && entry != 0) {
                fn_8012B954((u8 *)entry);
            }
        }
    }

    fn_80042974();
    fn_800429E8();

    for (i = 0; i < fn_801E88E4(lbl_8064C528); i++) {
        other = fn_801E86A0(lbl_8064C528, i);
        if (other != fn_801E86A0(lbl_8064C520, i) && other != 0) {
            fn_8012B954((u8 *)other);
        }
    }

    fn_80024B74(lbl_803003C8.room);
    if (update != 0) {
        int value = lbl_8064D18C;
        lbl_8064D18C = -1;
        loadFlags = 0;
        if (flags != 0) {
            loadFlags |= 8;
        }
        fn_80159440(value, loadFlags);
        if (lbl_803003C8.room == 13) {
            fn_801FA198((void *)fn_801E741C(lbl_80246F70), lbl_8063CD18 + 0x110,
                         0, 0, 0, 0, 0, 0, 0);
        }
    }
    fn_80138E9C();
    fn_80007EC0(cameraMode, cameraParam, action);
    fn_80200EAC(0x3e, 0, 0, lbl_8064D18C, lbl_8064F010);
    if (lbl_8064C5BC != 0) {
        fn_800AFE30();
    }
}
