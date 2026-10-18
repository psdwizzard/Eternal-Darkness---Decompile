typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef float Matrix34[3][4];

extern int lbl_8064D18C;
extern int lbl_8064C544;
extern u8 lbl_8023B5C0[];
extern float lbl_806511B8, lbl_806511CC;
extern void* fn_80201814(int);
extern u32 fn_80036D5C(void*);
extern void fn_80036DA4(void*, unsigned int);
extern int fn_80201B5C(void*);
extern void fn_80201D44(void*, int);
extern void fn_80201D24(void*, int);
extern void fn_802015A4(void*);
extern void fn_801D7E70(int, int);
extern void fn_801FE22C(int);
extern void fn_8020123C(int, int, int, int);
extern void fn_801B05B0(int, int);
extern void fn_801E1920(void*);
extern void fn_801FE934(int, int);
extern int fn_801D3A34(int, int);
extern u32 fn_801CEB2C(int);
extern void fn_8014EAA4();
extern int fn_801D0C94(void);
extern int fn_801D0C9C(void);
extern void fn_801D70B0();
extern int fn_800A4F98(int);
extern void* fn_80201BC8(void*);
extern int fn_801D38E8(int);
extern void fn_801D62D0();
extern Matrix34* fn_8011FE34(void*);
extern void PSMTXQuat(Matrix34, void*);
extern void fn_8011F114(Vec3*, void*);
extern void PSMTXMultVec(Matrix34, Vec3*, Vec3*);
extern void PSVECSubtract(Vec3*, Vec3*, Vec3*);
extern void PSVECAdd(Vec3*, Vec3*, Vec3*);
extern float PSVECDotProduct(Vec3*, Vec3*);
extern u32 fn_8006749C(int);
extern void fn_80120AD0(void*, Vec3*, int, u16, float, float);
extern int fn_8012A100(void*, int);
extern void* fn_801294DC(void*, int, int, int);
extern void fn_80128C44(void*, void*, int);
extern void fn_801DE7A0(int);
extern void fn_801DE8AC(void);

extern int lbl_8064C4E0, lbl_8064C4E4;
extern u8 lbl_80255888[], lbl_8063D378[], lbl_8063D400[];
extern u32 lbl_80651200, lbl_80651F28, lbl_806511FC;
extern int fn_801E79FC(int, int);
extern int fn_800460EC(void);
extern int fn_80072E48(void*, void*, int, void*, void*);
extern int fn_80073204(void*, void*, int, void*, void*);
extern void fn_8011F0E8(void*, void*);
extern void fn_8014F3A4(void*, int, int, int, void*);
extern void fn_801AC9F4(int, int, void*, int);
extern void fn_80045A24(int, int);
extern void fn_802020B4(void*, int);
extern int fn_801E741C(void*);
extern int fn_801F8748(int, void*, int, int, int);
extern void fn_801FA4F0(int, int);
extern void fn_801F6ED0(int, void*);
extern void fn_8011FA8C(void*, int, int);
extern u8* fn_80036D38(void*);
extern void fn_801DDB84(void*, int, int, void*);
extern void fn_801DE5DC(int, int);
extern void fn_801DE7FC(void);
extern void fn_80128C28(void*, void*, int);
extern void fn_8012C62C(void*, int, void*, void*, void*, int);
extern void fn_801F74EC(int, int, int);
extern void fn_801F74C8(int, int, int);
extern void fn_801441C0(int, int, int);
extern void fn_80120B4C(void*);
extern int fn_801F86F4(int);

/* Independent C reconstruction of the event dispatcher.
 * Separate vector temporaries preserve the distinct event-local storage. */
