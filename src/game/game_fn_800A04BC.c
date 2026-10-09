typedef unsigned char u8;
typedef short s16;
typedef unsigned int u32;
typedef float f32;

typedef struct Vec3f {
    f32 x, y, z;
} Vec3f;

typedef struct Trigger {
    u8 pad00[0x15];
    u8 stage;
    u8 pad16[0x38 - 0x16];
    int targetId;
} Trigger;

typedef struct ScriptVar {
    u8 pad00[0x8];
    s16 timer;
    u8 pad0A[0x18 - 0xA];
    int flags;
} ScriptVar;

#define VAR_TOGGLED 0x10000
#define VAR_WARNED 0x20000

extern int lbl_8064D18C;
extern char lbl_802455E8[];
extern int lbl_8064EE38, lbl_8064EE3C, lbl_80651A08;
extern int lbl_8064EE40, lbl_8064EE44, lbl_80651A0C;
extern int lbl_8064EE48, lbl_8064EE4C, lbl_80651A10;
extern int lbl_8064EE50, lbl_8064EE54, lbl_80651A14;

extern int fn_802019EC(int, int);
extern void *fn_80201814(int);
extern void *fn_80201BC8(void *);
extern ScriptVar *fn_8006D1DC(int);
extern void fn_801E7DCC(char *, ...);
extern Vec3f *fn_8011F130(void *);
extern u32 fn_80178F14(int, int, int, int, int, int);
extern void fn_8012C62C(void *, int, int *, int *, int *, int);
extern void fn_8020123C(int, int, int, int);

int fn_800A04BC(Trigger *trigger)
{
    ScriptVar *var;
    int result;
    void *self;
    void *target;
    void *object;
    int id;

    result = 0;
    if (lbl_8064D18C == 0x4D) {
        id = fn_802019EC(0x848, lbl_8064D18C);
        object = fn_80201814(id);
        if (object == 0) {
            fn_801E7DCC(lbl_802455E8, 0);
            return 0;
        }
        self = fn_80201BC8(object);
        target = fn_80201BC8(fn_80201814(trigger->targetId));
        var = fn_8006D1DC(0x25);
        if (trigger->stage >= 2) {
            if (var->timer == 0) {
                Vec3f *a = fn_8011F130(self);
                Vec3f *b = fn_8011F130(target);
                if (a != 0 && b != 0) {
                    if (fn_80178F14((int)a->x, (int)a->y, (int)a->z,
                                    (int)b->x, (int)b->y, (int)b->z) < 1200) {
                        int c0, c1, c2;
                        c2 = lbl_8064EE3C;
                        c1 = lbl_8064EE38;
                        c0 = lbl_80651A08;
                        fn_8012C62C(self, 0xF, &c0, &c1, &c2, 4);
                        if (var->flags & VAR_TOGGLED) {
                            fn_8020123C(0x13, 0, id, 0);
                            var->flags &= ~VAR_TOGGLED;
                        } else {
                            fn_8020123C(0x12, 0, id, 0);
                            var->flags |= VAR_TOGGLED;
                        }
                        result = 1;
                        var->timer = 600;
                        var->flags &= ~VAR_WARNED;
                    } else if (!(var->flags & VAR_WARNED)) {
                        int c0, c1, c2;
                        c2 = lbl_80651A0C;
                        c1 = lbl_8064EE44;
                        c0 = lbl_8064EE40;
                        fn_8012C62C(self, 0xF, &c0, &c1, &c2, 4);
                        var->flags |= VAR_WARNED;
                    }
                }
            } else if (var->timer > 0) {
                var->timer--;
                if (var->timer == 460) {
                    int c0, c1, c2;
                    c2 = lbl_80651A10;
                    c1 = lbl_8064EE4C;
                    c0 = lbl_8064EE48;
                    fn_8012C62C(self, 0xF, &c0, &c1, &c2, 4);
                    var->flags |= VAR_WARNED;
                }
            }
        } else if (!(var->flags & VAR_WARNED)) {
            int c0, c1, c2;
            c2 = lbl_80651A14;
            c1 = lbl_8064EE54;
            c0 = lbl_8064EE50;
            fn_8012C62C(self, 0xF, &c0, &c1, &c2, 4);
            var->flags |= VAR_WARNED;
        }
    }
    return result;
}
