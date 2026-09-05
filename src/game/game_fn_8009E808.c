typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Context8009E808 {
    u8 pad00[8];
    s16 counter;
    u8 pad0A[0xE];
    u32 flags;
} Context8009E808;

extern Context8009E808 *fn_8006ED3C(void *, int, int *);
extern void fn_801E7974(void*, int);
extern void* fn_8006D488(void*);
extern void fn_802020B4(void*, int);
extern void fn_801A5C30(int);
extern void fn_80052424(int, int, int, int);
extern void* lbl_8064C4E0;

#pragma opt_propagation off
int fn_8009E808(void* event)
{
    s16 sounds[4] = { 101, 102, 103, 104 };
    int index;
    Context8009E808* context;
    register void* owner;
    int sound_index;

    owner = event;
    context = fn_8006ED3C(owner, 0xC, &index);
    sound_index = context->counter % 4;
    fn_801E7974(lbl_8064C4E0, 0x3BF);
    fn_802020B4(fn_8006D488(owner), 0);
    fn_801A5C30(0);
    fn_80052424(sounds[sound_index], -1, 0, 0);
    context->counter++;
    if (context->counter >= 4) {
        context->flags |= 0x401;
    }
    return 1;
}
#pragma opt_propagation reset
