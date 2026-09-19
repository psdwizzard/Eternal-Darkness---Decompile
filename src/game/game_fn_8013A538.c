typedef struct Vec3 {
    float x, y, z;
} Vec3;
typedef struct Contact {
    Vec3 start;
    Vec3 end;
    float radius;
    Vec3 motion;
    float height;
} Contact;
typedef struct Matrix34 { float m[3][4]; } Matrix34;
typedef struct CollisionResult { unsigned int word[6]; } CollisionResult;

extern int lbl_8064B7E8;
extern int lbl_8064B7EC;
extern float lbl_806502CC;
extern unsigned int fn_8011FAEC(void*);
extern float fn_8011F6F8(void*);
extern float fn_8011F6F0(void*);
extern void fn_8013F3C0(Matrix34*, const Vec3*, const Vec3*, float);
extern int fn_80137350(void*, Matrix34*, void*, CollisionResult*, void*, void*);
extern int fn_8013A3C8(void*, Matrix34*, CollisionResult*, void*);
extern int fn_80137FF4(void*, Matrix34*, CollisionResult*);
extern float fn_80211D4C(const Contact*, const CollisionResult*);

/* Sweep the contact through all three collision back ends and retain the
 * nearest response.  The retail response/iteration state machine remains. */
int fn_8013A538(void* object, void* value, Contact* contact, int mode,
                CollisionResult* output, void* flags)
{
    Matrix34 primary_matrix;
    Matrix34 secondary_matrix;
    CollisionResult result[3];
    unsigned char primary_info[16];
    unsigned char secondary_info[16];
    int count[3];
    float nearest = lbl_806502CC;
    int selected = -1;
    int i;

    if ((fn_8011FAEC(object) & 2) != 0 || lbl_8064B7E8 == 0) {
        count[0] = 0;
    } else {
        float scale = fn_8011F6F8(object);
        fn_8013F3C0(&primary_matrix, &contact->start, &contact->end, scale);
        count[0] = fn_80137350(object, &primary_matrix, value, &result[0],
                              flags, primary_info);
    }

    if (lbl_8064B7EC == 0 || (fn_8011FAEC(object) & 0x40) == 0) {
        count[1] = 0;
        count[2] = 0;
    } else {
        float scale = fn_8011F6F0(object);
        fn_8013F3C0(&secondary_matrix, &contact->start, &contact->end, scale);
        count[1] = fn_8013A3C8(object, &secondary_matrix, &result[1],
                               secondary_info);
        count[2] = fn_80137FF4(object, &secondary_matrix, &result[2]);
    }

    for (i = 0; i < 3; i++) {
        if (count[i] != 0) {
            float distance = fn_80211D4C(contact, &result[i]);
            if (distance < nearest) {
                nearest = distance;
                selected = i;
                *output = result[i];
            }
        }
    }

    (void)mode;
    return selected != -1;
}
