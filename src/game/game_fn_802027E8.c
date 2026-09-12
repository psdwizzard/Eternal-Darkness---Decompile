typedef unsigned int u32;

typedef struct Vec3i802027E8 {
    int x;
    int y;
    int z;
} Vec3i802027E8;

extern void *lbl_8064C4E4;

extern void fn_8011F114(Vec3i802027E8 *position, void *object);
extern u32 fn_80178E94(Vec3i802027E8 *first, Vec3i802027E8 *second);
extern void fn_801F74C8(int first, int second, int third);
extern void fn_801441C0(int first, int second, int third);

int fn_802027E8(void *object)
{
    Vec3i802027E8 object_position;
    Vec3i802027E8 player_position;
    u32 distance;

    fn_8011F114(&object_position, object);
    fn_8011F114(&player_position, lbl_8064C4E4);
    distance = fn_80178E94(&object_position, &player_position);

    if (distance < 500) {
        fn_801F74C8(15, 1, 5);
        fn_801441C0(1, 1, 35);
    } else if (distance < 1000) {
        fn_801F74C8(15, 1, 3);
        fn_801441C0(1, 1, 22);
    } else if (distance < 2000) {
        fn_801F74C8(15, 1, 1);
        fn_801441C0(1, 1, 10);
    }

    return 1;
}
