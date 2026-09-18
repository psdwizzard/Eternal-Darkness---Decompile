typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Plane { Vec3 point, normal; } Plane;

extern int lbl_8064B7EC;
extern float lbl_806502B8;
extern float lbl_806502BC;
extern float lbl_806502C0;
extern float lbl_806502C4;
extern float lbl_806502C8;
extern unsigned int fn_8011FAEC(void*);
extern void *fn_80201B9C(void);
extern void *fn_80201BC8(void*);
extern void* fn_80201BC0(void*);
extern int fn_8011FB4C(void*);
extern Vec3* fn_8011F130(void*);
extern float fn_8011F6F0(void*);
extern int fn_80137658(float, void*, Vec3*, void*, Plane*);
extern void fn_8011F114(Vec3*, void*);
extern void fn_8011F104(float, float, float, void*);
extern void fn_8011F0E8(void*, Vec3*);
extern void fn_80211A48(const Vec3*, const Vec3*, Vec3*);
extern void fn_80211A6C(const Vec3*, const Vec3*, Vec3*);
extern void fn_8013F600(Plane*, Vec3*, float*);
extern void fn_8013C460(Vec3*, const Vec3*, float, float);

void fn_8013A140(void* object)
{
    if ((fn_8011FAEC(object) & 0x40) && lbl_8064B7EC != 0) {
        void* iterator = fn_80201B9C();
        Vec3* facing;
        int group;
        float radius;
        group = fn_8011FB4C(object);
        facing = fn_8011F130(object);
        radius = fn_8011F6F0(object);

        while (iterator != 0) {
            void* other = fn_80201BC8(iterator);
            if (other != 0 && object != other && fn_8011FB4C(other) == group &&
                (fn_8011FAEC(other) & 0x80)) {
                Plane contact;
                if (fn_80137658(radius, object, facing, other, &contact)) {
                    Vec3 normal;
                    Vec3 up;
                    Vec3 position;
                    float distance;
                    float other_radius = fn_8011F6F0(other);

                    up.x = lbl_806502B8;
                    up.y = lbl_806502B8;
                    up.z = other_radius;
                    fn_80211A48(fn_8011F130(other), &up, &position);
                    fn_8013F600(&contact, &normal, &distance);
                    fn_8013C460(&position, &normal,
                                lbl_806502BC + other_radius, distance);
                    fn_80211A6C(&position, &up, fn_8011F130(other));
                } else {
                    Vec3 position;
                    Vec3 original;
                    fn_8011F114(&original, other);
                    position = original;
                    fn_8011F104(position.x, position.y,
                                position.z - lbl_806502C0, other);
                    if (fn_80137658(radius, object, facing, other, &contact)) {
                        Vec3 normal;
                        Vec3 up;
                        Vec3 adjusted;
                        float distance;
                        float other_radius = fn_8011F6F0(other);

                        up.x = lbl_806502B8;
                        up.y = lbl_806502B8;
                        up.z = other_radius;
                        fn_8013F600(&contact, &normal, &distance);
                        if (normal.z >= lbl_806502C4 &&
                            normal.z <= lbl_806502C8) {
                            fn_80211A48(fn_8011F130(other), &up, &adjusted);
                            fn_8013C460(&adjusted, &normal,
                                        lbl_806502BC + other_radius, distance);
                            fn_80211A6C(&adjusted, &up,
                                       fn_8011F130(other));
                        } else {
                            fn_8011F0E8(other, &position);
                        }
                    } else {
                        fn_8011F0E8(other, &position);
                    }
                }
            }
            iterator = fn_80201BC0(iterator);
        }
    }
}
