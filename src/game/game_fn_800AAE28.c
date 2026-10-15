typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Color;

typedef struct Descriptor {
    unsigned int word;
    unsigned short half;
} Descriptor;

typedef struct EffectDescriptor {
    unsigned char unk00;
    unsigned char unk01;
    unsigned char pad02;
    signed char unk03;
    unsigned short unk04;
    unsigned char pad06[0x12];
    int unk18;
    unsigned char pad1C[0x74];
} EffectDescriptor;

typedef struct EffectState {
    unsigned char pad0[0x78];
    void* list[8];
    int count;
    int unk9C;
    int timer;
    signed char active;
    unsigned char padA5;
    unsigned char flags;
    signed char dispatched;
    signed char unkA8;
} EffectState;

typedef struct ObjExtra {
    unsigned char pad0[0xA0];
    Vec3 home;
} ObjExtra;

typedef struct ObjInfo {
    unsigned char pad0[0x5C];
    EffectState* effect;
    unsigned char pad60[0x2C];
    ObjExtra* extra;
} ObjInfo;

extern int fn_80200C10(void*);
extern int fn_80200C20();
extern int fn_80200C28();
extern int fn_80200C38();
extern Vec3* fn_8011F130();
extern void* fn_80201BC8();
extern ObjInfo* fn_80201B8C();
extern void* fn_80201B94();
extern int fn_80201B54();
extern int fn_80201B44();
extern void fn_80201C48();
extern int fn_80047304();
extern void fn_80047258();
extern void fn_801F49EC(Vec3, float, float);
extern int fn_80038308();
extern void fn_8020104C(int, int, int, int, float);
extern int fn_800389E0();
extern void fn_80201D2C();
extern void fn_80201D14();
extern void* fn_80201814();
extern int fn_80036E50();
extern int fn_800AD3A4();
extern void fn_8016B400();
extern unsigned long long fn_8020123C();
extern void fn_801A7228();

extern void fn_801D38BC();
extern void fn_80152404(Vec3*, short, int, int, Color);
extern void fn_80211A90(Vec3*, Vec3*, float);
extern void fn_80211A48(Vec3*, Vec3*, Vec3*);
extern int fn_801D3A24();
extern void fn_80152A88();
extern int fn_800AD1D0();
extern void fn_800337C8();
extern void* fn_800CF3D4();
extern void fn_8011FA8C();
extern void fn_800AD244();
extern void fn_8012B324();
extern void fn_80201D34();
extern void fn_80201D1C();
extern void fn_801E8328();
extern void fn_8012C62C(void*, int, Color, Color, Color, int);
extern void fn_802006D4();
extern void fn_800BE894();
extern int fn_800AA8A0();
extern void fn_8014F65C(Vec3*, float, int, short, int, Color);
extern int fn_800AD230();
extern void fn_8015E9EC();
extern void fn_8015DAB0();
extern void fn_800472B0();
extern int fn_801A98F4();
extern void fn_80006954();
extern void* fn_80201B3C();
extern void fn_800C9A2C();
extern void fn_8015C7D8();

extern int fn_801A9EF4();
extern void* fn_80050950();
extern void fn_801D0F70();
extern void fn_801AAE68(float, int, int, int, Vec3*, int, int, int, int, int);
extern void fn_800AA94C();
extern void fn_800AAAB8();
extern void fn_800AAB90();
extern void fn_80179DB0();
extern void fn_80181F5C();
extern void fn_80181FD8(void);
extern void* fn_80148008(Vec3, Descriptor*, EffectDescriptor*, void (*)(void));
extern unsigned int lbl_80651A44;
extern unsigned short lbl_80651A48;
extern const float lbl_8064EF58;
extern const float lbl_8064EFD4;
extern const float lbl_8064EFD8;
extern const float lbl_8064EFDC;
extern const float lbl_8064EFE0;
extern const float lbl_8064EFE4;
extern const float lbl_8064EFE8;
extern const float lbl_8064EFEC;
extern void fn_801A7588();
extern int fn_800654F8();
extern int fn_8011EB04();
extern int fn_801A74C0();
extern void* fn_801A7778();
extern unsigned char fn_801A7934();
extern void* fn_800AD208();
extern int fn_800C5FA4();
extern void fn_800A7F8C();
extern int fn_800C6890();
extern void fn_800AD210();
extern int fn_802020B4();
extern int fn_80201AE4();
extern void fn_80045A24();
extern void fn_801B05E8();
extern void fn_800AD034();
extern void fn_800C6C60();
extern void fn_800A7E88();
extern int fn_80201890();
extern void* fn_801A717C();
extern void fn_801A7470();
extern void fn_801A74A0();
extern void fn_801A74A8();
extern int fn_800F5C54(float);
extern void fn_800AAD14();
extern void fn_8012DBE8();
extern void fn_8011F0E8();
extern void fn_80048708();
extern void fn_8014F5B8(Vec3*, float, int, short, int, Color);
extern unsigned int fn_8011FAEC();
extern void fn_8011FADC();
extern void fn_800CA2C8();
extern void fn_80204FDC();

