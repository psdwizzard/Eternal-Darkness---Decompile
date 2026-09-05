typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

extern void *fn_80201814();
extern void* fn_80201C24();
extern void *fn_80201BC8();
extern int fn_8006749C(u8);
extern void fn_80120AD0(void *, int, s16, u16, float, float);
extern int fn_802006D4(int, int, int, int, int);
extern void fn_8020104C(int, void*, void*, int, float);
#define fn_8020104C(a,b,c,d,e) fn_8020104C((a),(void*)(c),(void*)(d),(int)(e),(b))
extern float lbl_8064F460;

#pragma opt_common_subs off
void fn_800DC2B8(int owner, int kind, int level, float amount)
{
    void *context = fn_80201814(owner);
    void *object;
    u16 flags;
    u16 combined;
    u8 level_byte;
    s16 offset;

    fn_80201C24(context);
    object = fn_80201BC8(context);
    flags = fn_8006749C(kind);
    level_byte = level;
    offset = (5 - level_byte) * 20;
    combined = flags | 0x202;
    fn_80120AD0(object, 0, offset, combined,
                 lbl_8064F460, lbl_8064F460);
    fn_802006D4(owner, owner, -1, 0x4b, 0);
    fn_8020104C(0x4b, amount, owner, owner, 0);
}
#pragma opt_common_subs reset
