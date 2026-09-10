typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Matrix {
    float m[12];
} Matrix;

typedef struct EntryTable {
    unsigned char pad[0xA4];
    unsigned int first;
    unsigned char padA8[4];
    unsigned int second;
} EntryTable;

extern Matrix lbl_8063BF28;
extern Vec3 lbl_8023B820;
extern int lbl_8064CBA4;
extern const float lbl_80651464;
extern const float lbl_80651478;
extern const float lbl_806514DC;
extern const float lbl_806514E0;
extern const float lbl_806514E4;
extern const float lbl_806514E8;
extern const float lbl_806514EC;
extern const double lbl_80651480;

extern void* memcpy(void*, const void*, unsigned int);
extern int fn_801FA250(int, int, int);
extern EntryTable* fn_8015C28C(int);
extern void fn_80179DB0(Vec3*, Vec3*);
extern void* fn_8011F130(void*);
extern float fn_8013CBE4(Vec3*, Vec3*, void*, Vec3*, int);
extern void fn_802118E0(Matrix*, float, float, float, float);
extern void fn_8011F114(Vec3*, void*);
extern int fn_801FBD2C(Vec3*, Vec3*, Vec3*, Vec3*, float);

int fn_801FC034(void* object, int value, float threshold)
{
    Vec3 first;
    Vec3 second;
    Vec3 intersection;
    Vec3 fixed;
    Vec3 position;
    Vec3 object_position;
    Matrix saved;
    EntryTable* table;
    unsigned int first_entry;
    unsigned int second_entry;
    int index;
    int area;
    float factor;
    float fraction;

    index = fn_801FA250(value, 2, 0);
    table = fn_8015C28C(2);
    factor = lbl_806514DC;
    if (lbl_8064CBA4 == 1) {
        factor = lbl_806514E0;
    }
    first_entry = table->first + index * 0x78;
    second_entry = table->second + index * 0x78;
    fn_80179DB0(&first, (Vec3*)first_entry);
    fn_80179DB0(&second, (Vec3*)second_entry);
    fraction = fn_8013CBE4(&first, &second, fn_8011F130(object),
                           &intersection, 0);
    if (fraction < lbl_80651464 || fraction > lbl_80651478) {
        return 0;
    }
    memcpy(&saved, &lbl_8063BF28, sizeof(Matrix));
    fn_802118E0(&lbl_8063BF28, *(float*)(first_entry + 0x24), factor, lbl_80651478,
                lbl_806514E4);
    fn_8011F114(&object_position, object);
    position = object_position;
    fixed = lbl_8023B820;
    area = fn_801FBD2C(&first, &second, &fixed, &position, lbl_806514E8);
    memcpy(&lbl_8063BF28, &saved, sizeof(Matrix));
    return ((float)area / lbl_806514EC) > threshold;
}
