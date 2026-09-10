typedef struct SavedState {
    float first_value;
    float second_value;
    unsigned int first_handle;
    unsigned int second_handle;
    unsigned int token;
} SavedState;

typedef struct LiveState {
    unsigned char pad0[0x30];
    float value;
    unsigned char pad34[0x3C];
    unsigned int handle;
    unsigned char pad74[0x14];
} LiveState;

typedef struct Globals {
    unsigned char pad0[0xCC0];
    LiveState first;
    LiveState second;
    SavedState saved[1];
} Globals;

extern Globals lbl_8063C6B8;
extern int lbl_8064D7BC;
extern unsigned int fn_801FA44C(void);

void fn_801F8620(void)
{
    volatile Globals* globals = &lbl_8063C6B8;
    volatile SavedState* saved;
    volatile LiveState* first;
    volatile LiveState* second;
    float first_value;
    float second_value;
    unsigned int first_handle;
    unsigned int second_handle;
    int count = lbl_8064D7BC;

    saved = &globals->saved[count];
    first = &globals->first;
    lbl_8064D7BC = count + 1;
    first_value = first->value;
    second = &globals->second;
    first_handle = first->handle;
    saved->first_value = first_value;
    second_value = second->value;
    second_handle = second->handle;
    saved->second_value = second_value;
    saved->first_handle = first_handle;
    saved->second_handle = second_handle;
    saved->token = fn_801FA44C();
}
