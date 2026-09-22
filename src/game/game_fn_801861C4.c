typedef signed char s8;
typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SixBytes {
    u32 word;
    u16 half;
} SixBytes;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef float Matrix34[3][4];

typedef struct Buffers {
    u8* vertices;
    u8* colors;
    u8* indices;
} Buffers;

typedef struct Quaternion {
    float x;
    float y;
    float z;
    float w;
} Quaternion;

extern u8 lbl_80607120[];
extern void* lbl_8064D738;
extern u32 lbl_80651D50;
extern u16 lbl_80651D54;
extern Vec3 lbl_8023B068;
extern const float lbl_80650A20;
extern const float lbl_80650A24;
extern const double lbl_80650A28;

extern void fn_8018D788(void*, void*, Buffers*, u16);
extern void fn_801869F8(void*, int, u16);
extern void fn_8018E26C(void*, void*);
extern void fn_8018680C(void*, void*, Vec3*, int, SixBytes*, u8);
extern void fn_8018E230(void*, void*, int, u8, u8, int);
extern void fn_80210FB0(Matrix34);
extern void fn_80211A48(Vec3*, Vec3*, Vec3*);
extern void fn_80211268(Matrix34, int, float);
extern void fn_80210FDC(Matrix34, Matrix34, Matrix34);
extern void fn_80211B64(Vec3*, Vec3*, Vec3*);
extern float fn_80211B08(Vec3*);
extern void fn_80211AAC(Vec3*, Vec3*);
extern float fn_80211B44(Vec3*, Vec3*);
extern double fn_80102340(float, float);
extern void fn_8017A244(Vec3*, Quaternion*, float);
extern void fn_802114E0(Matrix34, Quaternion*);
extern void fn_80211484(Matrix34, float, float, float);
extern void fn_80211710(Matrix34, Vec3*, Vec3*);

int fn_801861C4(u8* self)
{
    /* NonMatching: the conversion loop's hoisted 0x4330 uses r31 instead
     * of retail's r25. Buffers matches the three outputs of fn_8018D788;
     * indexed access lets GC/1.3 synthesize the first loop's byte offset. */
    SixBytes setup;
    Buffers buffers;
    Vec3 direction;
    Vec3 origin;
    Quaternion rotation;
    Vec3 transformed;
    Matrix34 transform;
    Matrix34 translation;
    Matrix34 x_rotation;
    Matrix34 y_rotation;
    Matrix34 z_rotation;
    Matrix34 combined;
    Matrix34 result;
    float length;
    float dot;
    int changed = 0;
    u8* self_local = self;
    u8 count;
    int generation;
    int index;
    u8* state;
    u8* entry;
    int vertex_index;
    int vertex_count;
    u8* vertex;

    state = self_local + 0x8C;
    setup.word = lbl_80651D50;
    setup.half = lbl_80651D54;
    generation = *(u16*)(self_local + 0xA);
    entry = *(u8**)(self_local + 0x4C);
    count = self_local[1];
    *(u16*)(self_local + 0xA) = generation + 1;

    fn_8018D788(lbl_8064D738, self_local, &buffers,
                *(u16*)(lbl_80607120 + 2));
    fn_801869F8(state, 0, *(u16*)(state + 8));

    index = 0;
    for (; index < count; index++) {
        if (entry[0] != 0) {
            fn_8018E26C(entry, entry + 0x2B);
            if (changed == 0 && (state[5] & 4) != 0) {
                if ((s8)state[1] > 2) {
                    state[1]--;
                } else if ((s8)state[1] < -2) {
                    state[1]++;
                }
                changed = 1;
            }
        }
        fn_8018680C(state, entry,
                    &((Vec3*)buffers.vertices)[index],
                    index, &setup, count);
        if ((int)generation == (int)*(u16*)(entry + 8) &&
            (state[5] & 1) == 0) {
            fn_8018E230(entry, entry + 0x2B, 1, self_local[2],
                        self_local[4], 0);
        }
        entry += 0x38;
    }

    origin = lbl_8023B068;
    vertex = buffers.vertices;
    vertex_count = (self_local[1] & 0x7F) << 1;
    fn_80210FB0(transform);
    fn_80211A48((Vec3*)(state + 0x60), (Vec3*)(state + 0x6C),
                (Vec3*)(state + 0x60));
    {
        float angle = *(float*)(state + 0x60);
        if (angle > lbl_80650A20)
            angle = *(float*)(state + 0x6C);
        *(float*)(state + 0x60) = angle;
    }
    {
        float angle = *(float*)(state + 0x64);
        if (angle > lbl_80650A20)
            angle = *(float*)(state + 0x70);
        *(float*)(state + 0x64) = angle;
    }
    {
        float angle = *(float*)(state + 0x68);
        if (angle > lbl_80650A20)
            angle = *(float*)(state + 0x74);
        *(float*)(state + 0x68) = angle;
    }

    fn_80211268(x_rotation, 0x78,
                lbl_80650A24 * *(float*)(state + 0x60));
    fn_80211268(y_rotation, 0x79,
                lbl_80650A24 * *(float*)(state + 0x64));
    fn_80211268(z_rotation, 0x7A,
                lbl_80650A24 * *(float*)(state + 0x68));
    fn_80210FDC(z_rotation, y_rotation, combined);
    fn_80210FDC(combined, x_rotation, result);

    fn_80211B64(&origin, (Vec3*)(state + 0x54), &direction);
    length = fn_80211B08(&direction);
    if (length > lbl_80650A28) {
        fn_80211AAC(&direction, &direction);
        dot = fn_80211B44(&origin, (Vec3*)(state + 0x54));
        fn_8017A244(&direction, &rotation,
                    (float)fn_80102340(length, dot));
        fn_802114E0(transform, &rotation);
    }
    fn_80210FDC(transform, result, transform);
    fn_80211484(translation, (float)*(s16*)(self_local + 0x10),
                 (float)*(s16*)(self_local + 0x12),
                 (float)*(s16*)(self_local + 0x14));
    fn_80210FDC(translation, transform, transform);

    vertex_index = 0;
    while (vertex_index < vertex_count) {
        transformed.x = (float)*(s16*)(vertex + 0);
        transformed.y = (float)*(s16*)(vertex + 2);
        transformed.z = (float)*(s16*)(vertex + 4);
        fn_80211710(transform, &transformed, &transformed);
        *(s16*)(vertex + 0) = (s16)transformed.x;
        *(s16*)(vertex + 2) = (s16)transformed.y;
        *(s16*)(vertex + 4) = (s16)transformed.z;
        vertex += 6;
        vertex_index++;
    }

    if ((*(u16*)(state + 0x40) & 2) != 0 ||
        ((state[5] & 1) == 0 &&
         (int)generation >= (int)*(u16*)(self_local + 0xC))) {
        *(u16*)(self_local + 0x22) = 8;
    }
    return 0;
}
