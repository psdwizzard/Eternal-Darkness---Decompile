typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;

extern int lbl_8064D18C;
extern u8 lbl_8023B5C0[];
extern float lbl_806511B8, lbl_806511CC;
extern int lbl_806511EC, lbl_806511F0, lbl_806511F4, lbl_806511F8;
extern int lbl_80651F20, lbl_80651F24;
extern u8 lbl_8063D378[], lbl_8063D400[];
extern void* fn_80201814(int);
extern void* fn_80201BC8(void*);
extern int fn_80036D5C(void);
extern void fn_80036DA4(void*, u32);
extern int fn_80201B5C(void*);
extern void fn_80201D44(void*, int);
extern void fn_80201D24(void*, int);
extern void fn_802015A4(void*);
extern void fn_801D0E78(void*);
extern int fn_801D38E8(int);
extern void fn_801DE5DC(int, int);
extern void* fn_8011FE34(void*);
extern void fn_802114E0(Vec3*, void*);
extern void fn_8011F114(Vec3*, void*);
extern void fn_80211710(Vec3*, Vec3*, Vec3*);
extern void fn_80211A6C(Vec3*, Vec3*, Vec3*);
extern void fn_80211A48(Vec3*, Vec3*, Vec3*);
extern float fn_80211B44(Vec3*, Vec3*);
extern u32 fn_8006749C(int);
extern void fn_80120AD0(void*, Vec3*, int, u16, float, float);
extern int fn_8012A100(void*, int);
extern void fn_801DE7A0(int);
extern void fn_8012C62C();
extern void fn_8011FA8C();
extern void fn_801F74EC(int, int, int);
extern void fn_801F74C8(int, int, int);
extern void fn_801441C0(int, int, int);
extern void fn_801D62D0();
extern void fn_80120B4C(void*);
extern int fn_801F86F4(int);

#define BURST(handle, a, b, c, d, owner, mask, tail) \
    fn_801D62D0((handle), (a), (b), (handle), (c), (d), (owner), 0, \
        0, 2, 7, 2, 3, 1, 0, 1, 17, 4, 1, 16, 0, 1, 34, (mask), 0, (tail))

/* NonMatching: complete honest-C reconstruction of the event-state dispatcher.
 * Retail's exact 0x100-byte frame, r26-r31 lifetimes, repeated 26-argument call
 * scheduling, and Vec3 aggregate copies remain compiler-codegen divergences. */
