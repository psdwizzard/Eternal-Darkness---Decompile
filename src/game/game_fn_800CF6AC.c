typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;

typedef struct ValueTable ValueTable;
typedef struct Object {
    u8 pad0[0x8C];
    ValueTable *table;
    u8 pad90[4];
    s32 kind;
} Object;

typedef struct Entry {
    u8 pad0[2];
    u8 amount;
    u8 flags;
    u8 pad4[4];
} Entry;

typedef struct EntryTable {
    u8 pad0[0x28];
    Entry entries[1];
} EntryTable;

typedef struct Effect Effect;
extern s16 fn_8003CC48(s32 unused, Object *object, s32 kind, s16 amount);
extern void fn_801A7518(Effect *effect, s16 value);
extern void fn_801A7520(Effect *effect, s16 value);
extern void fn_801A7528(Effect *effect, s16 value);
extern void fn_801A7538(Effect *effect, s32 value);
extern float lbl_8064F33C;

void fn_800CF6AC(void *unused, EntryTable *table, Object *object,
                  Effect *effect, s32 index, s32 mode)
{
    s32 kind = 2;
    u8 input = table->entries[index].amount;
    s16 amount;

    if (mode == 4) {
        kind = 3;
    }
    amount = fn_8003CC48((s32)unused, object, kind, input);
    if (table->entries[index].flags & 1) {
        fn_801A7518(effect, amount);
        fn_801A7538(effect, 1);
    }
    if (object->kind == 1) {
        fn_801A7518(effect, (s16)(lbl_8064F33C * (float)(s16)amount));
    }
    if (object->kind == 3) {
        fn_801A7520(effect, amount);
    }
    if (object->kind == 2) {
        fn_801A7528(effect, (s16)((s16)amount * 2));
    }
}
