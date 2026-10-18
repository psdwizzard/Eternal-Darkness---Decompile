typedef int s32;
typedef signed short s16;

extern const char lbl_8023BED8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern int fn_80038308(void *, int, short *);
extern void fn_80038878(s32, s32, s16);
extern int fn_800389E0(void*, int, s32, int);
extern float ceil(float);
extern void fn_8000C848(s32, s32, float, const char*, s32);

s32 fn_8000C91C(void* script)
{
    void* object = script;
    s32 id;
    s32 mode;
    float scale0;
    float scale8;
    float scale9;
    float scale1;
    float scale2;
    float scale3;
    float scale4;
    const char* strings = lbl_8023BED8;

    if (lua_gettop(object) != 9) {
        luaO_verror(object, strings + 0x20, 9, lua_gettop(object));
        return 0;
    }

    id = (s32)lua_tonumber(object, 1);
    mode = (s32)lua_tonumber(object, 2);
    scale0 = (float)lua_tonumber(object, 3);
    scale8 = (float)lua_tonumber(object, 4);
    scale9 = (float)lua_tonumber(object, 5);
    scale1 = (float)lua_tonumber(object, 6);
    scale2 = (float)lua_tonumber(object, 7);
    scale3 = (float)lua_tonumber(object, 8);
    scale4 = (float)lua_tonumber(object, 9);
    object = fn_80201814(id);
    if (object != 0) {
      switch (mode) {
      case 4: {
        s16 value = 0;

        fn_80038308(object, 0, &value);
        value = (s16)ceil((float)value * scale0);
        fn_80038878(id, 0, value);
        fn_800389E0(object, 0, value, 0);
        fn_8000C848(id, 0, scale8, strings + 0x2B8, 1);
        fn_8000C848(id, 8, scale9, strings + 0x2C8, 1);
        fn_8000C848(id, 9, scale1, strings + 0x2D8, 1);
        fn_8000C848(id, 1, scale2, strings + 0x2E8, 1);
        fn_8000C848(id, 2, scale3, strings + 0x2F8, 1);
        fn_8000C848(id, 3, scale4, strings + 0x30C, 1);
        break;
      }
      case 3:
        fn_8000C848(id, 0, scale8, strings + 0x320, 0);
        fn_8000C848(id, 8, scale9, strings + 0x32C, 0);
        fn_8000C848(id, 9, scale1, strings + 0x338, 0);
        fn_8000C848(id, 1, scale2, strings + 0x344, 0);
        fn_8000C848(id, 2, scale3, strings + 0x350, 0);
        fn_8000C848(id, 3, scale4, strings + 0x360, 0);
        break;
      }
    }
    return 0;
}
