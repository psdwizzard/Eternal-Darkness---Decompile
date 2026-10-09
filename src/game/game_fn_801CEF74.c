typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef float f32;

typedef struct Vec3 { f32 x, y, z; } Vec3;

typedef struct Object {
    u8 bytes[0x1000];
} Object;

typedef struct RingWork {
    u8 pad0[0x14];
    void* effects[1];
} RingWork;

typedef struct SpawnRequest {
    Vec3 position;
    f32 scale;
    u32 kind;
    u32 subtype;
    u32 param18;
    u32 param1C;
    u32 param20;
    u32 param24;
    u32 count;
    u32 owner;
    u32 enabled;
    u16 flags;
    u8 active;
    u8 pad37;
} SpawnRequest;

extern const f32 lbl_80651038;
extern const f32 lbl_80651058;
extern const f32 lbl_80651064;
extern int lbl_8064D18C;
extern int lbl_8064D548;
extern int lbl_8064D54C;
extern int lbl_8064D550;
extern int lbl_8064D6EC;
extern int lbl_8064D538;
extern int lbl_8064C4E0;
extern int lbl_8064C504;
extern const Vec3 lbl_8023B564;
extern void* fn_80201B54(void*);
extern void fn_8020123C(u32, void*, void*, u32);
extern void fn_801FDF3C(void*, u32);
extern void fn_801FDF00(void*, u32);
extern void fn_801FDFEC(void*, u32);
extern void fn_801FE024(void*, u32);
extern void fn_802006D4(void*, void*, int, u32, u32);
extern void fn_8019B134(void*, u32);
extern void fn_801D313C(u32, u32, void*);
extern void* fn_80201814(void*);
extern void* fn_80201C24(void*);
extern u32 fn_80157894(void*);
extern void fn_80027B78(u32, void*);
extern void fn_801D1318(u32);
extern void fn_801B05B0(int, u32);
extern void fn_801A9E40(int);
extern void fn_801D0E78(void*);
extern void fn_800A0B68(u32);
extern f32 fn_80048C2C(f32);
extern f32 fn_80048C50(f32);
extern void fn_801CEBC4(void*, void*, int, int, s16, void*);

extern int fn_80128258(void);
extern int fn_80128130(void);
extern void* fn_800453AC(int, int, int, int, int, int, int, int,
                           f32*, int, int, f32);
extern void fn_8020104C(int, void*, void*, int, f32);
extern void* fn_80201BC8(void*);
extern u32 fn_801D3944(u32);
extern const u32 lbl_80651EB8;
extern const u32 lbl_80651EBC;
extern const u32 lbl_80651EC0;
extern const u32 lbl_80651EC4;
extern void* fn_8012C62C(void*, int, void*, void*, void*, int);
extern void fn_8011FA8C(void*, int, u32);
extern void fn_8011FABC(void*, int, u32);
extern const u32 lbl_80651060;
extern void* fn_800CE9A4(void*, int, int);
extern void fn_801E8328(int, void*);
extern u32 fn_801D39F4(u32);
extern void fn_801E2B28(void*, void*, void*, int, int);
extern void fn_801B0CA4(int, int);
extern void fn_801CE720(u32, int, void*, u16, int, u8, void*, f32);

extern void fn_801A5C30(int);
extern void fn_8011E174(int, int);
extern int fn_801E79FC(int, int);
extern int fn_802019EC(int, int);
extern int fn_801E2E1C(u32, int, int);
extern int fn_80201B44(void);
extern void fn_80043F44(SpawnRequest*);
extern void* fn_80034708(SpawnRequest*);
extern void fn_802020B4(void*, int);
extern void fn_801261F4(void*);
extern void fn_80201D54(void*, int);
extern void fn_80201D24(void*, int);
extern void fn_802015A4(void*);
extern int fn_80072A2C(void*, void*, int, int);
extern int fn_8015ABD4(int, int);
extern int fn_80054BCC(int);
extern int fn_80073204(void*, void*, int, void*, void*);
extern int fn_80072E48(void*, void*, int, void*, void*);
extern void fn_8011F0E8(void*, void*);
extern u32 fn_80036D5C(void*);
extern void fn_80036DA4(void*, u32);
extern f32 fn_8012B7D0(void*, Vec3*);
extern f32 fn_8012B750(void*);
extern void fn_8012B7A0(void*, f32);
extern void fn_80048708(void*);
extern void fn_801D53F0(int);
extern void* fn_801E6CA0(int, int, int, int, int);
extern void fn_80027730(void*, int, int);
extern void fn_80045A24(int, int);

