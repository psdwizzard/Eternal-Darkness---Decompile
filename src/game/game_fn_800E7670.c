typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Entry {
    int id;
    u16 field4;
    u16 kind;
    u16 field8;
    u16 countdown;
    void **object;
} Entry;

typedef struct Value {
    u32 words[3];
} Value;

extern Entry lbl_80325DB8[10];
extern int fn_801DA27C(u32);
extern void *fn_801A717C(void);
extern void fn_801A7228(void *);
extern void fn_801A7470(void *, u32);
extern void fn_801A74A0(void *, u32);
extern void fn_801A74A8(void *, u32);
extern void fn_801A74D8(void *, u32);
extern void fn_801A7518(void *, s16);
extern void fn_801A7538(void *, u16);
extern void fn_801A764C(void *, const Value *);
extern void fn_801A7668(void *, u32);
extern u64 fn_8020123C(int, int, int, int);

int fn_800E7670(u8 index, const Value *value, register int amount)
{
    register void *event;
    register void *eventArg;
    int target;
    register int channel;
    register s16 shortAmount;

    target = fn_801DA27C(lbl_80325DB8[index].id);
    if (target != -1 && (s16)amount > 0 && lbl_80325DB8[index].kind != 0) {
        /* ASM: li preserves the channel in a register; C folds the constant mask. */
        asm { li channel, 0 }
        event = fn_801A717C();
        fn_801A74A0(event, 0);
        fn_801A74A8(event, target);
        fn_801A7538(event, (u16)(1 << channel));
        /* ASM: mr, mr pass the amount's low 16 bits in retail argument order.
         * C inserts an extsh for the short parameter; the setter only stores
         * the low halfword, so that conversion is redundant here. */
        asm {
            mr eventArg, event
            mr shortAmount, amount
        }
        fn_801A7518(eventArg, shortAmount);
        fn_801A764C(event, value);
        fn_801A7470(event, -1);
        fn_801A7668(event, 0);
        fn_801A74D8(event, 0x400000);
        amount = (u32)fn_8020123C(0xB, lbl_80325DB8[index].id, target, (int)event);
        fn_801A7228(event);
    }
    return amount;
}
