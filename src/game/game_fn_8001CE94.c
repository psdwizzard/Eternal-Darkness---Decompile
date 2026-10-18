typedef int s32;

char lbl_8023CE68[20] = "EDCleanUpSubtitles";
char lbl_8023CE7C[32] = "EDStartSubtitlesForGhostMaid";
char lbl_8023CE9C[40] = "EDStartSubtitlesForInsanityPhoneCall";
char lbl_8023CEC4[28] = "EDStartSubtitleForEdward";
char lbl_8023CEE0[24] = "EDQueryPlayerOkToBrush";
char lbl_8023CEF8[36] = "EDStartSubtitlesForMikeDestroyThis";
char lbl_8023CF1C[36] = "EDStartSubtitlesForAlexClockPuzzle";

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern s32 fn_800E4558(s32);
extern char lbl_8023BEF8[];

s32 fn_8001CE94(void* script)
{
    s32 value;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    value = (s32)lua_tonumber(script, 1);
    value = fn_800E4558(value);
    lua_pushnumber(script, (double)value);
    return 1;
}
