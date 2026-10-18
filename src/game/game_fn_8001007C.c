typedef int s32;

extern const char lbl_8023BED8[];

extern const double lbl_8064DCF8;
extern const double lbl_8064DD30;
extern const double lbl_8064DD38;
extern const double lbl_8064DD40;
extern const double lbl_8064DD48;
extern const double lbl_8064DD50;
extern const double lbl_8064DD58;
extern const double lbl_8064DD60;
extern const double lbl_8064DD68;
extern const double lbl_8064DD70;
extern const double lbl_8064DD78;
extern const double lbl_8064DD80;
extern const double lbl_8064DD88;
extern const double lbl_8064DD90;
extern const double lbl_8064DD98;
extern const double lbl_8064DDA0;
extern const double lbl_8064DDA8;
extern const double lbl_8064DDB0;
extern const double lbl_8064DDB8;
extern const double lbl_8064DDC0;
extern const double lbl_8064DDC8;
extern const double lbl_8064DDD0;
extern const double lbl_8064DDD8;
extern const double lbl_8064DDE0;
extern const double lbl_8064DDE8;
extern const double lbl_8064DDF0;
extern const double lbl_8064DDF8;
extern const double lbl_8064DE00;
extern const double lbl_8064DE08;
extern const double lbl_8064DE10;
extern const double lbl_8064DE18;
extern const double lbl_8064DE20;
extern const double lbl_8064DE28;
extern const double lbl_8064DE30;
extern const double lbl_8064DE38;
extern const double lbl_8064DE40;
extern const double lbl_8064DE48;
extern const double lbl_8064DE50;

extern double lua_tonumber(void*, int);
extern void lua_settop(void*, s32);
extern void lua_pushnumber(void*, double);
extern void lua_getglobal(void*, const char*);
extern void lua_setglobal(void*, const char*);

#define REGISTER(value, offset)             \
    if (enabled_reg == 0) {                  \
        lua_pushnumber(script_reg, value);       \
        lua_setglobal(script_reg, names + offset); \
    } else {                                 \
        lua_getglobal(script_reg, names + offset); \
        lua_tonumber(script_reg, 1);           \
        lua_settop(script_reg, -2);          \
    }

void fn_8001007C(void* script, s32 enabled)
{
    const char* names;
    s32 enabled_reg;
    void* script_reg;

    names = lbl_8023BED8;
    enabled_reg = enabled;
    script_reg = script;

    REGISTER(lbl_8064DD30, 0x46c);
    REGISTER(lbl_8064DCF8, 0x484);
    REGISTER(lbl_8064DD38, 0x498);
    REGISTER(lbl_8064DD40, 0x4a8);
    REGISTER(lbl_8064DD48, 0x4bc);
    REGISTER(lbl_8064DD50, 0x4d0);
    REGISTER(lbl_8064DD58, 0x4e4);
    REGISTER(lbl_8064DD60, 0x4f8);
    REGISTER(lbl_8064DD68, 0x50c);
    REGISTER(lbl_8064DD70, 0x524);
    REGISTER(lbl_8064DD78, 0x534);
    REGISTER(lbl_8064DD80, 0x54c);
    REGISTER(lbl_8064DD88, 0x55c);
    REGISTER(lbl_8064DD90, 0x56c);
    REGISTER(lbl_8064DD98, 0x584);
    REGISTER(lbl_8064DDA0, 0x5a4);
    REGISTER(lbl_8064DDA8, 0x5bc);
    REGISTER(lbl_8064DDB0, 0x5d8);
    REGISTER(lbl_8064DD40, 0x5ec);
    REGISTER(lbl_8064DCF8, 0x5fc);
    REGISTER(lbl_8064DD38, 0x610);
    REGISTER(lbl_8064DDB8, 0x624);
    REGISTER(lbl_8064DD40, 0x638);
    REGISTER(lbl_8064DCF8, 0x64c);
    REGISTER(lbl_8064DD38, 0x660);
    REGISTER(lbl_8064DDC0, 0x670);
    REGISTER(lbl_8064DDC8, 0x694);
    REGISTER(lbl_8064DDD0, 0x6b8);
    REGISTER(lbl_8064DDD8, 0x6dc);
    REGISTER(lbl_8064DDE0, 0x704);
    REGISTER(lbl_8064DDE8, 0x728);
    REGISTER(lbl_8064DDF0, 0x744);
    REGISTER(lbl_8064DDF8, 0x76c);
    REGISTER(lbl_8064DCF8, 0x790);
    REGISTER(lbl_8064DD38, 0x7a8);
    REGISTER(lbl_8064DDB8, 0x7c0);
    REGISTER(lbl_8064DD40, 0x7e0);
    REGISTER(lbl_8064DE00, 0x7fc);
    REGISTER(lbl_8064DE08, 0x810);
    REGISTER(lbl_8064DE10, 0x834);
    REGISTER(lbl_8064DE18, 0x848);
    REGISTER(lbl_8064DCF8, 0x85c);
    REGISTER(lbl_8064DD38, 0x86c);
    REGISTER(lbl_8064DDB8, 0x87c);
    REGISTER(lbl_8064DD40, 0x890);
    REGISTER(lbl_8064DE00, 0x8a0);
    REGISTER(lbl_8064DE08, 0x8b0);
    REGISTER(lbl_8064DE20, 0x8c4);
    REGISTER(lbl_8064DD48, 0x8d4);
    REGISTER(lbl_8064DE28, 0x8e8);
    REGISTER(lbl_8064DDF8, 0x900);
    REGISTER(lbl_8064DE30, 0x910);
    REGISTER(lbl_8064DDD8, 0x920);
    REGISTER(lbl_8064DE38, 0x93c);
    REGISTER(lbl_8064DE40, 0x958);
    REGISTER(lbl_8064DE48, 0x97c);
    REGISTER(lbl_8064DE50, 0x9a8);
    REGISTER(lbl_8064DE18, 0x9b4);
    REGISTER(lbl_8064DCF8, 0x9d0);
    REGISTER(lbl_8064DD38, 0x9ec);
    REGISTER(lbl_8064DDB8, 0xa08);
    REGISTER(lbl_8064DD40, 0xa24);
    REGISTER(lbl_8064DE00, 0xa40);
    REGISTER(lbl_8064DE08, 0xa60);
    REGISTER(lbl_8064DE18, 0xa7c);
    REGISTER(lbl_8064DCF8, 0xa90);
    REGISTER(lbl_8064DD38, 0xaa8);
    REGISTER(lbl_8064DDB8, 0xabc);
    REGISTER(lbl_8064DD40, 0xad0);
    REGISTER(lbl_8064DE00, 0xae8);
    REGISTER(lbl_8064DE08, 0xb00);
    REGISTER(lbl_8064DCF8, 0xb14);
    REGISTER(lbl_8064DD38, 0xb28);
    REGISTER(lbl_8064DDB8, 0xb3c);
    REGISTER(lbl_8064DCF8, 0xb50);
}
