typedef unsigned char u8;

typedef struct GameObject {
    u8 pad00[0x10];
    int handle;
    u8 pad14[0x1C];
    void* link30;
} GameObject;

extern int lbl_8064D54C;
extern int lbl_8064D548;
extern int lbl_8064D6EC;
extern void* fn_80201B54(void*);
extern void fn_8020123C(int, void*, void*, int);
extern void fn_8011E174(int, int);
extern void fn_801A9E40(int);
extern void fn_801D0E78(GameObject*);

void fn_801D2FA4(GameObject* object)
{
    if (object->link30 != 0) {
        void* link = fn_80201B54(object->link30);
        fn_8020123C(57, link, link, 0);
    }
    lbl_8064D54C = 0;
    fn_8011E174(0x800, 0);
    lbl_8064D548 = 0;
    lbl_8064D6EC = 0;
    fn_801A9E40(-1);
    fn_801D0E78(object);
}
