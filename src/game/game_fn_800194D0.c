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
    u8 bytes[144];
} EffectDescriptor;

typedef struct {
    u8 bytes[0x2C];
    Vec3s position;
    u8 pad32[2];
    u32 size;
    u8 pad38[0x14];
} EffectRecord;

typedef struct {
    u8 bytes[0x34];
    u16 count;
    u8 pad36[2];
    EffectRecord* records;
} EffectRecordTable;

extern const char lbl_8023BEF8[];
extern const u32 lbl_806518D0;
extern const u16 lbl_806518D4;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern int fn_8015C4A4(int, int);
extern EffectRecordTable* fn_8015C390(s32);
extern void fn_8019DFA0(EffectDescriptor*);
extern void fn_8019DFF8(void);
extern void* fn_80148008(Vec3f*, const Vec3s*, EffectDescriptor*, void (*)(void));

s32 fn_800194D0(void* script)
{
    Vec3s direction;
    Vec3f position;
    Vec3f submit_position;
    EffectDescriptor descriptor;
    EffectRecordTable* table;
    EffectRecord* record;
    s32 record_id;
    s32 doubled_size;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    record_id = fn_8015C4A4(fn_800F5C54(lua_tonumber(script, 1)), 2);
    if (record_id != -1) {
        table = fn_8015C390(2);
        if (table != 0 && record_id < table->count) {
            record = &table->records[record_id];
            if (record != 0) {
                *(u32*)&direction = lbl_806518D0;
                *(u16*)((u8*)&direction + 4) = lbl_806518D4;

                position.x = record->position.x;
                position.y = record->position.y;
                position.z = record->position.z;
                doubled_size = record->size * 2;

                fn_8019DFA0(&descriptor);
                *(u16*)&descriptor.bytes[20] = doubled_size;
                *(u16*)&descriptor.bytes[22] = doubled_size;
                *(u32*)&descriptor.bytes[24] = 0;
                *(u32*)&descriptor.bytes[28] = 0;

                submit_position = position;
                fn_80148008(&submit_position, &direction, &descriptor, fn_8019DFF8);
            }
        }
    }
    return 0;
}
