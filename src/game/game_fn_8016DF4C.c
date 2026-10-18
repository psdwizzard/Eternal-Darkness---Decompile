extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void lua_pushnumber(void*, double);
extern unsigned int fn_800F5C54(double);
extern int fn_80047180(void);
extern void* fn_80201B3C(void);
extern void fn_802020B4(void*, int);
extern void fn_8016E254(int);
extern void fn_8015C948(int, void*, void*, int, int, int, int, int, int, int, int);
extern void fn_801AC350(int, int, int);
extern void fn_801F348C(void*, int);
extern unsigned int lbl_806506BC;

int fn_8016DF4C(void* state)
{
    int arg1;
    void* arg2;
    void* arg3;
    int selector;
    int arg5;
    int arg6;
    int optional = 1;
    int current;
    int mode;
    int extra;
    volatile unsigned int timer_template = lbl_806506BC;

    switch (lua_gettop(state)) {
    case 7:
        optional = (int)lua_tonumber(state, 7);
    case 6:
        arg1 = (int)lua_tonumber(state, 1);
        arg2 = (void *)fn_800F5C54(lua_tonumber(state, 2));
        arg3 = (void *)fn_800F5C54(lua_tonumber(state, 3));
        selector = (int)lua_tonumber(state, 4);
        arg5 = (int)lua_tonumber(state, 5);
        arg6 = (int)lua_tonumber(state, 6);
        break;
    }

    current = fn_80047180();
    if (current != 0) {
        mode = -1;
        extra = 0;
        fn_802020B4(fn_80201B3C(), 0);

        switch (selector) {
        case 0: mode = -1; break;
        case 1: mode = 5; break;
        case 2: mode = 10; break;
        case 3: mode = 60; break;
        case 16: mode = 188; extra = 128; break;
        case 4: fn_8016E254(2); mode = 5; break;
        case 5: fn_8016E254(2); mode = 10; break;
        case 6: fn_8016E254(2); mode = 60; break;
        case 7: fn_8016E254(25); mode = 5; break;
        case 8: fn_8016E254(25); mode = 10; break;
        case 9: fn_8016E254(25); mode = 60; break;
        case 10: fn_8016E254(103); mode = 5; break;
        case 11: fn_8016E254(103); mode = 10; break;
        case 12: fn_8016E254(103); mode = 60; break;
        case 13: fn_8016E254(104); mode = 5; break;
        case 14: fn_8016E254(104); mode = 10; break;
        case 15: fn_8016E254(104); mode = 60; break;
        }

        if (mode == -1) {
            fn_8015C948(arg1, arg2, arg3, arg5, arg6, 1, extra, selector, 0, 0, optional);
            fn_801AC350(0, 1, 0);
        } else {
            int clamped;
            fn_8015C948(arg1, arg2, arg3, arg5, arg6, mode + 2, extra, selector, 0, 0, optional);
            if (selector != 16) {
                unsigned int timer = timer_template;
                fn_801F348C(&timer, mode);
            }
            clamped = mode > 254 ? 254 : mode;
            fn_801AC350((signed char)clamped, 1, 0);
        }
    }
    lua_pushnumber(state, (double)current);
    return 1;
}
