typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef signed long s32;
typedef unsigned long u32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct EffectRec {
    Vec3 pos;
    s32 value;
    s32 intensity;
} EffectRec;
typedef struct Entry {
    u8 pad00[0xB];
    u8 count;
    EffectRec* effects;
    u8 pad10[4];
} Entry;
typedef struct Input {
    u8 pad00[8];
    Vec3 minimum;
    u8 pad14[0xC];
    Entry* entries;
} Input;
typedef struct Candidate {
    u8 pad00[0x18];
    s32 kind;
    u8 pad1C[0xD];
    u8 flags;
    s16 id;
    u8 pad2C;
    u8 subtype;
    u8 pad2E[6];
    EffectRec effect; /* Embedded record at 0x34. */
    u8 payload[0x18];
    Vec3 direction;
    u8 pad6C[0x10];
} Candidate;

extern s32 lbl_8064C388;
extern s32 lbl_8064CB48;
extern s32 lbl_8064D18C;
extern const double lbl_80651360;
extern const float lbl_8065134C;
extern const float lbl_806513C0;
extern const s32 lbl_806513BC;
extern const float lbl_806513C4;

extern s32 fn_801FD258(void);
extern Candidate** fn_801FD240(void);
extern s32 fn_801F15D0(Vec3*, s32, Input*, s32*, EffectRec*);
extern void fn_801F3FD8(Vec3*, s32);
extern s32 fn_801F1A24(s32);
extern void fn_801F0CB0(EffectRec*, Vec3*, void*, s32, u8, Vec3*, u8*);
extern void fn_800EBA80(s32, EffectRec*, s32*, float, s32);
extern s32 fn_8015E4E8(void);
extern void* fn_80201B3C(void);
extern void fn_80201BC8(void);
extern s32 fn_8011FB4C(void);
extern void fn_801F10BC(u32, u32, s32);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#pragma use_lmw_stmw on

s32 fn_801F1A38(Vec3* point, Vec3* target, Input* input, s32 group,
                 s32 requested, s32 flags, float scale)
{
    s32 effect_count = 0;
    EffectRec effects[8];
    Vec3 clamped;
    Vec3 fixed_color;
    Candidate candidate;
    s32 i;
    s32 extra_count;
    s32 scaled_count;
    Candidate** candidates;
    s32 active_mask = 0;
    s32 candidate_index = 0;
    s32 selected;
    s32 ordinary_mask = 0x10;
    s32 seen_mask = 0;
    s32 enabled_mask = 0;
    s32 cap;
    s32 special_mask = 0;
    s32 max_count;
    s32 special_seen = 0;
    s32 special_count;

    max_count = fn_801FD258();
    candidates = fn_801FD240();
    clamped = *point;
    clamped.x = MAX(input->minimum.x, clamped.x);
    clamped.y = MAX(input->minimum.y, clamped.y);
    clamped.z = MAX(input->minimum.z, clamped.z);
    selected = fn_801F15D0(&clamped, group, input, &effect_count, effects);
    if (selected == -1) {
        fn_801F3FD8(point, 3000);
        return 0;
    }
    if (effect_count > 4) effect_count = 4;

    cap = max_count;
    if (cap > lbl_8064C388) cap = lbl_8064C388;
    cap = MIN(cap, 3);

    for (i = 0; i < effect_count; i++) {
        active_mask |= 1 << i;
        if (flags & 1) {
            s32 minimum = fn_801F1A24(i);
            if (flags & 2) minimum *= 5;
            effects[i].intensity = MAX(minimum, effects[i].intensity);
            fn_801F0CB0(&effects[i], point, target, i, 0, 0, 0);
        } else {
            effects[i].intensity *= scale;
            fn_801F0CB0(&effects[i], point, target, i, 0, 0, 0);
        }
        if (lbl_8064CB48) {
            s32 color = effects[i].value;
            fn_800EBA80(2, &effects[i], &color,
                         (float)(effects[i].intensity / 100), 64);
        }
    }

    scaled_count = (s32)((float)effects[0].intensity * scale);
    special_count = MIN(3 - cap, input->entries[selected].count);
    if (requested == 1) special_count = 0;
    extra_count = MIN(requested, 4 - cap - special_count);
    extra_count = MIN(effect_count, extra_count);
    if (special_count > 0) special_mask = 0x10 << (cap + extra_count);
    if (cap > 0) {
        enabled_mask = seen_mask = 0x10 << extra_count;
    }

    for (i = 0; i < extra_count; i++) {
        ordinary_mask |= 0x10 << i;
        active_mask |= ordinary_mask;
        effects[i].intensity *= scale;
        fn_801F0CB0(&effects[i], point, target, i + 4, 1, 0, 0);
        if (lbl_8064CB48) {
            s32 color = effects[i].value;
            fn_800EBA80(2, &effects[i], &color,
                         (float)(effects[i].intensity / 100), 64);
        }
    }

    /* The cap counts accepted candidates. */
    for (i = 0; candidate_index < cap; i++) {
        candidate = *candidates[i];
        if (candidate.id == lbl_8064D18C &&
            (!fn_8015E4E8() || candidate.subtype == 7)) {
            s32 valid = 1;
            if (fn_80201B3C() && (candidate.flags & 8)) {
                fn_80201BC8();
                if (candidate.id != fn_8011FB4C()) valid = 0;
            }
            if (valid) {
                s32 slot = 4 + extra_count + candidate_index;
                seen_mask |= enabled_mask << candidate_index;
                active_mask |= seen_mask;
                candidate.effect.intensity = (s32)((float)candidate.effect.intensity * scale);
                if (candidate.kind == 1) {
                    fn_801F0CB0(&candidate.effect, point, target,
                                 slot, 0,
                                 &candidate.direction,
                                 candidate.payload);
                    candidate_index++;
                } else {
                    fn_801F0CB0(&candidate.effect, point, target,
                                 slot, 0,
                                 &candidate.direction, 0);
                    candidate_index++;
                }
                if (lbl_8064CB48) {
                    s32 color = candidate.effect.value;
                    fn_800EBA80(2, &candidate.effect, &color,
                                 (float)(candidate.effect.intensity / 100), 64);
                }
            }
        }
    }

    seen_mask |= 0xF;
    if (selected != -1) {
        for (i = 0; i < special_count; i++) {
            Entry* entry = &input->entries[selected];
            EffectRec* effect = &entry->effects[i];
            fixed_color.x = lbl_8065134C;
            fixed_color.y = lbl_8065134C;
            fixed_color.z = lbl_806513C0;
            special_seen |= special_mask << i;
            active_mask |= special_seen;
            fn_801F0CB0(effect, point, target, 4 + extra_count + cap + i,
                         0, &fixed_color, 0);
            if (lbl_8064CB48) {
                s32 color = lbl_806513BC;
                fn_800EBA80(1, effect, &color, lbl_806513C4, 64);
                {
                    s32 effect_color = effect->value;
                    fn_800EBA80(2, effect, &effect_color,
                                 (float)(effect->intensity / 100), 64);
                }
            }
        }
        seen_mask |= special_seen;
    }
    fn_801F10BC(active_mask & seen_mask, active_mask & ordinary_mask, 0);
    return scaled_count;
}