void fn_801E0088(void* object)
{
    u8* info = object;
    u8* constants = lbl_8023B5C0;
    void* handle;
    int result;
    int a;
    void* target;
    void* effect;
    float distance;
    u32 flags;
    Matrix34 transform;
    Matrix34* matrix;
    Vec3 raised, position, from, to, from5, to5;
    u32 color2, color1, color0;

    if (*(int*)(info + 8) != lbl_8064D18C || (info[0xff0] & 1)) {
        handle = fn_80201814(*(int*)(info + 0xe0));
        if (handle) {
            result = fn_80036D5C(handle);
            fn_80036DA4(handle, result | 0x08000000);
            result = fn_80201B5C(handle);
            if (result == 0 || result == 40) {
                fn_80201D44(handle, *(int*)(info + 0x13c));
                fn_80201D24(handle, 1);
                fn_802015A4(handle);
            }
            if (!(info[0xff0] & 0x10) && !(info[0xff0] & 1) &&
                *(void (**)(void*, int))(info + 0x28))
                (*(void (**)(void*, int))(info + 0x28))(info, *(int*)(info + 0x2c));
        }
        if (*(u16*)(info + 0xff4) && (info[0xff0] & 0x10))
            fn_801D7E70(*(int*)(info + 0xc), 1);
        fn_801FE22C(*(int*)(info + 0x44));
        if (info[0xff0] & 0x10) {
            if (fn_80201814(lbl_8064C544))
                fn_8020123C(8, lbl_8064C544, lbl_8064C544, 0);
            lbl_8064C544 = *(int*)(info + 0xe0);
            fn_8020123C(195, *(int*)(info + 0xc), *(int*)(info + 0xc), 0);
        }
        if (*(int*)(info + 0x10) != -1)
            fn_801B05B0(*(int*)(info + 0x10), 10);
        fn_801E1920(info);
        return;
    }

    switch (*(u16*)(info + 0xff4)) {
    case 0:
        if (info[0xff0] & 0x10) {
            a = *(int*)(info + 4) & -0x821;
            fn_801D70B0(-1, a | 0x410,
                        *(int*)(info + 0xc), info + 0x38, 2, 0,
                        fn_801D0C9C, 0, fn_801D0C94, 0);
            a = fn_800A4F98(2);
            if (fn_80201814(a))
                fn_8020123C(8, a, a, 0);
        }
        break;
    case 20:
        fn_801FE934(*(int*)(info + 0x44), 5);
        break;
    case 40:
        fn_8014EAA4(info + 0x38, 250, (u8)fn_801CEB2C(*(int*)(info + 4)),
                    fn_801D3A34(*(int*)(info + 4), 0x35),
                    fn_801D3A34(*(int*)(info + 4), 0x46),
                    fn_801D3A34(*(int*)(info + 4), 0x4a),
                    fn_801D3A34(*(int*)(info + 4), 0x4e), 4);
        break;
    case 128: {
        if ((info[0xff0] & 0x10) && ((*(int*)(info + 4) & 15) == 8))
            break;
        switch (*(int*)(info + 0x13c)) {
        case 6: a = 125; break;
        case 5: a = 500; break;
        default: a = 350; break;
        }
        if (lbl_8064D18C == 97 && !(info[0xff0] & 0x10) &&
            (fn_801E79FC(lbl_8064C4E0, 163) ||
             (fn_800460EC() && !fn_801E79FC(lbl_8064C4E0, 558)))) {
            void* owner;
            void* target;
            owner = fn_80201BC8(fn_80201814(*(int*)(info + 0xc)));
            target = fn_80201BC8(fn_80201814(*(int*)(info + 0xe0)));
            *(int*)(info + 0xbc) = 0;
            *(int*)(info + 0xcc) = 0;
            if (fn_80072E48(info + 0x38, info + 0x108, 200, owner, target))
                fn_8011F0E8(target, info + 0x108);
        }
        if (*(int*)(info + 0xbc)) {
            void* owner;
            void* target;
            owner = fn_80201BC8(fn_80201814(*(int*)(info + 0xc)));
            target = fn_80201BC8(fn_80201814(*(int*)(info + 0xe0)));
            if (!fn_80073204(info + 0x38, info + 0x108, 200, owner, target)) {
                if (fn_80072E48(info + 0x38, info + 0x108, 200, owner, target))
                    fn_8011F0E8(target, info + 0x108);
            }
        }
        raised = *(Vec3*)(info + 0x108);
        raised.z += (float)a;
        fn_8014F3A4(&raised, (u8)fn_801CEB2C(*(int*)(info + 4)),
                    fn_801D3A34(*(int*)(info + 4), 0x35),
                    fn_801D3A34(*(int*)(info + 4), 0x4e), info + 0x140);
        fn_801AC9F4(360, 100, info + 0x108, 2);
        if (*(int*)(info + 0xbc) && *(int*)(info + 0xcc)) {
            handle = fn_80201814(*(int*)(info + 0xe0));
            target = fn_80201BC8(handle);
            if (!fn_800460EC())
                fn_80045A24(1, 1);
            fn_802020B4(handle, 0);
            if (!fn_801F8748(fn_801E741C(lbl_80255888), target, 0, 0, 0)) {
                fn_80045A24(0, 0);
                *(int*)(info + 0xcc) = 0;
                fn_802020B4(handle, 1);
            }
        }
        if (info[0xff0] & 0x10) {
            void* target;
            handle = fn_80201814(*(int*)(info + 0xe0));
            target = fn_80201BC8(handle);
            fn_801FA4F0(1, 1);
            if (*(int*)(info + 0xcc))
                fn_801F8748(fn_801E741C(lbl_80255888), target, 0, 0, 0);
            else
                fn_801F6ED0(lbl_8064C4E4, target);
            fn_802020B4(handle, 0);
        }
        break;
    }
    case 150: {
        int a, b;
        void* target;
        void* handle;
        u8* state;
        register int c;
        if ((info[0xff0] & 0x10) && ((*(int*)(info + 4) & 15) == 8))
            break;
        a = *(int*)(info + 0xe0);
        c = 0;
        handle = fn_80201814(a);
        target = fn_80201BC8(handle);
        b = fn_801D38E8(*(int*)(info + 4));
        if (*(int*)(info + 0xc0))
            c = *(int*)(info + 0x138);
        else if (*(int*)(info + 0x13c) != 6 && *(int*)(info + 0x13c) != 5) {
            *(int*)(info + 0x138) = 40;
            c = 40;
        }
        if (c) {
            fn_80201D44(handle, c);
            fn_80201D24(handle, 1);
            fn_802015A4(handle);
        }
        if (*(int*)(info + 0x138) == 40) {
            fn_8020123C(16, a, a, 0);
            fn_8011FA8C(target, 0, 0x100);
            if (*(int*)(info + 0x13c)) {
                state = fn_80036D38(handle);
                if ((info[0xff0] & 0x10) ||
                    (*(int*)(info + 0x13c) == 4 && fn_8012A100(target, 0x8a)))
                    *(int*)(state + 0x84) = 0;
                else
                    *(int*)(state + 0x84) = *(int*)(info + 0x13c);
            }
        }
        switch (*(int*)(info + 0x13c)) {
        case 6:
            fn_801DDB84(info + 0x108, b, 2, target);
            break;
        case 4:
            fn_801DDB84(info + 0x108, b, 1, target);
            fn_801DE5DC(a, b);
            break;
        case 5:
            fn_801DDB84(info + 0x108, b, 3, target);
            break;
        }
        if (*(int*)(info + 0x13c) == 4 && fn_8012A100(target, 0x8a)) {
            if (info[0xff0] & 0x10) {
                effect = fn_801294DC(target, 0x8a, 0x20, 9);
                if (effect)
                    fn_80128C44(effect, fn_801DE8AC, 0);
            } else if (*(int*)(info + 0x138) == 40) {
                effect = fn_801294DC(target, 0x8a, 0x20, 9);
                if (effect) {
                    fn_80128C44(effect, fn_801DE8AC, 0);
                    fn_80128C28(effect, fn_801DE7FC, a);
                }
            } else {
                fn_801DE7A0(a);
            }
        }
        break;
    }
    case 170:
        if (!(info[0xff0] & 0x10)) {
            handle = fn_80201814(*(int*)(info + 0xe0));
            if (*(int*)(info + 0x13c) == 6) {
                fn_80201D44(handle, 6);
                fn_80201D24(handle, 1);
                fn_802015A4(handle);
            } else if (*(int*)(info + 0x13c) == 5) {
                fn_80201D44(handle, 5);
                fn_80201D24(handle, 1);
                fn_802015A4(handle);
            }
        }
        if (!(info[0xff0] & 0x10) || ((*(int*)(info + 4) & 15) != 8)) {
            if (*(int*)(info + 0x13c) == 6) {
                from = *(Vec3*)(constants + 0xb4);
                to = *(Vec3*)(constants + 0xc0);
                target = fn_80201BC8(fn_80201814(*(int*)(info + 0xe0)));
                matrix = fn_8011FE34(target);
                PSMTXQuat(transform, matrix);
                fn_8011F114(&position, target);
                PSMTXMultVec(transform, &from, &from);
                PSMTXMultVec(transform, &to, &to);
                PSVECSubtract(&to, &from, &to);
                PSVECAdd(&position, &from, &from);
                distance = PSVECDotProduct(&to, &from);
                flags = fn_8006749C(fn_801D38E8(*(int*)(info + 4))) | 0x4000;
                fn_80120AD0(target, &to, 100, flags, distance, lbl_806511CC);
                if (fn_8012A100(target, 0x8a)) {
                    if (info[0xff0] & 0x10) {
                        effect = fn_801294DC(target, 0x8a, 0x20, 9);
                        if (effect)
                            fn_80128C44(effect, fn_801DE8AC, 0);
                    } else {
                        fn_801DE7A0(*(int*)(info + 0xe0));
                    }
                }
            } else if (*(int*)(info + 0x13c) == 5) {
                from5 = *(Vec3*)(constants + 0xcc);
                to5 = *(Vec3*)(constants + 0xd8);
                target = fn_80201BC8(fn_80201814(*(int*)(info + 0xe0)));
                from5.z = lbl_806511B8 + *(float*)(info + 0x110);
                distance = PSVECDotProduct(&to5, &from5);
                flags = fn_8006749C(fn_801D38E8(*(int*)(info + 4))) | 0x4000;
                fn_80120AD0(target, &to5, 100, flags, distance, lbl_806511CC);
                if (fn_8012A100(target, 0x8a)) {
                    if (info[0xff0] & 0x10) {
                        effect = fn_801294DC(target, 0x8a, 0x20, 9);
                        if (effect)
                            fn_80128C44(effect, fn_801DE8AC, 0);
                    } else {
                        fn_801DE7A0(*(int*)(info + 0xe0));
                    }
                }
            }
        }
        break;
    case 180:
        if (*(int*)(info + 0x13c) == 6 || *(int*)(info + 0x13c) == 5) {
            handle = fn_80201814(*(int*)(info + 0xe0));
            result = fn_80036D5C(handle);
            fn_80036DA4(handle, result & ~0x08000000);
            target = fn_80201BC8(handle);
            color0 = lbl_80651200;
            color1 = lbl_80651F28;
            color2 = lbl_806511FC;
            fn_8012C62C(target, 15, &color2, &color1, &color0, 4);
            fn_8011FA8C(target, 0, 0x100);
        }
        break;
    case 200: {
        int a, b;
        if ((info[0xff0] & 0x10) && ((*(int*)(info + 4) & 15) == 8))
            break;
        if (*(int*)(info + 0x13c) != 5)
            break;
        if (*(int*)(info + 0xcc))
            fn_801F74EC(35, 0, 6);
        else
            fn_801F74C8(35, 0, 6);
        fn_801441C0(1, 0, 20);
        if ((*(int*)(info + 4) & 15) != 1)
            break;
        a = *(int*)(info + 0xe0);
        fn_80201BC8(fn_80201814(a));
        b = fn_801D38E8(*(int*)(info + 4));
        fn_801D62D0(a, 33, 5, a, 32, 5, b, 0,
                    0, 2, 7, 2, 3, 1, 0, 1, 17, 4, 1, 16,
                    0, 1, 34, 0x70800, 0, 4);
        fn_801D62D0(a, 33, 5, a, 32, 4, b, 0,
                    0, 2, 7, 2, 3, 1, 0, 1, 17, 4, 1, 16,
                    0, 1, 34, 0x70800, 0, 4);
        break;
    }
    case 217: {
        int a, b;
        if ((info[0xff0] & 0x10) && ((*(int*)(info + 4) & 15) == 8))
            break;
        if (*(int*)(info + 0x13c) != 5)
            break;
        if ((*(int*)(info + 4) & 15) != 1)
            break;
        a = *(int*)(info + 0xe0);
        fn_80201BC8(fn_80201814(a));
        b = fn_801D38E8(*(int*)(info + 4));
        fn_801D62D0(a, 32, 4, a, 19, 1, b, 0,
                    0, 2, 7, 2, 3, 1, 0, 1, 17, 4, 1, 16,
                    0, 1, 34, 0x70800, 0, 4);
        fn_801D62D0(a, 32, 5, a, 19, 1, b, 0,
                    0, 2, 7, 2, 3, 1, 0, 1, 17, 4, 1, 16,
                    0, 1, 34, 0x70800, 0, 4);
        fn_801D62D0(a, 33, 5, a, 19, 1, b, 0,
                    0, 2, 7, 2, 3, 1, 0, 1, 17, 4, 1, 16,
                    0, 1, 17, 0x70800, 0, 4);
        break;
    }
    case 234: {
        int a, b;
        if ((info[0xff0] & 0x10) && ((*(int*)(info + 4) & 15) == 8))
            break;
        if (*(int*)(info + 0x13c) != 5)
            break;
        a = *(int*)(info + 0xe0);
        fn_80201BC8(fn_80201814(a));
        b = fn_801D38E8(*(int*)(info + 4));
        fn_801D62D0(a, 19, 1, a, 26, 1, b, 0,
                    0, 2, 7, 2, 3, 1, 0, 1, 17, 4, 1, 32,
                    0, 1, 34, 0x50800, 0, 4);
        fn_801D62D0(a, 19, 1, a, 26, 1, b, 0,
                    0, 2, 7, 2, 3, 1, 0, 1, 17, 4, 1, 32,
                    0, 1, 34, 0x60800, 0, 4);
        fn_801D62D0(a, 19, 1, a, 25, 1, b, 0,
                    0, 2, 7, 2, 3, 1, 0, 1, 17, 4, 1, 32,
                    0, 1, 34, 0x50800, 0, 4);
        fn_801D62D0(a, 19, 1, a, 25, 1, b, 0,
                    0, 2, 7, 2, 3, 1, 0, 1, 17, 4, 1, 32,
                    0, 1, 34, 0x60800, 0, 4);
        break;
    }
    case 240:
        if (!(info[0xff0] & 0x10) || ((*(int*)(info + 4) & 15) != 8)) {
            if (*(int*)(info + 0x13c) == 6 || *(int*)(info + 0x13c) == 5)
                fn_80120B4C(fn_80201BC8(fn_80201814(*(int*)(info + 0xe0))));
        }
        if (*(int*)(info + 0x13c) != 6 && *(int*)(info + 0x13c) != 4 &&
            *(int*)(info + 0x13c) != 5) {
            if (*(int*)(info + 0xcc) && fn_801F86F4(0)) {
                *(int*)(lbl_8063D378 + 0x40) = 1;
                *(int*)(lbl_8063D400 + 0x40) = 1;
            }
            if (*(void (**)(void*, int))(info + 0x28))
                (*(void (**)(void*, int))(info + 0x28))(info, *(int*)(info + 0x2c));
            handle = fn_80201814(*(int*)(info + 0xe0));
            result = fn_80036D5C(handle);
            fn_80036DA4(handle, result & ~0x08000000);
            fn_801E1920(info);
        }
        break;
    case 251: {
        int a, b;
        if (*(int*)(info + 0x13c) != 5)
            break;
        a = *(int*)(info + 0xe0);
        fn_80201BC8(fn_80201814(a));
        b = fn_801D38E8(*(int*)(info + 4));
        fn_801D62D0(a, 26, 1, a, 0, 2, b, 0,
                    0, 2, 7, 2, 3, 1, 0, 1, 17, 4, 1, 16,
                    0, 1, 34, 0x52800, 0, 4);
        fn_801D62D0(a, 26, 1, a, 0, 2, b, 0,
                    0, 2, 7, 2, 3, 1, 0, 1, 17, 4, 1, 16,
                    0, 1, 34, 0x62800, 0, 4);
        fn_801D62D0(a, 25, 1, a, 0, 3, b, 0,
                    0, 2, 7, 2, 3, 1, 0, 1, 17, 4, 1, 16,
                    0, 1, 34, 0x52800, 0, 4);
        fn_801D62D0(a, 25, 1, a, 0, 3, b, 0,
                    0, 2, 7, 2, 3, 1, 0, 1, 17, 4, 1, 16,
                    0, 1, 34, 0x62800, 0, 4);
        break;
    }
    case 268: {
        int a, b;
        if (*(int*)(info + 0x13c) != 5)
            break;
        a = *(int*)(info + 0xe0);
        fn_80201BC8(fn_80201814(a));
        b = fn_801D38E8(*(int*)(info + 4));
        fn_801D62D0(a, 0, 2, a, 24, 2, b, 0,
                    0, 2, 7, 2, 3, 1, 0, 1, 17, 4, 1, 16,
                    0, 1, 34, 0x70040, 0, 4);
        fn_801D62D0(a, 0, 3, a, 23, 3, b, 0,
                    0, 2, 7, 2, 3, 1, 0, 1, 17, 4, 1, 16,
                    0, 1, 34, 0x70040, 0, 4);
        break;
    }
    case 285:
        if (*(int*)(info + 0x13c) == 5) {
            a = *(int*)(info + 0xe0);
            fn_80201BC8(fn_80201814(a));
            result = fn_801D38E8(*(int*)(info + 4));
            fn_801D62D0(a, 24, 2, a, 23, 3, result, 0,
                        0, 4, 7, 2, 3, 1, 0, 1, 17, 10, 4, 60,
                        0, 1, 68, 0x42800, 0, 4);
        }
        break;
    case 350:
        if (*(int*)(info + 0x13c) == 6) {
            if (*(void (**)(void*, int))(info + 0x28))
                (*(void (**)(void*, int))(info + 0x28))(info, *(int*)(info + 0x2c));
            fn_801E1920(info);
        }
        break;
    case 400:
        if (*(int*)(info + 0x13c) == 5) {
            if (*(void (**)(void*, int))(info + 0x28))
                (*(void (**)(void*, int))(info + 0x28))(info, *(int*)(info + 0x2c));
            fn_801E1920(info);
        }
        break;
    case 460:
        if (*(int*)(info + 0x13c) == 4) {
            if (*(void (**)(void*, int))(info + 0x28))
                (*(void (**)(void*, int))(info + 0x28))(info, *(int*)(info + 0x2c));
            handle = fn_80201814(*(int*)(info + 0xe0));
            result = fn_80036D5C(handle);
            fn_80036DA4(handle, result & ~0x08000000);
            fn_801E1920(info);
        }
        break;
    }
}
