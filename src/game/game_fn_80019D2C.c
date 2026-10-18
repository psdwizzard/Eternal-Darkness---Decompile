typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
typedef float f32;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct {
    u8 bytes[0x2C];
    Vec3s position;
    u8 pad32[0x1A];
} EffectRecord;

typedef struct {
    u8 bytes[0x34];
    u16 count;
    u8 pad36[2];
    EffectRecord* records;
} EffectRecordTable;

extern const char lbl_8023BEF8[];
extern const double lbl_8064DCE8;
extern const f32 lbl_8064DE5C;
extern u32 lbl_8064DE88;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern int fn_8015C4A4(int, int);
extern EffectRecordTable* fn_8015C390(s32);
extern void fn_8014E6BC(Vec3f*, s32, u32*, s32, s32, s32);

s32 fn_80019D2C(void* script)
{
    s32 object_id;
    s32 second;
    s32 third;
    s32 fourth;
    s32 record_id;
    EffectRecordTable* table;
    EffectRecord* record;
    u32 direction;
    Vec3f position;

    direction = lbl_8064DE88;

    if (lua_gettop(script) != 4) {
        luaO_verror(script, lbl_8023BEF8, 4, lua_gettop(script));
        return 0;
    }

    object_id = fn_800F5C54(lua_tonumber(script, 1));
    second = (s32)lua_tonumber(script, 2);
    third = (s32)lua_tonumber(script, 3);
    fourth = (s32)lua_tonumber(script, 4);

    record_id = fn_8015C4A4(object_id, 2);
    if (record_id != -1) {
        table = fn_8015C390(2);
        if (table != 0 && record_id < table->count) {
            record = &table->records[record_id];
            if (record != 0) {
                position.x = record->position.x;
                position.y = record->position.y;
                position.z = record->position.z;
                position.z += lbl_8064DE5C;
                fn_8014E6BC(&position, second, &direction, third, fourth, 0);
            }
        }
    }
    return 0;
}