typedef struct TableEntry {
    int unk0;
    int unk4;
    int unk8;
} TableEntry;

extern TableEntry lbl_8023BA64[];
extern int lbl_8064C98C;
extern int lbl_8064C970;
extern Color lbl_8064EF9C;
extern Color lbl_8064EFA0;
extern Color lbl_80651A4C;
extern const float lbl_8064EF18;
extern const float lbl_8064EF34;
extern const float lbl_8064EF54;
extern const float lbl_8064EF60;
extern const float lbl_8064EFAC;
extern const float lbl_8064EFB0;
extern const float lbl_8064EFB4;
extern const float lbl_8064EFB8;
extern const float lbl_8064EFBC;
extern const float lbl_8064EFC0;

extern void* lbl_8064C4E4;
extern int lbl_8064C990;
extern float lbl_8064B674;
extern unsigned char lbl_8064C95C;
extern int lbl_8064C980;
extern int* lbl_8064C5A8;
extern int lbl_8064C984;
extern int lbl_8064D18C;
extern int lbl_8064C974;
extern int lbl_8064C968;
extern int lbl_8064C960;
extern Vec3 lbl_80239778;
extern Color lbl_8064EF80;
extern Color lbl_8064EF84;
extern Color lbl_8064EF88;
extern Color lbl_8064EF8C;
extern Color lbl_8064EF90;
extern Color lbl_8064EF94;
extern Color lbl_8064EF98;
extern Color lbl_80651A3C;
extern Color lbl_80651A40;
extern const float lbl_8064EF5C;
extern const float lbl_8064EF64;
extern const float lbl_8064EFA4;
extern const float lbl_8064EFA8;
extern const float lbl_8064EFC4;
extern const float lbl_8064EFC8;
extern const float lbl_8064EFCC;
extern const float lbl_8064EFD0;

