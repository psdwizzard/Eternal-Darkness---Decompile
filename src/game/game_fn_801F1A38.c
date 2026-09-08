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
typedef struct Input {
    u8 pad00[8];
    Vec3 minimum;
    u8 pad14[0xC];
    u8* entries;
} Input;
typedef struct Entry {
    u8 pad00[0xB];
    u8 count;
    EffectRec* effects;
} Entry;
typedef struct Candidate {
    u8 pad00[0x18];
    s32 kind;
    u8 pad1C[0xD];
    u8 flags;
    s16 id;
    u8 pad2C;
    u8 subtype;
    u8 pad2E[0x12];
    s32 value;
    s32 intensity;
    u8 pad48[0x34];
} Candidate;

extern s32 lbl_8064C388;
extern s32 lbl_8064CB48;
extern s32 lbl_8064D18C;
extern double lbl_80651360;
extern float lbl_8065134C;
extern float lbl_806513C0;
extern s32 lbl_806513BC;
extern float lbl_806513C4;

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

#pragma use_lmw_stmw on

s32 fn_801F1A38(Vec3* point, Vec3* target, Input* input, s32 group,
                 s32 requested, u32 flags, float scale)
{
    s32 max_count;
    Candidate** candidates;
    EffectRec effects[4];
    Candidate candidate;
    Vec3 debug_color;
    Vec3 fixed_color;
    s32 effect_count = 0;
    s32 selected;
    s32 active_mask = 0;
    s32 candidate_index = 0;
    u32 ordinary_mask = 0x10;
    u32 seen_mask = 0;
    u32 enabled_mask = 0;
    u32 special_mask = 0;
    s32 cap;
    s32 i;
    s32 extra_count;
    s32 special_count;
    s32 scaled_count;
    s32 base;

    max_count = fn_801FD258();
    candidates = fn_801FD240();
    effects[0].pos = *point;
    if (input->minimum.x > effects[0].pos.x) effects[0].pos.x = input->minimum.x;
    if (input->minimum.y > effects[0].pos.y) effects[0].pos.y = input->minimum.y;
    if (input->minimum.z > effects[0].pos.z) effects[0].pos.z = input->minimum.z;
    selected = fn_801F15D0(&effects[0].pos, group, input, &effect_count, effects);
    if (selected == -1) {
        fn_801F3FD8(point, 3000);
        return 0;
    }
    if (effect_count > 4) effect_count = 4;

    cap = max_count;
    if (cap > lbl_8064C388) cap = lbl_8064C388;
    if (cap > 3) cap = 3;

    for (i = 0; i < effect_count; i++) {
        active_mask |= 1 << i;
        if (flags & 1) {
            s32 minimum = fn_801F1A24(i);
            if (flags & 2) minimum *= 5;
            if (effects[i].intensity < minimum) effects[i].intensity = minimum;
            fn_801F0CB0(&effects[i], point, target, i, 0, 0, 0);
        } else {
            effects[i].intensity = (s32)((float)effects[i].intensity * scale);
            fn_801F0CB0(&effects[i], point, target, i, 0, 0, 0);
        }
        if (lbl_8064CB48) {
            s32 color = effects[i].value;
            fn_800EBA80(2, &effects[i], &color,
                         (float)(effects[i].intensity / 100), 64);
        }
    }

    scaled_count = (s32)((float)effects[0].intensity * scale);
    base = selected * 0x14;
    special_count = 3 - cap;
    if (special_count > ((Entry*)(input->entries + base))->count)
        special_count = ((Entry*)(input->entries + base))->count;
    if (requested == 1) special_count = 0;
    extra_count = 4 - cap - special_count;
    if (extra_count > requested) extra_count = requested;
    if (extra_count > effect_count) extra_count = effect_count;
    if (special_count > 0) special_mask = 0x10 << (cap + extra_count);
    if (cap > 0) {
        seen_mask = 0x10 << extra_count;
        enabled_mask = seen_mask;
    }

    for (i = 0; i < extra_count; i++) {
        ordinary_mask |= 0x10 << i;
        active_mask |= ordinary_mask;
        effects[i].intensity = (s32)((float)effects[i].intensity * scale);
        fn_801F0CB0(&effects[i], point, target, i + 4, 1, 0, 0);
        if (lbl_8064CB48) {
            s32 color = effects[i].value;
            fn_800EBA80(2, &effects[i], &color,
                         (float)(effects[i].intensity / 100), 64);
        }
    }

    for (i = 0; i < cap; i++) {
        candidate = **candidates;
        if (candidate.id == lbl_8064D18C &&
            (!fn_8015E4E8() || candidate.subtype == 7)) {
            s32 valid = 1;
            if (fn_80201B3C() && (candidate.flags & 8)) {
                fn_80201BC8();
                if (candidate.id != fn_8011FB4C()) valid = 0;
            }
            if (valid) {
                seen_mask |= enabled_mask << candidate_index;
                active_mask |= seen_mask;
                candidate.intensity = (s32)((float)candidate.intensity * scale);
                if (candidate.kind == 1) {
                    fn_801F0CB0((EffectRec*)&candidate, point, target,
                                 extra_count + candidate_index + 4, 0,
                                 (Vec3*)((u8*)&candidate + 0x60),
                                 (u8*)&candidate + 0x48);
                } else {
                    fn_801F0CB0((EffectRec*)&candidate, point, target,
                                 extra_count + candidate_index + 4, 0,
                                 (Vec3*)((u8*)&candidate + 0x60), 0);
                }
                candidate_index++;
                if (lbl_8064CB48) {
                    s32 color = candidate.value;
                    fn_800EBA80(2, (EffectRec*)&candidate, &color,
                                 (float)(candidate.intensity / 100), 64);
                }
            }
        }
        candidates++;
    }

    seen_mask |= 0xF;
    if (selected != -1) {
        fixed_color.x = lbl_8065134C;
        fixed_color.y = lbl_8065134C;
        fixed_color.z = lbl_806513C0;
        for (i = 0; i < special_count; i++) {
            Entry* entry = (Entry*)(input->entries + base);
            EffectRec* effect = (EffectRec*)((u8*)entry->effects + candidate_index);
            special_mask |= special_mask << i;
            active_mask |= special_mask;
            fn_801F0CB0(effect, point, target, cap + extra_count + 4 + i,
                         0, &fixed_color, 0);
            if (lbl_8064CB48) {
                s32 color = lbl_806513BC;
                fn_800EBA80(1, effect, &color, lbl_806513C4, 64);
                color = effect->value;
                fn_800EBA80(2, effect, &color,
                             (float)(effect->intensity / 100), 64);
            }
            candidate_index += 0x14;
        }
        seen_mask |= special_mask;
    }
    fn_801F10BC(active_mask & seen_mask, active_mask & ordinary_mask, 0);
    return scaled_count;
}
