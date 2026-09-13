typedef unsigned char u8;
typedef unsigned int u32;

typedef struct CounterState {
    u8 pad[0x168];
    u8 count;
} CounterState;

extern u32 fn_8011FAF4(void *);
extern unsigned int fn_8011FABC(void *, int, int);
extern void fn_800BCDF0(void *);

#pragma use_lmw_stmw on
#define MAX0(value) (0 > (value) ? 0 : (value))

int fn_800CA7D4(void *unused, void *owner, CounterState *state,
                void *resource, int limit, int decrement)
{
    int result;

    result = 0;
    if ((fn_8011FAF4(resource) & 2) != 0) {
        fn_8011FABC(resource, 2, 0);
        {
            int count = state->count + 1;
            state->count = count;
            if ((u8)count > (u8)limit) {
                fn_800BCDF0(owner);
                result = 1;
                state->count = 0;
            }
        }
    } else {
        state->count = MAX0(state->count - (u8)decrement);
    }
    return result;
}
