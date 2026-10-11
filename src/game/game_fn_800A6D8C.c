typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { u8 pad[0xB6]; u16 value; } StateBits;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Runtime Runtime;
typedef struct Entry80201814 Entry80201814;
typedef struct MessageTable {
    char idle[0x1C];
    char fade[0xC];
    char exit[0x18];
    char stand[0x14];
} MessageTable;

extern int fn_80035FB8();
extern int fn_80036E50();
extern int fn_80048A60();
extern void fn_80048A68();
extern void fn_80064B38();
extern int fn_800654F8();
extern void fn_80066754();
extern void fn_800A5390();
extern void fn_800A6AB8();
extern int fn_800AD208();
extern void fn_800AD210();
extern void fn_800AD218();
extern void fn_800C030C(void *, void *, float);
extern void fn_800C16F4();
extern int fn_800C3D94();
extern void fn_800C63D8();
extern void fn_800C6C60();
extern void fn_8011F114();
extern void *fn_8011F130();
extern void fn_8011FE64();
extern void fn_801287C4();
extern Runtime *fn_80128E30();
extern u8 fn_80128EE4();
extern u8 *fn_801294DC();
extern int fn_8012A1BC();
extern void fn_8012B344();
extern void fn_8016B400();
extern void fn_801A5910();
extern void fn_801A7228();
extern void fn_801A7470();
extern u32 fn_801A7490();
extern u32 fn_801A7498();
extern void fn_801A74A8();
extern u16 fn_801A7530(StateBits *);
extern void fn_801A7538(StateBits *, u16);
extern void fn_801E7974();
extern void fn_801E79A0();
extern int fn_80200C10();
extern int fn_80200C20();
extern int fn_80200C28();
extern void *fn_80200C38();
extern unsigned long long fn_8020123C();
extern Entry80201814 *fn_80201814();
extern int fn_80201B44();
extern int fn_80201B54();
extern void *fn_80201B8C();
extern void *fn_80201B94();
extern void *fn_80201BC8();
extern void fn_80201D14();
extern void fn_80201D1C();
extern void fn_80201D2C();
extern void fn_80201D34();
extern void fn_80201DD8();
extern u8 fn_80204578();
extern int fn_800C2180(int, int);
extern int fn_80204810(void *, int);
extern MessageTable lbl_80245738;
extern char lbl_8064B640[4];
extern char lbl_8064B644[8];
extern char lbl_8064B64C[8];
extern int lbl_8064B81C;
extern void *lbl_8064C4E0;
extern float lbl_8064EF04;

