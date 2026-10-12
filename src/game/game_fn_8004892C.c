typedef unsigned int u32;
typedef unsigned char u8;
typedef signed short s16;

typedef struct Slot {
    int type;
    int id;
    u8 reserved[0x18];
} Slot;

typedef struct SlotGroup {
    Slot slots[2];
    int reserved;
} SlotGroup;

typedef struct SlotState {
    u8 flags;
    u8 type;
    s16 reserved;
    s16 id;
    s16 padding;
    int value;
    int extra;
} SlotState;

extern u32 *lbl_8064C4E0;
extern SlotGroup lbl_803002E0[];
extern SlotState lbl_80300200[2][2];
extern int fn_801E79FC(u32 *set, u32 index);
extern void *memset(void *dest, int value, unsigned long size);

void fn_8004892C(s16 id)
{
    int i;
    int type;
    int group;
    int j;
    Slot *slots;

    group = fn_801E79FC(lbl_8064C4E0, 0x370) != 0;
    slots = lbl_803002E0[group].slots;

    for (i = 0; i < 2; i++) {
        if (id == slots[i].id) {
            type = 4;
            if (slots[i].type == 2) {
                type = 2;
            }
            for (j = 0; j < 2; j++) {
                if (type == lbl_80300200[j][group].type) {
                    memset(&lbl_80300200[j][group], 0, sizeof(SlotState));
                    lbl_80300200[j][group].type = 0xFF;
                    lbl_80300200[j][group].value = -1;
                    lbl_80300200[j][group].id = -1;
                    break;
                }
            }
            slots[i].type = 0;
            break;
        }
    }
}
