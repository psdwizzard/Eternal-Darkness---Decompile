typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct SixBytes { u32 word; u16 half; } SixBytes;

extern u32 lbl_8064D5A8;
extern int lbl_8064D18C;
extern u32 lbl_80651D28;
extern u16 lbl_80651D2C;
extern int fn_80180430(void*, u8);
extern int fn_80180454(void*);
extern void fn_80180518(void*, u8, int);
extern void fn_8017E1B0(void*, void*);
extern void* fn_80201B9C(void);
extern void* fn_80201BC0(void*);
extern int fn_80201B4C(void*);
extern void* fn_80201BC8(void*);
extern void* fn_80201B54(void*);
extern int fn_80201EB8(void*);
extern void fn_8011F114(void*, void*);
/* The caller truncates this ABI word explicitly; a u16 declaration changes
 * MWCC register allocation even though the callee returns a zero-extended half. */
extern u32 fn_8011F760(void*);
extern float fn_8011F6F0(void*);
extern u32 fn_80179064(int, int, s16, s16);
extern unsigned long long fn_8020123C(int, int, int, int);
extern void* fn_801A717C(void);
extern void fn_80179B08(void*, void*);
extern void fn_801A74A8(void*, void*);
extern void fn_801A7538(void*, int);
extern void fn_801A7518(void*, int);
extern void fn_801A7588(void*, int);
extern void fn_801A7470(void*, int);
extern void fn_801A764C(void*, void*);
extern void fn_801A7228(void*);
extern unsigned int rand(void);
extern void* memcpy(void*, const void*, u32);
extern u8 fn_8018E26C(void*, void*);
extern void fn_8018E230(void*, void*, int, u8, u8, int);
extern void fn_8018A88C(void);

int fn_8018437C(u8* self)
{
    /* Retail consumes these loop-carried registers before their first assignment.
     * This preserves that behavior, including the undefined first-use values. */
    int point_y;
    int point_x;
    int point_z;
    u8* timer;
    u8 count;
    int i;
    u8* entry;
    u8* timers;

    timers = self + 0x8C;
    entry = *(u8**)(self + 0x4C);
    count = self[1];

    if (*(u16*)(self + 0x92) == 0) {
        timer = timers;
        *(void**)(self + 0x148) = fn_8018A88C;
        for (i = 0; i < count; entry += 0x38, timer += 2, i++) {
            if (fn_80180430(self + 0x24, (u8)i)) {
                int mode = lbl_8064D5A8 & 0x1F;
                if (entry[0x21] < timers[1] && ((*(u16*)(self + 0xA) & 3) == 0))
                    entry[0x21] += timers[0];
                if (timers[4] != 2 || ((*(u16*)(self + 0xA) & 1) == 0))
                    fn_8017E1B0(entry + 0xA, entry + 0x10);
                if (timers[3] && mode == 0) {
                    void* node = fn_80201B9C();
                    while (node) {
                        int type = fn_80201EB8(node);
                        int state = fn_80201B4C(node);
                        if (type == lbl_8064D18C && (state == 0 || state == 1)) {
                            void* object = fn_80201BC8(node);
                            float point[3];
                            u32 bound;
                            int radius;
                            u32 distance_xy;
                            u32 distance_xz;
                            fn_8011F114(point, object);
                            bound = fn_8011F760(object) & 0xFFFF;
                            radius = (int)fn_8011F6F0(object);
                            distance_xy = fn_80179064(point_x, point_y, *(s16*)(entry + 0xA), *(s16*)(entry + 0xC));
                            distance_xz = fn_80179064(point_x, point_z, *(s16*)(entry + 0xA), *(s16*)(entry + 0xE));
                            point_x = (int)point[0];
                            point_y = (int)point[1];
                            point_z = (int)point[2];
                            if (distance_xy <= (u32)radius && distance_xz <= bound) {
                                void* actor = fn_80201B54(node);
                                u64 result = fn_8020123C(0x3B, 0, (int)actor, 0);
                                result &= 0xFFFFFFFFULL;
                                if ((u32)result == 1) {
                                    void* effect = fn_801A717C();
                                    float pos[3];
                                    fn_80179B08(entry + 0xA, pos);
                                    timers[3] = 0;
                                    fn_801A74A8(effect, actor);
                                    fn_801A7538(effect, 1);
                                    fn_801A7518(effect, 10);
                                    fn_801A7588(effect, 2);
                                    fn_801A7470(effect, -1);
                                    fn_801A764C(effect, pos);
                                    fn_8020123C(0x27, -1, (int)actor, (int)effect);
                                    fn_801A7228(effect);
                                }
                            }
                        }
                        node = fn_80201BC0(node);
                    }
                }
                if (entry[0] && !fn_8018E26C(entry, entry + 0x2B))
                    fn_80180518(self + 0x24, (u8)i, 0);
                if (*(u16*)(self + 0xA) == *(u16*)(entry + 8)) {
                    SixBytes setup;
                    setup.word = lbl_80651D28;
                    setup.half = lbl_80651D2C;
                    if (timers[2])
                        setup.half = (rand() & 1) + 1;
                    else
                        setup.half = -1 - (rand() & 1);
                    memcpy(entry + 0x10, &setup, 6);
                    fn_8018E230(entry, entry + 0x2B, 1, self[2], self[4], 0);
                }
            } else {
                --*(s16*)(timer + 8);
                if (*(s16*)(timer + 8) == 0) {
                    fn_80180518(self + 0x24, (u8)i, 1);
                    entry[0x2B] = self[2];
                }
            }
        }
    } else {
        *(u32*)(self + 0x148) = 0;
        --*(u16*)(timers + 6);
    }
    ++*(u16*)(self + 0xA);
    if (fn_80180454(self + 0x24) || *(u16*)(self + 0xA) > 300)
        *(u16*)(self + 0x22) = 8;
    return 0;
}
