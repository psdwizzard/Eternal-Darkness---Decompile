typedef unsigned char ObjectSlot[0x88];

extern ObjectSlot lbl_8063C6B8[];
extern ObjectSlot lbl_8063CD18[];

void* fn_801FBA94(int index, int alternate)
{
    ObjectSlot* slots;

    if (index < 12) {
        if (alternate != 0) {
            slots = lbl_8063C6B8;
        } else {
            slots = lbl_8063CD18;
        }
        return slots[index];
    }
    return 0;
}
