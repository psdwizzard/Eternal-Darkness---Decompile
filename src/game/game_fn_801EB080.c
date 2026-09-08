extern void* lbl_8064D718;
typedef struct CursorPair {
    void* current;
    void* fallback;
} CursorPair;
extern CursorPair lbl_8064D71C;

void* fn_801EB080(void)
{
    if (lbl_8064D71C.current != lbl_8064D718) {
        return lbl_8064D71C.current;
    }
    return lbl_8064D71C.fallback;
}
