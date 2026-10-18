typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

typedef struct Config {
    u8 pad_00[0x10];
    u32 flags;
} Config;

typedef struct Owner {
    void *pad_00;
    void *active;
    u8 pad_08[0xC];
    u8 count;
    u8 level;
    u8 pad_16[0xAE];
    Config *config;
} Owner;

typedef struct GlobalState {
    u8 pad_00[8];
    s32 level;
} GlobalState;

typedef struct Entry Entry;

extern Entry *fn_8006C75C(u8 count, u8 level);
extern s32 fn_8006D12C(Owner *owner, void *entry);
extern u32 rand(void);
extern void fn_801E7974(u8 *bits, u32 index);
extern s32 fn_801E79FC(u32 *bits, u32 index);
extern GlobalState lbl_803003C8;
extern u8 *lbl_8064C4E0;

s32 fn_8006CF74(Owner *owner)
{
    s32 result = 0;
    Config *config = owner->config;
    Entry *entry = fn_8006C75C(owner->count, owner->level);

    if (entry != 0 && fn_8006D12C(owner, entry) != 0) {
        result = 1;
    }
    if (owner->level >= 2) {
        GlobalState *state = &lbl_803003C8;

        if (state->level >= 4) {
            if (fn_801E79FC((u32 *)lbl_8064C4E0, 0x34D) == 0 &&
                (s32)(rand() & 0x3F) > 0x20) {
                fn_801E7974(lbl_8064C4E0, 0x34D);
            }
            if (!(config->flags & 0x10) &&
                (s32)(rand() & 0x3F) > 0x20) {
                fn_801E7974(lbl_8064C4E0, 0x3AA);
            }
        }
        if (state->level == 5) {
            if (!(config->flags & 4) &&
                (s32)(rand() & 0x3F) > 0x20) {
                fn_801E7974(lbl_8064C4E0, 0x466);
            }
        } else if (state->level > 5) {
            if (!(config->flags & 4)) {
                config->flags |= 4;
            }
        }
    }
    return result;
}
