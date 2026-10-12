typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Trigger {
    int position;
    int scale;
    int useLimit;
    int offset;
    int limit;
} Trigger;

#define FN_80128E30_RETURN u8*
#define FN_80128E30_PARAMETERS void*
extern FN_80128E30_RETURN fn_80128E30(FN_80128E30_PARAMETERS);
extern u16 fn_8012927C(void*);
extern int fn_801E82B4(u32, u32, u32, u16);

/* The event queue stores the owner address as a 32-bit word. */
void fn_8012AE78(u32 owner)
{
    int forward;
    u8* slot;
    u8* state;
    int position;
    Trigger* trigger;
    int i;
    u32 reverse;
    u16 selected;
    int active;
    int threshold;
    int passed;

    state = fn_80128E30((void*)owner);
    selected = fn_8012927C((void*)owner);
    if (selected == 0xFFFF) {
        selected = 0;
    }
    trigger = (Trigger*)(*(u8**)(owner + 0x160) + selected * 0x4C + 4);
    reverse = *(u32*)(state + 0xF4) & 2;
    slot = state;
    i = 0;
    position = trigger->position;
    forward = reverse == 0;
    do {
        if (*(u32*)slot != 0) {
            threshold = *(int*)(slot + 0x70);
            active = 0;
            if ((position >= threshold && forward) ||
                (position <= threshold && reverse)) {
                active = 1;
            }
            passed = active;
            if (active) {
                if (!(state[i + 0x102] & 1)) {
                    if (trigger->useLimit) {
                        passed = trigger->offset +
                            __abs(*(int*)(state + 0xC8) * trigger->scale) > trigger->limit;
                    }
                    if (passed) {
                        state[i + 0x102] |= 1;
                        fn_801E82B4(owner, *(u32*)(slot + 0x38),
                                     *(u32*)slot, 0);
                    }
                }
            }
        }
        ++i;
        slot += 4;
    } while (i < 14);
}
