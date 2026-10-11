/* The body matches retail. MWCC emits GPR save/restore helper calls
 * in place of the retail stmw/lmw pair under the current compiler settings. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Vec3f { float x, y, z; } Vec3f;
typedef struct PathSource {
    char pad0[0xC];
    Vec3f *points;
} PathSource;
typedef struct Entry {
    int id;
    int unknown;
    u16 period;
    u16 reserved;
    Vec3f *points;
} Entry;
typedef struct ModeState {
    int first, second, mode;
} ModeState;

extern Entry lbl_80325DB8[10];
extern ModeState lbl_803003C8;
extern int lbl_8064CB08;
extern int lbl_8064D18C;
extern int lbl_8064D5A8;
extern const float lbl_8064F7C8;
extern const float lbl_8064F7CC;

extern u32 fn_8015C910(void);
extern void fn_800E77A8(u8, int, void *);
extern void *fn_80201814(int);
extern int fn_80201B64(void *);
extern int fn_80201B5C(void *);
extern Vec3f fn_800E720C(void *, PathSource *);
extern u32 fn_801DA0EC(u32);
extern s16 fn_800E7670(u8, Vec3f *, s16);
extern void *fn_80201BC8(void *);
extern void fn_800E7504(void *, u8, s16);
extern void fn_80120AD0(void *, const Vec3f *, u16, u32, float, float);
extern void fn_800E7770(u8);

void fn_800E6EB0(void)
{
    u8 index;
    Entry *entry;
    void *object;
    void *actor;
    Vec3f position;
    s16 count;

    if (lbl_8064CB08 == lbl_8064D18C) {
        if (fn_8015C910() == 0) {
            for (index = 0; index < 10; index++) {
                entry = &lbl_80325DB8[index];
                if (entry->id != 0) {
                    /* The path header stores its owner before the point array. */
                    fn_800E77A8(index, entry->id, *(void **)entry->points);
                    if (lbl_8064D5A8 % entry->period == 0) {
                        object = fn_80201814(entry->id);
                        if (object != 0) {
                            if (fn_80201B64(object) != 8 && fn_80201B5C(object) != 0x15) {
                                position = fn_800E720C(object, (PathSource *)entry);
                                switch (lbl_803003C8.mode) {
                                case 0:
                                    count = 5;
                                    break;
                                case 11:
                                    count = 4;
                                    break;
                                default:
                                    count = 4;
                                    break;
                                }
                                if ((int)fn_801DA0EC(entry->id) != 0) {
                                    count = fn_800E7670(index, &position, count);
                                }
                                actor = fn_80201BC8(object);
                                fn_800E7504(object, index, count);
                                if (actor != 0 && count > 0) {
                                    fn_80120AD0(actor, 0, 100, 0x102, lbl_8064F7C8, lbl_8064F7CC);
                                }
                            } else {
                                fn_800E7770(index);
                            }
                        } else {
                            fn_800E7770(index);
                        }
                    }
                }
            }
        }
    } else {
        lbl_8064CB08 = lbl_8064D18C;
    }
}
