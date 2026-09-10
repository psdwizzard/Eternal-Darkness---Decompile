extern void* lbl_8064D274;
extern void* lbl_80607C10[];
extern int lbl_8064D270;

extern void fn_8017CE74(void*, void*);

void fn_801A7228(void* entry)
{
    int i;
    void* target = entry;

    if (target != 0) {
        for (i = 0; i < 40; i++) {
            if (lbl_80607C10[i] == target) {
                lbl_80607C10[i] = 0;
            }
        }
        fn_8017CE74(lbl_8064D274, target);
        lbl_8064D270--;
    }
}
