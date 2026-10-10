typedef int s32;
typedef unsigned int u32;
typedef short s16;
typedef unsigned short u16;
typedef signed char s8;
typedef unsigned char u8;

typedef struct Vec3 { float x, y, z; } Vec3;

typedef struct ModeState {
    u8 pad0[0x8];
    s32 mode; /* 0x8 */
} ModeState;

typedef struct SpawnPoint {
    s16 x;
    s16 y;
    s16 z;
    u8 pad06[0x0A];
    int id; /* 0x10 */
    u8 pad14[4];
} SpawnPoint;

typedef struct Room {
    u8 pad000[0xB8];
    u16 spawnCount; /* 0xB8 */
    u8 pad0BA[2];
    SpawnPoint *spawns; /* 0xBC */
    u8 pad0C0[0x8142 - 0xC0];
    signed char loaded; /* 0x8142 */
    signed char active; /* 0x8143 */
} Room;

extern ModeState lbl_803003C8;
extern s32 lbl_8064C900;
extern s32 lbl_8064D18C;
extern float lbl_8064EA08;
extern float lbl_8064EA60;

extern void *fn_80201ADC(void);
extern int fn_80201EB8(void *);
extern void *fn_80201BC8(void *);
extern int fn_800FBFB0(void);
extern Room *fn_8015C28C(int);
extern u16 fn_80050730(int type, int mode, u8 *out_level, u8 *out_flags,
                       u16 *out_time, u32 *out_value);
extern void fn_80179B08(SpawnPoint *, Vec3 *);
extern void fn_80152838(Vec3 *, Vec3 *, u8);
extern int fn_801AC9F4(int, int, Vec3 *, int);
extern s32 fn_8012FF34(void *, Vec3 *, s32, s32);
extern void fn_801302BC(void *, s32);
extern void fn_8013037C(void *, float);
extern void fn_801302FC(void *, u32);

void fn_8007FD7C(void)
{
    u16 count;
    Vec3 pos;
    Vec3 target;
    Room *room;
    u16 type;
    void *runtime;
    SpawnPoint *spawns;
    u16 chosen;
    u16 seen;
    void *object;
    u16 matches;
    u16 i;
    u16 j;
    u16 pick;

    if (lbl_803003C8.mode == 1) {
        return;
    }
    object = fn_80201ADC();
    if (object == 0) {
        return;
    }
    if (lbl_8064D18C != fn_80201EB8(object)) {
        return;
    }
    runtime = fn_80201BC8(object);
    if (runtime == 0) {
        return;
    }
    if (lbl_8064C900 == 0) {
        lbl_8064C900 = (fn_800FBFB0() & 0x1FFF) + 0x2A30;
        room = fn_8015C28C(2);
        if (room->active != 0 && room->loaded != 0) {
            type = fn_80050730(0x50, 0, 0, 0, 0, 0);
            count = room->spawnCount;
            if (count != 0) {
                spawns = room->spawns;
                matches = 0;
                for (i = 0; i < count; i++) {
                    if (spawns[i].id == type) {
                        matches++;
                    }
                }
                if (matches != 0) {
                    chosen = 0;
                    seen = 0;
                    pick = fn_800FBFB0() % matches;
                    for (j = 0; j < count; j++) {
                        if (spawns[j].id == type) {
                            if (++seen == pick) {
                                chosen = j;
                            }
                        }
                    }
                    fn_80179B08(&spawns[chosen], &pos);
                    target = pos;
                    target.z += lbl_8064EA60;
                    fn_80152838(&pos, &target, 4);
                    fn_801AC9F4(0x42, 0x64, &pos, 2);
                    if (runtime != 0 && fn_8012FF34(runtime, &pos, 4, 5) != 0) {
                        fn_801302BC(runtime, 0x3C);
                        fn_8013037C(runtime, lbl_8064EA08);
                        fn_801302FC(runtime, 4);
                    }
                }
            }
        }
    }
    lbl_8064C900--;
}
