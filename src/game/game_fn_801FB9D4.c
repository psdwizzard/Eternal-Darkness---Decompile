typedef unsigned char ObjectSlot[0x88];

extern ObjectSlot lbl_8063C6B8[];
extern ObjectSlot lbl_8063CD18[];

int fn_801FB9D4(void* object, int alternate)
{
    ObjectSlot* slots;
    int i;

    if (alternate != 0) {
        slots = lbl_8063C6B8;
    } else {
        slots = lbl_8063CD18;
    }
    for (i = 0; i < 12; i++) {
        if (slots == object) {
            return i;
        }
        slots++;
    }
    return -1;
}
