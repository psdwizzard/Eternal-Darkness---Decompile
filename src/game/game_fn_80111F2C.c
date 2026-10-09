typedef unsigned int u32;
typedef unsigned char u8;

typedef struct Vec3 { float x, y, z; } Vec3;

typedef struct PathSegment {
    int start[3];
    int end[3];
} PathSegment;

typedef struct CodecLayout {
    u8 pad0[0xE4];
    PathSegment small[3];
    PathSegment medium[5];
    PathSegment large[7];
} CodecLayout;

extern CodecLayout lbl_8023A3C0;
extern void *lbl_8024E08C[7];
extern int lbl_8064CD40;
extern u32 lbl_8064CD50;

extern unsigned int fn_80113CF8(unsigned int);
extern int fn_80113E48(unsigned int);
extern void *fn_80156938(void *);
extern u32 fn_80193860(void *);
extern void fn_801938D8(void *, u32);
extern int fn_801A98F4(int, int);
extern void fn_801B05B0(int, int);
extern void fn_801B05E8(int, int, int, int, int, int, int, int);
extern int fn_801B0B30(int);
extern int fn_801D10C0(u32);
extern void *fn_801D551C(Vec3 *, Vec3 *, int, int, int, u8, u8, u8, int, int, u8, u8, u8);
extern void fn_801F69F0(int *, Vec3 *, int);

void fn_80111F2C(int enable, unsigned int mode)
{
    PathSegment *seg;
    int i;
    CodecLayout *layout;
    u32 sound;
    int found;
    int speed;
    Vec3 start;
    Vec3 end;

    layout = &lbl_8023A3C0;
    if (enable) {
        sound = fn_80113CF8(mode);
        found = fn_80113E48(sound);
        speed = ((lbl_8064CD50 >> 4) & 0xF) + 1;
        fn_801A98F4(0x4A, 100);
        if (found != -1) {
            lbl_8064CD40 = fn_801D10C0(sound);
            if (lbl_8064CD40 > 0) {
                fn_801B05E8(lbl_8064CD40, 100, 4, 1, 0, 5, 0, 0);
            }
        }
        switch (mode & 0xF) {
        case 0:
            seg = layout->small;
            for (i = 0; i < 3; i++) {
                fn_801F69F0(seg[i].start, &start, 0);
                fn_801F69F0(seg[i].end, &end, 0);
                lbl_8024E08C[i] = fn_80156938(fn_801D551C(&start, &end, speed, 1, 1, 3, 8, 2, 1, 0, 0xD, 0xA, 4));
            }
            break;
        case 1:
            seg = layout->medium;
            for (i = 0; i < 5; i++) {
                fn_801F69F0(seg[i].start, &start, 0);
                fn_801F69F0(seg[i].end, &end, 0);
                lbl_8024E08C[i] = fn_80156938(fn_801D551C(&start, &end, speed, 1, 1, 3, 8, 2, 1, 0, 0xF, 0xA, 4));
            }
            break;
        case 2:
            seg = layout->large;
            for (i = 0; i < 7; i++) {
                fn_801F69F0(seg[i].start, &start, 0);
                fn_801F69F0(seg[i].end, &end, 0);
                lbl_8024E08C[i] = fn_80156938(fn_801D551C(&start, &end, speed, 1, 1, 3, 8, 2, 1, 0, 0x11, 0xA, 4));
            }
            break;
        }
    } else {
        if (lbl_8064CD40 != 0) {
            int voice = fn_801B0B30(lbl_8064CD40);
            if (voice != -1) {
                fn_801B05B0(voice, 5);
            }
        }
        lbl_8064CD40 = 0;
        for (i = 0; i < sizeof(lbl_8024E08C) / sizeof(lbl_8024E08C[0]); i++) {
            if (lbl_8024E08C[i] != 0) {
                u32 flags = fn_80193860(lbl_8024E08C[i]);
                fn_801938D8(lbl_8024E08C[i], flags | 0x40000);
                lbl_8024E08C[i] = 0;
            }
        }
    }
}
