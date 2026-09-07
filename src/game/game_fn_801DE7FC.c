typedef unsigned char u8;
typedef unsigned int u32;

extern void* fn_80201814(int);
extern void* fn_80201B8C(void);
extern void fn_800CAC5C(int, int, u32*, u32*, u32*);
extern int fn_80201B5C(void*);
extern void* fn_80036D38(void*);
extern void fn_80201D44(void*, u32);
extern void fn_80201D24(void*, int);
extern void fn_802015A4(void*);

int fn_801DE7FC(int unused, int id)
{
    u32 first;
    u32 second;
    u32 third;
    void* object = fn_80201814(id);
    void* context;

    if (object != 0 && (context = fn_80201B8C()) != 0) {
        fn_800CAC5C(*((u8*)context + 0x9f), *(int*)((u8*)context + 0x94),
                    &first, &second, &third);
        if (fn_80201B5C(object) == 0x28) {
            void* destination = fn_80036D38(object);
            *(u32*)((u8*)destination + 0x84) = third;
        } else if (fn_80201B5C(object) == 0) {
            fn_80201D44(object, third);
            fn_80201D24(object, 1);
            fn_802015A4(object);
        }
    }
    return 1;
}
