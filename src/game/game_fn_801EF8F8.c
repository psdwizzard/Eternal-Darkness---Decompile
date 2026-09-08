typedef void (*Callback)(void);

typedef struct CallbackState {
    unsigned char pad[0x198];
    Callback callback;
} CallbackState;

extern void fn_801EF810(void);
extern Callback lbl_8064D73C;

void fn_801EF8F8(void* arg0, CallbackState* state, void* arg2, Callback callback)
{
    lbl_8064D73C = (Callback)((unsigned int)callback + 0x80000000U);
    state->callback = fn_801EF810;
}
