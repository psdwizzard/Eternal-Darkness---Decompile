typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void* lbl_8064D718;
extern void* lbl_8064D6BC;
extern void* lbl_8064D6B8;
extern int lbl_8064D780;
extern int lbl_8064D76C;
extern u32 lbl_8065140C;
extern u8 lbl_8030F540[];

extern int fn_8015E4B4(void);
extern void fn_801F3528(u32*);
extern void* fn_801397F8(void*, int, int, int);
extern void DCInvalidateRange(void*, u32);
extern void fn_801F50EC(void*, void*);
extern void fn_8020B774(void*, u32);
extern void fn_801F5240(int);
extern void fn_80133300(void);
extern void fn_80134BFC(void);

void fn_801F53E8(int value)
{
    void* source = lbl_8064D718;
    void* buffer;
    u32 event;

    if (fn_8015E4B4() != 0 && (signed char)lbl_8030F540[472] != -1) {
        event = lbl_8065140C;
        fn_801F3528(&event);
        return;
    }
    buffer = lbl_8064D6BC;
    if (buffer == 0) {
        buffer = (void*)(((u32)fn_801397F8(&event, 1, 2, 1) + 31) & ~31);
    }
    lbl_8064D6B8 = buffer;
    DCInvalidateRange(source, 0x96000);
    fn_801F50EC(source, buffer);
    fn_8020B774(buffer, 0x96000);
    lbl_8064D780 = value;
    lbl_8064D76C = value;
    fn_801F5240(1);
    if (fn_8015E4B4() != 0) {
        fn_80133300();
        if (*(u32*)(lbl_8030F540 + 456) & 1) fn_80133300();
        if (*(short*)(lbl_8030F540 + 470) == -1) fn_80134BFC();
        *(u16*)(lbl_8030F540 + 470) = (u16)-1;
    }
}
