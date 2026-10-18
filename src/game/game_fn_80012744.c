typedef int s32;

typedef struct GameState {
    void* value;
    unsigned char pad_04[4];
    s32 first;
    s32 second;
} GameState;

extern const char lbl_8023BEF8[];
extern GameState lbl_803003C8;
extern void* lbl_8064C4E0;
extern s32 lbl_8064C5D8;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80113B50(s32);
extern s32 fn_801118E8(void);
extern int fn_801E79FC(void*, int);
extern void fn_801E7974(void*, int);
extern void fn_8001E644(s32, s32, s32);
extern s32 fn_80111C48(void);

s32 fn_80012744(void* script)
{
    s32 value;

    value = (s32)script;
    if (lua_gettop((void*)value) != 1) {
        luaO_verror((void*)value, lbl_8023BEF8, 1, lua_gettop((void*)value));
        return 0;
    }

    value = (s32)lua_tonumber((void*)value, 1);
    switch (value) {
    case 0xF2:
        fn_80113B50(0x01000000);
        break;
    case 0xF3:
        fn_80113B50(0x08000000);
        break;
    case 0xF4:
        fn_80113B50(0x00100000);
        break;
    case 0xF5:
        fn_80113B50(0x00010000);
        break;
    case 0xF6:
        fn_80113B50(0x02000000);
        break;
    case 0xF7:
        fn_80113B50(0x00080000);
        break;
    case 0xF8:
        fn_80113B50(0x00400000);
        break;
    case 0xF9:
        fn_80113B50(0x00800000);
        break;
    case 0xFA:
        fn_80113B50(0x20000000);
        if (fn_801118E8() != 0
            && fn_801E79FC(lbl_8064C4E0, 0xAA) == 0) {
            lbl_8064C5D8 = 1;
        }
        break;
    case 0xFB:
        fn_80113B50(0x04000000);
        break;
    case 0xFC:
        fn_80113B50(0x10000000);
        break;
    case 0xFD:
        fn_80113B50(0x00200000);
        break;
    case 0xFE:
        fn_80113B50(0x00020000);
        break;
    case 0xFF:
        fn_80113B50(0x00040000);
        break;
    default:
        fn_8001E644(lbl_803003C8.first, lbl_803003C8.second, 0);
        break;
    }

    if (fn_801E79FC(lbl_8064C4E0, 0x3DF) == 0) {
        fn_801E7974(lbl_8064C4E0, 0x3DF);
        fn_80111C48();
        if (fn_801118E8() != 0) {
            lbl_8064C5D8 = 1;
        }
    } else if (fn_80111C48() != 0) {
        lbl_8064C5D8 = 1;
    }
    return 0;
}
