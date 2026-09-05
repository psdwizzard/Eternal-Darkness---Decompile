typedef unsigned char u8;
typedef unsigned int u32;

typedef struct EffectNode {
    struct EffectNode* next;
    int state;
    u8 data[0x16];
    u8 flushed;
    u8 queued;
} EffectNode;

extern u32 lbl_8064D2FC;
extern int lbl_8064C2D0;
extern EffectNode* lbl_8064D304;
extern u8 lbl_805E2A5C[];
extern void fn_801B2428(int);
extern void fn_801ACFB0(void);
extern void fn_8020D250(void*, int, int);
extern void DCFlushRange(void*, u32);

void fn_801ACFE8(u32 event)
{
    EffectNode* node;
    switch (event) {
    case 1:
    case 2:
    case 4:
    case 8:
        break;
    case 16:
        if (lbl_8064D2FC == 0) {
            fn_801B2428(lbl_8064C2D0);
            fn_801ACFB0();
        }
        break;
    case 32:
        node = lbl_8064D304;
        if (node != 0 && node->state == 7) {
            if (node->queued != 0) {
                fn_8020D250(lbl_805E2A5C, 1, 1);
            } else {
                node->flushed = 1;
                DCFlushRange(node, 0x20);
            }
        }
        break;
    }
}
