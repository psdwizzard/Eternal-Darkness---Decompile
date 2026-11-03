typedef signed long s32;
typedef unsigned int u32;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef float f32;
typedef unsigned long long u64;

typedef struct CharWork {
    s32 unk0;
    u8 pad4[0x12];
    s16 unk16;
    u8 pad18[0x47];
    u8 unk5F;
    s32 unk60;
    s32 unk64;
    s32 unk68;
    s32 unk6C;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    s32 unk7C;
    f32 unk80;
    s32 unk84;
    s16 unk88[4];
    u8 unk90;
    u8 unk91;
} CharWork;

typedef struct CharExtra {
    u8 pad0[0x48];
    s32 unk48;
    u8 pad4C[0x70];
    s32 unkBC;
} CharExtra;

typedef struct CharState {
    CharWork *work;
    u8 pad4[0x88];
    CharExtra *extra;
    u8 pad90[0xE];
    u8 unk9E;
    u8 unk9F;
} CharState;

typedef struct Vec3 {
    f32 x, y, z;
} Vec3;

typedef struct GameMode {
    u8 pad0[8];
    s32 mode;
} GameMode;

typedef struct CameraFlags {
    u8 pad0[0x40];
    s32 unk40;
} CameraFlags;

extern void fn_80027730(s32, s32, s32);
extern s32 fn_80035FB8(void *, char *, char *, char *, void *, char *);
extern s32 fn_80036E50(void *);
extern void fn_800389E0(void *, s32, s32, s32);
extern void fn_8003BEEC(void *);
extern s32 fn_8003BF5C(void *);
extern s32 fn_8003BFC8(void *);
extern void fn_80046E98(s32);
extern s32 fn_80048A60(void);
extern void fn_80048A68(s32);
extern s32 fn_8004910C(s32);
extern s32 fn_8004918C(void);
extern s32 fn_80049220(void *, s32);
extern void *fn_80049304(void *, s32);
extern void fn_80049418(void *);
extern void fn_8004948C(void *, s32, s32);
extern void fn_80052424(u16, s32, s32, s32);
extern void fn_80052580(s32, u16, s32, s32, s32);
extern u32 fn_80054C14(void *, CharWork *);
extern s32 fn_80054ED8(void *, void *, u32 *);
extern s32 fn_80055350(void *, void *, u32 *);
extern s32 fn_80055774(void *, void *, u32 *);
extern s32 fn_80055A64(void *, void *, u32 *);
extern s32 fn_80055C88(void *, void *, u32 *);
extern s32 fn_80055EE0(void *, void *, u32 *);
extern s32 fn_800560C0(void *, void *, u32 *);
extern s32 fn_80056374(void *, void *, u32 *);
extern s32 fn_80056624(void *, void *, u32 *);
extern s32 fn_800568A4(void *, void *, u32 *);
extern s32 fn_80056B88(void *, void *, u32 *);
extern s32 fn_80056E18(void *, void *, u32 *);
extern s32 fn_80057154(void *, void *, u32 *);
extern s32 fn_800572D8(void *, void *, u32 *);
extern s32 fn_800577A0(void *, void *, u32 *);
extern s32 fn_80057AC0(void *, void *, u32 *);
extern s32 fn_80057E3C(void *, void *, u32 *);
extern s32 fn_80058154(void *, void *, u32 *);
extern s32 fn_80058394(void *, void *, u32 *);
extern s32 fn_80058834(void *, void *, u32 *);
extern s32 fn_80058FF4(void *, void *, u32 *);
extern s32 fn_8005948C(void *, void *, u32 *);
extern s32 fn_80059678(void *, void *, u32 *);
extern s32 fn_80059CBC(void *, void *, u32 *);
extern s32 fn_8005A108(void *, void *, u32 *);
extern s32 fn_8005A75C(void *, void *, u32 *);
extern s32 fn_8005AC7C(void *, void *, u32 *);
extern s32 fn_8005AF34(void *, void *, u32 *);
extern s32 fn_8005B528(void *, void *, u32 *);
extern s32 fn_8005BBB4(void *, void *, u32 *);
extern void fn_8005BC64(void *, void *);
extern void fn_8005BCC0(void *, void *, void *, u32 *);
extern void fn_8005FF94(void *, void *, u32 *);
extern void fn_80062ED0(void *, void *, void *, u32 *);
extern void fn_80064B38(void *, void *, u32 *);
extern u32 fn_800654F8(s32);
extern void fn_80066754(void *, void *, u32 *);
extern void fn_80068994(void *, void *);
extern void fn_8006D444(void);
extern s32 fn_80070A6C(s32);
extern void fn_80077C1C(void *, void *, void *, u32 *);
extern void fn_8007C6AC(void *, void *);
extern void fn_8007C814(void *, void *);
extern void fn_8007CB6C(void *, void *);
extern void fn_8007CD5C(void *, void *);
extern void fn_80093C04(void *, void *, void *, u32 *);
extern s32 fn_800A1060(void);
extern void fn_800AD034(s32, s32, s32, s32, s32, s32);
extern s32 fn_800AD1D0(s32);
extern void *fn_800AD208(void);
extern void fn_800AD210(void);
extern s32 fn_800AD218(s32, s32);
extern s32 fn_800AD2B4(void);
extern void fn_800BED54(void *, s32, s32 *);
extern void fn_800BF848(void *, void *);
extern void fn_800C030C(void *, void *, f32);
extern void fn_800C16F4(void *, s32, s32, s32);
extern s32 fn_800C193C(void *);
extern s32 fn_800C28D8(void *, void *);
extern void fn_800C2FC4(void *, void *, u32);
extern void fn_800C3D94(void *, void *, u32 *);
extern void fn_800C4AA0(void *, void *, u32 *);
extern void fn_800C4B6C(void *, void *);
extern void fn_800C4C4C(void *, void *);
extern u8 fn_800C4E94(void *, s32);
extern void fn_800C52B8(void *, void *);
extern void fn_800C5818(void *);
extern void fn_800C5A8C(void *, void *);
extern void fn_800C5EFC(s32, void *);
extern void fn_800C5FF0(void *, void *, CharState *, s32);
extern void fn_800C63D8(void);
extern void fn_800C677C(void *, s32, s32);
extern void fn_800C6890(s32, s32);
extern s32 fn_800C6F50(void *, s32);
extern void fn_800C9530(void);
extern void fn_800C9B08(void *, void *, void *);
extern s32 fn_800CCAD0(void *, void *, u32 *);
extern void fn_800CF8D0(void);
extern void fn_800CF904(s32);
extern void fn_8011E174(s32, s32);
extern void fn_8011E1C4(void);
extern void fn_8011E310(s32, s32, s32, s32, s32, s32, s32);
extern s32 fn_8011EB04(void *);
extern void fn_8011F114(Vec3 *, void *);
extern s32 fn_8011F130(void *);
extern void *fn_8011F950(void *);
extern s32 fn_8011FB4C(void *);
extern s32 fn_8011FE54(void *);
extern s32 fn_80126070(void *);
extern void fn_801287C4(void *, void (*)(void), s32, s32);
extern void fn_80128A84(void *, s32, s32);
extern void fn_80128C28(void *, void (*)(void), s32);
extern void fn_80128C44(void *, void (*)(void), s32);
extern s32 fn_80128EAC(void *);
extern u8 fn_80128EE4(void *);
extern void *fn_801294DC(void *, s32, s32, s32);
extern void *fn_80129A00(void *, s32, s32, f32, f32);
extern void fn_80129BA4(void *, f32, f32);
extern s32 fn_8012A100(void *, s32);
extern s32 fn_8012A1BC(void *, s32);
extern void fn_8012AC74(void *, s32, s32);
extern void fn_8012B344(void *);
extern f32 fn_8012B750(void *);
extern f32 fn_8012B7D0(void *, Vec3);
extern void fn_8012C478(void *, s32, s32);
extern void fn_8012C62C(void *, s32, void *, void *, void *, s32);
extern void fn_8012F58C(void *, s32, s32, s32, s32, s32);
extern void fn_80130434(void *, s32);
extern s32 fn_80155DB4(void *);
extern void fn_801568FC(s32, void (*)(void));
extern void *fn_8015790C(void);
extern u16 fn_80157948(void *);
extern u16 fn_80157994(void *);
extern s32 fn_80157E1C(void);
extern void *fn_80157E24(void *, s32);
extern void *fn_80158598(s32, s32);
extern s32 fn_80158D38(s32, s32, s32, Vec3 *);
extern void *fn_8015C910(void);
extern void fn_8016B400(s32, s32, s32);
extern void fn_8017A12C(f32 *, f32, f32);
extern void fn_801A5910(s32);
extern s32 fn_801A5CE0(void);
extern s32 fn_801A5D04(void);
extern void fn_801A6EB0(void);
extern void fn_801A7228(s32);
extern s16 fn_801A7434(s32);
extern s32 fn_801A7490(s32);
extern void fn_801A74A8(s32, s32);
extern s32 fn_801A74C0(s32);
extern void fn_801A74D8(s32, s32);
extern void fn_801A7560(s32, u32);
extern void fn_801A7588(s32, s32);
extern void fn_801A7678(s32, s32);
extern s32 fn_801A7770(s32);
extern u32 fn_801A7780(s32);
extern u8 fn_801A781C(s32);
extern void fn_801A7864(s32);
extern void fn_801AAE68(s32, s32, s32, Vec3 *, s32, s32, s32, u16, f32, s32);
extern void fn_801D0D30(s32);
extern s32 fn_801E2004(s32);
extern s32 fn_801E6CA0(s32, s32, s32, s32, s32);
extern s32 fn_801E741C(char *);
extern void fn_801E7974(s32, s32);
extern void fn_801E79A0(s32, s32);
extern s32 fn_801E79FC(s32, s32);
extern u16 fn_801F6228(s32, s32, s32);
extern void fn_801F63E4(s32, s32);
extern void fn_801F6ED0(void *, void *);
extern void fn_801F86F4(s32);
extern s32 fn_80200C10(void *);
extern s32 fn_80200C20(void *);
extern s32 fn_80200C28(void *);
extern s32 fn_80200C38(void *);
extern void fn_8020104C(s32, s32, s32, s32, f32);
extern u64 fn_802011D4(void *);
extern u64 fn_8020123C(s32, s32, s32, s32);
extern void *fn_80201814(s32);
extern void fn_80201AF8(s32);
extern s32 fn_80201B54(void *);
extern CharState *fn_80201B8C(void *);
extern s32 fn_80201B94(void *);
extern s32 fn_80201B9C(void);
extern void *fn_80201BC8(void *);
extern void *fn_80201C24(void *);
extern s32 fn_80201C48(s32);
extern void fn_80201D14(void *, s32);
extern void fn_80201D1C(void *, s32);
extern void fn_80201D2C(void *, s32);
extern void fn_80201D34(void *, s32);
extern void fn_80201D3C(void *, s32);
extern void fn_80201DD8(s32, s32);
extern Vec3 fn_80201E78(void *);
extern void fn_802020B4(void *, s32);
extern void fn_80204844(s32, s32);
extern u32 fn_802053B0(void *, void *);
extern void fn_80205680(s32, s32, s32);

