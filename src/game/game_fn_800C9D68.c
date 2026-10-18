typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct QueryResult {
    u8 pad[8];
    Vec3 position;
    u8 tail[0x18];
} QueryResult;

typedef struct Identifiers {
    u32 value[4];
} Identifiers;

extern const Identifiers lbl_802398B8;
extern u32 lbl_8064F2A8;
extern float lbl_8064F2AC;
extern float lbl_8064F2B0;

extern void *fn_80201BC8();
extern unsigned int rand(void);
extern int fn_8011F6A4(void *, int, int, int, QueryResult *, int);
extern void fn_8014D478(void *, Vec3 *, Vec3 *, int, int, void *, int);

void fn_800C9D68(void *object, float value)
{
    void *runtime;

    if (object != 0 && (runtime = fn_80201BC8(object)) != 0 &&
        value < lbl_8064F2AC) {
        Vec3 direction;
        Identifiers identifiers;
        u32 resource;
        QueryResult result;
        u32 random;

        resource = lbl_8064F2A8;
        identifiers = lbl_802398B8;
        random = rand();
        direction.x = lbl_8064F2B0;
        direction.y = lbl_8064F2B0;
        direction.z = lbl_8064F2B0;
        if (fn_8011F6A4(runtime, 0x14,
                        identifiers.value[random & 3], -1,
                        &result, 1) != -1) {
            fn_8014D478(runtime, &result.position, &direction,
                        0, 1, &resource, 1);
        }
    }
}
