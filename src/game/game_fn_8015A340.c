/* NonMatching: recovered streaming worker; shared state is re-read as in retail. */
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Transfer {
    s16 tag;
    u16 done;
    u32 address;
    u32 pad8;
    u32 offset;
    void* queue;
    u32 pad14;
} Transfer;

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
} StreamState;

typedef struct Record { u8 pad0[0x2048]; int active; } Record;
typedef struct Descriptor { int value; u8 pad4[0x14]; u8 kind; u8 pad19[0xF]; } Descriptor;

typedef struct Context {
    u8 pad0[0x180];
    volatile Transfer transfers[4];
    u8 pad1E0[0xC];
    u8* volatile controls[2];
    void* volatile queues[2];
    u8 messageQueue[0x6C];
    u8 transferQueue[0x4178];
    volatile StreamState stream;
    void* volatile streamQueue;
    u8 pad4434[0x2000C];
    u8 suspendQueue[0x20];
    u8 scratch[0x20];
    u8 data[0x7380];
} Context;
extern Context lbl_805B6E00;
extern u8 lbl_805BB240[], lbl_805E2600[], lbl_805E2620[];
extern char lbl_8024F038[];
extern Descriptor lbl_80241DE8[];
extern void* lbl_8064D170[2];
extern u32 lbl_8064D140;
extern int lbl_8064BA30, lbl_8064BA38;
extern char lbl_8064DC80[];

extern int OSReceiveMessage(void*, void*, int);
extern int OSSendMessage(void*, void*, int);
extern int sprintf(char*, const char*, ...);
extern void DVDChangeDir(void*);
extern int DVDOpen(char*, void*);
extern void DVDClose(void*);
extern int DVDReadPrio(void*, void*, u32, u32, int);
extern void ARQPostRequest(void*, int, int, int, void*, void*, u32, void*);
extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);
extern void DCInvalidateRange(void*, u32);
extern int fn_8015B274(void*, void*, void*, u32, void*, u32, void*, int);
extern Record* fn_8015A314(int);
extern void fn_8015A17C(void);
extern void fn_80159088(int);
extern void fn_80158E7C(int);
extern void fn_80158E84(int);
extern void fn_80155BB0(char*, char*, ...);
extern void fn_80008014(int, int);
extern void fn_8015D304(char*, Record*);
extern u32 fn_801332E0(void);
extern u32 fn_801332E8(void*);
extern void fn_80131408(void*);
extern void fn_8015D4EC(void*, u32, Record*);
extern u32 fn_8015DF60(void);
extern void fn_8015C020(int);

typedef struct FileInfo {
    u8 block[0x30];
    u32 start;
    u32 length;
    void* callback;
} FileInfo;
typedef struct Request { u32 words[8]; } Request;

