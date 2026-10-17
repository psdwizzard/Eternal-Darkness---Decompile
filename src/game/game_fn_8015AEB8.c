typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void* OSMessage;
typedef struct OSMessageQueue { u8 data[0x20]; } OSMessageQueue;
typedef struct OSThread { double data[0x310 / 8]; } OSThread;
typedef struct TaskState { u8 pad0[0x2060]; OSMessageQueue* volatile queues[4]; u8 pad2070[0x30]; } TaskState;

extern volatile u32 lbl_8064BA28[2];
extern int lbl_8064D120, lbl_8064D150, lbl_8064D154;
extern void (*lbl_8064D14C)(int, int);
extern u32* lbl_8064D158;
extern int lbl_8064D15C, lbl_8064D180, lbl_8064D184;
extern int lbl_8064D18C, lbl_8064D198;
extern u32 lbl_8064D190;

extern int fn_8015AC74(int);
extern int fn_8015AC84(int);
extern void fn_80158794(void);
extern int fn_800460FC(void);
extern void* fn_801E78DC(u32);
extern u32 fn_8021AAA0(u32*, u32);
extern void fn_8021B6C8(void);
extern void fn_8020D1F0(OSMessageQueue*, OSMessage*, int);
extern int fn_8020F84C(void*, void*, void*, void*, u32, int, u16);
extern void fn_8015D1C8(void*);
extern void fn_8015A340(void);
extern void fn_8015B800(void);
extern void fn_800BD94C(void);
extern void fn_801E7944(u32*);
extern void fn_801599BC(int, int);
extern void fn_8015DD48(void);
extern void fn_8015C918(void);
extern void fn_8013816C(void);
extern void fn_8015E794(void);
extern int fn_8020FC0C(void*);

static u8 unknown_00000[0x1FC] = {0};
static OSMessageQueue queue3 = {0};
static u8 unknown_0021C[0x2C] = {0};
static OSMessageQueue queue4 = {0};
static OSMessageQueue queue1 = {0};
static u8 unknown_00288[0x18] = {0};
static TaskState states[2] = {0};
static u8 unknown_043E0[0x20060] = {0};
static OSMessageQueue queue9 = {0};
static OSMessageQueue queue0 = {0};
static u8 unknown_24480[0x7380] = {0};
static OSMessageQueue queue5 = {0};
static u8 unknown_2B820[0x13C] = {0};
static OSMessage messages0[16] = {0};
static OSMessage messages1[16] = {0};
static OSMessageQueue queue2 = {0};
static OSMessage messages2[16] = {0};
static OSMessage messages3[16] = {0};
static OSMessage messages4[16] = {0};
static OSMessage messages5[16] = {0};
static OSMessageQueue queue6 = {0};
static OSMessage messages6[16] = {0};
static OSMessageQueue queue7 = {0};
static OSMessage messages7[16] = {0};
static OSMessageQueue queue8 = {0};
static OSMessage messages8[16] = {0};
static OSMessage messages9[16] = {0};
static OSMessageQueue queue10 = {0};
static OSMessage messages10[16] = {0};
static OSMessageQueue queue11 = {0};
static OSMessage messages11[16] = {0};
static OSMessageQueue queue12 = {0};
static OSMessage messages12[16] = {0};
static OSMessageQueue queue13 = {0};
static OSMessage messages13[16] = {0};
static OSMessageQueue queue14 = {0};
static OSMessage messages14[16] = {0};
static OSMessage task_messages_a[2][16] = {0};
static OSMessageQueue task_queues_a[2] = {0};
static OSMessage task_messages_b[2][16] = {0};
static OSMessageQueue task_queues_b[2] = {0};
static OSMessage task_messages_c[2][16] = {0};
static OSMessageQueue task_queues_c[2] = {0};
static OSMessage task_messages_d[2][16] = {0};
static OSMessageQueue task_queues_d[2] = {0};
static u8 task_stacks[2][0x2000] = {0};
static OSThread task_threads[2] = {0};
static OSThread thread0 = {0};
static u8 stack0[0x2000] = {0};
static OSThread thread1 = {0};
static u8 stack1[0x2000] = {0};
static OSThread thread2 = {0};
static u8 stack2[0x2000] = {0};

