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
extern void fn_801FA410(unsigned int);

int fn_801F85A4(void)
{
    Globals* globals = &lbl_8063C6B8;
    int result = 0;
    int count = lbl_8064D7BC;

    if (count > 0) {
        SavedState* saved;
        LiveState* first;
        LiveState* second;
        float first_value;
        float second_value;
        unsigned int first_handle;
        unsigned int second_handle;
        unsigned int token;

        count--;
        saved = &globals->saved[count];
        first = &globals->first;
        second = &globals->second;
        lbl_8064D7BC = count;
        first_value = saved->first_value;
        second_value = saved->second_value;
        first_handle = saved->first_handle;
        second_handle = saved->second_handle;
        token = saved->token;
        first->value = first_value;
        second->value = second_value;
        first->handle = first_handle;
        second->handle = second_handle;
        fn_801FA410(token);
        result = 1;
    }
    return result;
}
