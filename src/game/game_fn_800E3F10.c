typedef struct Object Object;
typedef struct Object80201C24 Object80201C24;
typedef struct FlagObject FlagObject;

extern void *fn_80200C38(void **);
extern void *fn_8004910C(void);
extern int fn_80201B54(int *);
extern void *fn_80201BC8(void *);
extern int fn_8011EB04(Object *);
extern int fn_80047CB4(void);
extern int fn_80200614(int, int, int);
extern void fn_800E406C(int);
extern void fn_800E4010(int);
extern void fn_8020104C(int, int, int, int, float);
extern void *fn_80201C24(Object80201C24 *);
extern unsigned int fn_80157888(FlagObject *);
extern unsigned long long fn_8020123C(int, int, int, int);
extern float lbl_8064F690;

void fn_800E3F10(int *object, void *unused, void **event)
{
    void *current;
    int id;
    int type;
    int player_type;
    void *resource;

    fn_80200C38(event);
    current = fn_8004910C();
    id = fn_80201B54(object);
    if (current != 0 && (resource = fn_80201BC8(current)) != 0) {
        type = fn_8011EB04(resource);
        player_type = fn_80047CB4();
        if (player_type == type) {
            if (fn_80200614(id, -1, 0x12) == 0) {
                fn_800E406C((int)object);
                fn_800E4010(id);
                fn_8020104C(0x12, id, id, 1, lbl_8064F690);
            }
        } else {
            if ((fn_80157888(fn_80201C24(current)) & 2) == 0) {
                fn_800E4010(id);
                fn_8020123C(0x12, id, id, 0);
            }
        }
    }
}
