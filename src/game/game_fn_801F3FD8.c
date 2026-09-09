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
typedef struct Candidate {
    u8 pad00[0x18];
    s32 kind;
    u8 pad1C[0xD];
    u8 flags;
    s16 id;
    u8 pad2C;
    u8 subtype;
    u8 pad2E[6];
    EffectRec effect;
    Vec3 color;
    u8 pad54[0xC];
    u8 attributes[0x1C];
} Candidate;

extern s32 lbl_8064D18C;
extern s32 lbl_806513EC;
extern float lbl_806513F0;
extern float lbl_806513F4;
extern float lbl_806513F8;

extern s32 fn_801FD258(void);
extern Candidate** fn_801FD240(void);
extern void fn_801F0CB0(EffectRec*, Vec3*, void*, s32, u8, Vec3*, u8*);
extern s32 fn_8015E4E8(void);
extern void* fn_80201B3C(void);
extern void fn_80201BC8(void);
extern s32 fn_8011FB4C(void);
extern void fn_801F10BC(u32, u32, s32);

#pragma use_lmw_stmw on

void fn_801F3FD8(Vec3* point, s32 duration)
{
    Vec3 target;
    EffectRec effect;
    Candidate candidate;
    Candidate** candidates;
    s32 active_mask = 0;
    u32 ordinary_mask = 0x10;
    u32 seen_mask = 0;
    u32 enabled_mask = 0;
    s32 candidate_index = 0;
    s32 cap;
    s32 extra_count;
    s32 i;

    cap = fn_801FD258();
    candidates = fn_801FD240();
    target.x = point->x;
    effect.pos.x = target.x - lbl_806513F0;
    target.y = point->y;
    effect.pos.y = target.y - lbl_806513F0;
    target.z = point->z;
    effect.pos.z = lbl_806513F4 + target.z;
    effect.value = lbl_806513EC;
    effect.intensity = duration;
    if (cap > 3) cap = 3;

    fn_801F0CB0(&effect, &target, 0, 0, 0, 0, 0);
    effect.pos.x += lbl_806513F8;
    fn_801F0CB0(&effect, &target, 0, 1, 0, 0, 0);
    effect.pos.y += lbl_806513F8;
    fn_801F0CB0(&effect, &target, 0, 2, 0, 0, 0);
    effect.pos.x -= lbl_806513F8;
    fn_801F0CB0(&effect, &target, 0, 3, 0, 0, 0);
    active_mask |= 0xF;

    extra_count = 4;
    if (cap > 0) {
        s32 remaining = 4 - cap;
        extra_count = 4;
        if (remaining <= 4) extra_count = remaining;
        seen_mask = 0x10 << extra_count;
        enabled_mask = seen_mask;
    }

    {
    float upper = lbl_806513F4;
    float lower = lbl_806513F0;
    for (i = 0; i < extra_count; i++) {
        ordinary_mask |= 0x10 << i;
        active_mask |= ordinary_mask;
        effect.pos.x = point->x - lower;
        effect.pos.y = point->y - lower;
        effect.pos.z = upper + point->z;
        switch (i) {
        case 0:
            break;
        case 1:
            effect.pos.x += lbl_806513F8;
            break;
        case 2:
            effect.pos.x += lbl_806513F8;
            effect.pos.y += lbl_806513F8;
            break;
        case 3:
            effect.pos.y += lbl_806513F8;
            break;
        }
        effect.intensity = 5000;
        fn_801F0CB0(&effect, &target, 0, i + 4, 1, 0, 0);
    }
    }

    while (candidate_index < cap) {
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
                if (candidate.kind == 1) {
                    fn_801F0CB0(&candidate.effect, point, 0,
                                 extra_count + candidate_index + 4, 0,
                                 &candidate.color, candidate.attributes);
                    candidate_index++;
                } else {
                    fn_801F0CB0(&candidate.effect, point, 0,
                                 extra_count + candidate_index + 4, 0,
                                 &candidate.color, 0);
                    candidate_index++;
                }
            }
        }
        candidates++;
    }

    fn_801F10BC(active_mask & (seen_mask | 0xF),
                 active_mask & ordinary_mask, 0);
}
