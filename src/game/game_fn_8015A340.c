typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void* OSMessage;
typedef struct OSMessageQueue { u8 data[0x20]; } OSMessageQueue;
typedef struct OSThread { double data[0x310 / 8]; } OSThread;
typedef struct TaskState { u8 pad0[0x2060]; OSMessageQueue* queues[4]; u8 pad2070[0x30]; } TaskState;

typedef struct Transfer {
    s16 tag;
    u16 done;
    u32 address;
    u32 pad8;
    u32 offset;
    void* queue;
    u32 pad14;
} Transfer;

typedef struct Banks {
    u8 pad0[0xC];
    u8* controls[2];
    OSMessageQueue* queues[2];
} Banks;

typedef struct StreamState {
    s16 index;
    u8 flag;
    u8 state;
    u8 pad4[0xC];
    u32 start;
    u32 end;
    u32 cursor;
    u32 loaded;
    u32 chunk;
    u32 chunkLoaded;
    u32 total;
    u32 boundary;
    u32 length;
    u32 initial;
    u32 loadedCopy;
    u8 pad3C[0x10];
    void* source;
    OSMessageQueue* queue;
    u8 pad54[0xC];
} StreamState;

typedef struct Record { u8 pad0[0x2048]; int active; } Record;
typedef struct Descriptor { int value; u8 pad4[0x14]; u8 kind; u8 pad19[0xF]; } Descriptor;
typedef struct FileInfo {
    u8 block[0x30];
    u32 start;
    u32 length;
    void* callback;
} FileInfo;
typedef struct Request { u32 words[8]; } Request;

extern u8 lbl_805BB240[];
extern OSMessageQueue lbl_805E2600;
extern u8 lbl_805E2620[];
extern char lbl_8024F038[];
extern Descriptor lbl_80241DE8[];
extern void* lbl_8064D170[2];
extern u32 lbl_8064D140;
extern char lbl_8064BA30[7], lbl_8064BA38[2];
extern char lbl_8064DC80[];
extern int fn_8020D318(void*, void*, int);
extern int fn_8020D250(OSMessageQueue*, OSMessage, int);
extern int fn_800F9D4C(char*, const char*, ...);
extern int fn_802136A4(const char*);
extern int fn_80213394(const char*, FileInfo*);
extern int fn_8021345C(FileInfo*);
extern int fn_802137F4(FileInfo*, void*, int, int, int);
extern void fn_8021B730(Request*, u32, u32, u32, u32, u32, u32, void (*)(u32));
extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);
extern void DCInvalidateRange(void*, u32);
extern int fn_8015B274(void*, void*, u8*, int, u8*, u32, void*, int);
extern Record* fn_8015A314(int);
extern void fn_8015A17C(void);
extern void fn_80159088(int);
extern void fn_80158E7C(int);
extern void fn_80158E84(int);
extern void fn_80155BB0(char*, char*, ...);
extern void fn_80008014(int, int);
extern u32 fn_8015D304(char*, Record*);
extern int fn_801332E0(void);
extern void* fn_801332E8(void**);
extern void fn_80131408(void*);
extern void fn_8015D4EC(void*, int, Record*);
extern u32 fn_8015DF60(void);
extern void fn_8015C020(int);


static u8 unknown_00000[0x180] = {0};
static volatile Transfer transfers[4] = {0};
static volatile Banks banks = {0};
static OSMessageQueue message_queue = {0};
static u8 unknown_0021C[0x2C] = {0};
static OSMessageQueue queue4 = {0};
static OSMessageQueue transfer_queue = {0};
static u8 unknown_00288[0x18] = {0};
static TaskState states[2] = {0};
static volatile StreamState stream = {0};
static u8 unknown_04440[0x20000] = {0};
static OSMessageQueue suspend_queue = {0};
static OSMessageQueue load_queue = {0};
static u8 stream_buffer[0x7380] = {0};
static u8 unknown_2B800[0x15C] = {0};
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

#pragma readonly_strings on
static const char file_name[] = "ld_loaddata.c";

