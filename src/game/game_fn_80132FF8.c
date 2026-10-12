typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct TextDescriptor TextDescriptor;

typedef struct TextSlot {
    TextDescriptor* text;
    int end;
    int delay;
    int index;
} TextSlot;

typedef struct Runtime {
    TextSlot slots[5];
    char pad50[0x188];
    s8 state;
    char pad1D9[6];
    s8 active_mask;
} Runtime;

extern Runtime lbl_8030F540;
extern void* lbl_8064C534;
extern TextDescriptor* fn_801E6CA0(void*, u32, u32, u32, int);
extern void fn_801E5FB0(void*);

void fn_80132FF8(int time)
{
    int i;

    if (lbl_8030F540.state == -1) {
        for (i = 0; i < 5; i++) {
            if (lbl_8030F540.active_mask & (1 << i)) {
                if (lbl_8030F540.slots[i].delay != -1) {
                    lbl_8030F540.slots[i].delay--;
                    if (lbl_8030F540.slots[i].delay == 0) {
                        lbl_8030F540.slots[i].delay = -1;
                        lbl_8030F540.slots[i].text = fn_801E6CA0(lbl_8064C534, 0,
                            (u16)lbl_8030F540.slots[i].index, 0x10008, 1);
                    }
                }
            }
        }
        for (i = 0; i < 5; i++) {
            if ((lbl_8030F540.active_mask & (1 << i)) && lbl_8030F540.slots[i].end <= time) {
                fn_801E5FB0(lbl_8030F540.slots[i].text);
                lbl_8030F540.slots[i].text = 0;
                lbl_8030F540.active_mask &= ~(1 << i);
            }
        }
    }
}