int fn_800A6D8C(int actor, int mode, void *event, int *out) {
    Vec3 position;
    int event_id;
    void *action;
    MessageTable *names;
    void *record;
    void *state;
    int model;

    names = &lbl_80245738;
    event_id = fn_80200C10(event);
    action = fn_80201BC8(actor);
    state = fn_80201B94(actor);
    model = fn_80201B54(actor);
    record = fn_80201B8C(actor);
    fn_8011F114(&position, action);

    if (mode == 0) {
        if (event_id == 1) {
            fn_80201D2C(actor, 1);
            fn_80201D14(actor, 1);
            fn_8011FE64(action, fn_800C2180);
            return 1;
        }
        if (event_id == 0xF0) {
            int target;
            fn_80201B54(actor);
            target = (int)fn_80200C38(event);
            fn_80201D34(actor, target);
            fn_80201D1C(actor, 1);
            if (out != 0) *out = 1;
            return 1;
        }
        if (event_id == 0xBB) {
            int target = (int)fn_80200C38(event);
            if (target != 0) fn_801E7974(lbl_8064C4E0, target);
            return 1;
        }
        if (event_id == 0x86) {
            fn_801A5910(fn_80200C38(event));
            return 1;
        }
        if (event_id == 0xBC) {
            int target = (int)fn_80200C38(event);
            if (target != 0) fn_801E79A0(lbl_8064C4E0, target);
            return 1;
        }
        if (event_id == 0xBE) {
            int target = (int)fn_80200C38(event);
            if (target != 0) fn_8016B400(target, model, 0);
            return 1;
        }
        /* These terminal events reuse the actor and event ID slots for payload IDs. */
        if (event_id == 0xED) {
            actor = (int)fn_80200C38(event);
            event_id = fn_80200C28(event);
            fn_8020123C(0xB, fn_80200C20(event), event_id, actor);
            fn_801A7228(fn_80200C38(event));
            return 1;
        }
        if (event_id == 0x3A) {
            actor = (int)fn_80200C38(event);
            event_id = fn_80200C28(event);
            fn_8020123C(0x27, fn_80200C20(event), event_id, actor);
            fn_801A7228(fn_80200C38(event));
            return 1;
        }
        if (event_id == 0xB) {
            int result = 0;
            int fallback = 1;
            if ((u32)fn_800AD208() == (u32)actor) {
                void *target = fn_80200C38(event);
                u32 other = fn_801A7498(target);
                Entry80201814 *current = fn_80201814(other);
                void *other_action = current != 0 ? fn_80201BC8(current) : 0;
                if ((int)other != 0) {
                    int selection = 0;
                    int kind;
                    int old_value;
                    int new_value;
                    if (other_action != 0 && fn_80204578(actor, fn_8011F130(other_action)) == 0)
                        selection = 1;
                    kind = 0xB;
                    if (selection) kind = 0xC;
                    fn_800C6C60(actor, action, record, 0);
                    fn_800AD210(0);
                    fn_800AD218(-1, -1);
                    fallback = 0;
                    result = 5;
                    old_value = fn_801A7490(target);
                    new_value = fn_80201B44();
                    fn_801A7470(target, kind);
                    fn_801A74A8(target, new_value);
                    fn_8020123C(0x35, other, new_value, target);
                    fn_801A74A8(target, old_value);
                }
            }
            if (fallback) result = fn_800654F8(fn_80200C38(event));
            if (out != 0) *out = result;
            return 1;
        }
        if (event_id == 0x35) {
            fn_80066754(actor, event, out);
            return 1;
        }
        if (event_id == 0x2B) {
            fn_800C3D94(actor, event, out);
            return 1;
        }
        if (event_id == 0x29) {
            void *target = fn_80200C38(event);
            fn_80201DD8(state, 0);
            fn_800C63D8();
            fn_800C16F4(actor, target, 1, 0);
            return 1;
        }
        if (event_id == 0x2A) {
            void *target = fn_80200C38(event);
            if (fn_80048A60() == 0) {
                fn_80201DD8(state, 0);
                fn_80048A68(1);
                fn_800C63D8();
            }
            fn_800C16F4(actor, target, 1, 1);
            return 1;
        }
        if (event_id == 8) return 1;
        if (event_id == 0x2D) {
            if (fn_80128EE4(action) != 0x10)
                fn_801294DC(action, 0xF, 0x21, 1);
            return 1;
        }
        if (event_id == 0x2C) {
            fn_800C030C((void *)actor, event, lbl_8064EF04);
            return 1;
        }
        if (event_id == 0x28) {
            fn_800A6AB8(actor, action, event);
            return 1;
        }
        if (event_id == 0x27) {
            StateBits *target = fn_80200C38(event);
            u16 flags = fn_801A7530(target);
            if (flags & 1) {
                fn_801A7538(target, 1);
                fn_80064B38(actor, event, out);
                fn_801A7538(target, flags);
            }
            return 1;
        }
        if (event_id == 0x3B) {
            int target = fn_80200C20(event);
            Entry80201814 *entry = fn_80201814(target);
            if (entry != 0 && fn_80036E50(entry) == 6) {
                if (out != 0) *out = 0;
            } else if (out != 0) {
                *out = lbl_8064B81C;
            }
            return 1;
        }
        if (event_id == 0x82) {
            if (out != 0) *out = 1;
            return 1;
        }
    } else if (mode != 1) {
        if (mode == 7) {
            if (event_id == 0x36) {
                fn_80201D2C(actor, 1);
                fn_80201D14(actor, 1);
                return 1;
            }
            if (event_id == 7) {
                if (fn_80035FB8(actor, names->idle, lbl_8064B640, names->fade, lbl_8064B644, names->exit) == 0) {
                    fn_80201D2C(actor, 1);
                    fn_80201D14(actor, 1);
                }
                return 1;
            }
            if (event_id == 2) return 1;
            if (event_id == 0x29) return 1;
            if (event_id == 0x2A) return 1;
            if (event_id == 0x2B) return 1;
            if (event_id == 0x2D) return 1;
            if (event_id == 0x2C) return 1;
            if (event_id == 0x28) return 1;
        } else if (mode == 6) {
            if (event_id == 0xC) {
                fn_80201D2C(actor, 1);
                fn_80201D14(actor, 1);
                return 1;
            }
            if (event_id == 7) {
                if (fn_80035FB8(actor, names->stand, lbl_8064B64C, names->fade, lbl_8064B644, names->exit) == 0) {
                    fn_80201D2C(actor, 1);
                    fn_80201D14(actor, 1);
                }
                return 1;
            }
            if (event_id == 0xD) {
                fn_80201D2C(actor, 1);
                fn_80201D14(actor, 1);
                fn_8012B344(action);
                return 1;
            }
            if (event_id == 0x29) return 1;
            if (event_id == 0x2A) return 1;
            if (event_id == 0x2B) return 1;
            if (event_id == 0x2D) return 1;
            if (event_id == 0x2C) return 1;
            if (event_id == 0x2E) return 1;
            if (event_id == 0x28) return 1;
        } else if (mode == 8) {
            if (event_id == 1) {
                int size = fn_8012A1BC(action, 0x18);
                Runtime *queue = fn_80128E30(action);
                fn_801287C4(queue, fn_80204810, ((u32)model << 8) | 6, size - 1);
                return 1;
            }
            if (event_id == 6) {
                fn_800A5390(actor, action, record, event, 1, 1, 0);
                return 1;
            }
            if (event_id == 0x20) return 1;
            if (event_id == 0x6B) return 1;
            if (event_id == 0x3F) return 1;
            if (event_id == 0x1E) return 1;
            if (event_id == 0x35) return 1;
            if (event_id == 0x37) return 1;
            if (event_id == 0x32) return 1;
            if (event_id == 8) return 1;
            if (event_id == 0xB) return 1;
            if (event_id == 0x27) return 1;
            if (event_id == 0x69) return 1;
            if (event_id == 0x87) return 1;
            if (event_id == 2) return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
