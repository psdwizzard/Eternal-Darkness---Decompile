typedef unsigned int u32;
typedef unsigned short u16;

/* NonMatching: behavior-complete, size- and relocation-exact reconstruction.
 * Retail reuses the known-zero secondary flag with `mr r0,r25`; GC/1.3 emits
 * the equivalent immediate materialization `li r0,0`. */

typedef struct Vec3 {
    u32 x;
    u32 y;
    u32 z;
} Vec3;

typedef struct PresetSet {
    Vec3 third;
    Vec3 second;
    Vec3 first;
} PresetSet;

extern Vec3 lbl_802478D0[];
extern u32 lbl_80651A58;
extern u32 lbl_8064F13C;
extern u32 lbl_8064F138;

extern u32 fn_801578AC(void *);
extern u16 fn_80157994(void *);
extern void fn_8012C478(void *, int, int);
extern int fn_8011EB04(void *);
extern void fn_8012CBE8(void *, int, Vec3 *, Vec3 *, Vec3 *, int);
extern void fn_8012F58C(void *, int, int, int, int, int);
extern void* fn_8012C62C(void *, int, u32 *, u32 *, u32 *, int);

void fn_800BFFDC(void *object, void *state, int enabled)
{
    Vec3 *presets = lbl_802478D0;
    u32 kind = fn_801578AC(state);
    int is_secondary;
    int is_primary = kind == 0x10;

    if (!is_primary) {
        fn_8012C478(object, 0x10, enabled);
    }

    is_secondary = 0;
    {
        int relevant = is_secondary;
        if (kind == 0x40 || kind == 0x80) {
            relevant = 1;
        }
        if (relevant) {
            int selected = 0;
            if (fn_80157994(state) >= 2 || enabled == 0) {
                selected = 1;
            }
            if (selected) {
                is_secondary = 1;
            }
        }
    }

    if (is_primary || is_secondary) {
        fn_8012C478(object, 0x11, enabled);
    }

    if (fn_8011EB04(object) != 0xC6) {
        if (enabled != 0) {
            if (!is_primary) {
                PresetSet values = *(PresetSet *)&presets[2];
                fn_8012CBE8(object, 0x10, &values.first, &values.second, &values.third, 0);
                fn_8012F58C(object, 0x10, 1, 0, 0, 4);
            }
            if (is_primary || is_secondary) {
                PresetSet values = *(PresetSet *)&presets[2];
                fn_8012CBE8(object, 0x11, &values.first, &values.second, &values.third, 0);
                fn_8012F58C(object, 0x11, 1, 0, 0, 4);
            }
        }
    } else if (enabled != 0) {
        u32 first;
        u32 second;
        u32 third;
        third = lbl_80651A58;
        second = lbl_8064F13C;
        first = lbl_8064F138;
        fn_8012C62C(object, 0x10, &first, &second, &third, 4);
        fn_8012F58C(object, 0x10, 0, 0, 0, 0);
    }
}
