/* Moves an actor toward its target, raising the goal height by the
 * distance to the room floor before handing the goal to the target. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
typedef float f32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec3s { s16 x, y, z; } Vec3s;
typedef struct QueryResult { u8 pad00[0x10]; f32 height; u8 pad14[0x18]; } QueryResult;

extern void* fn_80201B94();
extern void* fn_8018095C(void*);
extern Vec3s* fn_8017FDA8(void*, int);
extern int fn_80201B44();
extern void* fn_80201814();
extern void* fn_80201BC8();
extern void fn_800CE24C(void*, Vec3*, int, int, int);
extern void fn_802045AC(void*, Vec3*);
extern u32 fn_8019BBB4(void*);
extern int fn_800BE2CC(void*, void*, Vec3*);
extern int fn_8011F598(void*, int, int, int, QueryResult*, int);
extern Vec3* fn_8011F130(void*);
extern void fn_800BE390(void*, void*);
extern void fn_8019BBCC(void*, u32, u32);
extern void fn_8019BB78(void*, s16*);
extern const f32 lbl_8064ED4C;
extern const f32 lbl_8064ED8C;

int fn_8009C9D4(void* object, void* room, void* target, void* actor)
{
    u8* node;
    int result = 0;
    QueryResult query;
    Vec3 object_pos;
    Vec3 pos;
    Vec3 target_pos;
    s16 goal[3];
    Vec3s* origin;
    f32 height;
    Vec3* floor;

    fn_80201B94();
    if ((node = fn_8018095C(target)) != 0) {
        origin = fn_8017FDA8(node, 0);
        pos.x = origin->x;
        pos.y = origin->y;
        pos.z = origin->z;
        if (fn_80201B44() != -1) {
            fn_800CE24C(fn_80201BC8(fn_80201814()), &pos, 0x14, 0, 0x19);
        }
        fn_802045AC(object, &object_pos);
        if (fn_8019BBB4(node) & 2) {
            result = 1;
        } else if (fn_800BE2CC(object, actor, &target_pos) != 0) {
            if (fn_8011F598(room, 0, 1, -1, &query, 1) == -1) {
                target_pos.z += lbl_8064ED8C;
            } else {
                floor = fn_8011F130(room);
                height = query.height - floor->z;
                if (height < lbl_8064ED4C) {
                    height = -height;
                }
                target_pos.z += (u16)height + 0x14;
            }
            if (fn_8019BBB4(node) & 0x10) {
                fn_800BE390(object, actor);
                fn_8019BBCC(node, 0, 0x11);
            } else if (fn_8019BBB4(node) & 4) {
                goal[0] = target_pos.x;
                goal[1] = target_pos.y;
                goal[2] = target_pos.z;
                fn_8019BBCC(node, 1, 0);
                fn_8019BB78(node, goal);
            } else {
                fn_8019BBCC(node, 4, 0);
            }
        }
    }
    return result;
}
