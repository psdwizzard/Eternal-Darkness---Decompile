extern void* lbl_8064D274;
extern void* lbl_80607C10[];
extern int lbl_8064D270;

extern void* fn_8017CDB4(void*);
extern void* fn_801A7098(void);
extern void fn_801A7354(void*);
extern int fn_801A6F94(void);

void* fn_801A717C(void)
{
    void* entry;
    int found;
    int i;

    entry = fn_8017CDB4(lbl_8064D274);
    if (entry == 0) {
        entry = fn_801A7098();
    }
    if (entry != 0) {
        found = 0;
        fn_801A7354(entry);
        lbl_8064D270++;
        for (i = 0; i < 40 && !found; i++) {
            if (lbl_80607C10[i] == 0) {
                found = 1;
                lbl_80607C10[i] = entry;
            }
        }
    } else {
        fn_801A6F94();
    }
    return entry;
}
