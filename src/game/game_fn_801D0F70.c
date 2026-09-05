typedef unsigned char u8;

typedef struct Object Object;

struct Object {
    int field_00;
    int field_04;
    int field_08;
    int field_0C;
    char pad10[4];
    Object* next;
    Object* prev;
    char pad1C[0x18];
    void* field_34;
    char pad38[0xFB8];
    u8 flags;
    u8 state;
};

extern int lbl_8064D538;
extern Object* lbl_8064D544;
extern int fn_80201AE4(void);
extern int fn_801D30FC(void);
extern void fn_801D53F0(void);
extern int fn_80157994(void*);
extern void fn_80157A28(void*, int);
extern void fn_801D0CF0(Object*);

void fn_801D0F70(int update)
{
    int player = fn_80201AE4();

    if (lbl_8064D538 != 0 && fn_801D30FC() == 0) {
        Object* object = lbl_8064D544;
        int wanted = lbl_8064D538;

        while (object != 0) {
            if (object->field_0C == player && object->field_04 == wanted &&
                (object->state == 0 || object->state == 6)) {
                break;
            }
            object = object->next;
        }
        if (object != 0) {
            if (update != 0) {
                fn_801D53F0();
                if (object->field_34 != 0) {
                    int value = fn_80157994(object->field_34);
                    fn_80157A28(object->field_34, value + 1);
                }
            }
            object->flags &= ~8;
            fn_801D0CF0(object);
        }
    }
}