void fn_8015AEB8(void (*callback)(int, int), int allocation, int flags)
{
    int count;
    int i;
    int j;

    lbl_8064D14C = callback;
    lbl_8064D150 = 0;
    lbl_8064D154 = 0;
    lbl_8064D15C = 0;
    lbl_8064D18C = -1;
    lbl_8064D184 = 0;
    lbl_8064D180 = 0;
    lbl_8064D198 = 0;
    fn_8015AC74(1);
    fn_8015AC84(1);
    fn_80158794();

    if (lbl_8064D120 == 0) {
        count = fn_800460FC();
        lbl_8064D158 = fn_801E78DC(allocation);
        fn_8021AAA0(&lbl_8064D190, 2);
        fn_8021B6C8();
        for (i = 0; i < count; i++) {
        }

        fn_8020D1F0(&queue0, messages0, 0x10);
        fn_8020D1F0(&queue1, messages1, 0x10);
        fn_8020D1F0(&queue2, messages2, 0x10);
        fn_8020D1F0(&queue3, messages3, 0x10);
        fn_8020D1F0(&queue4, messages4, 0x10);
        fn_8020D1F0(&queue5, messages5, 0x10);
        fn_8020D1F0(&queue6, messages6, 0x10);
        fn_8020D1F0(&queue7, messages7, 0x10);
        fn_8020D1F0(&queue8, messages8, 0x10);
        fn_8020D1F0(&queue9, messages9, 0x10);
        fn_8020D1F0(&queue10, messages10, 0x10);
        fn_8020D1F0(&queue11, messages11, 0x10);
        fn_8020D1F0(&queue12, messages12, 0x10);
        fn_8020D1F0(&queue13, messages13, 0x10);
        fn_8020D1F0(&queue14, messages14, 0x10);

        for (i = 0; i < 2; i++) {
            fn_8020D1F0(&task_queues_a[i], task_messages_a[i], 0x10);
            fn_8020D1F0(&task_queues_b[i], task_messages_b[i], 0x10);
            fn_8020D1F0(&task_queues_c[i], task_messages_c[i], 0x10);
            fn_8020D1F0(&task_queues_d[i], task_messages_d[i], 0x10);
            states[i].queues[0] = &task_queues_a[i];
            states[i].queues[1] = &task_queues_b[i];
            states[i].queues[2] = &task_queues_c[i];
            states[i].queues[3] = &task_queues_d[i];
            fn_8020F84C(&task_threads[i], fn_8015D1C8, &states[i],
                        task_stacks[i] + 0x2000, 0x2000, lbl_8064BA28[i], 1);
        }
        fn_8020F84C(&thread0, fn_8015A340, 0, stack0 + 0x2000, 0x2000, 0x1D, 1);
        fn_8020F84C(&thread1, fn_8015B800, 0, stack1 + 0x2000, 0x2000, 0xA, 1);
        fn_8020F84C(&thread2, fn_800BD94C, 0, stack2 + 0x2000, 0x2000, 0x1F, 1);
    } else if ((flags & 2) == 0) {
        fn_801E7944(lbl_8064D158);
    }

    fn_801599BC(lbl_8064D120, flags & 1);
    fn_8015DD48();
    fn_8015C918();
    if (lbl_8064D120 == 0) {
        fn_8013816C();
        fn_8015E794();
        fn_8020FC0C(&thread0);
        fn_8020FC0C(&thread1);
        for (j = 0; j < 2; j++) {
            fn_8020FC0C(&task_threads[j]);
        }
        fn_8020FC0C(&thread2);
        lbl_8064D120 = 1;
    }
}
