typedef struct ListHdr {
    int unk0;
    int count;
} ListHdr;

extern ListHdr *lbl_8064D0BC;
extern void fn_800449EC(int index, void *arg);

void fn_80044B54(void *arg) {
    int i;

    for (i = 0; i < lbl_8064D0BC->count; i++) {
        fn_800449EC(i, arg);
    }
}