void fn_801CEF74(Object* object)
{
    Object* owner = *(Object**)(object->bytes + 0x284);
    u8* work = object->bytes + 0xBC;
    int local_gate = 0;
    int* gate = &local_gate;
    u8 flags = object->bytes[0xFF0];
    u32 color;
    u32 effect_desc;
    u32 path_desc;

    if (flags & 0x10) {
        gate = &lbl_8064D550;
    }

    if (*gate != 0 || *(int*)(object->bytes + 8) != lbl_8064D18C ||
        (owner->bytes[0xFF0] & 1) || (flags & 1)) {
        if (*(u16*)(object->bytes + 0xFF4) != 0 &&
            *(u16*)(object->bytes + 0xFF4) > 10) {
            void* effect = *(void**)(owner->bytes + 0x30);
            if (effect != 0) {
                void* data = fn_80201B54(effect);
                fn_8020123C(0x39, data, data, 0);
            }
            if (*(u16*)(object->bytes + 0xFF4) > 20) {
                fn_801FDF3C(*(void**)(owner->bytes + 0x44), 0);
                fn_801FDF00(*(void**)(owner->bytes + 0x44), 0);
                fn_801FDFEC(*(void**)(owner->bytes + 0x44), 0);
                fn_801FE024(*(void**)(owner->bytes + 0x44), 60);

                if (*(u16*)(object->bytes + 0xFF4) >= 30) {
                    int i;

                    for (i = 0; i < *(s16*)(work + 8); i++) {
                        int item = *(int*)(work + 0x14 + i * 4);
                        if (item != 0) {
                            fn_802006D4((void*)item, (void*)item, -1, 0x39, 0);
                            fn_8020123C(0x39, (void*)item, (void*)item, 0);
                        }
                    }

                    if (*(u16*)(object->bytes + 0xFF4) > 30) {
                        for (i = 0; i < *(s16*)(work + 8); i++) {
                            void* item = *(void**)(work + 0x1AC + i * 4);
                            if (item != 0) {
                                fn_8019B134(item, 0);
                            }
                        }

                        if (*(int*)(object->bytes + 8) == lbl_8064D18C &&
                            (object->bytes[0xFF0] & 8)) {
                            fn_801D313C(*(u32*)(owner->bytes + 4),
                                        *(u32*)(object->bytes + 0xC),
                                        owner->bytes + 0x38);
                        }
                    }
                }
            }
        }

        if ((*(int*)(owner->bytes + 4) & 0x1FF0) == 0x300) {
            void* resource = *(void**)(owner->bytes + 0xBC);
            void* data = fn_80201C24(fn_80201814(resource));
            if (fn_80157894(data) & 1) {
                fn_80027B78(*(u32*)(object->bytes + 0xC), resource);
            }
            lbl_8064D548 = 0;
        }

        if ((*(u16*)(object->bytes + 0xFF4) <= 30 ||
             !(object->bytes[0xFF0] & 8)) &&
            (object->bytes[0xFF0] & 0x10)) {
            fn_801D1318(0);
        }

        *gate = 0;
        fn_8020123C(0xB0, *(void**)(object->bytes + 0xC),
                    *(void**)(object->bytes + 0xC), 0);

        if (*(int*)(owner->bytes + 0x10) != -1) {
            fn_801B05B0(*(int*)(owner->bytes + 0x10), 10);
        }

        fn_801A9E40(-1);
        fn_801D0E78(owner);
        fn_801D0E78(object);
        fn_800A0B68(0);
        return;
    }

    if (*(u16*)(object->bytes + 0xFF4) >= 30) {
        if (work[1] < *(s16*)(work + 8)) {
            if (work[3] == 0) {
                f32 angle = lbl_80651038 * (f32)work[1] /
                            (f32)*(s16*)(work + 8);
                f32 point[3];
                u32 scratch;
                f32 trig;

                trig = fn_80048C2C(angle);
                point[0] = (f32)work[4] * trig + *(f32*)(work + 0x30);
                trig = fn_80048C50(angle);
                point[1] = (f32)work[4] * trig + *(f32*)(work + 0x34);
                point[2] = *(f32*)(work + 0x38);
                scratch = *(u32*)(work + 0x1CC);
                fn_801CEBC4(work + 0xF8, point, 4, 4,
                            *(s16*)(work + 6), &scratch);
                work[1]++;
                work[3] = work[2];

                if (fn_80128258() || fn_80128130()) {
                    void* effect = fn_800453AC(0x5B, 0x68,
                        *(int*)(object->bytes + 8), -1, -1, -1, -1, 0x3E,
                        point, 1, 0, lbl_80651064);
                    void* data;
                    ((void**)(work + 0x10))[work[1]] = effect;
                    fn_8020104C(0x39, effect, effect, 0,
                        (f32)(*(u16*)(work + 0xA) +
                            ((*(s16*)(work + 8) - work[1]) * 45 - work[1])));
                    fn_8020104C(0x9C, effect, effect, 6, lbl_80651058);
                    data = fn_80201814(effect);
                    if (data != 0) {
                        data = fn_80201BC8(data);
                        if (data != 0) {
                            u32 start, middle, end;
                            *(u32*)&color = fn_801D3944(*(u32*)(owner->bytes + 4));
                            end = color;
                            start = color;
                            middle = lbl_80651EB8;
                            fn_8012C62C(data, 0xF, &start, &middle, &end, 0x12);
                            fn_8011FA8C(data, 0, 0x01000000);
                            fn_8011FABC(data, 0, 0x20);
                        }
                    }
                } else {
                    ((void**)(work + 0x10))[work[1]] = 0;
                }
            } else {
                work[3]--;
            }
        } else {
            int kind;
            int ok = 1;
            kind = *(int*)(owner->bytes + 4) & 0x1FF0;

            if (flags & 0x10) {
                switch (kind) {
                case 0x300:
                    lbl_8064D6EC = 1;
                    fn_801A5C30(0);
                    fn_8011E174(0x800, 1);
                    lbl_8064D54C = 1;
                    break;
                case 0x410:
                    fn_8011E174(0x800, 1);
                    lbl_8064D54C = 1;
                    break;
                case 0x440:
                case 0x480:
                    fn_8011E174(0x800, 1);
                    lbl_8064D54C = 1;
                    lbl_8064D548 = 1;
                    break;
                case 0x810:
                    if (lbl_8064D18C == 0x29 &&
                        !fn_801E79FC(lbl_8064C4E0, 0x10)) {
                        int a = fn_802019EC(0x87A, lbl_8064D18C);
                        int b = fn_802019EC(0x87B, lbl_8064D18C);
                        if ((a == *(int*)(owner->bytes + 0xBC) ||
                             b == *(int*)(owner->bytes + 0xBC)) &&
                            fn_801E2E1C(*(u32*)(owner->bytes + 4),
                                        *(int*)(owner->bytes + 0xBC),
                                        *(int*)(owner->bytes + 0xC))) {
                            lbl_8064D6EC = 1;
                            fn_801A5C30(0);
                        }
                    }
                    break;
                }
            }

            if (kind == 0x820 &&
                (*(int*)(object->bytes + 0xC) != fn_80201B44() ||
                 (*(int*)(owner->bytes + 4) & 0xF) != 8) &&
                *(int*)(owner->bytes + 0xD0) == 0) {
                SpawnRequest req;
                void* spawned;

                fn_80043F44(&req);
                req.position = *(int*)(owner->bytes + 0xC4) != 0
                    ? *(Vec3*)(owner->bytes + 0x108) : lbl_8023B564;

                if (*(int*)(owner->bytes + 0xC0) != 0) {
                    if (*(int*)(owner->bytes + 0x13C) == 6 ||
                        *(int*)(owner->bytes + 0x13C) == 5) {
                        *(int*)(owner->bytes + 0x138) = 0;
                    }
                    req.count = *(u32*)(owner->bytes + 0x138);
                    req.scale = *(f32*)(owner->bytes + 0x104);
                    req.kind = *(u32*)(owner->bytes + 0xE4);
                    req.subtype = *(u32*)(owner->bytes + 0xE8);
                    req.param1C = *(u32*)(owner->bytes + 0xEC);
                    req.param20 = *(u32*)(owner->bytes + 0xF0);
                    req.param24 = *(u32*)(owner->bytes + 0xF4);
                } else {
                    int type;
                    req.count = 0;
                    type = *(int*)(owner->bytes + 4);
                    switch (type & 0x70000) {
                    case 0x10000:
                        switch (type & 0xF) {
                        case 1:
                            req.kind = 0x32;
                            req.subtype = 0x1C;
                            break;
                        case 2:
                            req.kind = 0x33;
                            req.subtype = 0x4F;
                            break;
                        case 4:
                            req.kind = 0x34;
                            req.subtype = 0x50;
                            break;
                        case 3:
                            break;
                        }
                        *(int*)(owner->bytes + 0x13C) = 6;
                        break;
                    case 0x20000:
                        switch (type & 0xF) {
                        case 1:
                            req.kind = 0xD;
                            req.subtype = 1;
                            break;
                        case 2:
                            req.kind = 0x16;
                            req.subtype = 6;
                            break;
                        case 4:
                            req.kind = 0x14;
                            req.subtype = 7;
                            break;
                        case 3:
                            break;
                        }
                        *(int*)(owner->bytes + 0x13C) = 4;
                        break;
                    case 0x40000:
                        switch (type & 0xF) {
                        case 1:
                            req.kind = 0xE;
                            req.subtype = 2;
                            break;
                        case 2:
                            req.kind = 0x25;
                            req.subtype = 0x10;
                            break;
                        case 4:
                            req.kind = 0x26;
                            req.subtype = 0xF;
                            break;
                        case 3:
                            break;
                        }
                        *(int*)(owner->bytes + 0x13C) = 5;
                        break;
                    }
                }

                spawned = fn_80034708(&req);
                if (spawned != 0) {
                    void* source = fn_80201B54(spawned);
                    void* model;

                    if ((owner->bytes[0xFF0] & 0x10) &&
                        (*(int*)(owner->bytes + 4) & 0xF) != 8) {
                        fn_802020B4(spawned, 0);
                    }
                    *(void**)(owner->bytes + 0xE0) = source;
                    model = fn_80201BC8(spawned);
                    if (model != 0) {
                        void* self = fn_80201BC8(
                            fn_80201814(*(void**)(owner->bytes + 0xC)));
                        fn_801261F4(model);
                        fn_80201D54(spawned, *(int*)(object->bytes + 8));
                        fn_80201D24(spawned, 1);
                        fn_802015A4(spawned);

                        if (*(int*)(owner->bytes + 0xC4) == 0) {
                            if (*(int*)(owner->bytes + 0xBC) != 0) {
                                ok = fn_80072A2C(owner->bytes + 0x38,
                                                 owner->bytes + 0x108, 800, 1);
                                if (ok) {
                                    fn_8011F0E8(model, owner->bytes + 0x108);
                                }
                            } else {
                                int range;
                                int near;
                                int id = *(int*)(object->bytes + 8);
                                near = 0;
                                if (id == 2 || id == 8) {
                                    near = 1;
                                }
                                if (near) {
                                    range = 120;
                                } else {
                                    range = *(s16*)(owner->bytes + 0xDC);
                                }

                                if (*(int*)(owner->bytes + 0xC8) != 0) {
                                    if (!fn_8015ABD4(2, 2) &&
                                        fn_80054BCC(*(int*)(object->bytes + 8))) {
                                        *(int*)(owner->bytes + 0xCC) = 1;
                                        ok = fn_80073204(owner->bytes + 0x38,
                                                         owner->bytes + 0x108,
                                                         range, self, model);
                                        if (!ok &&
                                            *(int*)(object->bytes + 8) != 2 &&
                                            *(int*)(object->bytes + 8) != 8) {
                                            ok = fn_80073204(owner->bytes + 0x38,
                                                             owner->bytes + 0x108,
                                                             150, self, model);
                                        }
                                    } else {
                                        ok = 0;
                                    }
                                    if (!ok) {
                                        *(int*)(owner->bytes + 0xCC) = 0;
                                        ok = fn_80072E48(owner->bytes + 0x38,
                                                         owner->bytes + 0x108,
                                                         range, self, model);
                                        if (!ok &&
                                            *(int*)(object->bytes + 8) != 2 &&
                                            *(int*)(object->bytes + 8) != 8) {
                                            ok = fn_80072E48(owner->bytes + 0x38,
                                                             owner->bytes + 0x108,
                                                             150, self, model);
                                        }
                                        if (ok) {
                                            fn_8011F0E8(model, owner->bytes + 0x108);
                                        }
                                    }
                                } else {
                                    ok = fn_80072A2C(owner->bytes + 0x38,
                                                     owner->bytes + 0x108,
                                                     range, 1);
                                    if (!ok &&
                                        *(int*)(object->bytes + 8) != 2 &&
                                        *(int*)(object->bytes + 8) != 8) {
                                        ok = fn_80072A2C(owner->bytes + 0x38,
                                                         owner->bytes + 0x108,
                                                         150, 1);
                                    }
                                    if (ok) {
                                        fn_8011F0E8(model, owner->bytes + 0x108);
                                    }
                                }
                            }
                        }

                        if (ok) {
                            u32 c0, c1, c2;
                            u32 state = fn_80036D5C(spawned);
                            fn_80036DA4(spawned, state | 0x08000000);
                            c2 = lbl_80651EC4;
                            c1 = lbl_80651EC0;
                            c0 = lbl_80651EBC;
                            fn_8012C62C(model, 0xF, &c0, &c1, &c2, 4);
                            fn_8011FA8C(model, 0x100, 0);
                            if (*(int*)(owner->bytes + 0xC4) != 0 ||
                                *(int*)(owner->bytes + 0xCC) == 0 ||
                                *(int*)(owner->bytes + 0xC8) == 0) {
                                if (*(int*)(owner->bytes + 0xC0) == 0) {
                                    if (object->bytes[0xFF0] & 0x10) {
                                        Vec3 target = *(Vec3*)(owner->bytes + 0x108);
                                        req.scale = fn_8012B7D0(self, &target);
                                    } else {
                                        req.scale = fn_8012B750(self);
                                    }
                                }
                                fn_8012B7A0(model, req.scale);
                            }
                            fn_80048708(model);
                            fn_801E8328(1, spawned);
                        } else {
                            fn_801E8328(0x1C, spawned);
                            if (object->bytes[0xFF0] & 0x10) {
                                fn_801D53F0(lbl_8064D538);
                                fn_80027730(
                                    fn_801E6CA0(lbl_8064C504, 0, 0x13, 0, 1),
                                    0, 0);
                            }
                        }
                    } else {
                        ok = 0;
                        fn_801E8328(0x1C, spawned);
                    }
                } else {
                    ok = 0;
                }
            }

            if (ok) {
                (*(void (**)(Object*))(work + 0x1A8))(owner);
                fn_801D0E78(object);
                if ((object->bytes[0xFF0] & 0x10) && kind == 0x820 &&
                    (*(int*)(owner->bytes + 4) & 0xF) != 8) {
                    fn_8020123C(0xB8, *(void**)(object->bytes + 0xC),
                                *(void**)(object->bytes + 0xC), 0);
                    fn_80045A24(1, 1);
                } else {
                    fn_8020123C(0xB0, *(void**)(object->bytes + 0xC),
                                *(void**)(object->bytes + 0xC), 0);
                }
            } else if (object->bytes[0xFF0] & 0x10) {
                lbl_8064D550 = 1;
            } else {
                owner->bytes[0xFF0] |= 1;
            }
        }
    }

    switch (*(u16*)(object->bytes + 0xFF4)) {
    case 0:
        {
            void (*callback)(Object*, u32) =
                *(void (**)(Object*, u32))(owner->bytes + 0x20);
            if (callback != 0) {
                callback(owner, *(u32*)(owner->bytes + 0x24));
            }
            if (*(s16*)(work + 8) >= 7) {
                u32 scratch = *(u32*)(work + 0x1CC);
                fn_801CEBC4(work + 0x48, work + 0x30, 12, 30,
                    *(s16*)(work + 6), &scratch);
            }
        }
        break;
    case 10:
        {
            u32 scratch;
            if (owner->bytes[0xFF0] & 4) {
                effect_desc = lbl_80651060;
                *(void**)(owner->bytes + 0x30) =
                    fn_800CE9A4(&effect_desc, 10, 0);
                if (*(void**)(owner->bytes + 0x30) != 0) {
                    fn_801E8328(13, *(void**)(owner->bytes + 0x30));
                }
            }
            scratch = *(u32*)(work + 0x1CC);
            fn_801CEBC4(work + 0x48, work + 0x30, 12, 30,
                *(s16*)(work + 6), &scratch);
        }
        break;
    case 20:
        {
            int duration = (*(s16*)(work + 8) - 1) * 45;
            path_desc = fn_801D39F4(*(u32*)(work + 0x10));
            fn_801E2B28(owner->bytes + 0x44, work + 0x3C, &path_desc,
                (u16)(*(u16*)(work + 0xC) + duration), work[0]);
            *(u16*)(owner->bytes + 0x74) = *(u16*)(work + 0xE);
            if (*(s16*)(work + 8) >= 5) {
                u32 scratch = *(u32*)(work + 0x1CC);
                fn_801CEBC4(work + 0x48, work + 0x30, 12, 30,
                    *(s16*)(work + 6), &scratch);
            }
        }
        break;
    case 30:
        {
            int duration = (*(s16*)(work + 8) - 1) * 45;
            if (*(int*)(owner->bytes + 0x10) != -1) {
                fn_801B0CA4(*(int*)(owner->bytes + 0x10), 0);
            }
            fn_801CE720(*(u32*)(work + 0x10),
                *(int*)(object->bytes + 8), object->bytes + 0x38,
                (u16)(*(u16*)(work + 0xA) + duration), 1,
                (u8)(work[5] + duration), work + 0x1AC, lbl_80651064);
        }
        break;
    }
}