extern void fn_800073E4(void);
extern void fn_8002AA18(void);
extern void fn_80204810(void);

extern char lbl_80243A40[];
extern GameMode lbl_803003C8;
extern CameraFlags lbl_8063D378;
extern CameraFlags lbl_8063D400;
extern s32 lbl_8064B4E4;
extern s32 lbl_8064B7F4;
extern s32 lbl_8064B81C;
extern s32 lbl_8064C4E0;
extern u32 lbl_8064C4E4;
extern s32 lbl_8064C504;
extern s32 lbl_8064C544;
extern s32 lbl_8064C5B4;
extern u8 lbl_8064C860;
extern s32 lbl_8064C880;
extern s32 lbl_8064CB94;
extern s32 lbl_8064D18C;
extern const f32 lbl_8064E4EC;
extern const f32 lbl_8064E504;
extern const f32 lbl_8064E508;
extern const f32 lbl_8064E50C;
extern const f32 lbl_8064E524;
extern const f32 lbl_8064E538;
extern u32 lbl_8064E55C;
extern u32 lbl_8064E560;
extern u32 lbl_8064E564;
extern u32 lbl_8064E568;
extern u32 lbl_8064E56C;
extern u32 lbl_8064E570;
extern u32 lbl_8064E574;
extern u32 lbl_8064E578;
extern u32 lbl_8064E57C;
extern u32 lbl_8064E580;
extern u32 lbl_8064E584;
extern u32 lbl_8064E588;
extern u32 lbl_8064E58C;
extern u32 lbl_8064E590;
extern u32 lbl_8064E594;
extern u32 lbl_8064E598;
extern u32 lbl_8064E59C;
extern u32 lbl_8064E5A0;
extern const f32 lbl_8064E5A4;
extern const f32 lbl_8064E5A8;
extern const f32 lbl_8064E5AC;
extern const f32 lbl_8064E5B0;

