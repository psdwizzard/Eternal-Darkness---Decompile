typedef unsigned char u8;

typedef struct Vec8012AC74 {
    float x;
    float y;
    float z;
} Vec8012AC74;

extern int fn_8011EB1C(void*);
extern int fn_8011EB04(void*);
extern void* fn_8011F770(void*);
extern void fn_80211A48(const Vec8012AC74*, const void*, Vec8012AC74*);
extern void fn_80211A6C();
extern void fn_80139F28(void*, const Vec8012AC74*, const Vec8012AC74*,
                       Vec8012AC74*, int);
extern void fn_8013A140(void*);

/* NonMatching: behavior-complete reconstruction. */
void fn_8012AC74(void* owner, const void* value, int flags)
{
    Vec8012AC74* object = (Vec8012AC74*)owner;
    const Vec8012AC74* input = (const Vec8012AC74*)value;
    int mode;
    int type;
    int condition;
    void* transform;
    Vec8012AC74 current;
    Vec8012AC74 target;
    Vec8012AC74 result;

    mode = fn_8011EB1C(object);
    type = fn_8011EB04(object);
    condition = 0;
    if (mode == 3) {
        int a = 1;
        int b = a;
        if (!((unsigned int)(type - 2) <= 1))
            b = condition;
        if (!b) {
            if (type != 0x57)
                a = 0;
        }
        if (a)
            condition = 1;
    }
    if (condition) {
        *object = *input;
        fn_8013A140(object);
    } else {
        transform = fn_8011F770(object);
        fn_80211A48(object, transform, &current);
        fn_80211A48(input, transform, &target);
        fn_80139F28(object, &current, &target, &result, flags);
        fn_80211A6C(&result, transform, object);
    }
}
