typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

extern float lbl_8064B720;
extern u32 lbl_8064B71C;

extern int fn_80200C38();
extern u16 fn_801A6DE4(void *);
extern float fn_801A6DDC(void *);
extern float fn_801A6DD4(void *);
extern int fn_801A6DC4(void *);
extern int fn_801A6DCC(void *);
extern u32 fn_801A6D9C(void *);
extern void *fn_80201BC8();
extern void *fn_80201B8C();
extern u8 fn_80128EE4(void *);
extern void *fn_801294DC(void *, int, int, int);
extern u32 fn_8011FAEC(void *);
extern int fn_80129228(void *);
extern int fn_80128608(void);
extern int fn_80128EAC(void *);
extern s8 fn_80128600(void);
extern int fn_80128F40(void *);
extern int fn_8012A1FC(void *, int);
extern int fn_8012A1BC(void *, int);
extern u32 fn_8011FCE4(void *);
extern int fn_800C07E0(void *, int, u32);
extern int fn_800C4880(int, int, int, int);
extern void fn_80129FD0(void *, int, int);
extern void fn_801296F8(void *, int);
extern int fn_8012AFC4(void *);
extern float fn_8012B750(void *);
extern void fn_8017A010(float *, float, float, float, int);
extern void fn_8012B7A0(void *, float);
extern void fn_80128610(int);
extern void fn_801285F8(int);

void fn_800C030C(void *context, void *encoded, float scale)
{
    void *parsed = (void *)fn_80200C38(encoded);
    u16 mode = fn_801A6DE4(parsed);
    float range = fn_801A6DDC(parsed);
    float base = fn_801A6DD4(parsed);
    float fraction;
    int amount = fn_801A6DC4(parsed);
    int selection = fn_801A6DCC(parsed);
    u32 parsed_flags = fn_801A6D9C(parsed);
    int action_flags = 0x21;
    void *object = fn_80201BC8(context);
    int changed = 0;
    void **state = ((void **)fn_80201B8C(context));
    u8 status = fn_80128EE4(object);
    int source;
    int position;
    int low;
    int high;

    if (selection == 0x16) {
        fn_801294DC(object, 2, 0x25, 1);
        goto finish;
    }
    if ((parsed_flags & 0x40) != 0) {
        action_flags |= 2;
    }

    parsed_flags = fn_8011FAEC(object);
    if (*state != 0 && ((u8 *)*state)[0x93] != 0) {
        selection = 1;
    }

    if ((parsed_flags & 0x10) != 0 && (status & 0x0A) != 0) {
        float timer;
        float ratio;
        lbl_8064B720 = lbl_8064B720 - 1.0f;
        timer = lbl_8064B720 > 2.5f ? lbl_8064B720 : 2.5f;
        lbl_8064B720 = timer;
        ratio = timer / 160.0f;
        if (ratio < 1.0f) {
            selection = 2;
            amount = (int)(ratio * amount);
        }
    } else {
        lbl_8064B720 = 190.0f;
    }

    if ((fn_8011FAEC(object) & 0x400) != 0 &&
        (fn_80129228(object) != 0 || fn_80128608() != -1)) {
        source = fn_80128EAC(object);
        if (fn_80128600() != 0 ||
            (selection != source &&
             ((unsigned)(selection - 2) <= 1 || selection == 1))) {
            if (fn_80128600() != 0) {
                source = fn_80128608();
            }
            position = fn_80128F40(object);
            low = fn_8012A1FC(object, source);
            high = fn_8012A1BC(object, source);
            if (fn_80128600() != 0) {
                source = fn_800C07E0(object, source, lbl_8064B71C);
            } else {
                source = fn_800C07E0(object, source, fn_8011FCE4(object));
            }
            fraction = ((float)((position >> 17) - low) -
                        (float)(source - low)) / (float)(high - low);
            if (fraction < 0.0) {
                fraction += 1.0f;
            }
            changed = 1;
        }
    }

    if (fn_801294DC(object, selection, action_flags, 1) != 0 && changed) {
        lbl_8064B71C = fn_8011FCE4(object);
        low = fn_8012A1FC(object, selection);
        high = fn_8012A1BC(object, selection);
        source = fn_800C07E0(object, selection, fn_8011FCE4(object));
        source = fn_800C4880(low + (int)(fraction * (float)(high - low)) + source, 4, low, high);
        fn_80129FD0(object, source << 17, 1);
    }

finish:
    status = fn_80128EE4(object);
    if ((status & 0x0F) != 0) {
        if ((status & 0x08) != 0) {
            amount = (int)(scale * amount);
        }
        fn_801296F8(object, amount);
    }
    if (mode != 0 && (status & 0x0F) != 0 && fn_8012AFC4(object) == 0) {
        float value = fn_8012B750(object);
        if (mode == 1) {
            float magnitude = range < 0.0f ? -range : range;
            fn_8017A010(&value, value + range, magnitude, 0.0087f, 0);
        } else {
            fn_8017A010(&value, base, range, 0.0087f, 0);
        }
        fn_8012B7A0(object, value);
    }
    fn_80128610(-1);
    fn_801285F8(0);
}
