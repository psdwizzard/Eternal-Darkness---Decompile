typedef unsigned int u32;
typedef signed int s32;
typedef void (*ARQCallback)(u32);

typedef struct ARQRequest ARQRequest;
struct ARQRequest {
    ARQRequest* next;
    u32 owner;
    u32 type;
    u32 priority;
    u32 source;
    u32 destination;
    u32 length;
    ARQCallback callback;
};

extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32 enable);
extern void fn_8021A9B0(u32 type, u32 mainMemory, u32 aram, u32 length);
extern void fn_8021B4F8(void);
extern void fn_8021B5F8(u32 request);
extern ARQRequest* lbl_8064DB38;
extern ARQRequest* lbl_8064DB3C;
extern ARQRequest* lbl_8064DB40;
extern ARQRequest* lbl_8064DB44;
extern ARQRequest* lbl_8064DB48;
extern ARQRequest* lbl_8064DB4C;
extern ARQCallback lbl_8064DB50;

/* Post an ARAM DMA request to the queue for its priority. */
void fn_8021B730(ARQRequest* request, u32 owner, u32 type, s32 priority,
                 u32 source, u32 destination, u32 length, ARQCallback callback)
{
    s32 enabled;

    request->next = 0;
    request->owner = owner;
    request->type = type;
    request->source = source;
    request->destination = destination;
    request->length = length;
    if (callback != 0) {
        request->callback = callback;
    } else {
        request->callback = fn_8021B5F8;
    }

    enabled = OSDisableInterrupts();
    switch (priority) {
    case 0:
        if (lbl_8064DB40 != 0) {
            lbl_8064DB44->next = request;
        } else {
            lbl_8064DB40 = request;
        }
        lbl_8064DB44 = request;
        break;
    case 1:
        if (lbl_8064DB38 != 0) {
            lbl_8064DB3C->next = request;
        } else {
            lbl_8064DB38 = request;
        }
        lbl_8064DB3C = request;
        break;
    }

    if (lbl_8064DB48 == 0 && lbl_8064DB4C == 0) {
        if (lbl_8064DB38 != 0) {
            if (lbl_8064DB38->type == 0) {
                fn_8021A9B0(lbl_8064DB38->type, lbl_8064DB38->source,
                            lbl_8064DB38->destination, lbl_8064DB38->length);
            } else {
                fn_8021A9B0(lbl_8064DB38->type, lbl_8064DB38->destination,
                            lbl_8064DB38->source, lbl_8064DB38->length);
            }
            lbl_8064DB50 = lbl_8064DB38->callback;
            lbl_8064DB48 = lbl_8064DB38;
            lbl_8064DB38 = lbl_8064DB38->next;
        }
        if (lbl_8064DB48 == 0) {
            fn_8021B4F8();
        }
    }
    OSRestoreInterrupts(enabled);
}
