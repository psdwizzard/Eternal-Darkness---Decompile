typedef signed int s32;
typedef unsigned int u32;

extern u32 fn_8004519C(void);

s32 fn_8004527C(void)
{
    switch ((s32)fn_8004519C()) {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
    case 3:
        return 4;
    default:
        return 1;
    }
}
