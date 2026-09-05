typedef unsigned int u32;

typedef struct Pair {
    u32 first;
    u32 second;
} Pair;

extern Pair lbl_8064D4DC;

void fn_801CD404(Pair* value)
{
    lbl_8064D4DC = *value;
}
