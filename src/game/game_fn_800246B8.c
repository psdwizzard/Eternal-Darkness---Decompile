typedef unsigned int u32;

#pragma use_lmw_stmw on

extern char lbl_8064B2C8;
extern char lbl_8064B2D0;
extern char lbl_8064B2D8;

extern void fn_80155C88(void*, char*, const char*);
extern void* fn_80024594(char*, u32*);
extern void fn_801E971C(void*, u32);
extern void fn_801E9564(void*, u32);
extern void TEXGetPalette(void*, char*);

void fn_800246B8(void* base, u32 first_value, void** second,
                 u32 second_value, void** first, void* path)
{
    u32 size = 0;
    char buffer[0x100];

    fn_80155C88(base, buffer, &lbl_8064B2C8);
    *first = fn_80024594(buffer, &size);
    fn_801E971C(*first, second_value);

    fn_80155C88(base, buffer, &lbl_8064B2D0);
    *second = fn_80024594(buffer, &size);
    fn_801E9564(*second, first_value);

    fn_80155C88(base, buffer, &lbl_8064B2D8);
    TEXGetPalette(path, buffer);
}
