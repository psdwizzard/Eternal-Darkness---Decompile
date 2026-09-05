typedef unsigned int u32;

extern void* lbl_806333A0[];
extern void fn_8017FD6C(void*);

void fn_801CEA8C(u32 slot)
{
    void* object = lbl_806333A0[slot];

    if (object != 0) {
        fn_8017FD6C(object);
        lbl_806333A0[slot] = 0;
    }
}