void fn_8015A340(void)
{
    FileInfo file;
    Request request;
    char name[0x10];
    char streamName[0x20];
    u32 message, reply, interrupts;
    /* Persistent across messages; the decompress and sentinel paths leave it alone. */
    int handled = 0;

    Context* context = &lbl_805B6E00;
    volatile StreamState* state = (volatile StreamState*)((u8*)&lbl_805B6E00 + 0x43E0);
    u8* upper = (u8*)&lbl_805B6E00 + 0x20000;
    void* volatile* streamQueue = (void* volatile*)((u8*)&lbl_805B6E00 + 0x4430);
    volatile u8* streamFlag = (volatile u8*)((u8*)&lbl_805B6E00 + 0x43E2);
    u8* dmaBuffer = lbl_805BB240;
    char* strings = lbl_8024F038;
    void* invalidateBuffer = lbl_805BB240;

    for (;;) {
        u32 tag, slot, bank, command;
        OSReceiveMessage(context->messageQueue, &message, 1);
        if (message == 0xFFFFFFFF) {
            OSSendMessage((upper + 0x4440), (void*)0x2A, 1);
            do OSReceiveMessage(context->messageQueue, &message, 1);
            while (message != 0xFFFFFFFE);
            continue;
        }
        tag = message & 0xFFF;
        slot = (message >> 12) & 0xFF;
        bank = (message >> 20) & 1;
        command = message & 0xFFE00000;
        sprintf(name, strings + 0x10, lbl_8064DC80, tag);

        switch (command) {
        case 0x80000000: {
            u32 remaining, position, destination, amount, actual;
            int alternate;
            int opened;
            DVDChangeDir(&lbl_8064BA30);
            opened = DVDOpen(name, &file);
            DVDChangeDir(&lbl_8064BA38);
            if (opened == 0) break;
            remaining = file.length;
            alternate = 0;
            position = 0;
            destination = (u32)context->transfers[slot].queue;
            interrupts = OSDisableInterrupts();
            context->transfers[slot].tag = tag;
            context->transfers[slot].done = 0;
            context->transfers[slot].offset = 0;
            context->transfers[slot].address = remaining;
            OSRestoreInterrupts(interrupts);
            while (OSReceiveMessage(context->transferQueue, &reply, 0) != 0) {}
            OSSendMessage(context->transferQueue, 0, 1);
            while (remaining != 0) {
                actual = remaining < 0x10000 ? remaining : 0x10000;
                amount = (actual + 0x1F) & ~0x1F;
                while (DVDReadPrio(&file, lbl_805BB240 + (alternate << 16), amount, position, 2) == -1) {}
                OSReceiveMessage(context->transferQueue, &reply, 1);
                ARQPostRequest(&request, 1, 0, 0, lbl_805BB240 + (alternate << 16),
                            (void*)destination, amount, fn_8015A17C);
                alternate ^= 1;
                destination += actual;
                remaining -= actual;
                position += actual;
            }
            OSReceiveMessage(context->transferQueue, &reply, 1);
            DVDClose(&file);
            interrupts = OSDisableInterrupts();
            if (context->transfers[slot].tag == tag && context->transfers[slot].address != 0)
                context->transfers[slot].done = 1;
            OSRestoreInterrupts(interrupts);
            handled = 1;
            break;
        }
        case 0x40000000: {
            fn_8015B274((void*)context->transfers[slot].address, context->transfers[slot].queue, lbl_8064D170[bank],
                        0x2C4020, lbl_805BB240, 0x10000, (upper + 0x4460), 0);
            interrupts = OSDisableInterrupts();
            context->controls[bank][0x8142] = 1;
            context->controls[bank][0x8143] = 0;
            context->controls[bank][0x8144] = 0;
            OSRestoreInterrupts(interrupts);
            fn_80159088(bank);
            if (context->queues[bank] != 0) {
                OSSendMessage(context->queues[bank], 0, 1);
                context->queues[bank] = 0;
            }
            fn_80158E7C(4);
            break;
        }
        case 0x08000000: {
            Record* record;
            u32 base;
            int descriptorValue = (s16)lbl_80241DE8[context->stream.index].value;
            fn_80008014(descriptorValue, lbl_80241DE8[context->stream.index].kind);
            sprintf(streamName, strings + 0x1C, descriptorValue);
            record = fn_8015A314(tag);
            fn_8015D304(streamName, record);
            state->start = 0xDBCAA0;
            state->initial = state->start;
            base = fn_801332E0();
            fn_8015D4EC(&lbl_8064D140, 4, record);
            state->total = lbl_8064D140;
            lbl_8064D140 = (lbl_8064D140 + 0x1F) & ~0x1F;
            fn_8015D4EC((upper + 0x4480), base, record);
            fn_8015D4EC((upper + 0x4480) + base,
                        fn_801332E8((upper + 0x4480)) - base, record);
            fn_80131408((upper + 0x4480));
            state->loaded = fn_801332E8((upper + 0x4480));
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
            state->source = (upper + 0x4480);
            state->state = 2;
            if (state->loaded > 0x7380)
                fn_80155BB0(strings + 0x30, strings + 0x54, state->loaded, 0x7380);
            if (OSSendMessage(lbl_805E2600, 0, 0) == 0)
                fn_80155BB0(strings + 0x30, strings + 0x98);
            handled = 1;
            break;
        }
        case 0x10000000: {
            Record* record = fn_8015A314(tag);
            u32 amount, destination;
            if (!record->active) break;
            while (OSReceiveMessage(context->transferQueue, &message, 0) != 0) {}
            interrupts = OSDisableInterrupts();
            if (state->cursor >= state->end) {
                state->cursor = state->start;
                state->boundary += state->end - state->start;
            }
            OSRestoreInterrupts(interrupts);
            amount = fn_8015DF60();
            if (amount == 0) break;
            destination = state->cursor;
            fn_8015D4EC(dmaBuffer, amount, record);
            DCInvalidateRange(invalidateBuffer, amount);
            ARQPostRequest(lbl_805E2620, 3, 0, 0, dmaBuffer,
                        (void*)destination, amount, fn_8015A17C);
            OSReceiveMessage(context->transferQueue, &message, 1);
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
                OSSendMessage(*streamQueue, 0, 0);
            handled = 1;
            break;
        }
        case 0xFFE00000:
            break;
        }
        fn_8015C020(handled);
    }
}
