typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

typedef struct Vec3 { f32 x, y, z; } Vec3;

typedef struct IndexTable {
    s32 v[4];
} IndexTable;
extern IndexTable lbl_80239044;
extern Vec3 lbl_80239054;
extern u8 lbl_802FC5BC[];
extern f32 lbl_8064E698;
extern f32 lbl_8064E6C8;

extern void *fn_80201B8C();
extern void *fn_80201BC8();
extern s32 fn_80072354();
extern void fn_8011F114();
extern int fn_80201B54();
extern s32 fn_80036D38();
extern s32 fn_8011EB1C();
extern s32 fn_80066D80();
extern s32 fn_8011F598();
extern void fn_8012B690();
extern void fn_80211AAC();
extern void fn_80211A90();
extern void fn_8014D478();
extern void fn_801A977C();
extern s32 fn_80158598();
extern s32 fn_80157FE0();
extern void fn_80158038();
extern void fn_8014CBE8();
extern s32 fn_80067728();
extern u32 fn_80205868();
extern void fn_8012C5B0();
extern int fn_80201B44();
extern s32 fn_8015C910();
extern void fn_8015C8A4();
extern unsigned long long fn_8020123C();

void fn_80067180(s32 context)
{
    s32 query[8];
    IndexTable indices = lbl_80239044;
    Vec3 fallback_position;
    Vec3 origin;
    Vec3 fallback_offset = lbl_80239054;
    Vec3 direction;
    s32 fallback_resource = *(s32 *)(lbl_802FC5BC + 0x18);
    s32 owner_state;
    s32 object;
    s32 owner;
    u32 actor;
    s32 actor_type;
    s32 i;

    owner_state = (s32)fn_80201B8C(context);
    object = (s32)fn_80201BC8(context);
    fn_80072354(*(s32 *)(owner_state + 0x90));
    fn_8011F114(&origin, (void *)object);
    owner = fn_80201B54(context);
    actor = fn_80036D38(context);
    actor_type = fn_8011EB1C(object);

    for (i = 0; i < 4; i++) {
        s32 index = indices.v[i];
        Vec3 *position;
        s32 effect = -1;
        s32 target;

        if (!fn_80066D80(object, index))
            continue;
        if (fn_8011F598(object, 0x14, index, -1, &query[0], 1) == -1) {
            fn_8012B690(object, &fallback_offset, &fallback_position);
            position = &fallback_position;
        } else {
            position = (Vec3 *)&query[2];
        }
        direction.x = position->x - origin.x;
        direction.y = position->y - origin.y;
        direction.z = lbl_8064E698;
        fn_80211AAC(&direction, &direction);
        fn_80211A90(&direction, &direction, lbl_8064E6C8);
        fn_8014D478(object, position, &direction, 0x10, 1, &fallback_resource, 7);

        if (actor != 0 && (*(u32 *)(actor + 0xB8) & (1U << index))) {
            switch (index) {
            case 0:
                fn_801A977C(object, 0x19);
                break;
            case 1:
            case 2:
            case 3:
                fn_801A977C(object, 0x18);
                if (actor_type == 1) {
                    effect = fn_80158598(fn_80201B54(context), 0);
                    if (index == 2)
                        target = fn_80157FE0(effect, 1, 0);
                    else if (index == 3)
                        target = fn_80157FE0(effect, 2, 0);
                    else if (index == 1)
                        target = fn_80157FE0(effect, 4, 0);
                    if (target != -1)
                        fn_80158038(effect, target);
                }
                break;
            }
            fn_8014CBE8(context, 0x14, index, lbl_802FC5BC + 0x18);
            if (fn_80067728(*(u8 *)(owner_state + 0x9F)) &&
                fn_80205868(object, index, &direction, 0x2000) == 0)
                fn_8012C5B0(object, index);
        }
    }

    if (owner == fn_80201B44()) {
        s32 state = fn_8015C910();
        fn_8015C8A4(state, 0);
        fn_8020123C(8, 0, owner, 0);
        fn_8015C8A4(state, 1);
    } else {
        fn_8020123C(8, 0, owner, 0);
    }
}