int fn_800AAE28(void* obj, int mode, void* evt, int* out)
{
    int hi;
    int lo;
    int type;
    ObjExtra* extra;
    void* target;
    ObjInfo* info;
    Vec3* tpos;
    EffectState* effect;
    void* r18val;
    int owner;
    Vec3* pos;

    type =fn_80200C10(evt);
    pos = fn_8011F130(lbl_8064C4E4);
    target = fn_80201BC8(obj);
    info = fn_80201B8C(obj);
    extra = info->extra;
    effect = info->effect;
    r18val = fn_80201B94(obj);
    owner = fn_80201B54(obj);
    lbl_8064C990 = owner;
    tpos = fn_8011F130(target);
    fn_80201C48(r18val);
    if (fn_80047304() != 0) {
        fn_801F49EC(*pos, lbl_8064EFA4, lbl_8064B674);
    } else {
        fn_80047258(1);
    }

    if (mode == 0) {
        if (type == 1) {
            short sp16;
            fn_80038308(obj, 0, &sp16);
            effect->active = 1;
            effect->dispatched = 0;
            effect->unkA8 = -1;
            effect->timer = 10000;
            fn_8020104C(0x69, owner, owner, 1, lbl_8064EFA8);
            fn_800389E0(obj, 0, 0x78, 0);
            lbl_8064C95C = 1;
            fn_80201D2C(obj, 1);
            fn_80201D14(obj, 1);
            return 1;
        }
        if (type == 0x3b) {
            int who = fn_80200C20(evt);
            void* other = fn_80201814();
            if (who == fn_80201B44() && effect->active == 1 && other != 0 &&
                fn_80036E50(other) != 6 && out != 0) {
                *out = 1;
            }
            return 1;
        }
        if (type == 0x27) {
            return 1;
        }
        if (type == 8) {
            if (fn_800AD3A4() == 0) {
                effect->timer = 10000;
                fn_80201D2C(obj, 1);
                fn_80201D14(obj, 1);
                fn_8016B400(0x8b6, lbl_8064C980, 0);
            }
            return 1;
        }
        if (type == 0xed) {
            fn_8020123C(0xb, fn_80200C20(evt), fn_80200C28(evt), fn_80200C38(evt));
            fn_801A7228(fn_80200C38(evt));
            return 1;
        }
        if (type == 0x3a) {
            fn_8020123C(0x27, fn_80200C20(evt), fn_80200C28(evt), fn_80200C38(evt));
            fn_801A7228(fn_80200C38(evt));
            return 1;
        }
        if (type == 0xb) {
            if (fn_800AD3A4() == 0 && effect->active == 1) {
                unsigned short sndId;
                Vec3* tgtPos;
                int ok;
                void* ctrl;
                int evtArg;
                int result;

                sndId = fn_801A9EF4(0x28, 0x2d);
                tgtPos = fn_8011F130(target);
                ok = 0;
                ctrl = fn_80050950();
                evtArg = fn_80200C38(evt);
                fn_801D0F70(0);
                fn_801AAE68(lbl_8064EF54, sndId, 0x78, 0, tgtPos, 2, 2, 0, (unsigned short)lbl_8064D18C, 0);
                fn_801A7588(evtArg, 0x8000);
                result = fn_800654F8(evtArg);

                if (ctrl != 0 && fn_8011EB04(ctrl) == 1 &&
                    !(fn_801A74C0(evtArg) & 0x10000) && fn_801A7778(evtArg) != 0) {
                    int id = fn_801A7934(evtArg);
                    if (id == fn_800AD1D0(1)) {
                        ok = 1;
                    }
                } else if (fn_800AD208() != 0) {
                    ok = 1;
                }
                if (fn_800C5FA4() != 0) {
                    ok = 0;
                }

                if (ok != 0 && (result & 5)) {
                    int msg = 0;
                    float scale = lbl_8064EFAC;
                    int count = 0;
                    int bonus = 0;
                    int doSelect = 0;
                    int doSfx = 0;
                    int arg4 = 0x23;
                    int arg3 = 4;
                    int slot = -1;
                    int doNotify = 0;
                    int handle;

                    switch (lbl_8064C974) {
                    case 0:
                    case 1:
                        break;
                    case 2:
                        fn_800A7F8C(owner, tpos, 0x32, 5);
                        effect->timer = 1000;
                        scale = lbl_8064EF18;
                        count = 1;
                        arg4 = 0x32;
                        arg3 = 2;
                        msg = 0x11;
                        fn_80201D2C(obj, 0x26);
                        fn_80201D14(obj, 1);
                        fn_8020104C(0xf2, owner, owner, 0, lbl_8064EFA8);
                        fn_80006954(0x14);
                        break;
                    case 3:
                        fn_800A7F8C(owner, tpos, 0x32, 5);
                        effect->timer = 1000;
                        scale = lbl_8064EF18;
                        count = 2;
                        arg4 = 0x46;
                        arg3 = 2;
                        msg = 0x11;
                        fn_80201D2C(obj, 0x26);
                        fn_80201D14(obj, 1);
                        fn_8020104C(0xf2, owner, owner, 1, lbl_8064EFA8);
                        fn_80006954(0x23);
                        break;
                    case 4:
                        effect->timer = 1000;
                        scale = lbl_8064EFB0;
                        slot = 0;
                        count = 3;
                        arg4 = 0x5a;
                        arg3 = 2;
                        msg = 0x19;
                        fn_8020123C(0xc3, owner, lbl_8064C98C, 0x46);
                        fn_8020104C(0xf2, owner, owner, 4, lbl_8064EF34);
                        fn_80006954(0x41);
                        break;
                    case 5:
                    case 7:
                    case 9:
                    case 11:
                    case 13:
                    case 15:
                        count = 3;
                        msg = 0x1c;
                        arg3 = 2;
                        lbl_8064C974++;
                        doSfx = 1;
                        doNotify = 1;
                        fn_801A98F4(0x2ab, 0x64);
                        fn_800AD210(fn_800C6890(lbl_8064C974, 1));
                        break;
                    case 6:
                        slot = 1;
                    case 8:
                        slot = (slot == -1) ? 2 : slot;
                    case 12:
                        slot = (slot == -1) ? 4 : slot;
                    case 14:
                        slot = (slot == -1) ? 5 : slot;
                        count = 3;
                        doSelect = 1;
                        lbl_8064C974++;
                        doSfx = 1;
                        doNotify = 1;
                        arg3 = 3;
                        msg = 0x11;
                        break;
                    case 10: {
                        int actor;
                        bonus = lbl_8023BA64[*lbl_8064C5A8].unk8 + 7;
                        slot = 3;
                        count = 5;
                        lbl_8064C974++;
                        doSfx = 1;
                        arg3 = 3;
                        msg = 0x11;
                        doSelect = 1;
                        doNotify = 1;
                        actor = fn_80201AE4(fn_802020B4(lbl_8064C970, 0));
                        fn_8020123C(0xfa, actor, actor, 0xc);
                        fn_8020104C(0xfa, actor, actor, 0xd, lbl_8064EFAC);
                        fn_80045A24(1, 0);
                        fn_8020123C(0xc3, owner, lbl_8064C98C, 0x7d);
                        fn_8020104C(0x8d, owner, lbl_8064C98C, 1, lbl_8064EFB4);
                        fn_80006954(5);
                        break;
                    }
                    case 16:
                        lbl_8064C974++;
                        slot = 6;
                        count = 5;
                        doSelect = 1;
                        doNotify = 1;
                        msg = 0;
                        doSfx = 1;
                        arg3 = 3;
                        fn_80201D2C(obj, 0x26);
                        fn_80201D14(obj, 1);
                        fn_8020123C(0xc3, owner, lbl_8064C98C, 0x64);
                        fn_8020104C(0xbe, owner, owner, 0x8b6, lbl_8064EF60);
                        fn_80006954(0x41);
                        break;
                    }

                    if (doNotify != 0) {
                        fn_800C9A2C(fn_80201B3C());
                    }
                    if (doSfx != 0) {
                        fn_801B05E8(0x51, 0x64, 2, 1, pos, 2, 1, 0);
                    }
                    fn_800AD034(*lbl_8064C5A8, 2, arg3, arg4, 0x64, 0);
                    if (doSelect != 0) {
                        void* a = fn_80201BC8(lbl_8064C970);
                        ObjInfo* b = fn_80201B8C(lbl_8064C970);
                        fn_800C6C60(lbl_8064C970, a, b, 0);
                        fn_800AD210(0);
                        fn_801A98F4(0x2ab, 0x64);
                    }
                    while (count != 0) {
                        fn_800A7E88(tpos, 0xa0);
                        count--;
                    }
                    if (bonus != 0) {
                        int player = fn_80201B44();
                        fn_80006954(0x7d);
                        fn_8020104C(0xf2, owner, player, bonus | 0x80000000, lbl_8064EFB8);
                        if (scale < lbl_8064EFBC) {
                            scale = scale;
                        } else {
                            scale = lbl_8064EFBC;
                        }
                    }
                    handle = (int)fn_801A717C(fn_80201890(lbl_8064C98C));
                    fn_801A7470(handle, 0x9b);
                    fn_801A74A0(handle, owner);
                    fn_801A74A8(handle, lbl_8064C98C);
                    fn_8020123C(0x35, owner, lbl_8064C98C, handle);
                    fn_801A7228(handle);
                    if (lbl_8064EF18 != scale) {
                        fn_800472B0(1);
                        fn_801F49EC(*pos, lbl_8064EFA4, lbl_8064EFC0);
                        lbl_8064B674 = lbl_8064EFC0;
                        fn_80006954(fn_800F5C54(scale) + 5);
                        fn_8020104C(0xf2, owner, owner, 5, scale);
                    }
                    if (msg != 0) {
                        fn_8020123C(0x69, owner, owner, msg);
                    }
                    if (slot > -1) {
                        if (msg & 0x1a) {
                            effect->unkA8 = slot;
                        } else {
                            fn_8020123C(0x92, owner, owner, slot << 16);
                        }
                    }
                }
                if (out != 0) {
                    *out = result;
                }
            }
            return 1;
        }
        if (type == 0xbe) {
            int sub;
            if (fn_800AD3A4() == 0) {
                sub = fn_80200C38(evt);
                if (sub != 0) {
                    fn_8016B400(sub, owner, 0);
                }
            }
            return 1;
        }
        if (type == 0xfa) {
            switch (fn_80200C38(evt)) {
            case 6: {
                Vec3 p;
                Vec3 v;
                Color col;
                short ang;
                int fx;
                p = *tpos;
                p.z += lbl_8064EF5C;
                v = lbl_80239778;
                fn_801D38BC(*lbl_8064C5A8, &col, &ang);
                fn_80152404(&p, ang, 0xfa, 4, col);
                fn_80211A90(&v, &v, (float)lbl_8064C95C);
                fn_80211A48(&v, &p, &v);
                lbl_8064C95C++;
                fx = fn_801D3A24(*lbl_8064C5A8, 0x31);
                fn_80152A88(&p, &v, fx, 4);
                break;
            }
            case 11: {
                Vec3 p;
                int r;
                p = *tpos;
                r = fn_800AD1D0(0);
                p.z += lbl_8064EFC4;
                fn_800337C8(&p, 0, r, 0, 0x12c, 1);
                break;
            }
            case 4:
                if (lbl_8064C984 == 0) {
                    Vec3 p;
                    p = *tpos;
                    p.z += lbl_8064EFC4;
                    lbl_8064C984 = fn_80201B54(fn_800CF3D4(&p, -1, 0, lbl_8064D18C));
                }
                break;
            case 5:
                if (lbl_8064C984 != 0) {
                    fn_8020123C(0xc4, owner, lbl_8064C984, 0);
                }
                break;
            case 8:
                fn_8011FA8C(target, 0x100, 0);
                break;
            case 9:
                fn_800AD244(obj);
                break;
            }
            return 1;
        }
        if (type == 0x35) {
            return 1;
        }
        if (type == 0x39) {
            fn_8012B324(target);
            fn_80201D34(obj, 0);
            fn_80201D1C(obj, 1);
            fn_801E8328(2, obj);
            return 1;
        }
        if (type == 0x10) {
            effect->timer = effect->unk9C;
            fn_8011FA8C(target, 0, 0xc0);
            if (!effect->active) {
                effect->active = 1;
                fn_8012C62C(target, 0xf, lbl_8064EF80, lbl_8064EF84, lbl_8064EF88, 4);
                if (effect->unkA8 != -1 && !effect->dispatched) {
                    fn_8020123C(0x92, owner, owner, effect->unkA8 << 16);
                }
            }
            return 1;
        }
        if (type == 0x11) {
            fn_8011FA8C(target, 0xc0, 0);
            if (effect->active == 1) {
                effect->active = 0;
                fn_8020123C(0x92, owner, owner, 0x29a);
                fn_8012C62C(target, 0xf, lbl_8064EF8C, lbl_8064EF90, lbl_80651A3C, 4);
            }
            return 1;
        }
        if (type == 0x69) {
            int flags;
            flags = fn_80200C38(evt);
            fn_802006D4(owner, owner, -1, 0x92, 0);
            effect->dispatched = 0;
            fn_800BE894();
            effect->flags = flags;
            extra->home = *tpos;
            if (flags & 0x10) {
                Vec3 tmp;
                if (fn_800AA8A0(&tmp, &lbl_8064C980)) {
                    extra->home = tmp;
                }
            }
            if (effect->active == 1) {
                if (flags & 4) {
                    Color col;
                    short ang;
                    fn_801D38BC(fn_800AD1D0(0), &col, &ang);
                    fn_8014F65C(tpos, lbl_8064EFC8, 0x64, ang, 0, col);
                }
                if (flags & 5) {
                    fn_8012C62C(target, 0xf, lbl_8064EF94, lbl_8064EF98, lbl_80651A40, 4);
                    fn_8011FA8C(target, 0xc0, 0);
                }
            }
            fn_80201D2C(obj, 0x30);
            fn_80201D14(obj, 1);
            return 1;
        }
        if (type == 0xf2) {
            if (fn_800AD3A4() == 0) {
                Vec3* curPos;
                int sub;

                sub = fn_80200C38(evt);
                curPos = fn_8011F130(lbl_8064C4E4);
                switch (sub) {
                case 0: {
                    effect->timer = 0;
                    lbl_8064C974 = 3;
                    fn_8015E9EC(0xDBCAA0, lbl_8064C968, fn_800AD230());
                    fn_8015DAB0(lbl_8064C968);
                    lbl_8064C960 = 1;
                    fn_800472B0(1);
                    fn_801A98F4(0x218, 0x3c);
                    fn_801A98F4(0x2a6, 0x64);
                    fn_801F49EC(*curPos, lbl_8064EFA4, lbl_8064EFCC);
                    lbl_8064B674 = lbl_8064EFCC;
                    fn_80006954(0x14);
                    fn_8020104C(0xf2, owner, owner, 2, lbl_8064EFD0);
                    break;
                }
                case 1: {
                    int first;
                    effect->timer = 0;
                    lbl_8064C974 = 4;
                    first = fn_800AD230();
                    fn_8015E9EC(fn_800AD230() + 0xDBCAA0, lbl_8064C968, first);
                    fn_8015DAB0(lbl_8064C968);
                    lbl_8064C960 = 1;
                    fn_800472B0(1);
                    fn_801A98F4(0x218, 0x64);
                    fn_801A98F4(0x2a6, 0x64);
                    fn_801F49EC(*curPos, lbl_8064EFA4, lbl_8064EFCC);
                    lbl_8064B674 = lbl_8064EFCC;
                    fn_80006954(0x23);
                    fn_8020104C(0xf2, owner, owner, 3, lbl_8064EF64);
                    break;
                }
                case 4: {
                    void* ctx;
                    int player;
                    ctx = fn_80201B3C();
                    player = fn_80201B44();
                    effect->timer = 0;
                    lbl_8064C974 = 5;
                    fn_800472B0(0);
                    fn_800C9A2C(ctx);
                    fn_8016B400(0x724, 0, 0);
                    fn_8020104C(0xfa, owner, player, 2, lbl_8064EFA8);
                    fn_80006954(5);
                    break;
                }
                case 2:
                    lbl_8064C960 = 0;
                    fn_800472B0(0);
                    break;
                case 3:
                    lbl_8064C960 = 0;
                    fn_800472B0(0);
                    fn_8015C7D8(5);
                    break;
                case 5:
                    fn_800472B0(0);
                    break;
                }
            }
            return 1;
        }
        if (type == 0x92) {
            int shifted;
            int packed;
            unsigned int arg;

            arg = fn_80200C38(evt);
            lo = arg & 0xFFFF;
            hi = arg >> 16;
            if (lo == 0) {
                effect->dispatched = 1;
                effect->unkA8 = hi;
            }
            if (lo == 0x29A || effect->active == 0) {
                effect->dispatched = 0;
            }
            if (effect->dispatched != 0) {
                fn_801AAE68(lbl_8064EF54, 0x289, 0x50, 0, tpos, 2, 2, 0,
                            (unsigned short)lbl_8064D18C, 0);
                switch (lo) {
                case 0:
                    fn_802006D4(owner, owner, -1, 0x92, 0);
                    switch (hi) {
                    case 0:
                        fn_800AA94C(owner, target, 0, 0, 0);
                        fn_8020104C(0x92, owner, owner, (hi << 16) | (int)lbl_8064EF58, lbl_8064EF58);
                        break;
                    case 1:
                        fn_800AA94C(owner, target, 0, 0, 0);
                        fn_8020104C(0x92, owner, owner, (hi << 16) | (int)lbl_8064EFB8, lbl_8064EFB8);
                        break;
                    case 2:
                        fn_800AA94C(owner, target, 0, 0, 0);
                        packed = (hi << 16) | (int)lbl_8064EFB8;
                        fn_8020104C(0x92, owner, owner, packed, lbl_8064EF60);
                        fn_8020104C(0x92, owner, owner, packed, lbl_8064EFB8);
                        break;
                    case 3:
                        fn_800AA94C(owner, target, 0, 0, 0);
                        shifted = hi << 16;
                        packed = shifted | (int)lbl_8064EFB8;
                        fn_8020104C(0x92, owner, owner, packed, lbl_8064EF60);
                        fn_8020104C(0x92, owner, owner, packed, lbl_8064EFB8);
                        fn_800AA94C(owner, target, 0x78, 0, 0);
                        fn_8020104C(0x92, owner, owner, shifted | (int)lbl_8064EF58, lbl_8064EF58);
                        break;
                    case 4:
                        fn_800AA94C(owner, target, 0, 0, 0);
                        shifted = hi << 16;
                        packed = shifted | (int)lbl_8064EFB8;
                        fn_8020104C(0x92, owner, owner, packed, lbl_8064EF60);
                        fn_8020104C(0x92, owner, owner, packed, lbl_8064EFB8);
                        fn_800AA94C(owner, target, 0xB4, 2, 0);
                        packed = shifted | (int)lbl_8064EFD4;
                        fn_8020104C(0x92, owner, owner, packed, lbl_8064EFB8);
                        fn_8020104C(0x92, owner, owner, packed, lbl_8064EFD4);
                        break;
                    case 5:
                        fn_800AA94C(owner, target, 0, 0, 0);
                        shifted = hi << 16;
                        packed = shifted | (int)lbl_8064EFB8;
                        fn_8020104C(0x92, owner, owner, packed, lbl_8064EF60);
                        fn_8020104C(0x92, owner, owner, packed, lbl_8064EFB8);
                        fn_800AA94C(owner, target, 0xB4, 2, 0);
                        packed = shifted | (int)lbl_8064EFD4;
                        fn_8020104C(0x92, owner, owner, packed, lbl_8064EFD8);
                        fn_8020104C(0x92, owner, owner, packed, lbl_8064EF5C);
                        fn_8020104C(0x92, owner, owner, packed, lbl_8064EFD4);
                        fn_800AAAB8(tpos, 0x12C, effect->list, &effect->count);
                        if (effect->count > 0) {
                            fn_800AAB90(owner, target, 0, 1, 0, effect->list, effect->count);
                            fn_8020104C(0x92, owner, owner, shifted | (int)lbl_8064EFAC, lbl_8064EFAC);
                        }
                        break;
                    case 6:
                        fn_800AA94C(owner, target, 0, 0, 1);
                        shifted = hi << 16;
                        packed = shifted | (int)lbl_8064EF60;
                        fn_8020104C(0x92, owner, owner, packed, lbl_8064EF64);
                        fn_8020104C(0x92, owner, owner, packed, lbl_8064EF60);
                        fn_800AA94C(owner, target, 0xB4, 3, 1);
                        packed = shifted | (int)lbl_8064EFE0;
                        fn_8020104C(0x92, owner, owner, packed, lbl_8064EFDC);
                        fn_8020104C(0x92, owner, owner, packed, lbl_8064EFE4);
                        fn_8020104C(0x92, owner, owner, packed, lbl_8064EFE0);
                        fn_800AAAB8(tpos, 0x12C, effect->list, &effect->count);
                        if (effect->count > 0) {
                            fn_800AAB90(owner, target, 0x1E, 2, 1, effect->list, effect->count);
                            packed = shifted | (int)lbl_8064EFB8;
                            fn_8020104C(0x92, owner, owner, packed, lbl_8064EFE8);
                            fn_8020104C(0x92, owner, owner, packed, lbl_8064EFEC);
                            fn_8020104C(0x92, owner, owner, packed, lbl_8064EFD8);
                            fn_8020104C(0x92, owner, owner, packed, lbl_8064EFB8);
                        }
                        break;
                    }
                    break;
                case 0x3C:
                    fn_800AA94C(owner, target, 0, 0, 1);
                    fn_8020104C(0x92, owner, owner, (hi << 16) | lo, (float)lo);
                    break;
                case 0x78:
                    switch (hi) {
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                        fn_800AA94C(owner, target, 0, 0, 0);
                        break;
                    case 6:
                        fn_800AAB90(owner, target, 0x1E, 2, 1, effect->list, effect->count);
                        break;
                    }
                    fn_8020104C(0x92, owner, owner, (hi << 16) | lo, (float)lo);
                    break;
                case 0xB4:
                    fn_800AAB90(owner, target, 0, 1, 0, effect->list, effect->count);
                    fn_8020104C(0x92, owner, owner, (hi << 16) | lo, (float)lo);
                    break;
                case 0xD2:
                    fn_800AA94C(owner, target, 0xB4, 3, 1);
                    fn_8020104C(0x92, owner, owner, (hi << 16) | lo, (float)lo);
                    break;
                case 0xF0:
                    switch (hi) {
                    case 4:
                    case 5:
                        fn_800AA94C(owner, target, 0xB4, 2, 0);
                        break;
                    }
                    fn_8020104C(0x92, owner, owner, (hi << 16) | lo, (float)lo);
                    break;
                case 0x12C:
                    switch (hi) {
                    case 0:
                        fn_800AA94C(owner, target, 0, 0, 0);
                        break;
                    case 3:
                        fn_800AA94C(owner, target, 0x78, 0, 0);
                        break;
                    }
                    fn_8020104C(0x92, owner, owner, (hi << 16) | lo, (float)lo);
                    break;
                }
            } else {
                fn_802006D4(owner, owner, -1, 0x92, 0);
            }
            return 1;
        }
        if (type == 0xF1) {
            Descriptor direction;
            Vec3 position;
            EffectDescriptor params;
            int idx;

            idx = fn_80200C38(evt);
            direction.word = lbl_80651A44;
            direction.half = lbl_80651A48;
            fn_80179DB0(&position, (unsigned char*)effect->list[idx] + 0x2C);
            fn_80181F5C(&params);
            params.unk01 = 4;
            params.unk03 = -20;
            params.unk18 = 0;
            params.unk04 = fn_801D3A24(*lbl_8064C5A8, 0x31);
            fn_80148008(position, &direction, &params, fn_80181FD8);
            return 1;
        }
    } else if (mode == 1) {
        if (type == 1) {
            return 1;
        }
        if (type == 2) {
            return 1;
        }
        if (type == 3) {
            fn_800AAD14(obj, target, evt);
            return 1;
        }
    } else if (mode == 0x26) {
        if (type == 1) {
            return 1;
        }
        if (type == 2) {
            return 1;
        }
        if (type == 0x27) {
            return 1;
        }
        if (type == 0xB) {
            return 1;
        }
        if (type == 8) {
            return 1;
        }
        if (type == 0xED) {
            fn_801A7228(fn_80200C38(evt));
            return 1;
        }
        if (type == 0x3A) {
            fn_8020123C(0x27, fn_80200C20(evt), fn_80200C28(evt), fn_80200C38(evt));
            fn_801A7228(fn_80200C38(evt));
            return 1;
        }
        if (type == 0x35) {
            return 1;
        }
        if (type == 0x69) {
            return 1;
        }
    } else if (mode == 0x30) {
        if (type == 1) {
            return 1;
        }
        if (type == 2) {
            return 1;
        }
        if (type == 3) {
            Color color;
            fn_8012DBE8(target, 0xF, &color);
            if (color.a <= 5 && !(effect->flags & 0x20)) {
                int doSend;
                doSend = (effect->active == 0);
                effect->flags |= 0x20;
                if (effect->flags & 0x10) {
                    fn_8011F0E8(target, &extra->home);
                }
                fn_80048708(target);
                if (effect->flags & 5) {
                    doSend = 1;
                    effect->active = 0;
                }
                if (effect->flags & 0xA) {
                    doSend = 0;
                    fn_8020104C(0x10, owner, owner, 0, lbl_8064EF64);
                }
                if (effect->flags & 8) {
                    Color rgba;
                    short sndId;
                    fn_801D38BC(fn_800AD1D0(0), &rgba, &sndId);
                    fn_8014F5B8(tpos, lbl_8064EFC8, 0x64, sndId, 0, rgba);
                }
                if (doSend) {
                    fn_8020123C(0x92, owner, owner, 0x29A);
                    fn_80201D2C(obj, 1);
                    fn_80201D14(obj, 1);
                }
            } else if (color.a >= 0xFB) {
                effect->timer = effect->unk9C;
                fn_80201D2C(obj, 1);
                fn_80201D14(obj, 1);
            }
            return 1;
        }
        if (type == 0x11) {
            return 1;
        }
        if (type == 0xB) {
            return 1;
        }
        if (type == 8) {
            return 1;
        }
        if (type == 0x27) {
            return 1;
        }
        if (type == 0x69) {
            return 1;
        }
    } else if (mode == 8) {
        if (type == 1) {
            if (target != 0) {
                unsigned int bits = fn_8011FAEC(target);
                fn_8011FADC(target, bits & ~0xC0);
            }
            fn_800CA2C8(obj);
            fn_80204FDC(obj);
            return 1;
        }
        if (type == 0x3D) {
            fn_8020123C(0x39, owner, owner, 0);
            return 1;
        }
        if (type == 0x11) {
            fn_8012C62C(target, 0xF, lbl_8064EF9C, lbl_8064EFA0, lbl_80651A4C, 4);
            fn_80201D34(obj, 0x15);
            fn_80201D1C(obj, 1);
            return 1;
        }
        if (type == 2) {
            fn_802006D4(owner, owner, 8, 0x11, 0);
            return 1;
        }
        if (type == 0x20) {
            return 1;
        }
        if (type == 0x6B) {
            return 1;
        }
        if (type == 0x3B) {
            return 1;
        }
        if (type == 0x3F) {
            return 1;
        }
        if (type == 0x1E) {
            return 1;
        }
        if (type == 0x35) {
            return 1;
        }
        if (type == 0x37) {
            return 1;
        }
        if (type == 0x32) {
            return 1;
        }
        if (type == 8) {
            return 1;
        }
        if (type == 0xB) {
            return 1;
        }
        if (type == 0x27) {
            return 1;
        }
        if (type == 0x69) {
            return 1;
        }
        if (type == 0x7D) {
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