s32 fn_8005BDA4(void *context, s32 type, u8 *event, u32 *result)
{
    CharExtra *extra;
    CharState *state;
    CharWork *work;
    s32 slot;
    s32 kind;
    s32 id;
    void *object;
    char *data;
    Vec3 pos;
    s32 room;
    s32 anim;
    f32 face_delta;
    f32 turn_delta;
    s32 item_count;

    data = lbl_80243A40;
    kind = fn_80200C10(event);
    object = fn_80201BC8(context);
    slot = fn_80201B94(context);
    id = fn_80201B54(context);
    state = fn_80201B8C(context);
    extra = state->extra;
    work = state->work;
    fn_8011F114(&pos, object);
    room = fn_8011FB4C(object);
    anim = fn_8011EB04(object);

    if (fn_8015C910() != 0) {
        fn_800C5EFC(id, event);
        if (fn_800CCAD0(context, event, result) != 0) {
            return 1;
        }
    }

    if (kind == 3) {
        fn_800C5FF0(context, object, state, room);
        if (lbl_8064CB94 == 1 && lbl_8064B7F4 != fn_80128EAC(object)) {
            lbl_8064C880++;
            if (lbl_8064C880 > 180) {
                if (fn_801294DC(object, lbl_8064B7F4, 0x20, 0xF) == 0) {
                    lbl_8064CB94 = 0;
                }
                lbl_8064C880 = 0;
            }
        }
    }

    if (type == 0) {
        if (kind == 1) {
            work->unk7C = -1;
            work->unk80 = lbl_8064E508;
            work->unk5F = 0;
            fn_801A5910(0);
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 0x1F) {
            if (result != 0) {
                *result = 1;
            }
            return 1;
        }
        if (kind == 0x34) {
            fn_8005BCC0(context, object, event, result);
            return 1;
        }
        if (kind == 0xF0) {
            fn_8005BC64(context, event);
            if (result != 0) {
                *result = 1;
            }
            return 1;
        }
        if (kind == 0x59) {
            if (object != 0 && fn_8011F950(object) != 0) {
                fn_8012B344(object);
            }
            return 1;
        }
        if (kind == 0xBB) {
            s32 value = fn_80200C38(event);
            if (value != 0) {
                fn_801E7974(lbl_8064C4E0, value);
            }
            return 1;
        }
        if (kind == 0xE) {
            fn_80068994(context, event);
            return 1;
        }
        if (kind == 0xBC) {
            s32 value = fn_80200C38(event);
            if (value != 0) {
                fn_801E79A0(lbl_8064C4E0, value);
            }
            return 1;
        }
        if (kind == 0xBE) {
            s32 value = fn_80200C38(event);
            if (value != 0) {
                fn_8016B400(value, id, 0);
            }
            return 1;
        }
        if (kind == 0x67) {
            fn_800C9B08(context, object, event);
            return 1;
        }
        if (kind == 0x3D) {
            fn_80130434(object, 1);
            return 1;
        }
        if (kind == 0xBF) {
            void *motion = fn_801294DC(object, fn_80200C38(event), 0x10002, 5);
            if (motion != 0) {
                fn_80128C28(motion, fn_80204810, (id << 8) | 6);
                fn_80128C44(motion, fn_80204810, (id << 8) | 7);
                fn_80201D2C(context, 0x50);
                fn_80201D14(context, 1);
            } else {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (kind == 0xFD) {
            s32 motion_id = fn_80200C38(event);
            Vec3 target;
            if (fn_80158D38(fn_8011F130(object), 2, 4, &target) != 0) {
                f32 angle;
                void *motion;
                angle = fn_8012B7D0(object, target);
                fn_8017A12C(&face_delta, fn_8012B750(object), angle);
                if (motion_id == 0x19 && fn_8012A100(object, motion_id) == 0) {
                    motion_id = 0x63;
                }
                if (motion_id == 2) {
                    motion = fn_80129A00(object, motion_id, 5, angle, lbl_8064E5A4);
                } else {
                    motion = fn_801294DC(object, motion_id, 0x100, 5);
                    if (motion != 0) {
                        f32 abs_delta = face_delta;
                        if (abs_delta < lbl_8064E4EC) {
                            abs_delta = -abs_delta;
                        }
                        if (abs_delta > lbl_8064E50C) {
                            fn_80129BA4(motion, angle, lbl_8064E5A4);
                        }
                    }
                }
                if (motion != 0) {
                    fn_80128C28(motion, fn_80204810, (id << 8) | 6);
                    fn_80128C44(motion, fn_80204810, (id << 8) | 7);
                    fn_80201D2C(context, 0x79);
                    fn_80201D14(context, 1);
                }
            }
            return 1;
        }
        if (kind == 0x8A) {
            u32 a;
            u32 b;
            u32 c;
            u32 member_a;
            u32 member_b;
            u32 member_c;
            if (room != lbl_8064D18C) {
                fn_8020104C(0x8A, id, id, 0, lbl_8064E504);
            } else {
                s32 light = fn_801E741C(data + 0x1B0);
                void *group;
                c = lbl_8064E564;
                b = lbl_8064E560;
                a = lbl_8064E55C;
                fn_8012C62C(object, 0xF, &a, &b, &c, 6);
                if (fn_801F6228(light, 0, 2) != 0) {
                    fn_801F63E4(light, 1);
                }
                group = fn_80158598(id, 0);
                if (group != 0) {
                    s32 count = fn_80157E1C();
                    s32 i;
                    for (i = 0; i < count; i++) {
                        void *member = fn_80201814((s32)fn_80157E24(group, i));
                        if (member != 0) {
                            void *member_object = fn_80201BC8(member);
                            if (member_object != 0) {
                                member_c = lbl_8064E570;
                                member_b = lbl_8064E56C;
                                member_a = lbl_8064E568;
                                fn_8012C62C(member_object, 0xF, &member_a, &member_b, &member_c, 6);
                            }
                        }
                    }
                }
                fn_8020104C(0x8B, id, id, 0, lbl_8064E5A8);
            }
            return 1;
        }
        if (kind == 0x8B) {
            u32 a;
            u32 b;
            u32 c;
            u32 member_a;
            u32 member_b;
            u32 member_c;
            if (room != lbl_8064D18C) {
                fn_8020104C(0x8B, id, id, 0, lbl_8064E504);
            } else {
                void *group;
                c = lbl_8064E57C;
                b = lbl_8064E578;
                a = lbl_8064E574;
                fn_8012C62C(object, 0xF, &a, &b, &c, 6);
                fn_8012F58C(object, 0xF, 0, 1, 0x1E, 8);
                group = fn_80158598(id, 0);
                if (group != 0) {
                    s32 count = fn_80157E1C();
                    s32 i;
                    for (i = 0; i < count; i++) {
                        void *member = fn_80201814((s32)fn_80157E24(group, i));
                        if (member != 0) {
                            void *member_object = fn_80201BC8(member);
                            if (member_object != 0) {
                                member_c = lbl_8064E588;
                                member_b = lbl_8064E584;
                                member_a = lbl_8064E580;
                                fn_8012C62C(member_object, 0xF, &member_a, &member_b, &member_c, 6);
                                fn_8012F58C(member_object, 0xF, 0, 1, 0x1E, 8);
                            }
                        }
                    }
                }
            }
            return 1;
        }
        if (kind == 0x8C) {
            u32 a;
            u32 b;
            u32 c;
            u32 member_a;
            u32 member_b;
            u32 member_c;
            if (room != lbl_8064D18C) {
                fn_8020104C(0x8C, id, id, 0, lbl_8064E504);
            } else {
                s32 light = fn_801E741C(data + 0x1B0);
                void *group;
                c = lbl_8064E594;
                b = lbl_8064E590;
                a = lbl_8064E58C;
                fn_8012C62C(object, 0xF, &a, &b, &c, 6);
                if (fn_801F6228(light, 0, 2) != 0) {
                    fn_801F63E4(light, 0);
                }
                group = fn_80158598(id, 0);
                if (group != 0) {
                    s32 count = fn_80157E1C();
                    s32 i;
                    for (i = 0; i < count; i++) {
                        void *member = fn_80201814((s32)fn_80157E24(group, i));
                        if (member != 0) {
                            void *member_object = fn_80201BC8(member);
                            if (member_object != 0) {
                                member_c = lbl_8064E5A0;
                                member_b = lbl_8064E59C;
                                member_a = lbl_8064E598;
                                fn_8012C62C(member_object, 0xF, &member_a, &member_b, &member_c, 6);
                            }
                        }
                    }
                }
            }
            return 1;
        }
        if (kind == 0x86) {
            fn_801A5910(fn_80200C38(event));
            return 1;
        }
        if (kind == 0x87) {
            if (lbl_8064D18C != 0x60) {
                fn_8020123C(0x87, id, work->unk70, 0);
                fn_800C63D8();
            }
            if (result != 0) {
                *result = lbl_8064D18C != 0x60;
            }
            return 1;
        }
        if (kind == 0x7D) {
            if (fn_80200C38(event) != 0) {
                fn_80093C04(context, object, event, result);
            } else if (result != 0) {
                *result = 1;
            }
            return 1;
        }
        if (kind == 0x93) {
            if (fn_80200C38(event) != 0) {
                s32 target = fn_800C193C(context);
                if (target != 0 && (u32)(fn_8020123C(0x93, id, target, 1) & 0xFFFFFFFFULL) == 1) {
                    state->work->unk60 = target;
                    fn_80201D2C(context, 0x47);
                    fn_80201D14(context, 1);
                }
            } else {
                fn_8011E310(2, 0x16, 0x76E, 0, 0x30, 3, 0);
            }
            return 1;
        }
        if (kind == 0xCF) {
            if (fn_80126070(object) != 0 && fn_80128EE4(object) == 0x10 &&
                fn_80070A6C(0x100000) == 0 && fn_800C4E94(context, 1) == 0) {
                fn_800C4E94(context, 0);
            }
            return 1;
        }
        if (kind == 0xD0) {
            if (fn_80070A6C(0x100000) == 0) {
                lbl_8064C860 = 1;
                fn_8007C814(context, event);
            }
            return 1;
        }
        if (kind == 0xB1) {
            if (fn_80070A6C(0x100000) == 0) {
                lbl_8064C860 = 0;
                fn_8007C814(context, event);
            }
            return 1;
        }
        if (kind == 0xC6) {
            if (fn_80070A6C(0x100000) == 0) {
                s32 index = fn_80049220(context, 1);
                void *item = fn_80049304(context, index);
                lbl_8064C860 = 0;
                if (item != 0) {
                    void *inventory = fn_80201C24(item);
                    if (fn_8015790C() != 0) {
                        if (fn_802053B0(context, inventory) != 0 &&
                            fn_80157948(inventory) != fn_80157994(inventory)) {
                            fn_8007CB6C(context, event);
                        } else {
                            fn_8007CD5C(context, event);
                        }
                    }
                }
            }
            return 1;
        }
        if (kind == 0x9B) {
            if (fn_80070A6C(0x100000) == 0) {
                lbl_8064C860 = 0;
                fn_8007C6AC(context, event);
            }
            return 1;
        }
        if (kind == 0x78) {
            s32 *params;
            s32 action;
            s32 other_action;
            void *other;
            CharState *other_state;
            s32 other_id;
            u32 other_object;
            s32 index;
            s32 message;
            params = (s32 *)fn_80200C38(event);
            action = fn_80155DB4(context);
            other_id = params[8];
            other = fn_80201814(other_id);
            if (other != 0) {
                other_state = fn_80201B8C(other);
                other_object = (u32)fn_80201BC8(other);
                other_action = fn_80155DB4(other);
                switch (other_state->unk9F) {
                case 5:
                    break;
                case 6:
                    index = 0;
                    message = 0x274;
                    break;
                case 3:
                    index = 1;
                    message = 0x392;
                    break;
                case 4:
                    index = 2;
                    message = 0x395;
                    break;
                }
                if (fn_801E79FC(lbl_8064C4E0, message) == 0) {
                    fn_801E7974(lbl_8064C4E0, message);
                    fn_80027730(fn_801E6CA0(lbl_8064C504, 0x13, index, 0, 1), 0, 0);
                }
                fn_801568FC(action, fn_8002AA18);
                fn_80201D3C(context, 1);
                fn_80201D2C(context, 0x52);
                fn_80201D14(context, 1);
                state->unk9E = 2;
                state->unk9F = 1;
                fn_801568FC(other_action, fn_800073E4);
                fn_80201D3C(other, 0);
                fn_80201D34(other, 0x32);
                fn_80201D1C(other, 1);
                other_state->unk9E = 1;
                other_state->extra->unkBC = id;
                lbl_8064C544 = other_id;
                if (params[0] != 0) {
                    fn_801F86F4(0);
                    lbl_8063D378.unk40 = 1;
                    lbl_8063D400.unk40 = 1;
                    fn_801F6ED0((void *)lbl_8064C4E4, (void *)other_object);
                }
                fn_80201AF8(other_id);
                lbl_8064C4E4 = other_object;
                lbl_8064C5B4 = other_action;
                fn_800CF904(0);
                fn_8011E1C4();
                {
                    s32 camera = fn_8004918C();
                    fn_8004948C(other, camera, 0);
                    fn_801A7864(camera);
                }
            }
            return 1;
        }
        if (kind == 0x69) {
            fn_8005FF94(context, event, result);
            return 1;
        }
        if (kind == 0x85) {
            u32 value = fn_80054C14(context, work);
            if (result != 0) {
                *result = value;
            }
            return 1;
        }
        if (kind == 0xED) {
            fn_8020123C(0xB, fn_80200C20(event), fn_80200C28(event), fn_80200C38(event));
            fn_801A7228(fn_80200C38(event));
            return 1;
        }
        if (kind == 0x3A) {
            fn_8020123C(0x27, fn_80200C20(event), fn_80200C28(event), fn_80200C38(event));
            fn_801A7228(fn_80200C38(event));
            return 1;
        }
        if (kind == 0xB) {
            s32 item = fn_80200C38(event);
            u32 value;
            fn_801A7588(item, 0x8000);
            value = fn_800654F8(item);
            if (lbl_803003C8.mode == 0xD) {
                fn_800AD034(fn_800AD1D0(1), 1, 1, 0x23, 0x64, 0);
            }
            if (result != 0) {
                *result = value;
            }
            return 1;
        }
        if (kind == 0x35) {
            fn_80066754(context, event, result);
            return 1;
        }
        if (kind == 0x20) {
            if (anim == 0) {
                if (result != 0) {
                    *result = 0;
                }
            } else {
                fn_80062ED0(context, object, event, result);
            }
            return 1;
        }
        if (kind == 0x6B) {
            if (fn_80200C38(event) != 0) {
                fn_80077C1C(context, object, event, result);
            } else if (state->work->unk16 == 0) {
                if (result != 0) {
                    *result = 1;
                }
            } else {
                if (result != 0) {
                    *result = 0;
                }
            }
            return 1;
        }
        if (kind == 0xD9) {
            if (result != 0) {
                *result = extra->unk48;
            }
            return 1;
        }
        if (kind == 0x99) {
            if (fn_80200C38(event) != 0) {
                work->unk64 = fn_80200C20(event);
                if (fn_801294DC(object, 0xB, 0x31, 8) != 0) {
                    fn_801AAE68(0x25E, 0x64, 0, &pos, 2, 2, 0, lbl_8064D18C, lbl_8064E538, 0);
                    fn_80201D2C(context, 0x43);
                    fn_80201D14(context, 1);
                }
                if (result != 0) {
                    *result = 1;
                }
            } else {
                if (result != 0) {
                    *result = 1;
                }
            }
            return 1;
        }
        if (kind == 0x9E) {
            void *motion = fn_801294DC(object, 0x25, 0x121, 8);
            if (motion != 0) {
                f32 angle;
                f32 abs_delta;
                void *other = fn_80201814(fn_80200C20(event));
                Vec3 target = fn_80201E78(other);
                angle = fn_8012B7D0(object, target);
                angle += lbl_8064E508;
                fn_8017A12C(&turn_delta, fn_8012B750(object), angle);
                abs_delta = turn_delta;
                if (abs_delta < lbl_8064E4EC) {
                    abs_delta = -abs_delta;
                }
                if (abs_delta > lbl_8064E5AC) {
                    fn_80129BA4(motion, angle, lbl_8064E5B0);
                }
                work->unk68 = fn_80200C20(event);
                fn_80201D2C(context, 0x45);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (kind == 0x82) {
            if (result != 0) {
                *result = 0;
            }
            return 1;
        }
        if (kind == 8) {
            if (fn_800A1060() != 0) {
                fn_8020123C(0x55, id, id, 0);
            } else if (lbl_8064D18C != 0x60) {
                void *motion = fn_801294DC(object, 0x18, 0x20, 0xA);
                if (motion != 0) {
                    s32 sound = fn_800AD2B4();
                    fn_80128C44(motion, fn_80204810, (id << 8) | 7);
                    if (anim == 0x55 || (u32)(anim - 0x77) <= 2 || anim == 0x7A) {
                        fn_80128C28(motion, fn_80204810, (id << 8) | 6);
                    } else {
                        s32 frame = fn_8012A1BC(object, 0x18);
                        void *item;
                        s32 index;
                        fn_80128A84(motion, 0, frame);
                        fn_801287C4(motion, fn_80204810, (id << 8) | 6, frame);
                        index = fn_80049220(context, 1);
                        item = fn_80049304(context, index);
                        if (item != 0) {
                            s32 *inventory = (s32 *)fn_80201C24(item);
                            fn_8003BEEC(item);
                            if (inventory[5] != 0) {
                                fn_8003BEEC(fn_80201814(inventory[5]));
                            }
                        }
                    }
                    fn_80201D2C(context, 8);
                    fn_80201D14(context, 1);
                    if (sound != 0) {
                        fn_8020123C(0xC3, id, sound, 0x2715);
                    }
                }
            }
            return 1;
        }
        if (kind == 0x55) {
            void *motion = fn_801294DC(object, 0x18, 0, 0xA);
            if (motion != 0) {
                fn_80128C28(motion, fn_80204810, (id << 8) | 6);
                fn_80128C44(motion, fn_80204810, (id << 8) | 7);
                fn_80201D2C(context, 8);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (kind == 0x29) {
            s32 item = fn_80200C38(event);
            fn_80201DD8(slot, 0);
            fn_800C63D8();
            fn_800C16F4(context, item, 1, 0);
            return 1;
        }
        if (kind == 0x2A) {
            s32 item = fn_80200C38(event);
            if (fn_80048A60() == 0) {
                fn_80201DD8(slot, 0);
                fn_80048A68(1);
                fn_800C63D8();
            }
            fn_800C16F4(context, item, 1, 1);
            return 1;
        }
        if (kind == 0x2B) {
            fn_800C3D94(context, event, result);
            return 1;
        }
        if (kind == 0x3C) {
            s32 camera = fn_8004918C();
            fn_8004948C(context, camera, 0);
            fn_801A7864(camera);
            fn_80049418(context);
            fn_80205680(fn_8004910C(camera), id, 0x5B);
            fn_801A7560(camera, fn_801A7780(camera));
            return 1;
        }
        if (kind == 0x2D) {
            if (fn_80128EE4(object) != 0x10) {
                fn_801294DC(object, 0xF, 0x21, 1);
            }
            return 1;
        }
        if (kind == 0x2C) {
            fn_800C030C(context, event, lbl_8064E504);
            return 1;
        }
        if (kind == 0x28) {
            if (fn_80070A6C(0x200) == 0) {
                s32 item = fn_80200C38(event);
                u32 flags = fn_801A7780(item);
                void *holder = fn_80201814(fn_80201C48(slot));
                u8 forced;
                item_count = fn_801A7770(item);
                if (holder != 0) {
                    fn_800BED54(holder, item, &item_count);
                }
                forced = fn_801A781C(item);
                if (fn_801A74C0(item) & 0x20) {
                    s32 handle = fn_8020123C(0x45, id, id, item) & 0xFFFFFFFFULL;
                    if (handle != 0) {
                        fn_8020104C(0x46, id, id, 0, lbl_8064E504);
                    }
                    state->work->unk0 = handle;
                    fn_80201D2C(context, 0x57);
                    fn_80201D14(context, 1);
                } else if ((fn_801A74C0(item) & 4) && (forced != 0 || (flags & 0x90038))) {
                    s32 handle;
                    fn_801A74C0(item);
                    handle = fn_8020123C(0x45, id, id, item) & 0xFFFFFFFFULL;
                    if (handle != 0) {
                        fn_8020104C(0x46, id, id, 0, lbl_8064E504);
                    }
                    fn_80201DD8(slot, 0);
                    fn_800C63D8();
                    fn_800C16F4(context, item, 1, 0);
                    fn_801A74A8(handle, fn_801A7490(item));
                    fn_801A7678(handle, 1);
                    state->work->unk0 = handle;
                    if (flags & 0x90018) {
                        fn_801A74D8(handle, 0x400);
                        fn_80201D2C(context, 0x57);
                        fn_80201D14(context, 1);
                    } else {
                        fn_80201D2C(context, 0x28);
                        fn_80201D14(context, 1);
                    }
                } else if (flags & 0x10018) {
                    fn_800BF848(context, event);
                } else if (flags & 4) {
                    if (fn_800C6F50(context, item) != 0) {
                        fn_800C2FC4(context, event, 0);
                    } else if (fn_800C28D8(context, event) != 0) {
                        work->unk90 |= 1;
                        work->unk88[work->unk91] = fn_801A7434(fn_80200C38(event));
                        fn_80201D2C(context, 6);
                        fn_80201D14(context, 1);
                    }
                } else if (flags == 0) {
                    fn_800C4C4C(context, event);
                } else if (flags & 0x80020) {
                    fn_800C2FC4(context, event, flags & 0x80000);
                }
            }
            return 1;
        }
        if (kind == 0x45) {
            if (fn_80070A6C(0x200) == 0) {
                fn_800C4AA0(context, event, result);
            }
            return 1;
        }
        if (kind == 0x46) {
            if (fn_80070A6C(0x200) == 0) {
                fn_800C4B6C(context, event);
            }
            return 1;
        }
        if (kind == 0x27) {
            fn_80204844(fn_80201B9C(), 0x20);
            fn_8006D444();
            if (lbl_8064D18C != 0x60) {
                fn_80064B38(context, event, result);
            }
            return 1;
        }
        if (kind == 0x3B) {
            u32 value = 1;
            if (lbl_8064B81C != 0) {
                s32 flags = fn_80200C38(event);
                if (lbl_803003C8.mode == 0xD && fn_800AD208() != 0) {
                    value = 0;
                } else if (flags & 2) {
                    value = 1;
                } else if (fn_801E2004(id) == 4) {
                    if (fn_8003BFC8(fn_80201814(fn_80200C20(event))) != 0) {
                        value = 0;
                    }
                }
            } else {
                value = 0;
            }
            if (result != 0) {
                *result = value;
            }
            return 1;
        }
        if (kind == 0x65) {
            if (result != 0) {
                *result = 1;
            }
            return 1;
        }
        if (kind == 0xA5) {
            s32 item = fn_80200C38(event);
            fn_801D0D30(id);
            fn_800C677C(context, item, 0);
            return 1;
        }
        if (kind == 0x9D) {
            s32 motion_id = fn_80200C38(event);
            fn_8012AC74(object, motion_id, 3);
            return 1;
        }
        if (kind == 0xAF) {
            fn_80201D2C(context, 0x40);
            fn_80201D14(context, 1);
            if (result != 0) {
                *result = 1;
            }
            return 1;
        }
        if (kind == 0xB9) {
            if (fn_801A5CE0() != 0 || fn_801A5D04() != 0) {
                if (result != 0) {
                    *result = 1;
                }
            } else {
                if (result != 0) {
                    *result = 0;
                }
            }
            return 1;
        }
        if (kind == 0xCA) {
            fn_800C52B8(context, event);
            return 1;
        }
        if (kind == 0x47) {
            fn_800C5818(context);
            return 1;
        }
        if (kind == 0xC2) {
            fn_800C5A8C(context, event);
            return 1;
        }
        if (kind == 0xF2) {
            u32 value = fn_80200C38(event);
            u16 sound = value;
            if (value & 0x80000000) {
                fn_80052580(2, sound, 1, 1, 0);
            } else {
                fn_80052424(sound, -1, 0, 0);
            }
            return 1;
        }
        if (kind == 0xFA) {
            switch (fn_80200C38(event)) {
            case 2: {
                s32 handle = fn_800AD218(6, 0);
                fn_800C9530();
                fn_800C6890(handle, 0);
                fn_800AD210();
                break;
            }
            case 13:
                fn_802020B4(context, 1);
                break;
            case 12:
                fn_802020B4(context, 0);
                break;
            }
            return 1;
        }
        if (kind == 0xEE) {
            s32 value = -1;
            if (work->unk7C != -1) {
                fn_8012B344(object);
                fn_80130434(object, 1);
                value = (work->unk7C == 0) ? -1 : work->unk7C;
                work->unk7C = -1;
                fn_801294DC(object, fn_8011FE54(object), 0x10031, 1);
            } else {
                s32 current = fn_80128EAC(object);
                if (current == 0x19 || current == 0x63 || current == 0x67 || current == 0x68) {
                    fn_8012B344(object);
                    fn_80130434(object, 1);
                    switch (current) {
                    case 0x19:
                        value = 0x19;
                        break;
                    case 0x63:
                        value = 0x63;
                        break;
                    case 0x67:
                        value = 0x68;
                        break;
                    case 0x68:
                        value = 0x67;
                        break;
                    }
                }
            }
            if (result != 0) {
                *result = value;
            }
            return 1;
        }
        if (kind == 0xFC) {
            fn_801D0D30(id);
            fn_800CF8D0();
            return 1;
        }
        if (kind == 0x33) {
            fn_8012C478(object, 0xF, 0);
            fn_80046E98(id);
            return 1;
        }
    } else if (type == 1) {
        return fn_8005BBB4(context, event, result);
    } else if (type == 0x4A) {
        return fn_80055350(context, event, result);
    } else if (type == 0x47) {
        return fn_80055774(context, event, result);
    } else if (type == 0x5F) {
        return fn_80055A64(context, event, result);
    } else if (type == 0x30) {
        return fn_80055C88(context, event, result);
    } else if (type == 0x4B) {
        return fn_800560C0(context, event, result);
    } else if (type == 0x48) {
        return fn_80056374(context, event, result);
    } else if (type == 0x4C) {
        return fn_80056624(context, event, result);
    } else if (type == 0x4D) {
        return fn_800568A4(context, event, result);
    } else if (type == 0x5A) {
        return fn_80056B88(context, event, result);
    } else if (type == 0x1E) {
        return fn_80054ED8(context, event, result);
    } else if (type == 0x38) {
        return fn_80056E18(context, event, result);
    } else if (type == 7) {
        return fn_80057154(context, event, result);
    } else if (type == 0x55) {
        return fn_8005948C(context, event, result);
    } else if (type == 6) {
        return fn_800572D8(context, event, result);
    } else if (type == 0x6C) {
        return fn_800577A0(context, event, result);
    } else if (type == 0x60) {
        return fn_80057AC0(context, event, result);
    } else if (type == 0x54) {
        return fn_80057E3C(context, event, result);
    } else if (type == 0x28) {
        return fn_80058154(context, event, result);
    } else if (type == 0x27) {
        return fn_80058394(context, event, result);
    } else if (type == 0x57) {
        return fn_80058834(context, event, result);
    } else if (type == 0x58) {
        return fn_80058FF4(context, event, result);
    } else if (type == 0x34) {
        return fn_80059678(context, event, result);
    } else if (type == 0x35) {
        return fn_80059CBC(context, event, result);
    } else if (type == 0x43) {
        return fn_8005A108(context, event, result);
    } else if (type == 0x45) {
        return fn_8005A75C(context, event, result);
    } else if (type == 0x7A) {
        return fn_8005AC7C(context, event, result);
    } else if (type == 0x40) {
        return fn_8005AF34(context, event, result);
    } else if (type == 0x4E) {
        if (kind == 0xC3) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 0x34) return 1;
        if (kind == 0x2E) return 1;
        if (kind == 0xB) return 1;
        if (kind == 0x28) return 1;
        if (kind == 0x6B) return 1;
        if (kind == 0xAF) return 1;
        if (kind == 8) return 1;
        if (kind == 0x2B) return 1;
        if (kind == 0x87) return 1;
        if (kind == 0x20) return 1;
        if (kind == 0x35) return 1;
        if (kind == 0x1E) return 1;
        if (kind == 0x2C) return 1;
        if (kind == 0x69) return 1;
        if (kind == 0x85) return 1;
        if (kind == 0x3D) return 1;
        if (kind == 0x7D) return 1;
        if (kind == 0x93) return 1;
    } else if (type == 0x79) {
        if (kind == 6) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 7) {
            if (fn_80035FB8(context, data + 0xA0, data + 0x1C0, data + 0xCC, &lbl_8064B4E4, data + 0xD8) == 0) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (kind == 0x34) return 1;
        if (kind == 0x20) return 1;
        if (kind == 0x6B) return 1;
        if (kind == 0x99) return 1;
        if (kind == 0x2C) return 1;
        if (kind == 0x69) return 1;
        if (kind == 0x7D) return 1;
        if (kind == 0xAF) return 1;
        if (kind == 0x28) return 1;
        if (kind == 0x93) return 1;
        if (kind == 0x2B) return 1;
    } else if (type == 0x50) {
        if (kind == 3) {
            fn_801A6EB0();
            return 1;
        }
        if (kind == 0x2C) {
            fn_8012B344(object);
            return 1;
        }
        if (kind == 6) {
            f32 angle = work->unk80;
            void *motion;
            angle += fn_8012B750(object);
            motion = fn_80129A00(object, 2, 5, angle, lbl_8064E524);
            if (motion != 0) {
                fn_80128C28(motion, fn_80204810, (id << 8) | 6);
                fn_80128C44(motion, fn_80204810, (id << 8) | 7);
                fn_80201D2C(context, 0x51);
                fn_80201D14(context, 1);
            } else {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (kind == 7) {
            if (fn_80035FB8(context, data + 0xA0, data + 0x1C0, data + 0xCC, &lbl_8064B4E4, data + 0xD8) == 0) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (kind == 0x3D) {
            fn_8012B344(object);
            if (result != 0) {
                *result = fn_802011D4(event) & 0xFFFFFFFFULL;
            }
            return 1;
        }
        if (kind == 0xFD) {
            fn_8012B344(object);
            if (result != 0) {
                *result = fn_802011D4(event) & 0xFFFFFFFFULL;
            }
            return 1;
        }
        if (kind == 0x34) return 1;
        if (kind == 0x20) return 1;
        if (kind == 0x6B) return 1;
        if (kind == 0x99) return 1;
        if (kind == 0x69) return 1;
        if (kind == 0x7D) return 1;
        if (kind == 0x28) return 1;
        if (kind == 0x93) return 1;
        if (kind == 0x2B) return 1;
    } else if (type == 0x51) {
        if (kind == 2) {
            work->unk80 = lbl_8064E508;
            return 1;
        }
        if (kind == 0x2C) {
            fn_8012B344(object);
            return 1;
        }
        if (kind == 6) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 7) {
            if (fn_80035FB8(context, data + 0xA0, data + 0x1D8, data + 0xCC, &lbl_8064B4E4, data + 0xD8) == 0) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (kind == 0x3D) {
            fn_8012B344(object);
            if (result != 0) {
                *result = fn_802011D4(event) & 0xFFFFFFFFULL;
            }
            return 1;
        }
        if (kind == 0xFD) {
            fn_8012B344(object);
            if (result != 0) {
                *result = fn_802011D4(event) & 0xFFFFFFFFULL;
            }
            return 1;
        }
        if (kind == 0x34) return 1;
        if (kind == 0x20) return 1;
        if (kind == 0x6B) return 1;
        if (kind == 0x99) return 1;
        if (kind == 0x69) return 1;
        if (kind == 0x7D) return 1;
        if (kind == 0x28) return 1;
        if (kind == 0x93) return 1;
        if (kind == 0x2B) return 1;
    } else if (type == 0x52) {
        if (kind == 0xC0) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 0x3B) {
            void *target = fn_80201814(fn_80200C20(event));
            if (target != 0 && fn_8003BF5C(target) != 0 && result != 0) {
                *result = 1;
            }
            return 1;
        }
        if (kind == 0xB) {
            void *target = fn_80201814(fn_80200C20(event));
            if (target != 0 && fn_8003BF5C(target) != 0 && fn_80036E50(target) != 0x28 && result != 0) {
                *result = 1;
            }
            return 1;
        }
        if (kind == 0x86) {
            fn_801A5910(fn_80200C38(event));
            return 1;
        }
        if (kind == 0x34) return 1;
        if (kind == 0xBF) return 1;
        if (kind == 0xE) return 1;
        if (kind == 0x87) return 1;
        if (kind == 0x7D) return 1;
        if (kind == 0x93) return 1;
        if (kind == 0xB1) return 1;
        if (kind == 0x9B) return 1;
        if (kind == 0x78) return 1;
        if (kind == 0x69) return 1;
        if (kind == 0x85) return 1;
        if (kind == 0x35) return 1;
        if (kind == 0x1E) return 1;
        if (kind == 0x20) return 1;
        if (kind == 0x6B) return 1;
        if (kind == 0x99) return 1;
        if (kind == 0x9E) return 1;
        if (kind == 0x82) return 1;
        if (kind == 8) return 1;
        if (kind == 0x55) return 1;
        if (kind == 0x29) return 1;
        if (kind == 0x2A) return 1;
        if (kind == 0x2B) return 1;
        if (kind == 0x3C) return 1;
        if (kind == 0x2D) return 1;
        if (kind == 0x2C) return 1;
        if (kind == 0x28) return 1;
        if (kind == 0x45) return 1;
        if (kind == 0x46) return 1;
        if (kind == 0x2E) return 1;
        if (kind == 0x27) return 1;
        if (kind == 0x65) return 1;
        if (kind == 0x68) return 1;
        if (kind == 0xA5) return 1;
        if (kind == 0xA6) return 1;
        if (kind == 0xAF) return 1;
        if (kind == 0xB9) return 1;
        if (kind == 0x34) return 1;
    } else if (type == 0x7F) {
        if (kind == 1) {
            fn_8011E174(8, 1);
            return 1;
        }
        if (kind == 6) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 7) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 8) {
            fn_800389E0(context, 0, 1, 0);
            return 1;
        }
        if (kind == 2) {
            fn_8011E174(8, 0);
            return 1;
        }
        if (kind == 0x34) return 1;
        if (kind == 0xE) return 1;
        if (kind == 0x67) return 1;
        if (kind == 0x87) return 1;
        if (kind == 0x7D) return 1;
        if (kind == 0x93) return 1;
        if (kind == 0xCF) return 1;
        if (kind == 0xD0) return 1;
        if (kind == 0xB1) return 1;
        if (kind == 0xC6) return 1;
        if (kind == 0x9B) return 1;
        if (kind == 0x85) return 1;
        if (kind == 0xB) return 1;
        if (kind == 0x35) return 1;
        if (kind == 0x20) return 1;
        if (kind == 0x6B) return 1;
        if (kind == 0x99) return 1;
        if (kind == 0x9E) return 1;
        if (kind == 0x28) return 1;
        if (kind == 0x45) return 1;
        if (kind == 0x27) return 1;
        if (kind == 0x46) return 1;
        if (kind == 0x3B) return 1;
        if (kind == 0x65) return 1;
        if (kind == 0xAF) return 1;
        if (kind == 0xB9) return 1;
        if (kind == 0xCA) return 1;
        if (kind == 0xC2) return 1;
    } else if (type == 8) {
        return fn_8005B528(context, event, result);
    } else if (type == 0x7D) {
        return fn_80055EE0(context, event, result);
    } else {
        return 0;
    }
    return 0;
}
