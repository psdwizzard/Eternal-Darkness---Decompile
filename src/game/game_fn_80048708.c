typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Plane { Vec3 point, normal; } Plane;

extern int lbl_8064D18C;
extern float lbl_8064E388;
extern float lbl_8064E38C;
extern void fn_8011F114(Vec3*, Vec3*);
extern void fn_8011F0E8(Vec3*, Vec3*);
extern float fn_8011F6F0(void*);
extern void* fn_8011F770(void*);
extern unsigned int fn_8011FAEC(void*);
extern void* fn_8011FB4C(void*);
extern int fn_8011EB1C(void*);
extern void* fn_80201B9C(void);
extern void* fn_80201BC0(void*);
extern void* fn_80201BC8(void*);
extern int fn_80201B5C(int*);
extern int fn_80201B4C(int*);
extern void* fn_80201B94(unsigned char*);
extern int fn_80201C58();
extern int fn_8003BF5C(void*);
extern int fn_80137658(float, void*, Vec3*, void*, Plane*);
extern void fn_8013F600(Plane*, Vec3*, float*);
extern void fn_8013C518(Vec3*, const Vec3*, float, float);
extern void fn_80211A48(const Vec3*, const Vec3*, Vec3*);
extern void fn_80211A6C(const Vec3*, const Vec3*, Vec3*);
extern void fn_80139F28(void*, const Vec3*, const Vec3*, Vec3*, void*);

void fn_80048708(Vec3* input)
{
    register Vec3* object;
    Plane contact;
    Vec3 position;
    Vec3 normal;
    Vec3 adjusted;
    Vec3 result;
    Vec3 original;
    float distance;
    register int excluded;
    register int kind;
    register void* iterator;
    register Vec3* other;
    register void* owner;
    float radius;
    register Vec3* offset;

    /* ASM: mr preserves the incoming object in a distinct register;
       C copy propagation otherwise coalesces this long-lived local. */
    asm { mr object, r3 }
    fn_8011F114(&original, object);
    fn_8011F6F0(object);
    iterator = fn_80201B9C();
    while (iterator != 0) {
        if (fn_80201B5C(iterator) != 12) {
            excluded = 0;
            fn_80201B4C(iterator);
            /* ASM: mr retains a separate kind local instead of coalescing
               it with the call result ahead of the other live locals. */
            asm { mr kind, r3 }
            owner = fn_80201B94(iterator);
            other = fn_80201BC8(iterator);
            if (owner != 0) {
                excluded = 0;
                if (kind == 2 || (kind == 1 && (unsigned int)fn_80201C58(owner) != 0))
                    excluded = 1;
            }
            if (other != 0 && lbl_8064D18C == (int)fn_8011FB4C(other) &&
                other != object && fn_8011EB1C(other) != 3 &&
                fn_8003BF5C(iterator) == 0 && excluded == 0 &&
                (fn_8011FAEC(other) & 0x80)) {
                radius = fn_8011F6F0(other);
                fn_8011F114(&position, other);
                if (fn_80201B5C(iterator) == 18 || fn_80201B5C(iterator) == 19)
                    radius = lbl_8064E388;
                if (fn_80137658(radius, other, &position, object, &contact)) {
                    adjusted = position;
                    offset = fn_8011F770(other);
                    fn_8013F600(&contact, &normal, &distance);
                    fn_8013C518(&adjusted, &normal, lbl_8064E38C + radius, distance);
                    fn_80211A48(&adjusted, offset, &adjusted);
                    fn_80139F28(other, &adjusted, &adjusted, &result, (void*)1);
                    fn_80211A6C(&result, offset, &result);
                    fn_8011F0E8(other, &result);
                }
            }
        }
        iterator = fn_80201BC0(iterator);
    }
}
