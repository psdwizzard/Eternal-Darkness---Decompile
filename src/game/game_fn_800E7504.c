/* The function body matches retail. The current compiler settings emit
 * GPR save/restore helpers in place of the retail stmw/lmw pair. */
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

extern Entry lbl_80325DB8[10];
extern u16 lbl_8064CB04;
extern void *fn_80201BC8(void *);
extern void *fn_801A717C(void);
extern void fn_801A7228(void *);
extern void fn_801A7470(void *, u32);
extern void fn_801A74A0(void *, u32);
extern void fn_801A74A8(void *, u32);
extern void fn_801A7518(void *, s16);
extern void fn_801A7538(void *, u16);
extern void fn_801A764C(void *, const void *);
extern void *fn_8011F130(void *);
extern int fn_80201B44(void);
extern u64 fn_8020123C(int, int, int, int);

void fn_800E7504(void *object, u8 index, s16 amount)
{
    u16 *countdown;
    Entry *entry;
    void *actor;
    void *event;
    int channel;

    actor = fn_80201BC8(object);
    if (actor != 0 && amount != 0) {
        if (lbl_80325DB8[index].kind != 0) {
            switch (lbl_80325DB8[index].kind) {
            case 1:
                channel = 0;
                break;
            case 2:
                channel = 2;
                break;
            case 3:
                channel = 1;
                break;
            case 4:
                channel = 3;
                break;
            }
            event = fn_801A717C();
            fn_801A74A0(event, 0);
            entry = &lbl_80325DB8[index];
            fn_801A74A8(event, entry->id);
            fn_801A7538(event, (u16)(1 << channel));
            fn_801A7518(event, amount);
            fn_801A764C(event, fn_8011F130(actor));
            if (entry->id == fn_80201B44()) {
                countdown = &lbl_8064CB04;
            } else {
                countdown = &entry->countdown;
            }
            if (*countdown == 0) {
                fn_801A7470(event, 11);
                *countdown = 2;
            } else {
                --*countdown;
                fn_801A7470(event, -1);
            }
            fn_8020123C(0x27, 0, entry->id, (int)event);
            fn_801A7228(event);
        }
    }
}
