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

typedef struct Placement {
    Vec3 position;
    u8 pad0C;
    u8 active;
} Placement;

typedef struct Work {
    u8 pad[0xC4];
    struct Work* owner;
    u8 padC8[0x84];
    Placement placement;
} Work;

extern void fn_8006ED3C(void*, int, int*);
extern int rand(void);
extern void fn_801F69F0(Int3*, Vec3*, int);
extern u8 lbl_8063D378[];

typedef struct Rows {
    s16 first[10];
    s16 second[10];
    s16 third[10];
} Rows;

extern Rows lbl_8031D3B8;

int fn_80088A04(Work* work)
{
    int index;
    Placement* placement;
    Rows* rows = &lbl_8031D3B8;

    fn_8006ED3C(work, 7, &index);
    placement = &work->owner->placement;
    if (placement->active == 0 && lbl_8063D378 != 0) {
        Int3 input;
        Vec3 output;
        int random;

        rows->first[0] = rand() % 512;
        random = rand() % 352;
        rows->third[0] = 128;
        input.x = rows->first[0] + 64;
        input.z = -1;
        rows->second[0] = random;
        input.y = rows->second[0] + 64;
        fn_801F69F0(&input, &output, 0);
        placement->position.x = output.x;
        placement->position.y = output.y;
        placement->position.z = output.z;
        placement->active = 1;
    }
    return 0;
}
