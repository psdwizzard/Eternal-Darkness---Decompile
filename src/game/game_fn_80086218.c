typedef unsigned char u8;
typedef signed char s8;

typedef struct Slot {
    void* object;
    u8 pad[4];
} Slot;

typedef struct EndingState {
    u8 pad[0x448];
    Slot slots[4];
    u8 pad2[0x1C8];
    s8 selected;
    s8 disabled;
} EndingState;

extern EndingState lbl_8031CD84;
extern int lbl_8064C8F0;
extern int lbl_8064D18C;
extern int lbl_8064D5A8;

extern unsigned int rand(void);
#define rand() ((int)rand())
extern void fn_8012C478(void*, int, int);

void fn_80086218(void)
{
    int i;

    if (lbl_8031CD84.disabled == 0) {
        if (lbl_8064D5A8 % 60 == 0) {
            lbl_8031CD84.selected = rand() % 4;
            lbl_8064C8F0 = lbl_8031CD84.selected;
            if (lbl_8064D18C == 83) {
                for (i = 0; i < 4; i++) {
                    if (lbl_8031CD84.slots[i].object != 0) {
                        fn_8012C478(lbl_8031CD84.slots[i].object, 15,
                                    i == lbl_8064C8F0);
                    }
                }
            }
        }
    }
}
