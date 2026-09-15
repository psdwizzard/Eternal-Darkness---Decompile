typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Context {
    u8 pad00[0xC];
    u32 handle;
    u32 end;
    u32 value;
    u32 argument;
    u8 pad1C[0x14];
    u32 flags;
    u8 pad34[4];
    u32 resource;
    u16 kind;
    u8 state;
    u8 pad3F;
    u8 limit;
    u8 pad41[3];
} Context;

typedef struct Timings {
    u32 first;
    u32 second;
    u32 third;
    u32 fourth;
} Timings;

typedef struct GlobalState {
    u8 pad00[0x1C];
    Context context;
    u8 object[0x26C];
    Timings timings;
} GlobalState;

typedef struct Block32 { u32 word[8]; } Block32;

extern GlobalState lbl_80302400;
extern u8 lbl_8023D020[];
extern Block32 lbl_80238978;
extern Block32 lbl_80238998;
extern u32 lbl_8064C6D0;
extern u32 lbl_8064C6C4;
extern u32 lbl_8064C6C8;
extern u32 lbl_8064C670;
extern void* lbl_8064C504;
extern u32 lbl_8064C51C;
extern u32 lbl_8064CA68;

extern void* memset(void*, int, u32);
extern void fn_8001D56C(void);
extern void fn_8001DE68(void);
extern void fn_8001DE84(int, int);
extern u32 fn_80024638(void*, void*, u32*);
extern void fn_80023B40(void);
extern void fn_80042E3C(void);
extern void fn_80042EDC(void);
extern void fn_800B177C(int, void*);
extern void fn_800B2548(int, int);
extern void fn_800B689C(u32, u32);
extern void* fn_80138164(void);
extern void* fn_8015AA0C(void);
extern void* fn_8015AA14(void);
extern void fn_8015D458(void*, void*, void*);
extern void fn_8015DAB0(void*);
extern int fn_801A98F4(int, int);
extern void fn_801A99B4(void);
extern void fn_801AD4B4(u32, u32, u32, u32);
extern void* fn_801E6CA0(void*, int, int, int, int);
extern void fn_801E6F9C(void*, u32);
extern void fn_801E85A8(void);
extern void fn_801EFE84(u32);
extern void fn_8020EF54(void*, void*);
extern void fn_8022A814(u32, u32);

void fn_8001E144(u32 mode)
{
    GlobalState* global = &lbl_80302400;
    u8* data = lbl_8023D020;
    Context* context = &global->context;
    Timings* timings = &global->timings;
    u32 sizes[5];
    void* object;
    u8* initial_data;
    fn_8022A814(0, 0);
    memset(context, 0, 0x44);
    context->limit = 200;
    context->kind = 7;
    context->value = 255;
    lbl_8064C6C8 = 0;
    lbl_8064C6C4 = 0;
    lbl_8064C670 = 0;
    context->argument = mode;
    context->flags = 0;
    object = global->object;
    initial_data = data + 0x83C;
    fn_8020EF54(object, initial_data);
    lbl_8064C6D0 = 0;
    fn_8001DE84(3, 0);
    fn_8001DE84(3, 0);
    context->value = 255;
    context->flags |= 0x20;
    timings->first = 2000;
    timings->second = 1000;
    timings->third = 1000;
    timings->fourth = 1000;

    if (mode == 0) {
        fn_801AD4B4(7, 0, 0, 0);
        fn_8001D56C();
        fn_801A99B4();
    }
    {
    Context* active = &global->context;
    active->handle = 0;
    active->end = 0;

    switch (mode) {
    case 1:
    case 12:
    case 13:
        fn_8001DE84(1, 0);
        fn_8001DE84(1, 0);
        context->value = 255;
        context->flags |= 1;
        context->flags |= 0x10;
        timings->second = 3000;
        timings->third = 1500;
        timings->fourth = 1500;
    case 0:
        {
            void* start = fn_80138164();
            active->handle = fn_80024638(data + 0x848, start, &sizes[4]);
            fn_8015DAB0((void*)active->handle);
            active->end = (u32)start + ((sizes[4] + 31) & ~31);
        }
        if (context->flags & 4) {
            context->resource = fn_801A98F4(629, 100);
            fn_8001DE84(25, 0);
            context->value = 255;
            context->flags |= 1;
        }
        fn_80042EDC();
        fn_80042E3C();
        break;
    case 3:
    {
        void* start = fn_80138164();
        active->handle = fn_80024638(data + 0x848, start, &sizes[3]);
        fn_8015DAB0((void*)active->handle);
        active->end = (u32)start + ((sizes[3] + 31) & ~31);
        fn_8015D458(data + 0x858, (void*)active->end, fn_8015AA14());
        fn_8015DAB0((void*)active->end);
        active->state = 253;
        break;
    }
    case 4:
    {
        void* start = fn_80138164();
        active->handle = fn_80024638(data + 0x848, start, &sizes[2]);
        fn_8015DAB0((void*)active->handle);
        active->end = (u32)start + ((sizes[2] + 31) & ~31);
        fn_8015D458(data + 0x858, (void*)active->end, fn_8015AA14());
        fn_8015DAB0((void*)active->end);
        fn_801E6F9C(fn_801E6CA0(lbl_8064C504, 0, 39, 0, 1), 0);
        active->state = 254;
        break;
    }
    case 5:
        {
            void* second = fn_8015AA0C();
            void* start = fn_80138164();
            active->handle = fn_80024638(data + 0x848, start, &sizes[1]);
            fn_8015DAB0((void*)active->handle);
            active->end = (u32)start + ((sizes[1] + 31) & ~31);
            fn_8015D458(data + 0x858, (void*)active->end, fn_8015AA14());
            fn_8015DAB0((void*)active->end);
            lbl_8064C51C = fn_80024638(data + 0x864, second, &sizes[1]);
        }
        fn_801E85A8();
        lbl_8064CA68 = 1;
        fn_800B177C(1, (void*)fn_80023B40);
        fn_800B689C(0, 1);
        fn_800B2548(12, 0);
        {
            Block32* blocks = (Block32*)(data + 0x75C);
            blocks[3] = lbl_80238978;
            blocks[4] = lbl_80238998;
        }
        fn_8001DE84(27, 0);
        fn_8001DE84(6, 0);
        lbl_8064C6C8 = 1;
        break;
    case 14:
    {
        void* start = fn_80138164();
        active->handle = fn_80024638(data + 0x848, start, &sizes[0]);
        fn_8015DAB0((void*)active->handle);
        active->end = (u32)start + ((sizes[0] + 31) & ~31);
        fn_8015D458(data + 0x858, (void*)active->end, fn_8015AA14());
        fn_8015DAB0((void*)active->end);
        active->state = 252;
        fn_8001DE84(27, 0);
        fn_8001DE84(252, 0);
        fn_801EFE84(0);
        break;
    }
    }
    }

    fn_8001DE68();
}
