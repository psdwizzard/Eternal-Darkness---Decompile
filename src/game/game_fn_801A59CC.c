typedef unsigned char u8;

typedef struct Entry {
    u8 pad0[0xC];
    void* value;
    u8 pad10[0x10];
} Entry;

extern Entry lbl_806079C0[];
extern Entry lbl_802512A4[];
extern void* lbl_8064D26C;
extern void* lbl_8064D264;

extern void fn_801A6CB4(void);
extern void* fn_80144628(int, Entry*, int);
extern void fn_801446D4(void*, void (*)(void));
extern void fn_801446DC(void*, void (*)(void));
extern void fn_801446E4(void*, void*);
extern void fn_801A5D5C(void);
extern void fn_801A5E68(void);
extern void fn_801A5FB0(void);

void fn_801A59CC(void* value)
{
    void* object;
    int i;

    fn_801A6CB4();
    for (i = 0; i < 3; i++) {
        lbl_802512A4[i].value = value;
    }
    for (i = 0; i < 9; i++) {
        lbl_806079C0[i].value = value;
    }

    object = fn_80144628(3, lbl_802512A4, 0);
    lbl_8064D26C = object;
    fn_801446D4(object, fn_801A5D5C);
    fn_801446E4(lbl_8064D26C, value);

    object = fn_80144628(9, lbl_806079C0, 0);
    lbl_8064D264 = object;
    fn_801446D4(object, fn_801A5E68);
    fn_801446DC(lbl_8064D264, fn_801A5FB0);
    fn_801446E4(lbl_8064D264, value);
}
