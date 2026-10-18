typedef struct Vec3 {
    float x, y, z;
} Vec3;
typedef struct Contact {
    Vec3 start;
    Vec3 end;
    float radius;
    Vec3 motion;
    float height;
    Vec3 center;
    float bound_radius;
} Contact;
typedef struct CollisionResult { Vec3 start, end; } CollisionResult;

extern int lbl_8064B7E8;
extern int lbl_8064B7EC;
extern float lbl_806502CC;
extern float lbl_806502D8;
extern float lbl_806502DC;
extern float lbl_806502E0;
extern float lbl_806502E4;
extern float lbl_806502B8;
extern float lbl_806502BC;
extern float lbl_806502EC;
extern float lbl_806502F8;
extern float lbl_806502E8;
extern double lbl_806502F0;
extern int lbl_8064D18C;
extern void* lbl_8064C4E4;
extern unsigned int fn_8011FAEC(void*);
extern float fn_8011F6F8(void*);
extern float fn_8011F6F0(void*);
extern void fn_8013F3C0(Contact*, const Vec3*, const Vec3*, float);
extern int fn_80137350(void*, Contact*, void*, CollisionResult*, void*, void*);
extern int fn_8013A3C8(void*, Contact*, CollisionResult*, void*);
extern int fn_80137FF4(void*, Contact*, CollisionResult*);
extern float PSVECSquareDistance(const void*, const void*);
extern void* fn_8011F8FC(void*);
extern int fn_8011EB1C(void*);
extern unsigned int fn_8011FA8C(void*, int, unsigned int);
extern unsigned int fn_8011FABC(void*, int, unsigned int);
extern void fn_8011F918(void*);
extern void fn_8011F90C(void*);
extern void fn_8012A24C(void*, unsigned short);
extern void fn_8013F600(CollisionResult*, Vec3*, float*);
extern void fn_80140408(Vec3*, CollisionResult*, void*);
extern void fn_8013C460(Vec3*, const Vec3*, float, float);
extern void fn_8013C518(Vec3*, const Vec3*, float, float);
extern void PSVECSubtract(const Vec3*, const Vec3*, Vec3*);
extern void PSVECNormalize(Vec3*, const Vec3*);
extern float PSVECDotProduct(const Vec3*, const Vec3*);

/* Each backend corrects its local sweep before rebuilding the caller's
 * contact. A no-hit probe updates support state; exhausted retries restore
 * the original start point. */
