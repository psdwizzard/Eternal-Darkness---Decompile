/* The body matches retail. Current compiler settings generate GPR
 * save/restore helpers in place of the retail stmw/lmw pair. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct Owner Owner;
typedef struct Entry Entry;

typedef struct Config {
    u8 pad00[0x1C];
    u32 flags;
    u8 pad20[0x2C];
    s32 event;
    u8 pad50[8];
    s32 value58;
    s32 value5C;
} Config;

typedef struct Slot {
    u8 pad00[0x28];
    u8 index;
    u8 pad29[3];
} Slot;

typedef struct State {
    u8 pad00[0x40];
    Slot slots[3];
    Config *config;
} State;

extern Entry *fn_8006ED3C(Owner *, int, int *);
extern s32 fn_8006B96C(s32, s32);
extern void fn_8015C948(int, int, int, int, int, int, int, int, int, int, int);
extern void fn_801EFE84(int);
extern void fn_801E7DCC(const char *, ...);
extern void fn_8006DEF8(Owner *, u32, u32, u32, u16);
extern void fn_8006BEE4(s32 *, s32);
extern int fn_8006EA4C(Owner *);
extern const char lbl_8024547C[];

int fn_8009E5C4(register State *state)
{
    int slot_index;
    register Config *config;
    register Entry *context;
    register int event_index;
    register int result;
    register int i;

    result = 0;
    config = state->config;
    context = fn_8006ED3C((Owner *)state, 0x16, &slot_index);
    if (context != 0) {
        event_index = fn_8006B96C(config->event, 1);
        if (event_index >= 0 && event_index < 10) {
            fn_8015C948(config->event + 1000, config->value58, config->value5C,
                       0, 0, 3, 2, 0, 0, 0, 1);
            fn_801EFE84(1);
            config->flags |= 1 << event_index;
            result = 1;
        } else {
            fn_801E7DCC(lbl_8024547C, config->event);
            state->slots[slot_index].index = 4;
            fn_8006DEF8((Owner *)state, 0x16, 0, 0, 0);
            for (i = 0; i < 3; i++) {
                state->slots[slot_index].index = i;
                fn_8006DEF8((Owner *)state, 0x16, 0, 0, 0);
            }
            fn_8006BEE4((s32 *)context, (s32)fn_8006EA4C);
        }
    }
    return result;
}
