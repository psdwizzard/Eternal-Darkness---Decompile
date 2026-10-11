typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Event {
    u8 pad00[8];
    short counter;
} Event;

typedef struct EffectState {
    u8 first[0xB00];
    u8 second[0xC40];
    u8 pad1740[0x40];
    int value;
} EffectState;

typedef struct State {
    u8 pad00[0x15C];
    EffectState *effect;
} State;

typedef struct Entry {
    u32 callbacks[4];
    u32 arguments[4];
    u16 ids[4];
    u8 index;
    u8 lastIndex;
    u8 resetIndex;
    u8 limit;
} Entry;

typedef struct Owner {
    u8 pad00[0x18];
    char text[0x28];
    Entry entries[3];
    State *state;
} Owner;

extern Event *fn_8006ED3C(Owner *, int, int *);
extern void fn_8006BEE4(int *, int);
extern int fn_8006EB60(Owner *);
extern int fn_8006E20C(Owner *);
extern int fn_800AEE80(Owner *);
extern void fn_8006DEF8(Owner *, u32, int (*)(Owner *), Owner *, u16);
extern void *memset(void *, int, unsigned long);
extern char *fn_800FD40C(char *, const char *);
extern u8 fn_801A9B28(void);
extern u8 fn_801A9B30(void);
extern char lbl_80246E1C[];
extern int lbl_8064C9D4, lbl_8064C9D8, lbl_8064C9DC, lbl_8064C9E0;

void fn_800AECDC(Owner *owner)
{
    int index;
    Event *event;
    EffectState *effect;
    int i;
    u8 value;

    event = fn_8006ED3C(owner, 0x1F, &index);
    event->counter = 0;
    effect = owner->state->effect;
    effect->value = -1;
    fn_8006BEE4((int *)event, (int)fn_8006EB60);
    owner->entries[index].resetIndex = 0;
    owner->entries[index].limit = 0;
    memset(effect->first, 0, 0xB00);
    memset(effect->second, 0, 0xC40);
    owner->entries[index].index = 4;
    fn_8006DEF8(owner, 0x1F, fn_800AEE80, owner, 5);
    owner->entries[index].index = 0;
    fn_8006DEF8(owner, 0x1F, fn_8006E20C, owner, 10);
    for (i = 1; i < 3; i++) {
        owner->entries[index].index = i;
        fn_8006DEF8(owner, 0x1F, 0, 0, 1);
    }
    owner->entries[index].index = 0;
    fn_800FD40C(owner->text, lbl_80246E1C);
    lbl_8064C9E0 = fn_801A9B28();
    value = fn_801A9B30();
    lbl_8064C9DC = value;
    lbl_8064C9D4 = value;
    lbl_8064C9D8 = ((value << 6) / 127) >> 1;
}