int fn_8013A538(void* object, void* value, Contact* contact, int mode,
                CollisionResult* output, void* flags)
{
    Contact primary_shape;
    Contact secondary_shape;
    CollisionResult result[3];
    unsigned short primary_info;
    void* secondary_info;
    int count[3];
    Vec3 initial_start = contact->start;
    float radius = contact->radius;
    Vec3 previous_start = contact->start;
    Vec3 previous_end = contact->end;
    int i;
    unsigned char pass = 0;
    unsigned char zero_kind = 0;
    unsigned char repeated = 0;
    int selected;
    signed char primary_state = 0;
    signed char secondary_state = 0;
    int did_mode_response = 0;

    do {
        float nearest = lbl_806502CC;
        float height = contact->height;
        selected = -1;

        if ((fn_8011FAEC(object) & 2) != 0 || lbl_8064B7E8 == 0) {
            count[0] = 0;
        } else {
            float scale = fn_8011F6F8(object);
            fn_8013F3C0(&primary_shape, &contact->start, &contact->end, scale);
            count[0] = fn_80137350(object, &primary_shape, value, &result[0],
                                  flags, &primary_info);
        }

        if (lbl_8064B7EC == 0 || (fn_8011FAEC(object) & 0x40) == 0) {
            count[1] = 0;
            count[2] = 0;
        } else {
            float scale = fn_8011F6F0(object);
            fn_8013F3C0(&secondary_shape, &contact->start, &contact->end, scale);
            count[1] = fn_8013A3C8(object, &secondary_shape, &result[1],
                                   &secondary_info);
            count[2] = fn_80137FF4(object, &secondary_shape, &result[2]);
        }

        for (i = 0; i < 3; i++) {
            if (count[i] != 0) {
                float distance = PSVECSquareDistance(contact, &result[i]);
                if (distance < nearest) {
                    nearest = distance;
                    selected = i;
                    *output = result[i];
                }
            }
        }

        if (selected != -1) {
            switch (selected) {
            case 0: {
                Vec3 normal;
                float amount;
                void* body = fn_8011F8FC(object);
                int special = 0;
                fn_8012A24C(object, primary_info);
                fn_8013F600(output, &normal, &amount);
                fn_80140408(&normal, output, body);
                if (mode != 0) {
                    float threshold = lbl_806502D8;
                    float dot = PSVECDotProduct((Vec3*)body, &normal);
                    if (lbl_8064D18C == 0x32)
                        threshold = lbl_806502DC;
                    if (dot <= threshold) {
                        special = 1;
                        primary_shape.end = output->end;
                        primary_shape.start = primary_shape.end;
                        if (dot > lbl_806502E0 && object == lbl_8064C4E4)
                            fn_8011FA8C(object, 0x10, 0);
                    }
                    if (dot > lbl_806502E4)
                        fn_8011F918(object);
                    else
                        fn_8011F90C(object);
                    did_mode_response = 1;
                }
                if (!special) {
                    fn_8013C460(&primary_shape.start, &normal,
                                lbl_806502BC + primary_shape.radius, amount);
                    fn_8013C460(&primary_shape.end, &normal,
                                lbl_806502BC + primary_shape.radius, amount);
                }
                fn_8013F3C0(contact, &primary_shape.start, &primary_shape.end,
                            radius);
                break;
            }
            case 1: {
                Vec3 normal;
                float amount;
                fn_8011FA8C(secondary_info, 0, 0x200000);
                if (fn_8011EB1C(secondary_info) == 3)
                    fn_8011FA8C(object, 0, 0x10);
                else
                    fn_8011FABC(object, 0, 2);
                if (object == lbl_8064C4E4)
                    fn_8011FA8C(secondary_info, 0, 0x40000000);
                fn_8013F600(output, &normal, &amount);
                if ((fn_8011FAEC(secondary_info) & 0x100000) != 0) {
                    fn_8013C518(&secondary_shape.start, &normal,
                                lbl_806502BC + secondary_shape.radius, amount);
                    fn_8013C518(&secondary_shape.end, &normal,
                                lbl_806502BC + secondary_shape.radius, amount);
                } else {
                    fn_8013C460(&secondary_shape.start, &normal,
                                lbl_806502BC + secondary_shape.radius, amount);
                    fn_8013C460(&secondary_shape.end, &normal,
                                lbl_806502BC + secondary_shape.radius, amount);
                }
                fn_8013F3C0(contact, &secondary_shape.start, &secondary_shape.end,
                            radius);
                break;
            }
            case 2: {
                Vec3 normal;
                float amount;
                fn_8011FABC(object, 0, 0x10);
                fn_8013F600(output, &normal, &amount);
                fn_8013C518(&secondary_shape.start, &normal,
                            lbl_806502BC + secondary_shape.radius, amount);
                fn_8013C518(&secondary_shape.end, &normal,
                            lbl_806502BC + secondary_shape.radius, amount);
                fn_8013F3C0(contact, &secondary_shape.start, &secondary_shape.end,
                            radius);
                break;
            }
            }

            if (PSVECSquareDistance(&previous_start, &contact->start) == lbl_806502B8 &&
                PSVECSquareDistance(&previous_end, &contact->end) == lbl_806502B8) {
                if (zero_kind)
                    repeated = 1;
                zero_kind = 1;
            } else {
                zero_kind = 0;
            }
            previous_start = contact->start;
            previous_end = contact->end;

            if (!primary_state && mode == 0) {
                if (selected == 0) {
                    Vec3 direction;
                    void* body = fn_8011F8FC(object);
                    float dot;
                    PSVECSubtract(&output->end,
                                &output->start, &direction);
                    PSVECNormalize(&direction, &direction);
                    dot = PSVECDotProduct((Vec3*)body, &direction);
                    if (dot <= lbl_806502E8) {
                        if (contact->height < lbl_806502EC * height) {
                            if (contact->height > lbl_806502F0)
                                fn_8011FA8C(object, 0, 0x10);
                        } else if (contact->height > lbl_806502F8 * height) {
                            fn_8011FA8C(object, 0x10, 0);
                        }
                    } else {
                        fn_8011FA8C(object, 0, 0x10);
                    }
                } else {
                    fn_8011FA8C(object, 0x10, 0);
                }
                primary_state = 1;
            }
            if (!secondary_state) {
                if (selected == 1) {
                    if (contact->height < lbl_806502EC * height)
                        fn_8011FA8C(object, 0, 0x20);
                    else
                        fn_8011FA8C(object, 0x20, 0);
                } else {
                    fn_8011FA8C(object, 0x20, 0);
                }
                secondary_state = 1;
            }
        } else {
            if (!secondary_state) {
                fn_8011FA8C(object, 0x20, 0);
                secondary_state = 1;
            }
            if (!primary_state && mode == 0) {
                Vec3 probe_end;
                Contact probe;
                CollisionResult probe_result;
                probe_end.x = contact->end.x + lbl_806502BC * contact->motion.x;
                probe_end.y = contact->end.y + lbl_806502BC * contact->motion.y;
                probe_end.z = contact->end.z + lbl_806502BC * contact->motion.z;
                fn_8013F3C0(&probe, &contact->start, &probe_end, fn_8011F6F8(object));
                if ((fn_8011FAEC(object) & 2) == 0 && lbl_8064B7E8 != 0) {
                    if (fn_80137350(object, &probe, value, &probe_result,
                                    flags, &primary_info) == 0)
                        fn_8011FA8C(object, 0x10, 0);
                }
                primary_state = 1;
            }
            if (mode != 0 && !did_mode_response) {
                fn_8011F918(object);
                did_mode_response = 1;
            }
        }
        ++pass;
    } while (selected != -1 && pass < 8 && !repeated);

    if (pass >= 8 && (selected != -1 || !repeated)) {
        fn_8013F3C0(contact, &initial_start, &initial_start, radius);
        return 0;
    }
    return 1;
}
