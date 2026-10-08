typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

typedef struct FourWords {
    u32 words[4];
} FourWords;

typedef union RotationValue {
    Vec4 vector;
    FourWords words;
} RotationValue;

typedef struct QueryResult {
    u8 pad_0[8];
    Vec3 position;
    Vec3 direction;
    u8 pad_20[8];
} QueryResult;

typedef struct EntryRecord {
    u8 pad_0[0xE];
    u16 record_index;
} EntryRecord;

typedef struct Entry {
    u8 pad_0[4];
    EntryRecord* record;
} Entry;

typedef struct RuntimeState {
    u8 pad_0[0x44];
    int state;
} RuntimeState;

typedef struct ObjectRecord {
    u8 pad_0[0x48];
    void* value;
} ObjectRecord;

typedef struct Object {
    u8 pad_0[0x160];
    ObjectRecord* records;
    u8 pad_164[0xDC];
    Entry** entries;
    u8 pad_244[0x4C];
    RuntimeState* runtime;
} Object;

extern int lbl_8064CF30;
extern int lbl_8064CF34;
extern const float lbl_80650210;
extern const float lbl_80650214;

extern void fn_80125ECC(void*);
extern int fn_8011F6A4(void*, int, int, int, void*, int);
extern int fn_8012EF98(void*, int, QueryResult*, QueryResult*,
                       const Vec3*, Vec4*, float);
extern void fn_8012CEA4(u8*, int, Vec4*);
extern float fn_8017A5A8(const Vec4*, const Vec4*, float);
extern void fn_8017A7D4(const Vec4*, const Vec4*, float, Vec4*);
extern void fn_8012CDF0(u8*, int, FourWords, int);
extern void fn_8012F474(void*, int, int, int, const Vec3*, Vec3*, Vec3*);

static Vec3 point0 = {0};
static Vec3 point1 = {0};
static Vec3 point2 = {0};
static Vec3 point3 = {0};
static Vec3 point4 = {0};
static Vec3 point5 = {0};
static Vec3 point6 = {0};
static Vec3 point7 = {0};
static Vec3 point8 = {0};
static Vec3 point9 = {0};

int fn_8012F2DC(Object* object, const Vec3* target, int index,
                void* query_object, int query_key)
{
    QueryResult first;
    QueryResult second;
    Vec4 desired;
    Vec4 current;
    RotationValue blended;
    Entry* entry;

    fn_80125ECC(object);
    entry = object->entries[index];
    if (entry != 0) {
        object->records[entry->record->record_index].value = 0;
        fn_8011F6A4(query_object, query_key, 15, -1, &first, 1);
        fn_8011F6A4(query_object, query_key, 15, -1, &second, 4);

        point9 = first.position;
        lbl_8064CF34 = 1;
        if (fn_8012EF98(object, index, &first, &second, target, &desired,
                        lbl_80650210)) {
            float amount;

            fn_8012CEA4((u8*)object, index, &current);
            amount = fn_8017A5A8(&current, &desired, lbl_80650214);
            fn_8017A7D4(&current, &desired, amount, &blended.vector);
            fn_8012CDF0((u8*)object, index, blended.words, 0);

            if (lbl_8064CF30 != 0 && object->runtime->state > 0) {
                fn_8012F474(object, 0, 15, query_key, &point0, &point1, &point2);
            }
        }
    }
    return 0;
}
