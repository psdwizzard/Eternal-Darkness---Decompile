typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct PuzzleState {
    u8 pad[0x88];
    u16 entries[4];
    u8 flags;
    u8 count;
} PuzzleState;

extern void *fn_80201B8C(unsigned char *);
extern void *fn_80201BC8(void *);
extern int fn_80201B54(void *);
extern void *fn_80200C38(void **);
extern u16 fn_801291CC(void *);
extern u16 fn_801A7434(void *);
extern int fn_800C34A8(void *, void *, void *);
extern u32 fn_801A74C0(void *);
extern void fn_800C3C6C();
extern int fn_800C28D8(void *, void *);
extern u64 fn_8020123C(int, int, int, int);
extern int lbl_8064C864;

int fn_800C3514(void *context, void *event)
{
    PuzzleState **owner = (PuzzleState **)fn_80201B8C(context);
    int object;
    void *value;
    PuzzleState *state;
    int result;
    int scene_or_proceed;
    scene_or_proceed = (int)fn_80201BC8(context);
    object = fn_80201B54(context);
    value = fn_80200C38((void **)event);
    state = *owner;
    result = 0;

    if ((state->flags & 0xC) == 0) {
        /* The scene pointer is dead after this call, so its slot holds the proceed flag. */
        void *scene = (void *)scene_or_proceed;
        scene_or_proceed = 1;
        if (fn_801291CC(scene) <= 5) {
            u8 old_count;
            state->flags &= ~0x10;
            old_count = state->count;
            state->count = old_count + 1;
            state->entries[state->count] = fn_801A7434(value);
            if ((u8)fn_800C34A8(state->entries, (void *)(u32)state->count, value) == 0) {
                state->flags |= 8;
            }
            if (state->count == 2) {
                u8 flags = state->flags;
                if (flags & 8) {
                    scene_or_proceed = 0;
                } else {
                    state->flags = flags | 2;
                    fn_800C3C6C((fn_801A74C0(value) & 4) ? 3000 : 2000);
                    state->flags |= 4;
                }
            } else {
                u8 flags = state->flags;
                if (!(flags & 8)) {
                    state->flags = flags | 2;
                    fn_800C3C6C((fn_801A74C0(value) & 4) ? 2000 : 1000);
                }
            }
            if (scene_or_proceed) {
                lbl_8064C864 = 1;
                result = fn_800C28D8(context, event);
                lbl_8064C864 = 0;
            }
        } else if (!(fn_801A74C0(value) & 2)) {
            u32 handle = fn_8020123C(0x45, object, object, (int)value) & 0xFFFFFFFFULL;
            if (handle) {
                fn_8020123C(0x46, object, object, 0);
                result = 1;
            }
        }
    }
    return result;
}
