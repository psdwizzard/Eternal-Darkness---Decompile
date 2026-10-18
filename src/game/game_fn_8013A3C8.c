typedef struct Contact {
    unsigned char data[0x18];
    float value18;
    unsigned char pad1C[0x0C];
    float value28;
} Contact;

typedef struct Result {
    unsigned int word[6];
} Result;

extern float lbl_806502CC;
extern float lbl_806502D0;
extern float lbl_806502D4;

extern void *fn_80201B9C();
extern void *fn_80201BC8();
extern void* fn_80201BC0(void*);
extern void* fn_80201CDC(void*);
extern void* fn_8011FB4C(void*);
extern unsigned int fn_8011FAEC(void*);
extern int fn_80137658(void*, Contact*, void*, void*, float);
extern int fn_801377A4(void*, Contact*, void*, void*);
extern float PSVECSquareDistance(Contact*, void*);

int fn_8013A3C8(void* object, Contact* contact, Result* result, void** hit)
{
    float best = lbl_806502CC;
    int found = 0;
    void* iterator = fn_80201B9C();
    int group = (int)fn_8011FB4C(object);

    while (iterator != 0) {
        void* other = fn_80201BC8(iterator);
        if (other != 0 && object != other &&
            (fn_8011FAEC(other) & 0x80) != 0 &&
            group == (int)fn_8011FB4C(other) &&
            (((unsigned int)fn_80201CDC(iterator) & 4) == 0)) {
            unsigned char local[24];
            int ok;

            if (contact->value28 >= lbl_806502D0 && contact->value28 <= lbl_806502D4) {
                ok = fn_80137658(object, contact, other, local, contact->value18);
            } else {
                ok = fn_801377A4(object, contact, other, local);
            }
            if (ok != 0) {
                float distance = PSVECSquareDistance(contact, local);
                found = 1;
                if (distance < best) {
                    best = distance;
                    *result = *(Result*)local;
                    *hit = other;
                }
            }
        }
        iterator = fn_80201BC0(iterator);
    }
    return found;
}