void fn_801DF060(void* object)
{
    u8* info = object;
    u8* constants = lbl_8023B5C0;
    void* handle;
    void* target;
    int owner;
    int a, b, c;
    int result;
    Vec3 p, q, r, s, t, u;

    if (*(int*)(info + 8) != lbl_8064D18C || (info[0xff0] & 1)) {
        handle = fn_80201814(*(int*)(info + 0xe0));
        if (handle) {
            fn_80036DA4(handle, fn_80036D5C() | 0x08000000);
            result = fn_80201B5C(handle);
            if (result == 0 || result == 40) {
                fn_80201D44(handle, *(int*)(info + 0x13c));
                fn_80201D24(handle, 1);
                fn_802015A4(handle);
            }
        }
        fn_801D0E78(info);
        return;
    }

    switch (*(u16*)(info + 0xff4)) {
    case 0:
        if (*(int*)(info + 0xf8) == 3 && *(int*)(info + 0xd4))
            fn_801DE5DC(*(int*)(info + 0xe0), fn_801D38E8(*(int*)(info + 4)));
        break;
    case 20:
        if (*(int*)(info + 0xf8) == 6) {
            p = *(Vec3*)(constants + 0x84);
            q = *(Vec3*)(constants + 0x90);
            handle = fn_80201814(*(int*)(info + 0xe0));
            target = fn_80201BC8(handle);
            fn_802114E0(&r, fn_8011FE34(target));
            fn_8011F114(&s, target);
            fn_80211710(&r, &p, &p);
            fn_80211710(&r, &q, &q);
            fn_80211A6C(&q, &p, &q);
            fn_80211A48(&s, &p, &p);
            fn_80120AD0(target, &q, 100,
                (u16)(fn_8006749C(fn_801D38E8(*(int*)(info + 4))) | 0x4000),
                fn_80211B44(&q, &p), lbl_806511CC);
            fn_80201D44(handle, 6); fn_80201D24(handle, 1); fn_802015A4(handle);
            if (fn_8012A100(target, 0x8a)) fn_801DE7A0(*(int*)(info + 0xe0));
        } else if (*(int*)(info + 0xf8) == 4) {
            t = *(Vec3*)(constants + 0x9c);
            u = *(Vec3*)(constants + 0xa8);
            handle = fn_80201814(*(int*)(info + 0xe0));
            target = fn_80201BC8(handle);
            t.z = lbl_806511B8 + *(float*)(info + 0x110);
            fn_80120AD0(target, &u, 100,
                (u16)(fn_8006749C(fn_801D38E8(*(int*)(info + 4))) | 0x4000),
                fn_80211B44(&u, &t), lbl_806511CC);
            fn_80201D44(handle, 5); fn_80201D24(handle, 1); fn_802015A4(handle);
            if (fn_8012A100(target, 0x8a)) fn_801DE7A0(*(int*)(info + 0xe0));
        }
        break;
    case 30:
        if (*(int*)(info + 0xf8) == 6) {
            target = fn_80201BC8(fn_80201814(*(int*)(info + 0xe0)));
            a = lbl_806511EC; b = lbl_80651F20; c = lbl_806511F0;
            fn_8012C62C(target, 15, &c, &b, &a, 4);
            fn_8011FA8C(target, 0, 0x100);
        } else if (*(int*)(info + 0xf8) == 4) {
            target = fn_80201BC8(fn_80201814(*(int*)(info + 0xe0)));
            a = lbl_806511F4; b = lbl_80651F24; c = lbl_806511F8;
            fn_8012C62C(target, 15, &c, &b, &a, 4);
            fn_8011FA8C(target, 0, 0x100);
        }
        break;
    case 50:
        if (*(int*)(info + 0xf8) == 4) {
            if (*(int*)(info + 0xcc)) fn_801F74EC(35, 0, 6);
            else fn_801F74C8(35, 0, 6);
            fn_801441C0(1, 0, 20);
            if ((*(int*)(info + 4) & 15) == 1) {
                handle = fn_80201814(*(int*)(info + 0xe0)); target = fn_80201BC8(handle);
                owner = fn_801D38E8(*(int*)(info + 4));
                BURST(handle, 33, 5, 32, 5, owner, 0x70800, 4);
                BURST(handle, 33, 5, 32, 4, owner, 0x70800, 4);
            }
        }
        break;
    case 67:
        if (*(int*)(info + 0xf8) == 4 && ((*(int*)(info + 4) & 15) == 1)) {
            handle = fn_80201814(*(int*)(info + 0xe0)); target = fn_80201BC8(handle);
            owner = fn_801D38E8(*(int*)(info + 4));
            BURST(handle, 32, 4, 19, 1, owner, 0x70800, 4);
            BURST(handle, 32, 5, 19, 1, owner, 0x70800, 4);
            BURST(handle, 33, 5, 19, 1, owner, 0x70800, 4);
        }
        break;
    case 84:
        if (*(int*)(info + 0xf8) == 4) {
            handle = fn_80201814(*(int*)(info + 0xe0)); target = fn_80201BC8(handle);
            owner = fn_801D38E8(*(int*)(info + 4));
            BURST(handle, 19, 1, 26, 1, owner, 0x50800, 4);
            BURST(handle, 19, 1, 26, 1, owner, 0x60800, 4);
            BURST(handle, 19, 1, 25, 1, owner, 0x50800, 4);
            BURST(handle, 19, 1, 25, 1, owner, 0x60800, 4);
        }
        break;
    case 90:
        if (*(int*)(info + 0xf8) == 6 || *(int*)(info + 0xf8) == 4)
            fn_80120B4C(fn_80201BC8(fn_80201814(*(int*)(info + 0xe0))));
        break;
    case 101:
        if (*(int*)(info + 0xf8) == 4) {
            handle = fn_80201814(*(int*)(info + 0xe0)); target = fn_80201BC8(handle);
            owner = fn_801D38E8(*(int*)(info + 4));
            BURST(handle, 26, 1, 0, 2, owner, 0x52800, 4);
            BURST(handle, 26, 1, 0, 2, owner, 0x62800, 4);
            BURST(handle, 25, 1, 0, 3, owner, 0x52800, 4);
            BURST(handle, 25, 1, 0, 3, owner, 0x62800, 4);
        }
        break;
    case 118:
        if (*(int*)(info + 0xf8) == 4) {
            handle = fn_80201814(*(int*)(info + 0xe0)); target = fn_80201BC8(handle);
            owner = fn_801D38E8(*(int*)(info + 4));
            BURST(handle, 0, 2, 24, 2, owner, 0x70040, 4);
            BURST(handle, 0, 3, 23, 3, owner, 0x70040, 4);
        }
        break;
    case 135:
        if (*(int*)(info + 0xf8) == 4) {
            handle = fn_80201814(*(int*)(info + 0xe0)); target = fn_80201BC8(handle);
            owner = fn_801D38E8(*(int*)(info + 4));
            fn_801D62D0(handle,24,2,handle,23,3,owner,0,0,4,7,2,3,1,0,1,17,10,4,60,0,1,68,0x42800,0,4);
        }
        break;
    case 200:
        if (*(int*)(info + 0xf8) == 6 && fn_801F86F4(0)) {
            *(int*)(lbl_8063D378 + 0x40) = 1; *(int*)(lbl_8063D400 + 0x40) = 1;
        }
        break;
    case 250:
        if (*(int*)(info + 0xf8) == 4 && fn_801F86F4(0)) {
            *(int*)(lbl_8063D378 + 0x40) = 1; *(int*)(lbl_8063D400 + 0x40) = 1;
        }
        break;
    case 310:
        if (*(int*)(info + 0xf8) == 3 && fn_801F86F4(0)) {
            *(int*)(lbl_8063D378 + 0x40) = 1; *(int*)(lbl_8063D400 + 0x40) = 1;
        }
        fn_801D0E78(info);
        break;
    case 500:
        fn_801D0E78(info);
        break;
    }
}
