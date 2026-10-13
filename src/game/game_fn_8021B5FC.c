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

extern void fn_8021A9B0(u32 type, u32 mainMemory, u32 aram, u32 length);
extern void fn_8021B4F8(void);
extern ARQRequest* lbl_8064DB38;
extern ARQRequest* lbl_8064DB48;
extern ARQRequest* lbl_8064DB4C;
extern ARQCallback lbl_8064DB50;
extern ARQCallback lbl_8064DB54;

/* ARQ DMA-complete interrupt: run the finished request's callback, then
 * start the next high-priority request or resume the low-priority chunks. */
void fn_8021B5FC(void)
{
    if (lbl_8064DB50 != 0) {
        lbl_8064DB50((u32)lbl_8064DB48);
        lbl_8064DB48 = 0;
        lbl_8064DB50 = 0;
    } else if (lbl_8064DB54 != 0) {
        lbl_8064DB54((u32)lbl_8064DB4C);
        lbl_8064DB4C = 0;
        lbl_8064DB54 = 0;
    }

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
