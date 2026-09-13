typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Shared {
    int primary;
    int secondary;
    s16 requested;
    u8 padA[2];
    u8* slots[2];
    void* queues[2];
} Shared;

typedef struct Auxiliary { u8 pad[0x18]; int enabled; } Auxiliary;

extern volatile Shared lbl_805B6FE0;
extern Auxiliary lbl_805B701C;
extern void* lbl_8064C4E4;
extern int lbl_8064C5C0;
extern void* lbl_8064D158;
extern int lbl_8064D180;
extern int lbl_8064D184;
extern int lbl_8064D188;
extern int lbl_8064D18C;

extern int fn_800460FC(void);
extern void fn_80046B68(void);
extern void fn_80046F28(int, int);
extern void fn_80046FC4(int, int);
extern void fn_8011FB54(void*, int);
extern void fn_80158E7C(int);
extern void fn_80159E0C(void);
extern void fn_8015BDAC(void);
extern void fn_8015C020(int);
extern unsigned int fn_801E7998(void*);
extern int fn_80201AE4(void);
extern int fn_80201B3C();
extern int fn_80201B44();
extern void fn_8020D250(void*, int, int);
extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);

static s16* slot_id_ptr(int slot)
{
    return (s16*)(lbl_805B6FE0.slots[slot] + 0x8140);
}

void fn_8015BDF0(int requested, void* queue)
{
    int secondary;
    int audio_mode;
    int expected;
    s16* ptr;
    u32 interrupts;

    fn_800460FC();
    secondary = lbl_805B6FE0.secondary;
    fn_80158E7C(1);
    lbl_8064D180 = lbl_8064D18C;
    lbl_8064D18C = requested;
    if (lbl_8064D188 == 0) {
        unsigned int limit = fn_801E7998(lbl_8064D158);
        if ((unsigned int)lbl_8064D18C < limit) {
            lbl_8064D184 = lbl_8064D18C;
        }
    }
    if (lbl_8064C4E4 != 0 && lbl_8064C5C0 == 0 && lbl_805B701C.enabled != 0) {
        fn_8011FB54(lbl_8064C4E4, lbl_8064D18C);
        fn_80046F28(fn_80201B3C(), lbl_8064D18C);
        audio_mode = fn_80201AE4();
        expected = fn_80201B44();
        if (expected == audio_mode) {
            fn_80046FC4(lbl_8064D18C, 0);
        }
    }
    fn_80046B68();
    if (secondary != -1 && (ptr = slot_id_ptr(secondary), *ptr == requested)) {
        fn_8015BDAC();
    } else if (ptr = slot_id_ptr(lbl_805B6FE0.primary), *ptr != requested) {
        fn_8015BDAC();
        interrupts = OSDisableInterrupts();
        *slot_id_ptr(lbl_805B6FE0.primary) = requested;
        lbl_805B6FE0.slots[lbl_805B6FE0.primary][0x8142] = 0;
        lbl_805B6FE0.slots[lbl_805B6FE0.primary][0x8143] = 0;
        OSRestoreInterrupts(interrupts);
    }
    lbl_805B6FE0.queues[lbl_805B6FE0.primary] = queue;
    if ((signed char)lbl_805B6FE0.slots[lbl_805B6FE0.primary][0x8142] == 1) {
        lbl_805B6FE0.queues[lbl_805B6FE0.primary] = 0;
        if (queue != 0) {
            fn_8020D250(queue, 0, 1);
        }
    }
    fn_80159E0C();
    lbl_805B6FE0.requested = -1;
    fn_80158E7C(2);
    fn_8015C020(0);
}
