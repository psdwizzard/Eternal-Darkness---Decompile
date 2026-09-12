extern int fn_80200C10(void*);
extern void *fn_80201BC8();
extern int fn_80201B54();
extern void *fn_80201B8C();
extern void fn_80128754(void*, int);
extern unsigned int fn_8011FA8C(void*, int, int);
extern int fn_80201EB8();
extern void *fn_801294DC(void *, int, int, int);
extern int fn_80128EAC(void*);
extern int fn_8012A1BC(void*, int);
extern void fn_801289A0(void*);
extern void fn_80129FD0(void*, int, int);
extern void fn_8011ECF8(void*, void*);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern int lbl_8064D18C;

int fn_8009A0EC(register void* object, register int phase, void* event)
{
    register void* room;
    register int kind;
    register void* created;
    register int index;
    int result;

    kind = fn_80200C10(event);
    room = fn_80201BC8(object);
    ((void*)fn_80201B54(object));
    fn_80201B8C(object);
    if (kind == 3) {
        fn_80128754(room, -1);
    }
    if (phase == 0) {
        if (kind == 1) {
            fn_8011FA8C(room, 0xC0, 0);
            if (fn_80201EB8(object) == lbl_8064D18C) {
                created = fn_801294DC(room, 0x18, 0x34, 0xA);
                if (created != 0) {
                    fn_80128EAC(room);
                    index = fn_8012A1BC(room, 0x18);
                    fn_801289A0(created);
                    fn_80129FD0(room, index << 17, 0);
                    fn_8011FA8C(room, 0, 4);
                    fn_8011ECF8(room, created);
                }
            }
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            result = 1;
        } else if (kind == 0x3E) {
            created = fn_801294DC(room, 0x18, 0x34, 0xA);
            if (created != 0) {
                fn_80128EAC(room);
                index = fn_8012A1BC(room, 0x18);
                fn_801289A0(created);
                fn_80129FD0(room, index << 17, 0);
                fn_8011FA8C(room, 0, 4);
                fn_8011ECF8(room, created);
            }
            result = 1;
        } else {
            goto zero_result;
        }
    } else if (phase != 1) {
        result = 0;
    } else {
zero_result:
        result = 0;
    }
    return result;
}
