typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Contact {
    Vec3 first;
    Vec3 second;
    float radius;
    unsigned char pad1C[0x0C];
    float kind;
} Contact;
typedef struct Result { unsigned int word[6]; } Result;

extern int lbl_8064B7EC;
extern void* lbl_8064C4E4;
extern float lbl_806502B8;
extern float lbl_806502BC;
extern float lbl_806502CC;
extern float lbl_806502D0;
extern float lbl_806502D4;
extern int fn_8011EB04(void*);
extern int fn_8011EB1C(void*);
extern void* fn_8011F130(void*);
extern int fn_8011FB4C(void*);
extern unsigned int fn_8011FAEC(void*);
extern unsigned int fn_8011FA8C(void*, int, int);
extern unsigned int fn_8011FABC(void*, int, int);
extern void* fn_80201B9C(void);
extern void* fn_80201BC8(void*);
extern void* fn_80201BC0(void*);
extern int fn_80137658(void*, Contact*, void*, Result*, float);
extern int fn_801377A4(void*, Contact*, void*, Result*);
extern int fn_80137FF4(void*, Contact*, Result*);
extern float fn_80211D4C(Result*, Contact*);
extern void fn_8013F600(Result*, Vec3*, float*);
extern void fn_8013C518(Vec3*, Vec3*, float, float);
extern void fn_8013C460(Vec3*, Vec3*, float, float);
extern void fn_8013F3C0(Contact*, Vec3*, Vec3*, float);

/* Iterative contact correction reconstructed from the retail control flow. */
int fn_8013AD48(void* object, Contact* contact, Result* output)
{
    int group;
    void* iterator;
    void* other;
    int active;
    unsigned char pass;
    unsigned short contacts;
    unsigned char zero_kind;
    unsigned char repeated;

    fn_8011EB04(object);
    fn_8011EB1C(object);
    group = fn_8011FB4C(object);
    fn_80201B9C();
    active = 1;
    pass = 0;
    zero_kind = 0;
    repeated = 0;
    if (lbl_8064B7EC == 0 || (fn_8011FAEC(object) & 0x40) == 0)
        return 0;
    if (lbl_806502B8 == contact->kind)
        return 1;

    do {
        float best = lbl_806502CC;
        Result candidate;

        iterator = fn_80201B9C();
        contacts = 0;
        while (iterator != 0) {
            other = fn_80201BC8(iterator);
            if (other != 0 && object != other &&
                fn_8011FB4C(other) == group &&
                (fn_8011FAEC(other) & 0x80) != 0) {
                int ok;
                if (contact->kind >= lbl_806502D0 &&
                    contact->kind <= lbl_806502D4)
                    ok = fn_80137658(object, contact, other, &candidate,
                                    contact->radius);
                else
                    ok = fn_801377A4(object, contact, other, &candidate);
                if (ok != 0) {
                    float distance;
                    Vec3 normal;
                    float amount;

                    fn_8011F130(other);
                    distance = fn_80211D4C(&candidate, contact);
                    if (distance < best) {
                        best = distance;
                        *output = candidate;
                    }
                    fn_8011FA8C(other, 0, 0x200000);
                    if (fn_8011EB1C(other) == 3)
                        fn_8011FA8C(object, 0, 0x10);
                    else
                        fn_8011FABC(object, 0, 2);
                    if (object == lbl_8064C4E4)
                        fn_8011FA8C(other, 0, 0x40000000);

                    fn_8013F600(&candidate, &normal, &amount);
                    if ((fn_8011FAEC(other) & 0x100000) != 0)
                        fn_8013C518(&contact->first, &normal,
                                    lbl_806502BC + contact->radius, amount);
                    else
                        fn_8013C460(&contact->first, &normal,
                                    lbl_806502BC + contact->radius, amount);
                    if ((fn_8011FAEC(other) & 0x100000) != 0)
                        fn_8013C518(&contact->second, &normal,
                                    lbl_806502BC + contact->radius, amount);
                    else
                        fn_8013C460(&contact->second, &normal,
                                    lbl_806502BC + contact->radius, amount);
                    fn_8013F3C0(contact, &contact->first, &contact->second,
                                contact->radius);
                    if (lbl_806502B8 == contact->kind) {
                        if (zero_kind != 0)
                            repeated = 1;
                        zero_kind = 1;
                    } else {
                        zero_kind = 0;
                    }
                    active = 0;
                    ++contacts;
                }
            }
            iterator = fn_80201BC0(iterator);
        }

        if (fn_80137FF4(object, contact, &candidate) != 0) {
            Vec3 normal;
            float amount;
            float distance = fn_80211D4C(&candidate, contact);
            if (distance < best)
                *output = candidate;
            fn_8013F600(&candidate, &normal, &amount);
            fn_8013C518(&contact->first, &normal,
                        lbl_806502BC + contact->radius, amount);
            fn_8013C518(&contact->second, &normal,
                        lbl_806502BC + contact->radius, amount);
            fn_8013F3C0(contact, &contact->first, &contact->second,
                        contact->radius);
            if (lbl_806502B8 == contact->kind) {
                if (zero_kind != 0)
                    repeated = 1;
                zero_kind = 1;
            } else {
                zero_kind = 0;
            }
            active = 0;
            ++contacts;
        }

        ++pass;
        if (contacts != 0 && pass < 8 && repeated == 0)
            continue;
        if (pass < 8 && contacts == 0) {
            int result = 2;
            if (active != 0)
                result = 0;
            return result;
        }
        return 3;
    } while (1);
}
