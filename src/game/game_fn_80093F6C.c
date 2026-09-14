typedef unsigned char u8;

typedef struct Vec3_80093F6C {
    float x, y, z;
} Vec3_80093F6C;

typedef struct Target80093F6C {
    u8 pad00[0x163];
    signed char mode;
} Target80093F6C;

extern float lbl_8064EC9C;
extern float lbl_8064EC78;
extern float lbl_8064ECA0;
extern float lbl_8064EC7C;
extern float lbl_8064ECA4;

extern void* fn_80201B94();
extern void fn_8011F114();
extern int fn_80066D04(void*, int);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern int fn_800359A0(void*, int);
extern int fn_80201C48(void*);
extern void *fn_80201814();
extern void fn_802045AC(void*, Vec3_80093F6C*);
extern int fn_80178E94(Vec3_80093F6C*, Vec3_80093F6C*);
extern float fn_800CB444(void*, void*);
extern float fn_8011F6F8(void*);
extern int fn_8003E1F0(void*, Vec3_80093F6C*, int, float);
extern float fn_8012B7D0(void*, Vec3_80093F6C*);
extern float fn_8012B750(void*);
extern void fn_8017A12C(float*, float, float);
extern int fn_800938E4(void*, void*, int);
extern int fn_8012AFC4(void*);
#define FN_80128E30_RETURN void*
#define FN_80128E30_PARAMETERS void*
extern FN_80128E30_RETURN fn_80128E30(FN_80128E30_PARAMETERS);
extern void fn_80128C3C(float);
extern void fn_80129928(void*, Vec3_80093F6C*);
extern void fn_8012976C(float, void*, int, int, Vec3_80093F6C*);
extern int fn_800BE2CC(void*, Target80093F6C*, Vec3_80093F6C*);
extern void fn_800BE390(void*, Target80093F6C*);

int fn_80093F6C(register void* object, register void* resource, void* unused,
                register Target80093F6C* target, register int value,
                register int flags1, register int flags2)
{
    register void* component;
    register void* other;
    register int result = 0;
    Vec3_80093F6C position;
    Vec3_80093F6C base;
    Vec3_80093F6C alternate;
    Vec3_80093F6C copy;
    float angle;
    float turn_speed;

    component = fn_80201B94(object);
    fn_8011F114(&base, resource);
    turn_speed = target->mode != 0 ? lbl_8064EC9C : lbl_8064EC78;

    if (fn_80066D04(object, 0) == 0) {
        fn_80201D2C(object, 1);
        fn_80201D14(object, 1);
        return 1;
    }

    if ((flags1 & flags2) == 0) {
        fn_800359A0(object, 0);
    }

    if (fn_80201C48(component) != 0 && (other = fn_80201814()) != 0) {
            int delta;
            int distance;
            float speed;
            fn_802045AC(object, &position);
            delta = fn_80178E94(&base, &position);
            distance = (int)fn_800CB444(object, other);
            speed = fn_8011F6F8(resource);
            speed *= lbl_8064ECA0;

            if (delta < distance ||
                (delta < 600 &&
                 fn_8003E1F0(object, &position, 1, speed) != 0)) {
                copy = position;
                {
                    float direction = fn_8012B7D0(resource, &copy);
                    float heading = fn_8012B750(resource);
                    fn_8017A12C(&angle, heading, direction);
                }
                if (delta < distance) {
                    float magnitude = angle < lbl_8064EC7C ? -angle : angle;
                    if (magnitude <= lbl_8064ECA4) {
                        if (fn_800938E4(object, resource, value) == 0) {
                            fn_80201D2C(object, 1);
                            fn_80201D14(object, 1);
                        }
                        result = 1;
                        goto done;
                    }
                }

                if (fn_8012AFC4(resource) != 0) {
                    fn_80128E30(resource);
                    fn_80128C3C(turn_speed);
                    fn_80129928(resource, &position);
                } else {
                    fn_8012976C(turn_speed, resource, 2, 0x21, &position);
                }
            } else if (fn_800BE2CC(object, target, &alternate) != 0) {
                if ((unsigned)fn_80178E94(&base, &alternate) < 0x50) {
                    fn_800BE390(object, target);
                } else if (fn_8012AFC4(resource) != 0) {
                    fn_80128E30(resource);
                    fn_80128C3C(turn_speed);
                    fn_80129928(resource, &alternate);
                } else {
                    fn_8012976C(turn_speed, resource, 2, 0x21, &alternate);
                }
            } else {
                result = 1;
                fn_80201D2C(object, 1);
                fn_80201D14(object, 1);
            }
    } else {
        fn_80201D2C(object, 1);
        fn_80201D14(object, 1);
    }
done:
    return result;
}
