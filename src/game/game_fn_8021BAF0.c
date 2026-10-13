typedef signed short s16;
typedef signed int s32;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct OSContext {
    char data[0x2C8];
} OSContext;

typedef struct DSPTask DSPTask;
struct DSPTask {
    u32 state;
    u32 priority;
    u32 flags;
    u16 *iram;
    u32 iramLength;
    u32 iramAddress;
    u16 *dram;
    u32 dramLength;
    u32 dramAddress;
    u16 initVector;
    u16 resumeVector;
    void (*initCallback)(DSPTask *);
    void (*resumeCallback)(DSPTask *);
    void (*doneCallback)(DSPTask *);
    void (*requestCallback)(DSPTask *);
    DSPTask *next;
    DSPTask *prev;
};

extern void OSClearContext(OSContext *context);
extern void OSSetCurrentContext(OSContext *context);
extern u32 fn_8021B894(void);
extern u32 fn_8021B8A4(void);
extern u32 fn_8021B8B4(void);
extern void fn_8021B8CC(u32 mail);
extern void fn_8021BF14(DSPTask *outgoing, DSPTask *incoming);
extern void fn_8021C2E0(DSPTask *task);

extern s32 lbl_8064DB68;
extern DSPTask *lbl_8064DB6C;
extern DSPTask *lbl_8064DB74;
extern DSPTask *lbl_8064DB78;
extern DSPTask *lbl_8064DB7C;

volatile u16 DSPRegisters[] : 0xCC005000;

void fn_8021BAF0(s16 interrupt, OSContext *context)
{
    /* Preserve the interrupt handler's eight-byte stack scratch slot. */
    double contextPadding;
    OSContext exceptionContext;
    s32 mail;
    u16 status;

    status = DSPRegisters[5];
    DSPRegisters[5] = (status & ~0x28) | 0x80;
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);

    while (fn_8021B8A4() == 0) {
    }
    mail = fn_8021B8B4();
    if ((lbl_8064DB7C->flags & 2) && (mail == 0xDCD10002)) {
        mail = 0xDCD10003;
    }

    switch (mail) {
    case (s32)0xDCD10000:
        lbl_8064DB7C->state = 1;
        if (lbl_8064DB7C->initCallback != 0) {
            lbl_8064DB7C->initCallback(lbl_8064DB7C);
        }
        break;
    case (s32)0xDCD10001:
        lbl_8064DB7C->state = 1;
        if (lbl_8064DB7C->resumeCallback != 0) {
            lbl_8064DB7C->resumeCallback(lbl_8064DB7C);
        }
        break;
    case (s32)0xDCD10002:
        if (lbl_8064DB68 != 0) {
            if (lbl_8064DB7C == lbl_8064DB6C) {
                fn_8021B8CC(0xCDD10003);
                while (fn_8021B894() != 0) {
                }
                lbl_8064DB6C = 0;
                lbl_8064DB68 = 0;
                if (lbl_8064DB7C->resumeCallback != 0) {
                    lbl_8064DB7C->resumeCallback(lbl_8064DB7C);
                }
            } else {
                fn_8021B8CC(0xCDD10001);
                while (fn_8021B894() != 0) {
                }
                fn_8021BF14(lbl_8064DB7C, lbl_8064DB6C);
                lbl_8064DB7C->state = 2;
                lbl_8064DB7C = lbl_8064DB6C;
                lbl_8064DB68 = 0;
                lbl_8064DB6C = 0;
            }
        } else if (lbl_8064DB7C->next == 0) {
            if (lbl_8064DB7C == lbl_8064DB78) {
                fn_8021B8CC(0xCDD10003);
                while (fn_8021B894() != 0) {
                }
                if (lbl_8064DB7C->resumeCallback != 0) {
                    lbl_8064DB7C->resumeCallback(lbl_8064DB7C);
                }
            } else {
                fn_8021B8CC(0xCDD10001);
                while (fn_8021B894() != 0) {
                }
                fn_8021BF14(lbl_8064DB7C, lbl_8064DB78);
                lbl_8064DB7C->state = 2;
                lbl_8064DB7C = lbl_8064DB78;
            }
        } else {
            fn_8021B8CC(0xCDD10001);
            while (fn_8021B894() != 0) {
            }
            fn_8021BF14(lbl_8064DB7C, lbl_8064DB7C->next);
            lbl_8064DB7C->state = 2;
            lbl_8064DB7C = lbl_8064DB7C->next;
        }
        break;
    case (s32)0xDCD10003:
        if (lbl_8064DB68 != 0) {
            if (lbl_8064DB7C->doneCallback != 0) {
                lbl_8064DB7C->doneCallback(lbl_8064DB7C);
            }
            fn_8021B8CC(0xCDD10001);
            while (fn_8021B894() != 0) {
            }
            fn_8021BF14(0, lbl_8064DB6C);
            fn_8021C2E0(lbl_8064DB7C);
            lbl_8064DB7C = lbl_8064DB6C;
            lbl_8064DB68 = 0;
            lbl_8064DB6C = 0;
        } else if (lbl_8064DB7C->next == 0) {
            if (lbl_8064DB7C == lbl_8064DB78) {
                if (lbl_8064DB7C->doneCallback != 0) {
                    lbl_8064DB7C->doneCallback(lbl_8064DB7C);
                }
                fn_8021B8CC(0xCDD10002);
                while (fn_8021B894() != 0) {
                }
                lbl_8064DB7C->state = 3;
                fn_8021C2E0(lbl_8064DB7C);
            } else {
                if (lbl_8064DB7C->doneCallback != 0) {
                    lbl_8064DB7C->doneCallback(lbl_8064DB7C);
                }
                fn_8021B8CC(0xCDD10001);
                while (fn_8021B894() != 0) {
                }
                lbl_8064DB7C->state = 3;
                fn_8021BF14(0, lbl_8064DB78);
                lbl_8064DB7C = lbl_8064DB78;
                fn_8021C2E0(lbl_8064DB74);
            }
        } else {
            if (lbl_8064DB7C->doneCallback != 0) {
                lbl_8064DB7C->doneCallback(lbl_8064DB7C);
            }
            fn_8021B8CC(0xCDD10001);
            while (fn_8021B894() != 0) {
            }
            lbl_8064DB7C->state = 3;
            fn_8021BF14(0, lbl_8064DB7C->next);
            lbl_8064DB7C = lbl_8064DB7C->next;
            fn_8021C2E0(lbl_8064DB7C->prev);
        }
        break;
    case (s32)0xDCD10004:
        if (lbl_8064DB7C->requestCallback != 0) {
            lbl_8064DB7C->requestCallback(lbl_8064DB7C);
        }
        break;
    }

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}
