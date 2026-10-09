typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct Entry {
    u32 id;
    u32 owner;
    u32 packed_velocity;
    u8 pad0C[0x10];
    s16 finished;
    s16 active;
    u8 pad20[2];
    s16 status;
    u8 pad24[2];
    u16 timer;
    u8 pad28[4];
    s8 retry;
    u8 pad2D[3];
    u32 flags;
} Entry;

typedef union Color {
    u32 word;
    u8 channel[4];
} Color;

extern u8 lbl_8064B588[4];
extern u8 lbl_8064B58C[4];
extern u32 fn_800FBFB0(void);
extern Entry *fn_801FD6F4(u32);
extern void fn_801FD880(u32, u32 *);
extern u32 fn_801FD8BC(u32);
extern void fn_801FD80C(u32, const u32 *);
extern void fn_801FDF74(u32, s32);
extern s32 fn_801FE05C(u32);

s32 fn_8008250C(u32 id)
{
    Entry *state = fn_801FD6F4(id);
    Color color;
    s32 lifetime;
    s32 random;
    s8 velocity[3];
    s32 i;

    if (state != 0 && state->finished == 0) {
        if (state->active != 0) {
            fn_801FD880(id, &color.word);
            lifetime = fn_801FD8BC(id);
            velocity[0] = (s8)(u8)(state->packed_velocity >> 24);
            velocity[1] = (s8)(u8)(state->packed_velocity >> 16);
            velocity[2] = (s8)(u8)(state->packed_velocity >> 8);
            if (color.channel[0] == lbl_8064B58C[0] &&
                color.channel[1] == lbl_8064B58C[1] &&
                color.channel[2] == lbl_8064B58C[2]) {
                random = fn_800FBFB0() & 63;
                color.channel[0] = lbl_8064B58C[0] +
                    ((random * (lbl_8064B588[0] - lbl_8064B58C[0])) >> 6);
                color.channel[1] = lbl_8064B58C[1] +
                    ((random * (lbl_8064B588[1] - lbl_8064B58C[1])) >> 6);
                color.channel[2] = lbl_8064B58C[2] +
                    ((random * (lbl_8064B588[2] - lbl_8064B58C[2])) >> 6);
                color.channel[0] = color.channel[0] < 255U ? color.channel[0] : 255;
                color.channel[1] = color.channel[1] < 255U ? color.channel[1] : 255;
                color.channel[2] = color.channel[2] < 255U ? color.channel[2] : 255;
                lifetime = ((random * 100) >> 6) + 200;
                velocity[0] = (s8)((fn_800FBFB0() & 31) - 16);
                velocity[1] = (s8)((fn_800FBFB0() & 31) - 16);
                velocity[2] = (s8)((fn_800FBFB0() & 31) - 16);
            } else {
                color.channel[0] = color.channel[0] - 2 > lbl_8064B58C[0] ?
                    color.channel[0] - 2 : lbl_8064B58C[0];
                color.channel[1] = color.channel[1] - 2 > lbl_8064B58C[1] ?
                    color.channel[1] - 2 : lbl_8064B58C[1];
                color.channel[2] = color.channel[2] - 2 > lbl_8064B58C[2] ?
                    color.channel[2] - 2 : lbl_8064B58C[2];
                lifetime = lifetime - 5 > 200 ? lifetime - 5 : 200;
                for (i = 0; i < 3; i++) {
                    if (velocity[i] > 0) {
                        velocity[i]--;
                    } else if (velocity[i] < 0) {
                        velocity[i]++;
                    }
                }
            }
            state->packed_velocity = ((u32)(u8)velocity[0] << 24) |
                                     ((u32)(u8)velocity[1] << 16) |
                                     ((u32)(u8)velocity[2] << 8);
            fn_801FD80C(id, &color.word);
            fn_801FDF74(id, lifetime);
            state->flags = 0x10000;
            state->timer = 0;
            state->retry = 10;
        } else if (state->retry > 0) {
            state->retry--;
        } else {
            state->finished = 1;
        }
    } else if (fn_801FE05C(id) != 0) {
        state->status = 2;
    }
    return 0;
}

