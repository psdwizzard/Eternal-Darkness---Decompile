typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#pragma use_lmw_stmw on

typedef struct Context {
    u8 pad[0x18];
    u32 flags;
} Context;

typedef struct Runtime {
    u8 pad[0x20];
    u32 flags;
    u8 pad24[0x138];
    u8* memory;
} Runtime;

typedef struct Work {
    u8 bytes[0xC4];
    Runtime* runtime;
} Work;

extern void *fn_8006ED3C();
extern void fn_8006BEE4(Context*, void (*)(void));
extern void fn_8006DEF8(Work*, int, void*, Work*, u16);
extern void fn_8006EB60(void);
extern void fn_80089A34(void);
extern unsigned int rand(void);
extern char* fn_800FD40C(void*, const void*);
extern const u8 lbl_8024514C[];

void fn_800898E0(Work* work)
{
    int index;
    Context* context = fn_8006ED3C(work, 0xB, &index);
    Runtime* runtime = work->runtime;
    u8* memory = runtime->memory;
    int i;

    fn_8006BEE4(context, fn_8006EB60);
    work->bytes[index * 0x2C + 0x6A] = 0;
    work->bytes[index * 0x2C + 0x6B] = 4;
    work->bytes[index * 0x2C + 0x68] = 4;
    fn_8006DEF8(work, 0xB, fn_80089A34, work,
                (u16)((rand() & 0xF) + 100));
    for (i = 0; i < 3; i++) {
        work->bytes[index * 0x2C + 0x68] = (u8)i;
        fn_8006DEF8(work, 0xB, fn_80089A34, work,
                    (u16)((rand() & 0x1F) + 300));
    }
    *(int*)(memory + 0x1740) = 0;
    *(int*)(memory + 0x1744) = 2;
    *(int*)(memory + 0x1748) = 3;
    *(int*)(memory + 0x174C) = 1;
    *(int*)(memory + 0x1780) = 0;
    work->bytes[index * 0x2C + 0x68] = 0;
    fn_800FD40C(work->bytes + 0x18, lbl_8024514C);
    context->flags |= 0x10;
    runtime->flags = (runtime->flags >> 2) << 2;
}
