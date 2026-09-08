typedef void (*Callback)(void);

typedef struct CallbackState {
    unsigned char pad[0x198];
    Callback callback;
} CallbackState;

extern void fn_801EF800(void);
extern void fn_801EF804(void);
extern Callback lbl_8064D73C;

void fn_801EF814(void* arg0, CallbackState* state, void* arg2, Callback callback)
{
    if (callback == 0) {
        state->callback = fn_801EF800;
    } else {
        state->callback = fn_801EF804;
    }
    lbl_8064D73C = callback;
}
