typedef unsigned int u32;
typedef signed int s32;
typedef struct ARQRequest ARQRequest;
typedef void (*ARQCallback)(u32);
typedef void (*ARCallback)(void);

extern ARCallback fn_8021A96C(ARCallback callback);
extern void fn_8021B5FC(void);
extern ARQRequest* lbl_8064DB38;
extern ARQRequest* lbl_8064DB40;
extern ARQRequest* lbl_8064DB48;
extern ARQRequest* lbl_8064DB4C;
extern ARQCallback lbl_8064DB50;
extern ARQCallback lbl_8064DB54;
extern u32 lbl_8064DB58;
extern s32 lbl_8064DB5C;

/* Initialize the ARAM request queues and install the DMA completion handler. */
void fn_8021B6C8(void)
{
    if (lbl_8064DB5C == 1) {
        return;
    }

    lbl_8064DB40 = 0;
    lbl_8064DB38 = 0;
    lbl_8064DB58 = 0x1000;
    fn_8021A96C(fn_8021B5FC);
    lbl_8064DB48 = 0;
    lbl_8064DB4C = 0;
    lbl_8064DB50 = 0;
    lbl_8064DB54 = 0;
    lbl_8064DB5C = 1;
}
