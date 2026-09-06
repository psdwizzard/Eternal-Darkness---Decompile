
typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#pragma use_lmw_stmw on
typedef struct SixBytes
{
    u32 word;
    u16 half;
} SixBytes;
typedef struct Vec3
{
    float x;
    float y;
    float z;
} Vec3;
typedef struct Locals
{
    SixBytes setup;
    void *vectors;
} Locals;
extern u8 lbl_80607120[];
extern void *lbl_8064D738;
extern u32 lbl_80651D58;
extern u16 lbl_80651D5C;
extern const float lbl_80650A20;
extern void fn_8018D788(void *, void *, void **, u16);
extern void fn_801869F8(void *, int, u16);
extern void fn_8018E26C(void *, void *);
extern void fn_801865EC(void *, SixBytes *, int);
extern void fn_80186954(void *, void *, Vec3 *, int, SixBytes *);
extern void fn_8018E230(void *, void *, int, u8, u8, int);
extern void fn_80211A48(Vec3 *, Vec3 *, Vec3 *);
extern void fn_80198154(void *, void *, int, int, Vec3 *);
int fn_80186A88(u8 *self)
{
    Locals locals;
    int changed = 0;
    int loop[2];
    u8 *self_local = self;
    u16 generation;
    int index;
    u8 *state;
    u8 *entry;
    float component;
    u8 *state_bytes;
    state = self_local + 0x8C;
    locals.setup.word = lbl_80651D58;
    locals.setup.half = lbl_80651D5C;
    generation = *((u16 *) (self_local + 0xA));
    entry = *((u8 **) (self_local + 0x4C));
    loop[1] = self_local[1];
    *((u16 *) (self_local + 0xA)) = generation + 1;
    fn_8018D788(lbl_8064D738, self_local, &locals.vectors, *((u16 *) (lbl_80607120 + 2)));
    fn_801869F8(state, 0, *((u16 *) (state + 8)));
    index = 0;
    loop[0] = 0;
    for (; index < loop[1]; index++) {
        if (entry[0] != 0) {
            fn_8018E26C(entry, entry + 0x2B);
            if ((changed == 0) && ((state[5] & 4) != 0)) {
                if (((s8) state[1]) > 2) {
                    state[1]--;
                } else
                    if (((s8) state[1]) < (-2)) {
                    state[1]++;
                }
                changed = 1;
            }
        }
        fn_801865EC(self_local, &locals.setup, index);
        fn_80186954(state, entry, (Vec3 *) (((u8 *) locals.vectors) + loop[0]), index, &locals.setup);
        if ((((int) generation) == ((int) (*((u16 *) (entry + 8))))) && ((state[5] & 1) == 0)) {
            fn_8018E230(entry, entry + 0x2B, 1, self_local[2], self_local[4], 0);
        }
        entry += 0x38;
        loop[0] += 0xC;
    }

    fn_80211A48((Vec3 *) (state + 0x60), (Vec3 *) (state + 0x6C), (Vec3 *) (state + 0x60));
    component = *((float *) (state + 0x60));
    if (component > lbl_80650A20) {
        component = *((float *) (state + 0x6C));
    }
    state_bytes = state;
    *((float *) (state_bytes + 0x60)) = component;
    component = *((float *) (state_bytes + 0x64));
    if (component > lbl_80650A20) {
        component = *((float *) (state_bytes + 0x70));
    }
    *((float *) (state_bytes + 0x64)) = component;
    component = *((float *) (state_bytes + 0x68));
    if (component > lbl_80650A20) {
        component = *((float *) (state_bytes + 0x74));
    }
    *((float *) (state_bytes + 0x68)) = component;
    fn_80198154(self_local + 0x10, locals.vectors, (self_local[1] & 0x7F) << 1, 0, (Vec3 *) (state_bytes + 0x60));
    if ((((*((u16 *) (state_bytes + 0x40))) & 2) != 0) || (((state_bytes[5] & 1) == 0) && (((int) generation) >= ((int) (*((u16 *) (self_local + 0xC))))))) {
        *((u16 *) (self_local + 0x22)) = 8;
    }
    return 0;
}
