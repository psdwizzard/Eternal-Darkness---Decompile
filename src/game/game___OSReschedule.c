extern volatile int RunQueueHint_8064D98C;
extern void SelectThread_8020F61C(int yield);

void __OSReschedule(void) {
    if (RunQueueHint_8064D98C != 0) {
        SelectThread_8020F61C(0);
    }
}
