typedef unsigned char u8;
typedef signed short s16;
typedef signed long s32;
typedef unsigned long u32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct EffectRec { Vec3 pos; s32 value; s32 intensity; } EffectRec;
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
extern s32 fn_801FD258(void);
extern Candidate** fn_801FD240(void);
extern s32 fn_8015E4E8(void);
extern void fn_801F0CB0(EffectRec*, Vec3*, void*, s32, u8, Vec3*, u8*);
extern void fn_801F10BC(u32, u32, s32);

#pragma use_lmw_stmw on

void fn_801F4380(Vec3* point)
{
    Candidate candidate;
    u32 active_mask = 0;
    s32 count = 0;
    s32 cap;
    Candidate** candidates;

    cap = fn_801FD258();
    candidates = fn_801FD240();
    if (cap > 3) cap = 3;
    if (cap > 0) {
        Candidate** current = candidates;
        while (count < cap) {
            candidate = **current;
            if (candidate.id == lbl_8064D18C &&
                (!fn_8015E4E8() || candidate.subtype == 7)) {
                active_mask |= 0x20 << count;
                if (candidate.kind == 1) {
                    fn_801F0CB0(&candidate.effect, point, 0, count + 5, 0,
                                 &candidate.color, candidate.attributes);
                    count++;
                } else {
                    fn_801F0CB0(&candidate.effect, point, 0, count + 5, 0,
                                 &candidate.color, 0);
                    count++;
                }
            }
            current++;
        }
        fn_801F10BC(active_mask, 0, 0);
    }
}
