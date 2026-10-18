typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

/*
 * Script/debug enum names retained by the retail translation unit.  Each
 * entry is padded to a four-byte boundary in the original data object.
 */
char lbl_8023C344[] =
    "SP_RUNE_EFFECT_RADIUS\0\0\0"
    "SP_RUNE_CHATTURGAR\0\0"
    "SP_RUNE_ULYAOTH\0"
    "SP_RUNE_ZELLOTATH\0\0\0"
    "SP_RUNE_MANTOROK\0\0\0\0"
    "SP_CIRCLE_TRIANGLE\0\0"
    "SP_CIRCLE_PENTAGON\0\0"
    "SP_CIRCLE_HEPTAGON\0\0"
    "SP_CASE_ENCHANT_ITEM\0\0\0\0"
    "SP_CASE_RECOVER\0"
    "SP_CASE_DAMAGE_FIELD\0\0\0\0"
    "SP_CASE_BIND\0\0\0\0"
    "SP_CASE_SHIELD\0\0"
    "SP_CASE_DISPEL_MAGICK\0\0\0"
    "SP_CASE_MAGICKAL_AREA_ATTACK\0\0\0\0"
    "SP_CASE_SUMMON_CREATURE\0"
    "SP_CASE_REVEAL_INVISIBLE\0\0\0\0"
    "SP_CASE_MAGICK_POOL\0"
    "SP_DF_GATING\0\0\0\0"
    "ED_ALIGNMENT_CHAT\0\0\0"
    "ED_ALIGNMENT_ULY\0\0\0\0"
    "ED_ALIGNMENT_XEL\0\0\0\0"
    "ED_ALIGNMENT_MANT\0\0\0"
    "ED_RETURN_DISTANCE\0\0"
    "ED_RETURN_UID\0\0\0"
    "ED_AI_VAMPIRE_SUMMON_ROOM_NUMBER_1\0\0"
    "ED_AI_VAMPIRE_SUMMON_ROOM_NUMBER_2\0\0"
    "ED_AI_VAMPIRE_SUMMON_ROOM_NUMBER_3\0\0"
    "ed_INSANE_OBJ_TRAUM_TIMELINE_VISITATION\0"
    "ed_INSANE_OBJ_TRAUM_EDWARDS_GHOST\0\0\0"
    "ed_INS_OBJ_ALEX_PHONE_CALL\0\0"
    "ed_INSANE_OBJ_TRAUM_PHANTOM_CREATURES\0\0\0"
    "ed_INSANE_OBJ_TRAUM_LOCKED_IN_ROOM\0\0"
    "ED_CREATE_AS_CHARACTER\0\0"
    "ED_CREATE_AS_INVENTORY\0\0"
    "ED_CREATE_AS_EQUIPPED_INVENTORY\0"
    "ED_CREATE_DROPPED_INVENTORY\0"
    "ED_CREATE_CUSTOM\0\0\0\0"
    "ED_CREATE_AS_CHARACTER_DONT_FADE\0\0\0\0"
    "ED_LEVEL_ALEX_DREAM\0"
    "ED_LEVEL_ALEX_START\0"
    "ED_LEVEL_PIOUS\0\0"
    "ED_LEVEL_ELLIA\0\0"
    "ED_LEVEL_ANTHONY\0\0\0\0"
    "ED_LEVEL_KARIM\0\0"
    "ED_LEVEL_MAX\0\0\0\0"
    "ED_LEVEL_LINDSEY\0\0\0\0"
    "ED_LEVEL_PAUL\0\0\0"
    "ED_LEVEL_ROBERTO\0\0\0\0"
    "ED_LEVEL_EDWARD_START\0\0\0"
    "ED_LEVEL_PETER\0\0"
    "ED_LEVEL_MAJOR\0\0"
    "ED_LEVEL_BOSSFIGHT_LICHE\0\0\0\0"
    "ED_LEVEL_BOSSFIGHT_PETER\0\0\0\0"
    "SOUNDTYPE_PLAYER_DESPERATION_STREAM\0"
    "SOUNDTYPE_PLAYER_THIS_ISNT_REALLY_STREAM\0\0\0\0"
    "ELLIA_GHOST\0"
    "SD_STREAM_PRIORITY_LOWEST\0\0\0"
    "SD_STREAM_PRIORITY_AMBIENT\0\0"
    "SD_STREAM_PRIORITY_INSANITY\0"
    "SD_STREAM_PRIORITY_PUZZLE\0\0\0"
    "SD_STREAM_PRIORITY_DIALOG\0\0\0"
    "SD_STREAM_PRIORITY_CINEMATIC\0\0\0\0"
    "SD_STREAM_PRIORITY_HIGHEST\0\0"
    "SOUNDVOLTYPE_NONE\0\0\0"
    "SOUNDVOLTYPE_EMITTER\0\0\0\0"
    "SOUNDVOLTYPE_EFFECT\0"
    "SOUNDVOLTYPE_GUN\0\0\0\0"
    "SOUNDVOLTYPE_AMBIENT\0\0\0\0"
    "SOUNDVOLTYPE_FIXEDVOL\0\0\0"
    "SOUNDVOLTYPE_SPELL\0\0"
    "SD_AUDIOTYPE_SAMPLE\0"
    "SD_AUDIOTYPE_STREAM\0"
    "SD_AUDIOTYPE_MUSIC\0\0"
    "ED_DISABLE_CAMERA_TILT_FOR_SCRIPTS\0";

#pragma use_lmw_stmw on

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct Object {
    u8 pad0[0x9E];
    u8 type;
} Object;

extern const char lbl_8023BEF8[];
extern s32 lbl_8064D18C;
extern void *fn_80201B9C();
extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void* lua_touserdata(void*, int);
extern double lua_tonumber(void*, int);
extern unsigned int fn_800F5C54(double);
extern int fn_80201EB8();
extern void *fn_80201B8C();
extern void *fn_80201BC8();
#define FN_80201E78_RETURN void
#define FN_80201E78_PARAMETERS void*, void*
extern FN_80201E78_RETURN fn_80201E78(FN_80201E78_PARAMETERS);extern u32 fn_80178F14(s32, s32, s32, s32, s32, s32);
extern void* fn_80201BC0(void*);
extern int fn_80201B54();
extern void lua_pushnumber(void*, double);

s32 fn_8000EFC4(void* script)
{
    register u32 mode;
    register void* iterator;
    register void* best;
    register u32 best_distance;
    s32 kind;
    Object* object;
    float z;
    float y;
    float x;
    Vec3s* target;
    Vec3f position;
    s32 result;

    iterator = fn_80201B9C();
    best = 0;
    best_distance = -1;
    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    target = lua_touserdata(script, 1);
    mode = fn_800F5C54(lua_tonumber(script, 2));
    z = target->z;
    y = target->y;
    x = target->x;

    while (iterator != 0) {
        kind = fn_80201EB8(iterator);
        object = fn_80201B8C(iterator);
        if (lbl_8064D18C == kind && fn_80201BC8(iterator) != 0 &&
            object != 0 && object->type == 2) {
            fn_80201E78(&position, iterator);
            result = fn_80178F14(x, y, z, (s32)position.x,
                                 (s32)position.y, (s32)position.z);
            if ((u32)result < best_distance) {
                best_distance = result;
                best = iterator;
            }
        }
        iterator = fn_80201BC0(iterator);
    }

    if (best != 0) {
        result = fn_80201B54(best);
        if (mode == 1) {
            result = best_distance;
        }
    } else {
        result = -1;
    }
    lua_pushnumber(script, result);
    return 1;
}
