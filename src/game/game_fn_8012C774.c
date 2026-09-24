typedef unsigned char u8;

#pragma use_lmw_stmw on

extern int fn_8012FA54(u8*, int);
extern void* fn_8012C62C(u8*, int, void*, void*, void*, int);

/* NonMatching: stage the three reads before materializing the call's copies.
 * Retail retains the c value in r5; GC/1.3 retains it in r7 and stores it
 * after setting up the first two copy addresses. */
void fn_8012C774(u8* state, void* a, void* b, void* c, int flags)
{
    int i;
    unsigned int av;
    unsigned int bv;
    unsigned int cv;

    for (i = 0; i < 15; i++) {
        if (fn_8012FA54(state, i)) {
            unsigned int ta;
            unsigned int tb;
            unsigned int tc;

            tc = *(volatile unsigned int*)c;
            tb = *(volatile unsigned int*)b;
            ta = *(volatile unsigned int*)a;
            cv = tc;
            bv = tb;
            av = ta;
            fn_8012C62C(state, i, &av, &bv, &cv, flags);
        }
    }
}
