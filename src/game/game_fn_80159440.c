typedef unsigned short u16;
typedef unsigned int u32;

typedef void (*TransitionCallback)(int*, int*);

typedef struct ChannelTable {
    int unused;
    volatile int current;
    int pad08;
    void* channels[12];
} ChannelTable;

typedef struct TransitionState {
    char pad00[0x18];
    int pending;
} TransitionState;

typedef struct Globals {
    char pad000[0x1E0];
    ChannelTable channel_table;
    TransitionState transition;
    char pad238[0x10];
    int message_queue;
} Globals;

extern Globals lbl_805B6E00;
extern char lbl_8063CD18[];
extern int lbl_8064C4F4;
extern int lbl_8064D18C;
extern signed char lbl_8064D118;
extern TransitionCallback lbl_8064D150;
extern TransitionCallback lbl_8064D154;
extern void (*lbl_8064D198)(void);

extern void fn_80237D2C(int);
extern void fn_8015AD00(int);
extern void fn_801ACC10(void);
extern void fn_801AC350(int, int, int);
extern void fn_800459C0(void);
extern int fn_801358B4(int);
extern u32 fn_8022658C(void);
extern void fn_8015BDF0(int, void*);
extern int fn_8020D318(void*, void*, int);
extern void fn_80228D9C(void);
extern void fn_80159184(u32);
extern void fn_801F7034(void*, int);
extern void fn_8015AC94(int, int);
extern void fn_8015BCB0(void);
extern void fn_8015C020(int);

void fn_80159440(int value, u32 flags)
{
    int special;
    int saved;
    Globals* globals = &lbl_805B6E00;
    int message;

    fn_80237D2C(1);
    if (lbl_8064D118 != 0) {
        lbl_8064D118 = 0;
    } else {
        globals->transition.pending = 1;
    }

    special = flags & 0x40;
    if (special == 0) {
        if (lbl_8064D198 != 0) {
            lbl_8064D198();
        }
        fn_8015AD00(2);
    }

    if (lbl_8064D154 != 0) {
        lbl_8064D154(&lbl_8064D18C, &value);
    }
    if (value != lbl_8064D18C) {
        fn_801ACC10();
        fn_801AC350(10, 1, 0);
        fn_800459C0();
    } else {
        lbl_8064C4F4 = 1;
    }

    saved = fn_801358B4(0);
    while ((u16)fn_8022658C() != 0xBEEF) {
    }
    fn_8015BDF0(value, &globals->message_queue);
    fn_8020D318(&globals->message_queue, &message, 1);
    fn_80228D9C();
    fn_80159184(flags);

    {
        ChannelTable* channels = (ChannelTable*)((u32)globals + 0x1E0);
        if (channels->current != -1) {
            char* channel = (char*)channels->channels[channels->current];
            *(short*)(channel + 0x8140) = -1;
            channel = (char*)channels->channels[channels->current];
            channel[0x8142] = 0;
            channel = (char*)channels->channels[channels->current];
            channel[0x8143] = 0;
        }
    }

    if (special == 0) {
        fn_801F7034(lbl_8063CD18 + 0x110, 0);
        fn_8015AC94(2, 0);
    }
    fn_8015BCB0();
    fn_8015C020(0);
    fn_801358B4(saved);
    if (lbl_8064D150 != 0) {
        lbl_8064D150(&lbl_8064D18C, &value);
    }
    fn_80237D2C(0);
}
