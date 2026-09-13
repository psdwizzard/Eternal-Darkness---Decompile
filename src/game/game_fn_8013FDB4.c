#pragma use_lmw_stmw on

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Result { Vec3 normal; Vec3 point; } Result;

extern const float lbl_806503D8;
extern int lbl_8064D18C;
extern void* fn_8013FBE4(void*, const void*, Result*, void*, unsigned int);
extern float fn_80211D4C(const void*, const Vec3*);
extern void *fn_80201B9C();
extern void *fn_80201BC8();
extern int fn_80201EB8();
extern void* fn_80201B94();
extern int fn_8011FAEC(void*);
extern int fn_80201CDC(void*);
extern int fn_80047C70(void*);
extern int fn_80136FF8(const void*, void*, Result*);
extern void* fn_80201BC0(void*);

int fn_8013FDB4(void* owner, const void* value, Result* out, void* skip,
                unsigned int flags, unsigned short* kind)
{
    Result candidate;
    float best;
    void* hit;
    Vec3* candidate_point;
    int found;

    *kind = 0;
    best = lbl_806503D8;
    found = 0;
    hit = fn_8013FBE4(owner, value, out, skip, flags);
    if (hit != 0) {
        *kind = *(unsigned short*)hit;
        found = 1;
        best = fn_80211D4C(value, &out->point);
    }
    if (flags & 2) {
        void* node = fn_80201B9C();

        candidate_point = &candidate.point;
        while (node != 0) {
            void* object = fn_80201BC8(node);
            if (lbl_8064D18C == fn_80201EB8(node) && object != 0 &&
                object != skip && fn_80201B94(node) != 0 &&
                (fn_8011FAEC(object) & 0x80) != 0 &&
                (fn_80201CDC(node) & 4) != 0 &&
                fn_80047C70(object) == 0 &&
                fn_80136FF8(value, object, &candidate)) {
                float distance = fn_80211D4C(value, candidate_point);
                found = 1;
                if (distance < best) {
                    best = distance;
                    *kind = 0;
                    *out = candidate;
                }
            }
            node = fn_80201BC0(node);
        }
    }
    return found;
}
