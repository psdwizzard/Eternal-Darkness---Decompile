typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Info {
    u8 pad48[0x48];
    void* field48;
    u8 pad4C[0x14];
    void* field60;
} Info;

extern void* fn_801A7498(void*);
extern void* fn_801A7490(void*);
extern void *fn_80201814();
extern void* fn_800CC458(void*, void*, int);
extern void *fn_80201B8C();
extern void* fn_80035628(void*);
extern void fn_800355F0(void*, void*);

#pragma opt_propagation off
int fn_8008AE40(void* unused, void* config)
{
    void* first;
    void* argument;
    void* first_object;
    void* created;
    void* transform;

    argument = config;
    first = fn_801A7498(argument);
    first_object = fn_80201814(first);
    argument = fn_801A7490(argument);

    if (first_object != 0 && fn_80201814(argument) != 0) {
        created = fn_800CC458(first, argument, 1);
        argument = ((Info*)fn_80201B8C(created));
        first = ((Info*)fn_80201B8C(first_object));
        transform = fn_80035628(first_object);
        fn_800355F0(created, transform);
        *(u16*)((u8*)((Info*)argument)->field60 + 0x17C) =
            *(u16*)((u8*)((Info*)first)->field48 + 6);
        if (*(u16*)((u8*)((Info*)argument)->field60 + 0x17C) == 0) {
            *(u16*)((u8*)((Info*)argument)->field60 + 0x17C) = 0x968;
        }
    }
    return 1;
}
#pragma opt_propagation reset
