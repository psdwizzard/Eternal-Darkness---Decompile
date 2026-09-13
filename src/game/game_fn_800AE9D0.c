typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct RequestContext {
    u8 pad0[8];
    short timer;
} RequestContext;

extern void *fn_8006ED3C();
extern int fn_8006EB60(void*);
extern void fn_8006E20C(void);
extern void fn_8006BEE4(RequestContext*, int (*)(void*));
extern void fn_8006DEF8(void*, int, void (*)(void), void*, int);
extern void fn_800AEB48(void);
extern char* fn_800FD40C(void*, const void*);
extern unsigned int fn_801A9B28(void);
extern unsigned int fn_801A9B30(void);
extern void* memset(void*, int, unsigned int);
extern const u8 lbl_80246E08[];
extern u32 lbl_8064C9E0;
extern u32 lbl_8064C9DC;

void fn_800AE9D0(void* object)
{
    u8* owner = object;
    u32 index;
    RequestContext* context;
    u8* runtime;
    int i;

    context = fn_8006ED3C(owner, 24, &index);
    context->timer = 0;
    runtime = *(u8**)(*(u8**)(owner + 0xC4) + 0x15C);
    *(int*)(runtime + 0x1780) = -1;
    fn_8006BEE4(context, fn_8006EB60);
    owner[index * 0x2C + 0x6A] = 0;
    owner[index * 0x2C + 0x6B] = 0;
    memset(runtime, 0, 0xB00);
    memset(runtime + 0xB00, 0, 0xC40);

    owner[index * 0x2C + 0x68] = 4;
    fn_8006DEF8(owner, 24, fn_800AEB48, owner, 1);
    owner[index * 0x2C + 0x68] = 0;
    fn_8006DEF8(owner, 24, fn_8006E20C, owner, 10);
    for (i = 1; i < 3; i++) {
        owner[index * 0x2C + 0x68] = i;
        fn_8006DEF8(owner, 24, 0, 0, 1);
    }
    owner[index * 0x2C + 0x68] = 0;
    fn_800FD40C(owner + 0x18, lbl_80246E08);
    lbl_8064C9E0 = fn_801A9B28() & 0xFF;
    lbl_8064C9DC = fn_801A9B30() & 0xFF;
}
