typedef unsigned int u32;
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
extern ARQRequest* lbl_8064DB40;
extern ARQRequest* lbl_8064DB4C;
extern ARQCallback lbl_8064DB54;
extern u32 lbl_8064DB58;

/* Start the next chunk of the pending low-priority ARAM request. */
void fn_8021B4F8(void)
{
    if (lbl_8064DB4C == 0 && lbl_8064DB40 != 0) {
        lbl_8064DB4C = lbl_8064DB40;
        lbl_8064DB40 = lbl_8064DB40->next;
    }
    if (lbl_8064DB4C != 0) {
        if (lbl_8064DB4C->length <= lbl_8064DB58) {
            if (lbl_8064DB4C->type == 0) {
                fn_8021A9B0(lbl_8064DB4C->type, lbl_8064DB4C->source,
                            lbl_8064DB4C->destination, lbl_8064DB4C->length);
            } else {
                fn_8021A9B0(lbl_8064DB4C->type, lbl_8064DB4C->destination,
                            lbl_8064DB4C->source, lbl_8064DB4C->length);
            }
            lbl_8064DB54 = lbl_8064DB4C->callback;
        } else {
            if (lbl_8064DB4C->type == 0) {
                fn_8021A9B0(lbl_8064DB4C->type, lbl_8064DB4C->source,
                            lbl_8064DB4C->destination, lbl_8064DB58);
            } else {
                fn_8021A9B0(lbl_8064DB4C->type, lbl_8064DB4C->destination,
                            lbl_8064DB4C->source, lbl_8064DB58);
            }
        }
        lbl_8064DB4C->length -= lbl_8064DB58;
        lbl_8064DB4C->source += lbl_8064DB58;
        lbl_8064DB4C->destination += lbl_8064DB58;
    }
}
