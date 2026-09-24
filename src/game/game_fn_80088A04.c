typedef unsigned char u8;
typedef signed short s16;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Int3 {
    int x;
    int y;
    int z;
} Int3;

typedef struct Settings {
    s16 angle;
    u8 pad02[0x12];
    s16 phase;
    u8 pad16[0x12];
    s16 scale;
} Settings;

typedef struct Work {
    u8 pad[0xC4];
    struct Work* owner;
    u8 padC8[0x84];
    Vec3 position;
    u8 pad158;
    u8 active;
} Work;

extern void *fn_8006ED3C();
extern unsigned int fn_800FBFB0(void);
#define fn_800FBFB0() ((int)fn_800FBFB0())
extern void fn_801F69F0(Int3*, Vec3*, int);
extern Settings lbl_8031D3B8;
extern u8 lbl_8063D378[];

int fn_80088A04(Work* work)
{
    int index;
    Settings* settings = &lbl_8031D3B8;
    Work* owner = work;

    fn_8006ED3C(owner, 7, &index);
    owner = owner->owner;
    if (owner->active == 0 && lbl_8063D378 != 0) {
        Int3 input;
        Vec3 output;
        int random;

        settings->angle = fn_800FBFB0() % 512;
        random = fn_800FBFB0() % 352;
        settings->scale = 128;
        input.x = settings->angle + 64;
        input.z = -1;
        settings->phase = random;
        input.y = settings->phase + 64;
        fn_801F69F0(&input, &output, 0);
        owner->position.x = output.x;
        owner->position.y = output.y;
        owner->position.z = output.z;
        owner->active = 1;
    }
    return 0;
}
