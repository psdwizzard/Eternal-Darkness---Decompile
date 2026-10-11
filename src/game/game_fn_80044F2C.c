typedef struct SpawnList {
    unsigned char pad[0x1C];
    int count;
} SpawnList;

extern SpawnList *lbl_8064D0BC;
extern void fn_80044D50(int index, int mask);

void fn_80044F2C(int mask)
{
    int index;

    for (index = 0; index < lbl_8064D0BC->count; index++) {
        fn_80044D50(index, mask);
    }
}
