typedef struct Entry {
    unsigned char active;
    unsigned char padding[79];
    void* handle;
    unsigned char remainder[48];
} Entry;

extern Entry lbl_8060B430[];
extern void sndStreamDeactivate(void*);
extern void sndStreamActivate(void*);

void fn_801AD95C(int state)
{
    int i;
    if (state != 0) {
        i = 0;
        do {
            if (lbl_8060B430[i].active != 0) {
                sndStreamDeactivate(lbl_8060B430[i].handle);
            }
            i++;
        } while (i < 3);
    } else {
        i = 0;
        do {
            if (lbl_8060B430[i].active != 0) {
                sndStreamActivate(lbl_8060B430[i].handle);
            }
            i++;
        } while (i < 3);
    }
}
