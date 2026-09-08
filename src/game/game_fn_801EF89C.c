typedef void (*Callback)(void);

typedef struct CallbackState {
    unsigned char pad[0x198];
    Callback callback;
} CallbackState;

extern void fn_801EF80C(void);

void fn_801EF89C(void* arg0, CallbackState* state, ...)
{
    state->callback = fn_801EF80C;
}
