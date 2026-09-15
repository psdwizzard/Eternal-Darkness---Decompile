typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct Slot {
    void* handle;
    s32 value;
    u8 pad08[8];
} Slot;

typedef struct TransitionState {
    Slot slots[5];
    u8 pad050[0x18A];
    u8 type;
    u8 pad1DB[4];
    s8 used_slots;
} TransitionState;

typedef struct Record {
    u16 value;
    u8 addend;
    u8 enabled;
} Record;

typedef struct GameState {
    u8 pad00[0x10];
    u32 flags;
} GameState;

extern TransitionState lbl_8030F540;
extern GameState lbl_803003C8;
extern void* lbl_8064C510;
extern void* lbl_8064C514;

extern u32 fn_801E88FC(void*, s32);
extern Record* fn_801E880C(void*, s32, s32);
extern void* fn_801E6CA0(void*, s32, u16, s32, s32);
extern void fn_801E5FB0(void*);

void fn_80053048(s32 value)
{
    u32 count;
    Record* record;
    s32 record_type;
    s32 type = lbl_8030F540.type;
    u32 i;

    if ((u32)(type - 0x25) <= 1 || type == 0x27) {
        type = 0x21;
    }
    if (lbl_8064C514 == 0) {
        return;
    }
    count = fn_801E88FC(lbl_8064C510, type);
    if (count == 0) {
        return;
    }
    record = fn_801E880C(lbl_8064C514, type, 0);
    record_type = type;

    for (i = 0; i < count; i++, record++) {
        if (value == record->value) {
            for (type = 0; type < 5; type++) {
                s32 mask = 1 << type;
                if (((s8)lbl_8030F540.used_slots & mask) == 0) {
                    void* handle;
                    if (lbl_8064C510 == 0) {
                        return;
                    }
                    if (record->enabled == 0 && (lbl_803003C8.flags & 1) == 0) {
                        break;
                    }
                    handle = fn_801E6CA0(lbl_8064C510, record_type, (u16)i,
                                        0x10000, 1);
                    lbl_8030F540.used_slots |= mask;
                    lbl_8030F540.slots[type].handle = handle;
                    lbl_8030F540.slots[type].value = value + record->addend;
                    break;
                }
            }
        }
    }

    {
        s32 cleanup_slot;
        for (cleanup_slot = 0; cleanup_slot < 5; cleanup_slot++) {
            s32 mask = 1 << cleanup_slot;
            if (((s8)lbl_8030F540.used_slots & mask) != 0 &&
                value == lbl_8030F540.slots[cleanup_slot].value) {
                fn_801E5FB0(lbl_8030F540.slots[cleanup_slot].handle);
                lbl_8030F540.slots[cleanup_slot].handle = 0;
                lbl_8030F540.used_slots &= ~mask;
            }
        }
    }
}
