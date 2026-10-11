typedef struct ListHdr {
    int unk0;
    int count;
} ListHdr;

typedef struct ListState {
    ListHdr header;
    int unk8;
    int pendingCount;
} ListState;

extern ListHdr *lbl_8064D0BC;
extern void fn_80044888(int index);

void fn_800449A4(void) {
    int i;

    for (i = 0; i < ((ListState *)lbl_8064D0BC)->pendingCount; i++) {
        fn_80044888(i);
    }
}