#pragma opt_dead_assignments off
#pragma opt_propagation off
void fn_8015A340(void)
{
    FileInfo file;
    Request request;
    char name[0x10];
    char streamName[0x20];
    u32 message, reply, interrupts;

    void* invalidateBuffer;
    volatile u8* streamFlag;
    OSMessageQueue* volatile* streamQueue;
    volatile StreamState* state = 0;
    u32 dmaBuffer = 0;
    u32 amount = 0;
    u32 bank;
    u32 command;
    int handled;

    handled = 0;
    state = &stream;
    streamQueue = &state->queue;
    streamFlag = &state->flag;
    dmaBuffer = (u32)lbl_805BB240;
    invalidateBuffer = lbl_805BB240;

    for (;;) {
        u32 tag;
        u32 slot;
        fn_8020D318(&message_queue, &message, 1);
        if (message == 0xFFFFFFFF) {
            fn_8020D250(&suspend_queue, (void*)0x2A, 1);
            do fn_8020D318(&message_queue, &message, 1);
            while (message != 0xFFFFFFFE);
            continue;
        }
        tag = message & 0xFFF;
        command = message & 0xFFE00000;
        slot = (message >> 12) & 0xFF;
        bank = (message & 0x100000) ? 1 : 0;
        fn_800F9D4C(name, "%s%04d.bpe", lbl_8064DC80, tag);

        switch (command) {
        case 0x80000000: {
            u32 remaining, destination, actual;
            int alternate;
            int opened;
            u32 offset;
            fn_802136A4(lbl_8064BA30);
            opened = fn_80213394(name, &file);
            fn_802136A4(lbl_8064BA38);
            if (opened == 0) break;
            remaining = file.length;
            alternate = 0;
            offset = 0;
            destination = (u32)transfers[slot].queue;
            interrupts = OSDisableInterrupts();
            transfers[slot].tag = tag;
            transfers[slot].done = 0;
            transfers[slot].offset = 0;
            transfers[slot].address = remaining;
            OSRestoreInterrupts(interrupts);
            while (fn_8020D318(&transfer_queue, &reply, 0) != 0) {}
            fn_8020D250(&transfer_queue, 0, 1);
            while (remaining != 0) {
                u8* p;
                actual = remaining < 0x10000 ? remaining : 0x10000;
                p = lbl_805BB240 + (alternate << 16);
                amount = (actual + 0x1F) & ~0x1F;
                while (fn_802137F4(&file, p, amount, offset, 2) == -1) {}
                fn_8020D318(&transfer_queue, &reply, 1);
                fn_8021B730(&request, 1, 0, 0, (u32)p, destination, amount,
                            (void (*)(u32))fn_8015A17C);
                alternate ^= 1;
                destination += actual;
                remaining -= actual;
                offset += actual;
            }
            fn_8020D318(&transfer_queue, &reply, 1);
            fn_8021345C(&file);
            interrupts = OSDisableInterrupts();
            if (transfers[slot].tag == tag && transfers[slot].address != 0)
                transfers[slot].done = 1;
            OSRestoreInterrupts(interrupts);
            handled = 1;
            break;
        }
        case 0x40000000: {
            {
                void* source = (void*)transfers[slot].address;
                void* queue = transfers[slot].queue;
                fn_8015B274(source, queue, lbl_8064D170[bank], 0x2C4020, lbl_805BB240, 0x10000, &load_queue, 0);
            }
            interrupts = OSDisableInterrupts();
            banks.controls[bank][0x8142] = 1;
            banks.controls[bank][0x8143] = 0;
            banks.controls[bank][0x8144] = 0;
            OSRestoreInterrupts(interrupts);
            fn_80159088(bank);
            if (banks.queues[bank] != 0) {
                fn_8020D250(banks.queues[bank], 0, 1);
                banks.queues[bank] = 0;
            }
            fn_80158E7C(4);
            break;
        }
        case 0x08000000: {
            Record* record;
            u32 base;
            int descriptorValue = (s16)lbl_80241DE8[stream.index].value;
            fn_80008014(descriptorValue, lbl_80241DE8[stream.index].kind);
            fn_800F9D4C(streamName, "/Cinematics/cin%04d", descriptorValue);
            record = fn_8015A314(tag);
            fn_8015D304(streamName, record);
            state->start = 0xDBCAA0;
            state->initial = state->start;
            base = fn_801332E0();
            fn_8015D4EC(&lbl_8064D140, 4, record);
            state->total = lbl_8064D140;
            lbl_8064D140 = (lbl_8064D140 + 0x1F) & ~0x1F;
            fn_8015D4EC(stream_buffer, base, record);
            fn_8015D4EC(stream_buffer + base,
                        (u32)fn_801332E8((void**)stream_buffer) - base, record);
            fn_80131408(stream_buffer);
            state->loaded = (u32)fn_801332E8((void**)stream_buffer);
            state->boundary = state->loaded;
            state->length = state->loaded;
            state->loadedCopy = state->loaded;
            if (state->start + lbl_8064D140 - state->loaded < state->end) {
                state->chunk = state->start + lbl_8064D140 - state->loaded;
                state->chunkLoaded = lbl_8064D140;
            } else {
                state->chunk = state->end;
                state->chunkLoaded = state->chunk - state->start;
                state->chunkLoaded += state->loaded;
            }
            state->source = stream_buffer;
            state->state = 2;
            if (state->loaded > 0x7380)
                fn_80155BB0("LD_MSGFLAG_SPOOL_CINEMATIC_HEADER", "Header loaded (%d bytes) was larger than CinHeaderBufferSize (%d)\n", state->loaded, 0x7380);
            if (fn_8020D250(&lbl_805E2600, 0, 0) == 0)
                fn_80155BB0("LD_MSGFLAG_SPOOL_CINEMATIC_HEADER", "OSSendMessage FAILED");
            handled = 1;
            break;
        }
        case 0x10000000: {
            Record* record = fn_8015A314(tag);
            u32 amount, destination;
            if (!record->active) break;
            while (fn_8020D318(&transfer_queue, &message, 0) != 0) {}
            interrupts = OSDisableInterrupts();
            if (state->cursor >= state->end) {
                state->cursor = state->start;
                state->boundary += state->end - state->start;
            }
            OSRestoreInterrupts(interrupts);
            amount = fn_8015DF60();
            if (amount == 0) break;
            destination = state->cursor;
            fn_8015D4EC((void*)dmaBuffer, amount, record);
            DCInvalidateRange(invalidateBuffer, amount);
            fn_8021B730((Request*)lbl_805E2620, 3, 0, 0, dmaBuffer, destination,
                        amount, (void (*)(u32))fn_8015A17C);
            fn_8020D318(&transfer_queue, &message, 1);
            streamQueue = &stream.queue;
            streamFlag = &stream.flag;
            interrupts = OSDisableInterrupts();
            state->cursor += amount;
            state->loaded += amount;
            fn_80158E84(2);
            if (state->loaded >= state->total) {
                *streamFlag = 0; state->state = 5;
            } else if (state->loaded == state->chunkLoaded) {
                *streamFlag = 1; state->state = 4;
            } else state->state = 3;
            OSRestoreInterrupts(interrupts);
            if (*streamQueue != 0)
                fn_8020D250(*streamQueue, 0, 0);
            handled = 1;
            break;
        }
        case 0xFFE00000:
            break;
        }
        fn_8015C020(handled);
    }
}
#pragma opt_propagation reset
#pragma opt_dead_assignments reset
