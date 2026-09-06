typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

extern u8* lbl_8064D3D0;
extern u32 fn_801C14D0(u32);
extern void fn_801CAD90(u8, u8, u8, u16);

u32 fn_801B7F6C(u32 handle, u8 control, u16 value)
{
    u32 result = 0;
    u32 voice = fn_801C14D0(handle);

    while (voice != 0xFFFFFFFF) {
        u32 index = voice & 0xFF;
        u32 offset = index * 0x404;

        if (voice == *(u32*)(lbl_8064D3D0 + offset + 0xF4)) {
            u8* state = lbl_8064D3D0 + offset;

            if ((*(u64*)(state + 0x114) & 2) != 0) {
                fn_801CAD90(control, index, state[0x20B], value);
            } else {
                fn_801CAD90(control, index, state[0x122], value);
            }

            result = 1;
            voice = *(u32*)(lbl_8064D3D0 + offset + 0xEC);
        } else {
            return result;
        }
    }
    return result;
}
