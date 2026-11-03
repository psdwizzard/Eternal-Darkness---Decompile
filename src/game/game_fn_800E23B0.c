typedef unsigned long long u64;

typedef struct Vec {
    float x;
    float y;
    float z;
} Vec;

typedef struct Target {
    unsigned char pad0[0x5C];
    int unk5C;
    unsigned char pad60[0x34];
    Vec unk94;
    unsigned char padA0[0xAC];
    short unk14C;
    short unk14E;
    short unk150;
    unsigned char pad152[0xF];
    signed char unk161;
} Target;

typedef struct Link {
    unsigned char pad0[0x4];
    int unk4;
} Link;

typedef struct ActorData {
    unsigned char pad0[0x4];
    Link *unk4;
    unsigned char pad8[0x84];
    Target *unk8C;
    unsigned char pad90[0xC];
    short unk9C;
} ActorData;

typedef struct AnimNames {
    char idle[0x1C];
    char walk[0xC];
    char run[0x18];
    char special[0x10];
} AnimNames;

extern int fn_80200C10(void *);
extern int fn_80200C20(void *);
extern int fn_80200C28(void *);
extern int fn_80200C38(void *);
extern void *fn_80201BC8(void *);
extern ActorData *fn_80201B8C(void *);
extern void *fn_80201B94(void *);
extern int fn_80201B54(void *);
extern int fn_80201B44(void);
extern void *fn_80201814(int);
extern int fn_80201B5C(void *);
extern int fn_80201C48(void *);
extern int fn_80201C50(void *);
extern void *fn_80201C2C(void *);
extern int fn_80201EB8(void *);
extern void fn_80201D14(void *, int);
extern void fn_80201D1C(void *, int);
extern void fn_80201D2C(void *, int);
extern void fn_80201D34(void *, int);
extern void fn_8020104C(int, int, int, int, float);
extern void fn_80201138(int, void *, int, int, int, float);
extern u64 fn_802011D4(void *);
extern void fn_8020123C(int, int, int, int);
extern void fn_802006D4(int, int, int, int, int);
extern void fn_80204810(void);
extern void *fn_80205288(void *);
extern int fn_801E79FC(int, int);
extern void fn_801E8328(int, void *);
extern void fn_801B05E8(int, int, int, int, int, int, int, int);
extern void fn_801B1A1C(int, int);
extern void fn_801A7228(int);
extern void fn_801A977C(void *, int);
extern void fn_8016B400(int, int, int);
extern int fn_8015C9F0(void);
extern int fn_8013017C(void *);
extern void fn_801301B0(void *, int, int);
extern int fn_801305D4(void *);
extern void fn_8012B324(void *);
extern void fn_8012B344(void *);
extern void fn_8012A1FC(void *, int);
extern int fn_8012A1BC(void *, int);
extern void *fn_801294DC(void *, int, int, int);
extern int fn_801290D0(void *);
extern void fn_80128F74(void *, int);
extern int fn_80128EAC(void *);
extern void *fn_80128E30(void *);
extern void fn_80128C44(void *, void (*)(void), int);
extern void fn_80128C28(void *, void (*)(void), int);
extern void fn_80128A84(void *, int, int);
extern void fn_80128754(void *, int);
extern void fn_80120AD0(void *, int, int, int, float, float);
extern int fn_8011FAEC(void *);
extern void fn_8011FADC(void *, int);
extern void fn_8011F114(Vec *, void *);
extern void fn_800EA0FC(void *, Target *, int, void *, int *);
extern void fn_800EA3A0(void *, Target *);
extern void fn_800E39A8(void *, void *, int, Target *, void *, int, int);
extern int fn_800E3618(void *, void *, void *);
extern int fn_800E34B4(void *, void *, void *, int, int);
extern void fn_800E2344(int, void *);
extern void fn_800E2150(int, void *, Target *, void *);
extern void fn_800E2128(void *);
extern void fn_800E20A4(void *);
extern void fn_800CC860(void *, int, int);
extern int fn_800CB254(void *, int, int, int, int);
extern void fn_800CA2C8(void *);
extern int fn_800BE86C(void *, Vec *, int, int, float);
extern void fn_800BE010(void *, Target *);
extern void fn_800BDEE4(void *, Target *);
extern void fn_800BD2DC(void *, Target *);
extern void *fn_800930B0(void *, int, int, int, int);
extern void fn_80068994(void *, void *);
extern void fn_80066888(void *, int, float, float);
extern void fn_80066754(void *, void *, int *);
extern int fn_800654F8(int);
extern void fn_80064B38(void *, void *, int *);
extern int fn_800460EC(void);
extern void fn_8003E5DC(void *, void *, int, Target *);
extern void fn_800389E0(void *, int, int, int);
extern void fn_80038544(int, int, int);
extern void fn_80038464(void *, int, short *);
extern int fn_80036E50(void *);
extern int fn_80036D5C(void *);
extern void fn_80036DA4(void *, int);
extern int fn_80035FB8(void *, char *, char *, char *, char *, char *);
extern void fn_800359A0(void *, int);
extern void fn_800073D8(int);

