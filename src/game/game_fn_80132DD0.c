typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct TextDescriptor TextDescriptor;

typedef struct Cue {
    u8 text;
    u8 enabled;
    u8 variant;
    u8 language;
    u8 delay;
    u8 pad;
    u16 duration;
} Cue;

typedef struct Sequence {
    char pad0[0x64];
    Cue* cues;
    char pad68[0x18];
    u8 count;
} Sequence;

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
    s8 variant;
} Runtime;

typedef struct Manager {
    char pad0[4];
    u8 mode;
} Manager;

typedef struct Options {
    char pad0[0x10];
    u32 flags;
} Options;

extern Runtime lbl_8030F540;
extern Options lbl_803003C8;
extern void* lbl_8064C534;
extern void* fn_8015E4A4(void);
extern int fn_80054BC4(void);
extern TextDescriptor* fn_801E6CA0(void*, u32, u32, u32, int);
extern void fn_801E5FB0(void*);

void fn_80132DD0(Sequence* sequence, int time)
{
    Manager* manager = fn_8015E4A4();
    int language = fn_80054BC4();
    int i;
    int slot;

    if (lbl_8030F540.state == -1) {
        i = 0;
        while (i < sequence->count) {
            for (slot = 0; slot < 5; slot++) {
                if (!(lbl_8030F540.active_mask & (1 << slot))) {
                    if (lbl_8064C534 == 0) {
                        return;
                    }
                    if ((sequence->cues[i].enabled || (lbl_803003C8.flags & 1)) &&
                        (manager->mode == 10 ||
                         (u8)language == sequence->cues[i].language) &&
                        (!sequence->cues[i].variant ||
                         lbl_8030F540.variant == sequence->cues[i].variant)) {
                        if (manager->mode == 10 || sequence->cues[i].delay == 0) {
                            TextDescriptor* text = fn_801E6CA0(
                                lbl_8064C534, 0, sequence->cues[i].text,
                                0x10008, 1);
                            lbl_8030F540.slots[slot].end =
                                time + sequence->cues[i].duration;
                            lbl_8030F540.slots[slot].text = text;
                            lbl_8030F540.slots[slot].delay = -1;
                        } else {
                            lbl_8030F540.slots[slot].index = sequence->cues[i].text;
                            lbl_8030F540.slots[slot].end =
                                time + sequence->cues[i].duration * 2 +
                                sequence->cues[i].delay * 2;
                            lbl_8030F540.slots[slot].delay =
                                sequence->cues[i].delay * 2;
                        }
                        lbl_8030F540.active_mask |= 1 << slot;
                    }
                    break;
                }
            }
            i++;
        }
        i = 0;
        for (; i < 5; i++) {
            if ((lbl_8030F540.active_mask & (1 << i)) &&
                lbl_8030F540.slots[i].end <= time) {
                fn_801E5FB0(lbl_8030F540.slots[i].text);
                lbl_8030F540.slots[i].text = 0;
                lbl_8030F540.active_mask &= ~(1 << i);
            }
        }
    }
}
