typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed char s8;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Entry80201814 Entry80201814;

extern int lbl_8064D18C;
extern u32 lbl_8064C8A8;
extern float lbl_8064E7A4;
extern const float lbl_8064E7A8;
extern float lbl_8064E7AC;

extern int fn_802019EC(int resource, int manager);
extern Entry80201814 *fn_80201814(int id);
extern void *fn_80201BC8(void *object);
extern int fn_8006AEA4(int object);
extern float fn_8006AF20(void *object, int kind);
extern void fn_8011F114(Vec3 *destination, Vec3 *source);
extern void fn_8011F0E8(Vec3 *destination, Vec3 *source);
extern int fn_801AAE68(u16 id, u8 volume, u8 value, float magnitude,
                     Vec3 *position, s8 active, u8 mode, u8 option,
                     u16 kind, u32 flags);
extern void fn_801AC980(u32 key, int value);

void fn_8006ACC4(int object)
{
    Vec3 position;
    int id;
    int kind;
    float magnitude;
    Entry80201814 *entry;
    Vec3 *runtime;

    id = fn_802019EC(0x54, lbl_8064D18C);
    if (id != -1 && (entry = fn_80201814(id)) != 0 &&
        (runtime = fn_80201BC8(entry)) != 0) {
        kind = fn_8006AEA4(object);
        if (fn_8006AF20(entry, kind) > lbl_8064E7A4) {
            if (lbl_8064C8A8 == 0) {
                magnitude = lbl_8064E7A8;
                lbl_8064C8A8 = fn_801AAE68(0x62, 0x7F, 0, magnitude,
                                         &position, 1, 2, 0,
                                         (u16)lbl_8064D18C, 0);
            }
            fn_8011F114(&position, runtime);
            position.z -= lbl_8064E7AC;
            fn_8011F0E8(runtime, &position);
        } else if (lbl_8064C8A8 != 0) {
            fn_801AC980(lbl_8064C8A8, 0x3C);
            lbl_8064C8A8 = 0;
        }
    }
}
