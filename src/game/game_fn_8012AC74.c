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

/* Keep the nested equalities: GC/1.3 shares their materialized booleans. */
void fn_8012AC74(Vec8012AC74* object, const Vec8012AC74* input, int flags)
{
    int mode;
    int type;
    int condition;
    void* transform;
    Vec8012AC74 current;
    Vec8012AC74 target;
    Vec8012AC74 result;

    mode = fn_8011EB1C(object);
    type = fn_8011EB04(object);
    condition = (mode == 3) && ((type == 2 || type == 3) || type == 0x57);
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
