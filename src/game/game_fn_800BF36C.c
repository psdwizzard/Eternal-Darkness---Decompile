typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Color {
    u8 red, green, blue, alpha;
} Color;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct QueryResult {
    u32 word0, word4;
    Vec3 position;
    Vec3 direction;
    u8 pad20[8];
} QueryResult;

typedef struct Effect {
    u32 state;
    int timer;
    u8 pad08[0x14];
    Vec3 position;
    Color color;
    u16 kind;
    u8 pad2E[9];
    u8 active;
    u8 mode;
    u8 pad39[0xF];
    int (*callback)(u32);
    Vec3 direction;
    u16 duration;
    u8 rate, enabled, type;
    u8 pad5D[0x1B];
} Effect;

extern Effect lbl_803250A8;
extern const float lbl_8064F110, lbl_8064F128;
extern const Color lbl_8064F12C;
extern void fn_8014CBC0(void *);
extern u32 fn_801A7498(void *);
extern u32 fn_801A7490(void *);
extern void *fn_80201814(u32);
extern void *fn_8004910C();
extern void *fn_80201BC8(void *);
extern int fn_8011F6A4(void *, int, int, int, void *, int);
extern int fn_801FD958(u32);
extern void fn_801FE8DC(void *, float, float, float);
extern int fn_801E8328(u32, u32);

int fn_800BF36C(void *unused, void *event)
{
    Color color = lbl_8064F12C;
    QueryResult query;
    void *event_object = (void *)(u32)event;
    u32 first, second;
    void *owner;

    fn_8014CBC0(&lbl_803250A8);
    first = fn_801A7498(event_object);
    second = fn_801A7490(event_object);
    owner = fn_80201814(first);
    fn_80201814(second);
    if (owner != 0) {
        if (fn_8011F6A4(fn_80201BC8(fn_8004910C(event_object)), 4, 15, -1, &query, 1) != -1) {
            lbl_803250A8.state = 0;
            lbl_803250A8.timer = 15000;
            lbl_803250A8.position = query.position;
            lbl_803250A8.color = color;
            lbl_803250A8.callback = fn_801FD958;
            lbl_803250A8.kind = 10;
            lbl_803250A8.active = 1;
            lbl_803250A8.mode = 3;
            lbl_803250A8.direction = query.direction;
            lbl_803250A8.duration = 1000;
            lbl_803250A8.rate = 60;
            lbl_803250A8.enabled = 1;
            lbl_803250A8.type = 4;
            fn_801FE8DC(&lbl_803250A8.timer, lbl_8064F110, lbl_8064F110, lbl_8064F128);
            fn_801E8328(19, (u32)&lbl_803250A8);
        }
    }
    return 1;
}
