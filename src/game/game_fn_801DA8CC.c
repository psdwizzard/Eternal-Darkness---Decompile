typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct EffectInfo {
    u8 type;
    u8 count;
    u8 pad2;
    u8 flags;
    s16 value;
    u8 pad6[0x14];
    void* owner;
} EffectInfo;

extern Vec3 lbl_8023B5A8;
extern Vec3 lbl_8023B5B4;
extern float lbl_80651170;
extern float lbl_80651174;
extern void* fn_80201814(u32);
extern int fn_80035628(void);
extern int fn_80036E50(void*);
extern int fn_80201B5C(void*);
extern int fn_800CF52C(void*);
extern void* fn_80201BC8(void*);
extern int fn_80129258(void);
extern void fn_8012B344(void*);
extern u32 fn_801D3944(u32);
extern u32 fn_801D38E8(u32);
extern void fn_8014C060(Vec3*, u32, u32, u32*, u32, u32, u8*, Vec3*);
extern void fn_80181F5C(EffectInfo*);
extern u32 fn_801CEB2C(u32);
extern u32 fn_801D3A34(u32, u32);
extern void fn_8012B690(void*, Vec3*, Vec3*);
extern void fn_8011F114(Vec3*, void*);
extern void fn_80211A6C(Vec3*, Vec3*, Vec3*);
extern void fn_80211AAC(Vec3*, Vec3*);
extern void fn_80211A90(Vec3*, Vec3*, float);
extern void fn_80211A48(Vec3*, Vec3*, Vec3*);
extern void* fn_80148008(Vec3*, s16*, EffectInfo*, void (*)(void));
extern void fn_80182014(void);
extern void* fn_80156938(void*);
extern void fn_8017FF1C(void*, u32);

void fn_801DA8CC(u32 target, Vec3* source, u32 owner, u8* state)
{
    Vec3 zero = lbl_8023B5A8;
    void* actor;
    void* attached = 0;
    u32 packed;
    u32 mask;
    Vec3 direction;
    EffectInfo info;
    s16 offsets[3];

    actor = fn_80201814(owner);
    if (actor != 0) {
        int mode = fn_80035628();
        if (!((fn_80036E50(actor) == 13 && mode == 3) ||
              fn_80201B5C(actor) == 44)) {
            mode = fn_800CF52C(actor);
            attached = fn_80201BC8(actor);
            if (attached != 0 && mode == 0 && fn_80129258() != 0)
                fn_8012B344(attached);
        }
    }

    packed = fn_801D3944(*(u32*)(state + 0xB8));
    switch (fn_801D38E8(*(u32*)(state + 0xB8))) {
    case 0: mask = 0x100; break;
    case 1: mask = 0x20; break;
    case 2: mask = 8; break;
    case 3: mask = 0x10; break;
    case 4: mask = 0x40; break;
    }
    fn_8014C060(source, target, 0, &packed, mask, (u32)(state + 4),
                state + 4, &direction);
    fn_80181F5C(&info);
    info.type = (u8)(fn_801CEB2C(*(u32*)(state + 0xB8)) << 1);
    info.count = fn_801D38E8(*(u32*)(state + 0xB8)) == 4 ? 2 : 4;
    info.value = (s16)fn_801D3A34(*(u32*)(state + 0xB8), 0x42);
    info.flags = 0xF0;
    info.owner = 0;

    if (attached != 0) {
        Vec3 target_pos;
        Vec3 actor_pos;
        fn_8012B690(attached, &zero, &target_pos);
        fn_8011F114(&actor_pos, attached);
        offsets[0] = (s16)(target_pos.x - actor_pos.x);
        offsets[1] = (s16)(target_pos.y - actor_pos.y);
        offsets[2] = (s16)(target_pos.z - actor_pos.z);
    } else {
        Vec3 base = lbl_8023B5B4;
        Vec3 actor_pos;
        Vec3 delta;
        Vec3 normalized;
        Vec3 scaled;
        void* other = fn_80201BC8(fn_80201814(owner));
        fn_8011F114(&actor_pos, other);
        fn_80211A6C(source, &actor_pos, &delta);
        fn_80211AAC(&delta, &delta);
        fn_80211A90(&delta, &scaled, lbl_80651170);
        fn_8012B690(other, &base, &normalized);
        fn_80211A48(&normalized, &scaled, &direction);
        fn_80211A90(&delta, &scaled, lbl_80651174);
        offsets[0] = (s16)scaled.x;
        offsets[1] = (s16)scaled.y;
        offsets[2] = 6;
    }

    actor = fn_80148008(&direction, offsets, &info, fn_80182014);
    if (actor != 0)
        fn_8017FF1C(fn_80156938(actor), 4);
}
