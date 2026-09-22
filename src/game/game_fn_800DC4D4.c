typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

extern void *fn_80201B9C(void *); extern void *fn_80201B94(void *);
extern void *fn_80201BC8(void *); extern float *fn_8011F130(void *);
extern int fn_80204844(void *, int); extern int fn_8006D444(void);
extern int fn_8006D344(int, int, int); extern void *fn_80204A8C(void);
extern int fn_80204D98(void); extern int fn_8011FB4C(void *);
extern u16 fn_8011F760(void *); extern void *fn_802051A4(void *);
extern void *fn_80205134(void *); extern void *fn_80201814(void *);
extern int fn_80201B5C(void *); extern int fn_80201B64(void *);
extern void *fn_80201C24(void *); extern u32 fn_80179064(int, int, int, int);
extern int fn_801E1E38(void); extern u32 fn_80157894(void *);
extern u32 fn_80157888(void *); extern void fn_8012DBE8(void *, int, u32 *);
extern void fn_8012C62C(void *, int, u32 *, u32 *, u32 *, int);
extern void fn_8011FA8C(void *, int, int); extern void fn_801441C0(int, int, int);
extern void fn_80157B80(void *, int); extern void fn_80157B6C(void *, int);
extern int fn_8015821C(void *); extern int fn_80204888(int);
extern int fn_8004919C(void); extern int fn_8012FA54(void *, int);
extern int fn_80201B4C(void *); extern u32 fn_8011FAEC(void *);
extern void *fn_80201B54(void *); extern void *fn_80201BC0(void *);
extern void fn_80201E68(void *, int);
extern u32 lbl_8064F4D0, lbl_8064F4D4, lbl_8064F4D8;
extern u32 lbl_8064F4DC, lbl_8064F4E0, lbl_80651AFC;
extern float lbl_8064F4E4, lbl_8064F4E8, lbl_8064F4EC, lbl_8064F464;

/* NonMatching: behavior-complete reconstruction of both candidate searches. */
int fn_800DC4D4(void *context)
{
    void *cursor = fn_80201B9C(context);
    int mode = 0;
    int result = 0;
    void *output = fn_80201B94(context);
    void *owner = fn_80201BC8(context);
    float *origin = fn_8011F130(owner);
    int i;
    fn_80204844(fn_80201B9C(owner), 0x20);
    if (fn_8006D344(fn_8006D444(), 0x20200, 0)) {
        mode = 1;
    }
    if (!mode) {
        void *scan_base = fn_80204A8C();
        int count = fn_80204D98();
        int owner_group = fn_8011FB4C(owner);
        float upper = lbl_8064F4E4 + (float)fn_8011F760(owner);
        void *scan = scan_base;
        for (i = 0; i < count; i++) {
            void *entry, *candidate, *candidate_owner, *candidate_state;
            float *position; float dz; u32 distance, flags; int active;
            scan = fn_802051A4(scan);
            entry = fn_80205134(scan);
            candidate = fn_80201814(entry);
            if (fn_80201B5C(candidate) != 30) continue;
            candidate_owner = fn_80201BC8(candidate);
            if (fn_8011FB4C(candidate_owner) != owner_group) continue;
            if (fn_80201B64(candidate) == 36) continue;
            candidate_state = fn_80201C24(candidate);
            position = fn_8011F130(candidate_owner);
            distance = fn_80179064((int)position[0], (int)position[1],
                                   (int)origin[0], (int)origin[1]);
            dz = position[2] - origin[2];
            active = fn_801E1E38();
            flags = fn_80157894(candidate_state);
            if (flags & 0x10) {
                u32 value;
                fn_8012DBE8(candidate_owner, 15, &value);
                if (((u8 *)&value)[3] == 0 && active) {
                    u32 a = lbl_8064F4D8, b = lbl_8064F4D4, c = lbl_8064F4D0;
                    fn_8012C62C(candidate_owner, 15, &c, &b, &a, 4);
                    fn_8011FA8C(candidate_owner, 0, 0x10000);
                } else if (((u8 *)&value)[3] == 0xff && !active) {
                    u32 a = lbl_80651AFC, b = lbl_8064F4E0, c = lbl_8064F4DC;
                    fn_8012C62C(candidate_owner, 15, &c, &b, &a, 4);
                    fn_8011FA8C(candidate_owner, 0x10000, 0);
                }
            }
            if (!(dz <= upper) || !(dz >= lbl_8064F4E8)) continue;
            flags = fn_80157894(candidate_state);
            if (distance <= 500 && ((fn_80157888(candidate_state) & 0x20) || (flags & 0x18))) {
                if (!(flags & 0x40)) {
                    fn_801441C0(5, 5, 30); fn_801441C0(4, 30, 30);
                }
                fn_80157B80(candidate_state, 0x40);
            } else fn_80157B6C(candidate_state, 0x40);
            if (flags & 8) continue;
            if ((flags & 0x10) && !active) continue;
            if (distance > 250) continue;
            if (fn_8015821C(candidate_state) == 188) {
                if (!fn_80204888(105)) goto done;
            }
            if (fn_8004919C() && fn_8012FA54(candidate_owner, 15) &&
                !(fn_80157894(candidate_state) & 0x80)) {
                fn_80201E68(output, (int)entry);
                result = 1;
                goto done;
            }
        }
    } else {
        while (cursor != 0) {
            if (fn_80201B4C(cursor) == 3 || fn_80201B5C(cursor) == 30) {
                void *candidate_owner = fn_80201BC8(cursor);
                if (fn_8011FAEC(candidate_owner) & 0x4000) {
                    float *position = fn_8011F130(candidate_owner);
                    u32 distance = fn_80179064((int)position[0], (int)position[1],
                                              (int)origin[0], (int)origin[1]);
                    float dz = position[2] - origin[2];
                    if (dz < lbl_8064F464) dz = -dz;
                    if (distance <= 250 && dz <= lbl_8064F4EC) {
                        fn_80201E68(output, (int)fn_80201B54(cursor));
                        result = 1;
                        goto done;
                    }
                }
            }
            cursor = fn_80201BC0(cursor);
        }
    }
    fn_80201E68(output, -1);
done:
    return result;
}
