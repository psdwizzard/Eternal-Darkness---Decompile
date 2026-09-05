typedef unsigned char u8;

extern void* lbl_8064D544;
extern int fn_801911D0(void*);
extern void fn_801914D8(void*);
extern void fn_801911F4(void*, int);

void fn_801D16E4(int id, int disabled)
{
    if (disabled == 0) {
        void* object = lbl_8064D544;
        while (object != 0) {
            if (*(int*)((u8*)object + 0xC) == id &&
                (*(int*)((u8*)object + 4) & 0x1FF0) == 0x1010 &&
                ((u8*)object)[0xFF1] == 2) {
                void* link = *(void**)((u8*)object + 0x18C);
                if (link != 0) {
                    void* actor = *(void**)((u8*)link + 0x88);
                    if (actor != 0) {
                        int flags = fn_801911D0(actor);
                        fn_801914D8(actor);
                        fn_801911F4(actor, flags & ~0x18);
                    }
                }
                break;
            }
            object = *(void**)((u8*)object + 0x14);
        }
    }
}
