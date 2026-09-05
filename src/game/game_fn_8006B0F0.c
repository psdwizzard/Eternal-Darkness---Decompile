typedef signed int s32;
typedef unsigned int u32;

#pragma use_lmw_stmw on

extern void *fn_80036D38(s32 object);
extern s32 fn_80066D04(s32 object, s32 kind);
extern s32 fn_801A7770(s32 value);

s32 fn_8006B0F0(s32 kind, s32 object, s32 unused, s32 value)
{
    s32 kinds[3] = {0, 2, 3};
    s32 i;
    void *state = fn_80036D38(object);

    for (i = 0; i < 3; i++) {
        if (kind == kinds[i] && fn_80066D04(object, kinds[i]) &&
            (*(u32 *)((char *)state + 0xB8) & (1U << kinds[i])) &&
            kinds[i] == fn_801A7770(value)) {
            return kinds[i];
        }
    }
    return -1;
}
