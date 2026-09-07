typedef unsigned char u8;

extern int fn_80201B54(void*);
extern void fn_8020123C(int, int, int, int);
extern void fn_801D1318(int);
extern void fn_801A9E40(int);
extern void fn_801D0E78(void*);

void fn_801DAD68(u8* object)
{
    if (*(void**)(object + 0x30) != 0) {
        int id = fn_80201B54(*(void**)(object + 0x30));
        fn_8020123C(0x39, id, id, 0);
    }

    if ((object[0xFF0] & 0x10) != 0)
        fn_801D1318(0);

    fn_801A9E40(-1);
    fn_801D0E78(object);
}
