typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Contact { u8 bytes[24]; } Contact;
typedef struct QueryObject {
    Vec3 position;
    Vec3 direction;
    u8 pad18[0x10];
    float limit;
} QueryObject;

extern float lbl_80650428;
extern float lbl_8065042C;
extern int fn_8013FDB4(void*, QueryObject*, Contact*, int, int, void*);
extern void fn_8013F600(Contact*, Vec3*, float*);
extern void fn_8013C5F4(QueryObject*, Contact*, Vec3*, float, float);
extern float PSVECSquareDistance(Vec3*, Vec3*);

int fn_80142808(void* world, QueryObject* query, Contact* output,
                float distance, float threshold)
{
    Vec3 original = query->position;
    Contact contact;
    Vec3 normal;
    float plane;
    float query_result;
    int clear = 1;

    if (lbl_80650428 == query->limit || query->limit <= threshold)
        return 0;
    if (fn_8013FDB4(world, query, &contact, 0, 2, &query_result)) {
        clear = 0;
        fn_8013F600(&contact, &normal, &plane);
        fn_8013C5F4(query, &contact, &normal, plane, distance);
        *output = contact;
    }
    if (clear)
        return 1;
    return PSVECSquareDistance(&query->direction, &original) < lbl_8065042C ? 3 : 2;
}
