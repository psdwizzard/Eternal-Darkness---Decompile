typedef unsigned char u8;

extern int fn_80201B54(void*);
extern void fn_8020123C(int, int, int, int);
extern void* fn_80201814(int);
extern void fn_80047700(void*, int);
extern void fn_801F86F4(int);
extern void fn_802020B4(void*, int);
extern void fn_801D1318(int);
extern void fn_80045A24(int, int);
extern void fn_801A9E40(int);
extern void fn_801D0E78(void*);

void fn_801E1920(void* object)
{
    u8* info = object;
    void* handle;
    int id;

    if (*(void**)(info + 0x30)) {
        id = fn_80201B54(*(void**)(info + 0x30));
        fn_8020123C(57, id, id, 0);
    }
    if (*(int*)(info + 0xbc) && *(int*)(info + 0xcc)) {
        handle = fn_80201814(*(int*)(info + 0xe0));
        fn_80047700(handle, 1);
        fn_801F86F4(0);
        fn_802020B4(handle, 1);
    }
    if (info[0xff0] & 0x10) {
        fn_801D1318(0);
        if ((*(int*)(info + 4) & 15) != 8) {
            handle = fn_80201814(*(int*)(info + 0xe0));
            fn_80047700(handle, 1);
            fn_80045A24(0, 0);
            fn_802020B4(handle, 1);
        }
    }
    fn_801A9E40(-1);
    fn_801D0E78(info);
}
