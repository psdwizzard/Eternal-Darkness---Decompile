typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;

typedef struct Track {
    u32 data;
    u32 frame;
    u8 state;
    u8 pad[3];
} Track;

typedef struct Stream {
    u8 pad0[0xF0];
    Track tracks[6];
    u8 pad138[0x150 - 0x138];
    s32 start_time;
    u8 pad154[0x174 - 0x154];
    volatile s32 frame;
    u32 active;
    u8 pad17C[0x180 - 0x17C];
    s32 counter;
    s32 period;
    u8 pad188[0x1A0 - 0x188];
    void (*trackCb)(u32, s32);
    u8 pad1A4[0x1A8 - 0x1A4];
    void (*frameCb)(u32);
    u8 status;
    u8 mode;
} Stream;

extern int fn_80109790(void* state, u8 mode);
extern s32 fn_802365C0(void);
extern s32 fn_802365D4(void);

extern u32* lbl_8064CC88;
extern s32 lbl_8064CC8C;
extern s32 lbl_8064CC90;
extern void (*lbl_8064CC94)(u32, s32);
extern void (*lbl_8064CC98)(u32*);

void fn_801091B0(Stream* s)
{
    s32 done = 0;
    u32 buf = lbl_8064CC88[lbl_8064CC90];
    s32 i;
    s32 frame;
    s32 target;
    s32 diff;
    s32 next;

    if (s == 0) {
        return;
    }
    if (s->active != 0) {
        fn_80109790(s, s->mode);
        if (lbl_8064CC98 != 0) {
            lbl_8064CC98(&buf);
        }
        if (!(s->status & 1)) {
            return;
        }
        if (s->status & 8) {
            if (s->tracks[0].state != 1) {
                done = 1;
            }
            if (s->tracks[1].state != 1) {
                done = 1;
            }
            if (s->tracks[2].state != 1) {
                done = 1;
            }
            if (s->tracks[3].state != 1) {
                done = 1;
            }
            if (s->tracks[4].state != 1) {
                done = 1;
            }
            if (s->tracks[5].state != 1) {
                done = 1;
            }
            if (done != 0) {
                return;
            }
            s->status = 1;
        }

        frame = s->frame;
        s->counter--;
        if (s->counter <= 0) {
            frame++;
            s->counter = s->period;
        }
        if (fn_802365C0() != 0) {
            target = (fn_802365D4() - s->start_time) >> 1;
        } else {
            target = frame;
        }
        diff = target - frame;
        if (diff > 0) {
            s->frame = frame + diff;
        } else if (diff >= -2) {
            s->frame = frame;
        }

        for (i = 0; i < 6; i++) {
            if (s->tracks[i].state == 1) {
                if ((u32)s->frame == s->tracks[i].frame) {
                    if (s->trackCb != 0) {
                        s->trackCb(s->tracks[i].data, s->frame);
                    }
                    done = 1;
                    s->tracks[i].state = 2;
                }
            }
        }
        if (s->frameCb != 0) {
            s->frameCb(s->frame);
        }
    }
    if (lbl_8064CC94 != 0) {
        lbl_8064CC94(buf, done);
        next = lbl_8064CC90 + 1;
        lbl_8064CC90 = (next >= lbl_8064CC8C) ? 0 : next;
    }
}
