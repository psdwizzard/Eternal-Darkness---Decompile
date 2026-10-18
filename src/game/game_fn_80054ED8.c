typedef signed int s32;
typedef unsigned char u8;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern char lbl_80243A40[];
extern Vec3 lbl_80238FB0;
extern s32 lbl_8064B4DC;
extern s32 lbl_8064C868;
extern s32 lbl_8064C86C;
extern s32 lbl_8064D18C;

extern int fn_80200C10(void *);
extern void *fn_80201B8C();
extern void *fn_80201B9C();
extern void *fn_80201BC0(void *object);
extern void *fn_80201BC8();
extern void *fn_80201814();
extern int fn_80201EB8();
extern int fn_80201B54();
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_8011E174(s32 index, s32 value);
extern void fn_80130434(void *object, s32 value);
extern void fn_801301B0(void *object, s32 value, s32 mask);
extern void fn_8011F114();
extern s32 fn_8003D69C(void *object);
extern s32 fn_80036E50(void *object);
extern unsigned int fn_80178E94(Vec3 *a, Vec3 *b);
extern void *fn_801E741C(char *name);
extern unsigned int rand(void);
#define rand() ((int)rand())
extern void fn_80145490(void);
extern void fn_801F86F4(s32 value);
extern s32 fn_80054BCC(s32 value);
extern s32 fn_80054D14(void *context, void *owner, void *object, s32 force);
extern void fn_80054DF4(void *context, void *owner, void *object, s32 force);

s32 fn_80054ED8(void *context, void *event)
{
    char *strings = lbl_80243A40;
    s32 kind = fn_80200C10(event);
    u8 *state = fn_80201B8C(context);
    void *owner = *(void **)(state + 0x8C);
    void *object = fn_80201BC8(context);

    if (kind == 1) {
        s32 found;

        fn_8011E174(8, 1);
        fn_80130434(object, 1);
        fn_801301B0(object, 0, 0x20);
        lbl_8064B4DC--;
        if (lbl_8064C86C == 0 && lbl_8064B4DC <= 0) {
            void *head = fn_80201814(*(void **)((u8 *)owner + 0x1C));
            s32 allowed = fn_80054BCC(lbl_8064D18C);
            void *item;
            Vec3 origin;
            Vec3 position;
            Vec3 current;
            Vec3 item_current;
            Vec3 fallback;

            found = 0;
            if (fn_8003D69C(*(void **)((u8 *)owner + 0x1C)) != 0) {
                found = 1;
            } else if (head != 0) {
                void *head_object;
                item = fn_80201B9C();
                head_object = fn_80201BC8(head);
                fn_8011F114(&current, head_object);
                origin = current;
                while (item != 0 && found == 0) {
                    void *item_object = fn_80201BC8(item);
                    Vec3 *source_position;
                    s32 item_id;
                    void *related;

                    if (item_object != 0) {
                        fn_8011F114(&item_current, item_object);
                        source_position = &item_current;
                    } else {
                        fallback = lbl_80238FB0;
                        source_position = &fallback;
                    }
                    position = *source_position;
                    item_id = fn_80201EB8(item);
                    related = (void *)fn_80201B54(item);
                    if (lbl_8064D18C == item_id && item_object != 0 &&
                        fn_80036E50(item) == 3 &&
                        fn_80178E94(&origin, &position) < 700 &&
                        fn_8003D69C(related) != 0) {
                        found = 1;
                    }
                    item = fn_80201BC0(item);
                }
            }

            if (found == 0 && allowed != 0) {
                s32 attempt = 0;
                s32 created = 0;
                while (created == 0 && attempt < 3) {
                    void *resource;

                    switch (lbl_8064C868) {
                    case 0:
                        resource = fn_801E741C(strings + 0x7C);
                        break;
                    case 1:
                        resource = fn_801E741C(strings + 0x88);
                        break;
                    default:
                        resource = fn_801E741C(strings + 0x94);
                        break;
                    }
                    if (fn_80054D14(resource, context, object, 1) == 0) {
                        s32 random = rand();
                        lbl_8064B4DC = random % 3 + 4;
                        lbl_8064C86C = -1;
                        created = 1;
                        fn_80054DF4(resource, context, object, 1);
                    }
                    switch (lbl_8064C868) {
                    case 0:
                        lbl_8064C868 = 1;
                        break;
                    case 1:
                        lbl_8064C868 = 2;
                        break;
                    default:
                        lbl_8064C868 = 0;
                        break;
                    }
                    attempt++;
                }
            }
        }
        return 1;
    }

    if (kind == 12) {
        fn_80145490();
        fn_80201D2C(context, 1);
        fn_80201D14(context, 1);
        return 1;
    }
    if (kind == 52) return 1;
    if (kind == 41) return 1;
    if (kind == 42) return 1;
    if (kind == 43) return 1;
    if (kind == 45) return 1;
    if (kind == 44) return 1;
    if (kind == 40) return 1;
    if (kind == 46) return 1;
    if (kind == 125) return 1;
    if (kind == 175) return 1;
    if (kind == 202) return 1;
    if (kind == 147) return 1;
    if (kind == 135) return 1;
    if (kind == 31) return 1;
    if (kind == 2) {
        fn_801301B0(object, 0x20, 0);
        fn_8011E174(8, 0);
        if (lbl_8064C86C <= -1) {
            lbl_8064C86C = 0;
            fn_801F86F4(0);
        }
        return 1;
    }
    return 0;
}
