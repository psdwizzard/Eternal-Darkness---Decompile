typedef struct Entry80201B3C Entry80201B3C;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Actor {
    unsigned char pad00[0x20];
    Vec3 position;
    unsigned char pad2C[0x2C];
    float heading;
} Actor;

typedef struct CameraState {
    unsigned char pad00[0x40];
    int enabled;
} CameraState;

extern Entry80201B3C *fn_80201B3C(void);
extern void *fn_80201BC8(void *object);
extern void *fn_80201B8C(unsigned char *object);
extern void fn_8011F0E8(Vec3 *destination, Vec3 *source);
extern void fn_8012B7A0();
extern void fn_801FA454(unsigned short state, int token);
extern void fn_801FA748(int index, Vec3 *position);
extern void fn_80088F4C(void);
extern int fn_801F86F4(int index);
extern void fn_8016B400(int id, void *context, void *value);
extern int fn_801E79FC(unsigned int *set, unsigned int index);
extern void fn_8016ADF0(short id, short value2, short value4);

extern int lbl_8064D18C;
extern float lbl_8064F85C;
extern float lbl_8064F860;
extern Vec3 lbl_80239B80;
extern CameraState lbl_8063D378;
extern CameraState lbl_8063D400;
extern unsigned int *lbl_8064C4E0;

void fn_800EAA84(int arg)
{
    Entry80201B3C *entry;
    Vec3 *object;
    Actor **slot;
    Vec3 position;

    entry = fn_80201B3C();
    if (entry) {
        object = fn_80201BC8(entry);
        slot = entry ? (Actor **)fn_80201B8C((unsigned char *)entry) : 0;
        if (lbl_8064D18C == 0xBE) {
            Actor *actor = *slot;
            if (actor->position.z < lbl_8064F85C) {
                actor->position.z = lbl_8064F860;
            }
        }
        fn_8011F0E8(object, &(*slot)->position);
        fn_8012B7A0(object, (*slot)->heading);
        fn_801FA454(2, 2);
        position = lbl_80239B80;
        fn_801FA748(2, &position);
        fn_80088F4C();
        if (fn_801F86F4(0)) {
            lbl_8063D378.enabled = 1;
            lbl_8063D400.enabled = 1;
        }
        if (arg == 0) {
            fn_8016B400(0x3FF, 0, 0);
        }
        if (fn_801E79FC(lbl_8064C4E0, 0x2BA)) {
            fn_8016ADF0(0xAE8, 7, 1);
        }
    }
}
