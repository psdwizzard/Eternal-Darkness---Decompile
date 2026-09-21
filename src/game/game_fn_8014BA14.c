typedef signed short s16;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;

extern u32 lbl_8064D5A8;
extern u32 lbl_8064D0AC;
extern const float lbl_806504AC;

extern unsigned char fn_8018F764(void*);
extern void fn_80198C8C(void*, int, int, int, int, int);
extern void* fn_8011FE4C(void*);
extern int fn_80201A84(int);
extern void *fn_80201814();
extern long long fn_8020123C();
extern int fn_80201B64(void*);
extern int fn_80201B44();
extern void* fn_801A717C(void);
extern void fn_801A74A0(void*, int);
extern void fn_801A74A8(void*, int);
extern void fn_801A7538(void*, int);
extern void fn_801A7518(void*, int);
extern void fn_801A7588(void*, int);
#define FN_80201E78_RETURN void
#define FN_80201E78_PARAMETERS Vec3*, void*
extern FN_80201E78_RETURN fn_80201E78(FN_80201E78_PARAMETERS);
extern u32 fn_80179004(Vec3*, Vec3*);
extern void fn_801A764C(void*, Vec3*);
extern void fn_801A7670(void*, int);
extern void fn_8020104C(int, void*, void*, int, float);
extern int fn_801A98F4(int, int);

void fn_8014BA14(s16* first, s16* second, u32 id, void* owner)
{
    int special = 0;
    int effect = 0;
    int allowed = 1;
    int zone;
    void* room;
    void* spawn;
    Vec3 point;
    Vec3 a;
    Vec3 b;
    Vec3 middle;
    float x2, z1, y1, x1, y2, z2;
    u32 da, db, dm;
    Vec3* nearest;

    if (id == 0)
        return;
    switch (id) {
    case -1:
        special = 1;
        break;
    case -2:
        effect = 0;
        special = 1;
        break;
    case -3:
        effect = 1;
        special = 1;
        break;
    case -4:
        effect = 2;
        special = 1;
        break;
    }

    if (owner != 0) {
        switch (id) {
        case -1:
            if (fn_8018F764(owner) == 9)
                fn_80198C8C(owner, 6, 255, -3, 150, 0);
            else
                fn_80198C8C(owner, 1, 255, -3, 90, 0);
            break;
        case -4:
        case -3:
        case -2: {
            effect = (unsigned char)((effect + 1) * 17 - 5);
            if (fn_8018F764(owner) == 9)
                fn_80198C8C(owner, 6, 255, -3, 150, effect);
            else
                fn_80198C8C(owner, 1, 255, -3, 90, effect);
            break;
        }
        default:
            if (fn_8018F764(owner) == 9)
                fn_80198C8C(owner, 6, 220, -2, 150, 0);
            else
                fn_80198C8C(owner, 1, 220, -2, 90, 0);
            break;
        }
    }
    if (special)
        return;

    zone = fn_80201A84(id);
    room = fn_80201814();
    if (id != 0 && fn_8011FE4C((void*)id) != (void*)id) {
        zone = fn_80201A84((int)fn_8011FE4C((void*)id));
        room = fn_80201814();
    }
    if ((u32)(fn_8020123C(59, -1, zone, 4) & 0xffffffffULL) != 1)
        return;
    if (room == 0)
        return;
    if (fn_80201B64(room) == 8)
        return;
    if (zone == fn_80201B44()) {
        u32 now = lbl_8064D5A8;
        u32 last = lbl_8064D0AC;
        int elapsed = (int)(now - last);
        if (elapsed > 120 || (elapsed < 0 && (int)(elapsed + 0x80000000U - 1) > 119))
            lbl_8064D0AC = now;
        else
            allowed = 0;
    }
    if (!allowed)
        return;
    spawn = fn_801A717C();
    if (spawn == 0)
        return;

    fn_801A74A0(spawn, 0);
    fn_801A74A8(spawn, zone);
    fn_801A7538(spawn, 1);
    fn_801A7518(spawn, 10);
    fn_801A7588(spawn, 2);
    fn_80201E78(&point, room);
    x1 = first[0]; y1 = first[1]; z1 = first[2];
    x2 = second[0]; y2 = second[1]; z2 = second[2];
    a.x = x1; a.y = y1; a.z = z1;
    b.x = x2; b.y = y2; b.z = z2;
    da = fn_80179004(&point, &a);
    db = fn_80179004(&point, &b);
    z1 = first[2] + ((second[2] - first[2]) >> 1);
    x1 = first[0] + ((second[0] - first[0]) >> 1);
    y1 = first[1] + ((second[1] - first[1]) >> 1);
    middle.z = z1; middle.x = x1; middle.y = y1;
    dm = fn_80179004(&point, &middle);
    if (da < db) {
        if (da < dm)
            nearest = &a;
        else
            nearest = &middle;
    } else if (db < dm) {
        nearest = &b;
    } else {
        nearest = &middle;
    }
    fn_801A764C(spawn, nearest);
    fn_801A7670(spawn, 0);
    fn_8020104C(237, (void *)-1, (void *)zone, (int)spawn, lbl_806504AC);
    fn_801A98F4(552, 100);
}
