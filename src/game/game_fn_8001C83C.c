typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

typedef struct Command {
    u32 words[8];
} Command;

typedef struct Status {
    u8 pad[0x9E];
    u8 field_9e;
    u8 field_9f;
} Status;

extern void fn_80201ADC(void);
extern void *fn_80201B8C();
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern int fn_80070A6C(int);
extern void fn_8001C310(void*);
extern void fn_8001C500(void*);
extern void fn_8001C6D8(void*);
extern s32 fn_8011E310(s32, s32, s32, s32, s32, s32, s32);
extern char lbl_8023BEF8[];
extern Command lbl_803023E0;
extern Command lbl_80300368[];
extern s32 lbl_8064D1BC;

s32 fn_8001C83C(void* arg)
{
    Status* status;
    s32 result;

    fn_80201ADC();
    status = fn_80201B8C();
    if (lua_gettop(arg) != 6) {
        luaO_verror(arg, lbl_8023BEF8, 6, lua_gettop(arg));
        return 0;
    }

    if (fn_80070A6C(0x4000) == 0 && status->field_9e == 1 && status->field_9f == 1) {
        lbl_803023E0.words[0] = 3;
        fn_8001C310(arg);
        fn_8001C500(arg);
        fn_8001C6D8(arg);
        if ((s32)lbl_803023E0.words[4] >= 0) {
            result = fn_8011E310(2, 6, -2, lbl_8064D1BC, 50, 2, 0);
            switch (result) {
            case 2:
                lbl_80300368[0] = lbl_803023E0;
                break;
            case 4:
                lbl_80300368[1] = lbl_803023E0;
                break;
            }
        }
    }
    return 0;
}
