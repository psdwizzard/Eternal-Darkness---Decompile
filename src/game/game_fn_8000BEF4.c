typedef int s32;

extern double lua_tonumber(void*, int);
extern void fn_8011E19C(s32, s32);

s32 fn_8000BEF4(void* script)
{
    if ((s32)lua_tonumber(script, 1) != 0) {
        fn_8011E19C(1, 0);
    } else {
        fn_8011E19C(1, 1);
    }
    return 0;
}