extern AnimNames lbl_80248D58;
extern char lbl_8064B7B8[8];
extern char lbl_8064B7C0[8];
extern char lbl_8064B7C8[8];
extern int lbl_8064C4E0;
extern int lbl_8064D18C;
extern int lbl_8064D5A8;
extern const float lbl_8064F648;
extern const float lbl_8064F64C;
extern const float lbl_8064F650;
extern const float lbl_8064F654;
extern const float lbl_8064F658;
extern const float lbl_8064F65C;
extern const float lbl_8064F660;
extern const float lbl_8064F664;
extern const float lbl_8064F668;
extern const float lbl_8064F66C;

int fn_800E23B0(void *context, int phase, void *message, int *result)
{
    int variant;
    int tick;
    int id;
    void *owner;
    Target *target;
    AnimNames *names;
    int kind;
    ActorData *data;
    void *object;

    names = &lbl_80248D58;
    kind = fn_80200C10(message);
    object = fn_80201BC8(context);
    data = fn_80201B8C(context);
    target = data->unk8C;
    owner = fn_80201B94(context);
    id = fn_80201B54(context);
    tick = lbl_8064D5A8 + data->unk9C;
    variant = data->unk8C->unk161;

    if (kind == 3) {
        short t;
        t = target->unk150;
        if (t >= 1)
            t -= 1;
        target->unk150 = t;
        t = target->unk14C;
        if (t >= 1)
            t -= 1;
        target->unk14C = t;
        if ((fn_8013017C(object) & 0x40) && fn_801305D4(object) == 0)
            fn_801301B0(object, 0x40, 0);
        fn_80128754(object, -1);
    }

    if (phase == 0) {
        if (kind == 1) {
            fn_80036DA4(context, fn_80036D5C(context) | 0x1000);
            fn_8020104C(0x91, id, id, 0, lbl_8064F648);
            fn_80201D2C(context, 0x72);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 59) {
            void *self = fn_80201814(fn_80201B44());
            int sender = fn_80200C20(message);
            void *link = fn_80201814(sender);
            if (link != 0 && self != 0 && fn_80036E50(self) == 1 &&
                (sender == fn_80201B44() || fn_80201B5C(link) == 0x19)) {
                if (result != 0)
                    *result = 1;
            } else if (result != 0) {
                *result = 0;
            }
            return 1;
        }
        if (kind == 14) {
            void *self = fn_80201814(fn_80201B44());
            if (self != 0 && fn_80036E50(self) == 1)
                fn_80068994(context, message);
            return 1;
        }
        if (kind == 39) {
            void *self = fn_80201814(fn_80201B44());
            if (self != 0 && fn_80036E50(self) == 1)
                fn_80064B38(context, message, result);
            return 1;
        }
        if (kind == 8) {
            if (fn_8015C9F0() == 0) {
                void *self = fn_80201814(fn_80201B44());
                fn_80201EB8(context);
                if (self != 0 && fn_80036E50(self) == 1) {
                    void *anim = fn_801294DC(object, 0x18, 0x20, 10);
                    if (anim != 0) {
                        int slot;
                        fn_8012A1FC(object, 0x18);
                        slot = fn_8012A1BC(object, 0x18);
                        if (data->unk8C->unk14E == 0) {
                            fn_80201138(0x19, context, 9, -1, 0, lbl_8064F64C);
                            fn_80201D2C(context, 9);
                            fn_80201D14(context, 1);
                        } else {
                            fn_801B1A1C(7, 5);
                            fn_80201138(0x11, context, 8, -1, 0, lbl_8064F650);
                            fn_80201138(0xF9, context, 8, 0x4A, 0, slot + 0x28);
                            fn_80201D2C(context, 8);
                            fn_80201D14(context, 1);
                        }
                        fn_800389E0(context, 0, 0, 1);
                        fn_80128A84(anim, 0, slot);
                        if (target->unk5C != 0) {
                            void *other = fn_80201BC8(fn_80201814(target->unk5C));
                            anim = fn_801294DC(other, 0x18, 0x20, 10);
                            if (anim == 0)
                                anim = fn_80128E30(other);
                            if (anim != 0)
                                fn_80128A84(anim, 0, slot);
                        }
                    }
                } else {
                    fn_800389E0(context, 0, 1, 0);
                    fn_80038544(id, 1, 1);
                }
            } else {
                fn_800389E0(context, 0, 1, 0);
                fn_80038544(id, 1, 1);
            }
            return 1;
        }
        if (kind == 237) {
            fn_8020123C(11, fn_80200C20(message), fn_80200C28(message), fn_80200C38(message));
            fn_801A7228(fn_80200C38(message));
            return 1;
        }
        if (kind == 58) {
            fn_8020123C(39, fn_80200C20(message), fn_80200C28(message), fn_80200C38(message));
            fn_801A7228(fn_80200C38(message));
            return 1;
        }
        if (kind == 11) {
            void *self = fn_80201814(fn_80201B44());
            int value = 0;
            if (self != 0 && fn_80036E50(self) == 1) {
                value = fn_800654F8(fn_80200C38(message));
                fn_801A977C(object, 0x21);
            }
            if (result != 0)
                *result = value;
            return 1;
        }
        if (kind == 230) {
            int value = fn_80200C38(message);
            void *link = fn_80201814(fn_80200C20(message));
            if (link != 0 && fn_80201B5C(link) == 0x19)
                fn_80066754(context, message, result);
            else
                fn_80066888(object, value, lbl_8064F654, lbl_8064F658);
            return 1;
        }
        if (kind == 53) {
            fn_80066754(context, message, result);
            return 1;
        }
        if (kind == 57) {
            fn_8012B324(object);
            fn_80201D34(context, 0);
            fn_80201D1C(context, 1);
            fn_801E8328(2, context);
            return 1;
        }
        if (kind == 145) {
            void *found = 0;
            if (fn_80201C2C(context) == 0) {
                if (fn_801E79FC(lbl_8064C4E0, 0x36E) != 0)
                    found = fn_800930B0(context, 0x6E, 0x4B, 0x41, 0x30C);
            } else {
                found = fn_80205288(context);
            }
            if (found != 0) {
                target->unk5C = fn_80201B54(found);
                fn_800E2128(object);
            } else {
                fn_800E20A4(object);
            }
            return 1;
        }
        if (kind == 61) {
            fn_800BD2DC(context, target);
            fn_800EA3A0(context, target);
            return 1;
        }
        if (kind == 243) {
            int value = fn_80200C38(message);
            fn_800EA0FC(context, target, value, message, result);
            return 1;
        }
    } else if (phase == 0x72) {
        if (kind == 62) {
            fn_801294DC(object, 0x4F, 0x25, 10);
            return 1;
        }
        if (kind == 24) {
            int busy = fn_800CB254(context, 0x32, 0, lbl_8064D18C, 1);
            int timer = fn_80201C50(fn_80201B94(context));
            if (busy == 0) {
                int flags = fn_8011FAEC(object);
                Link *link = data->unk4;
                void *anim;
                if (link != 0 && link->unk4 != 0)
                    fn_8016B400(link->unk4, id, 0);
                fn_8012B344(object);
                anim = fn_801294DC(object, 0x29, 0x20, 8);
                if (anim != 0) {
                    int tag = id << 8;
                    fn_80128C44(anim, fn_80204810, tag | 7);
                    fn_80128C28(anim, fn_80204810, tag | 0x38);
                    fn_80201D2C(context, 0x21);
                    fn_80201D14(context, 1);
                } else {
                    fn_800073D8(lbl_8064D18C);
                }
                fn_8011FADC(object, flags | 0xC0);
            } else if (timer != 0 && timer != -1 && timer != 0xFFFF && timer < 2000) {
                fn_8020104C(0x18, id, id, 0, lbl_8064F65C);
            }
            return 1;
        }
    } else if (phase == 1) {
        if (kind == 3) {
            fn_800E34B4(context, object, message, tick, variant);
            return 1;
        }
        if (kind == 90) {
            void *link = fn_80201814(fn_80200C20(message));
            void *other;
            if (link != 0)
                other = fn_80201BC8(link);
            else
                other = 0;
            if (other != 0 && fn_800460EC() == 0) {
                Vec pos;
                fn_8011F114(&pos, other);
                target->unk94 = pos;
                fn_80201D2C(context, 0x15);
                fn_80201D14(context, 1);
            }
            return 1;
        }
    } else if (phase == 0x21) {
        if (kind == 3) {
            if ((tick & 7) == 0)
                fn_800359A0(context, 0);
            return 1;
        }
        if (kind == 56) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 62)
            return 1;
    } else if (phase == 0x15) {
        if (kind == 1) {
            fn_8012B344(object);
            return 1;
        }
        if (kind == 3) {
            if (fn_800E34B4(context, object, message, tick, variant) == 0 &&
                fn_800BE86C(object, &target->unk94, 2, 0, lbl_8064F660) == 0) {
                fn_801294DC(object, 0xF, 0x25, 1);
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (kind == 90) {
            void *link = fn_80201814(fn_80200C20(message));
            void *other;
            if (link != 0)
                other = fn_80201BC8(link);
            else
                other = 0;
            if (other != 0 && fn_800460EC() == 0) {
                Vec pos;
                fn_8011F114(&pos, other);
                target->unk94 = pos;
            }
            return 1;
        }
        if (kind == 2) {
            int model = fn_80128EAC(object);
            int flags = fn_801290D0(object);
            if ((flags & 4) && (model == 3 || model == 2))
                fn_80128F74(object, flags & ~4);
            return 1;
        }
    } else if (phase == 3) {
        if (kind == 3) {
            fn_800BE010(context, target);
            if (fn_80201C48(owner) != 0)
                fn_800BDEE4(context, target);
            fn_800E39A8(context, object, id, target, message, tick, variant);
            return 1;
        }
        if (kind == 102) {
            fn_8012B344(object);
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
    } else if (phase == 6) {
        if (kind == 12) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 7) {
            if (fn_80035FB8(context, names->idle, lbl_8064B7B8, names->walk, lbl_8064B7C0, names->run) == 0) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (kind == 2) {
            target->unk14C = 0;
            return 1;
        }
    } else if (phase == 7) {
        if (kind == 54) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 7) {
            if (fn_80035FB8(context, names->idle, lbl_8064B7C8, names->walk, lbl_8064B7C0, names->run) == 0) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
    } else if (phase == 0x7C) {
        if (kind == 6) {
            if (fn_800E3618(context, object, message) == 0) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (kind == 7) {
            if (fn_80035FB8(context, names->idle, names->special, names->walk, lbl_8064B7C0, names->run) == 0) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
    } else if (phase == 9) {
        if (kind == 1) {
            short frame;
            fn_80038464(context, 0, &frame);
            fn_800389E0(context, 0, frame, 1);
            data->unk8C->unk14E++;
            return 1;
        }
        if (kind == 25) {
            if (lbl_8064D18C == fn_80201EB8(context)) {
                void *anim;
                fn_80120AD0(object, 0, 100, 0x102, lbl_8064F664, lbl_8064F668);
                fn_801B05E8(0x21E, 100, 2, 1, 0, 5, 0, 0);
                fn_8012B344(object);
                anim = fn_801294DC(object, 0x29, 0x20, 8);
                if (anim != 0) {
                    int tag = id << 8;
                    fn_80128C44(anim, fn_80204810, tag | 7);
                    fn_80128C28(anim, fn_80204810, tag | 0x36);
                    fn_80201D2C(context, 7);
                    fn_80201D14(context, 1);
                }
            } else {
                fn_8020104C(0x19, id, id, 0, lbl_8064F66C);
            }
            return 1;
        }
        if (kind == 59)
            return 1;
        if (kind == 39)
            return 1;
        if (kind == 8)
            return 1;
        if (kind == 53)
            return 1;
        if (kind == 145)
            return 1;
    } else if (phase == 8) {
        if (kind == 1) {
            fn_800CC860(context, 1, 0);
            fn_800CA2C8(context);
            return 1;
        }
        if (kind == 3) {
            fn_8003E5DC(context, object, id, target);
            return 1;
        }
        if (kind == 249) {
            fn_800E2150(id, context, target, object);
            return 1;
        }
        if (kind == 61) {
            if (result != 0)
                *result = fn_802011D4(message) & 0xFFFFFFFF;
            fn_8020123C(57, id, id, 0);
            return 1;
        }
        if (kind == 17) {
            fn_800EA3A0(context, target);
            fn_80201D34(context, 0x15);
            fn_80201D1C(context, 1);
            fn_800E2344(id, object);
            return 1;
        }
        if (kind == 2) {
            fn_802006D4(id, id, 8, 0x11, 0);
            return 1;
        }
        if (kind == 59)
            return 1;
        if (kind == 39)
            return 1;
        if (kind == 8)
            return 1;
        if (kind == 53)
            return 1;
        if (kind == 145)
            return 1;
    } else {
        return 0;
    }
    return 0;
}
