typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

extern s32 lbl_8064D538;
extern s32 fn_80201AE4(void);
extern void fn_801D1318(u32);
extern s32 fn_801D10C0(u32);
extern void fn_801A9E40(s32);
extern s32 fn_801B05E8(s32, s32, s32, s32, s32, s32, s32, s32);
extern void* fn_801D18FC(s32, u32, u32, u32, s32, u32, s32, u32, u32, u32, u32, u32);
extern void* fn_801D8760(s32, u32, u32, s32, u32, u32, u32, u32, u32);
extern void* fn_801D70B0(s32, u32, u32, s32, u8, u32, u32, u32, u32, u32);
extern void* fn_801E2F04(s32, u32, u32, s32, u32, u32, u32, u32, u32, u32);
extern void* fn_801DA794(s32, u32, u32, s32, u32, u8, u32, u32, u32, u32, u32);
extern void* fn_801DA2C0(s32, u32, u32, s32, u8, u32, u32, u32, u32, u32);
extern void* fn_801DB7B0(s32, u32, u32, s32, u32, u32, u32, u32, u32);
extern void* fn_801D997C(s32, u32, u32, s32, u32, u32, u32, u32, u32);
extern void* fn_801DE4A8(s32, u32, u32, s32, u32, u32, u32, u32, u32);
extern void* fn_801E1F18(s32, u32, u32, s32, u32, u32, u32, u32, u32);
extern void* fn_801E1A18(s32, u32, u32, s32, u32, u32, u32, u32, u32);
extern void fn_801B08BC(s32, s32, s32);

void* fn_801D0814(u32 flags, u32 arg1, s32 subject, void* data, u32 arg4,
                  u32 arg5, u32 arg6, u32 arg7, s32 stack_arg)
{
    s32 resource = -1;
    s32 kind;
    void* result = 0;

    if (lbl_8064D538 != 0 && subject == fn_80201AE4()) {
        goto done;
    }
    if (subject == fn_80201AE4()) {
        fn_801D1318(flags);
    }
    kind = fn_801D10C0(flags);
    if (kind > 0) {
        resource = subject != fn_80201AE4();
        fn_801A9E40(1);
        resource = fn_801B05E8(kind, 0x7f, 4, 1, stack_arg, 6, resource, 1);
    }

    switch (flags & 0x1ff0) {
    case 0x300:
        result = fn_801D18FC(resource, flags, subject, ((u32*)data)[1], stack_arg,
                             arg1, ((u32*)data)[0], arg4, arg5, arg6, arg7, 0);
        break;
    case 0x1040:
        result = fn_801D8760(resource, flags, subject, stack_arg, arg1, arg4,
                             arg5, arg6, arg7);
        break;
    case 0x410:
        result = fn_801D70B0(resource, flags, subject, stack_arg, *(u8*)data,
                             arg1, arg4, arg5, arg6, arg7);
        break;
    case 0x810:
        result = fn_801E2F04(resource, flags, subject, stack_arg, ((u32*)data)[0],
                             arg1, arg4, arg5, arg6, arg7);
        break;
    case 0x1010:
        if (((s32*)data)[0] > 0) {
            result = fn_801DA794(resource, flags, subject, ((s32*)data)[0], stack_arg,
                                 ((u8*)data)[4], arg1, arg4, arg5, arg6, arg7);
        } else {
            result = fn_801DA2C0(resource, flags, subject, stack_arg, ((u8*)data)[4],
                                 arg1, arg4, arg5, arg6, arg7);
        }
        break;
    case 0x480:
        result = fn_801DB7B0(resource, flags, subject, stack_arg, arg1, arg4,
                             arg5, arg6, arg7);
        break;
    case 0x500:
        result = fn_801D997C(resource, flags, subject, stack_arg, arg1, arg4,
                             arg5, arg6, arg7);
        break;
    case 0x820:
        result = fn_801DE4A8(resource, flags, subject, stack_arg, arg1, arg4,
                             arg5, arg6, arg7);
        break;
    case 0x440:
        result = fn_801E1F18(resource, flags, subject, stack_arg, arg1, arg4,
                             arg5, arg6, arg7);
        break;
    case 0x420:
        result = fn_801E1A18(resource, flags, subject, stack_arg, arg1, arg4,
                             arg5, arg6, arg7);
        break;
    }
    if (result == 0 && resource != 0) {
        fn_801B08BC(resource, -2, 0);
        fn_801A9E40(-1);
    }
done:
    return result;
}
