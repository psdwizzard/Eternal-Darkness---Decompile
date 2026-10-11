typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

typedef struct ObjectData {
    u8 pad[0x9F];
    u8 kind;
} ObjectData;


extern s32 fn_80201B44(void);
extern s32 fn_80201B54(s32);
extern s32 fn_80201814(s32);
extern s32 fn_80201BC8();
extern ObjectData *fn_80201B8C(s32);
extern void fn_8011F114(Vec3f *, s32);
extern s32 fn_80036D5C(s32);
extern u8 fn_80204434(s32, Vec3f *, s32, float);
extern s32 fn_8012AB2C(s32);
extern float fn_8011F6F8(s32);
extern void fn_8013F3C0(void *, Vec3f *, Vec3f *, float);
extern u32 fn_8013FBE4(s32, void *, void *, s32, s32);
extern s32 fn_801A717C(void);
extern void fn_801A74A0(s32, s32);
extern void fn_801A74A8(s32, s32);
extern void fn_801A7538(s32, s32);
extern void fn_801A7518(s32, s32);
extern void fn_801A7470(s32, s32);
extern void fn_801A764C(s32, Vec3f *);
extern void fn_8020104C(s32, s32, s32, s32, float);
extern void fn_80036DA4(s32, s32);
extern void fn_801A977C(s32, s32);
extern float lbl_8064F29C;
extern double lbl_8064F2F8;
extern float lbl_8064F300;
extern float lbl_8064F304;

s32 fn_800CC650(s32 object, s32 flags, s32 mode, s32 param3)
{
    u8 matrix[0x3C];
    u8 pad2C[0x0C];
    u8 result[0x0C];
    Vec3f second_pos;
    Vec3f first_pos;
    s32 actor;
    s32 object_id;
    u32 actor_id;
    u32 object_transform;
    u32 actor_object;
    s32 sound;
    s32 model;
    s32 candidate;

    actor = fn_80201B44();
    object_id = fn_80201B54(object);
    actor_id = fn_80201814(actor);
    actor_object = fn_80201BC8();
    object_transform = fn_80201BC8(object);
    if (fn_80201B8C(actor_id)->kind != 1)
        return 0;
    {
        if (actor_object != 0)
            fn_8011F114(&first_pos, actor_object);
        if (actor_id != 0 && (flags & fn_80036D5C(object)) == 0 &&
            actor_object != 0 && object_transform != 0 &&
            fn_80204434(object_transform, &first_pos, 0, lbl_8064F300) != 0) {
            candidate = fn_8012AB2C(object_transform);
            fn_8011F114(&second_pos, object_transform);
            {
                double delta = lbl_8064F2F8 + fn_8011F6F8(object_transform);
                second_pos.z = (float)((double)second_pos.z + delta);
            }
            {
                double delta = lbl_8064F2F8 + fn_8011F6F8(object_transform);
                first_pos.z = (float)((double)first_pos.z + delta);
            }
            fn_8013F3C0(matrix, &second_pos, &first_pos, lbl_8064F304);
            if (fn_8013FBE4(candidate, matrix, result, 0, 8) == 0) {
                sound = fn_801A717C();
                fn_801A74A0(sound, object_id);
                fn_801A74A8(sound, actor);
                fn_801A7538(sound, 2);
                fn_801A7518(sound, param3);
                fn_801A7470(sound, -1);
                fn_801A764C(sound, &second_pos);
                fn_8020104C(0x3A, object_id, actor, sound, lbl_8064F29C);
                fn_80036DA4(object, flags | fn_80036D5C(object));
                if (mode != -1)
                    fn_801A977C(object_transform, 0x17);
                return 1;
            }
        }
    }
    return 0;
}
