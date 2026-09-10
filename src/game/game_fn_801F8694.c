typedef struct Entry {
    unsigned char pad0[8];
    unsigned int first;
    unsigned int second;
    unsigned char pad10[4];
} Entry;

extern int lbl_8064D7BC;
extern Entry lbl_8063D488[];

int fn_801F8694(int value, int use_first)
{
    int index = 0;

    while (index < lbl_8064D7BC) {
        Entry* entry = &lbl_8063D488[index];
        if (use_first != 0) {
            if (entry->first == value) {
                return index;
            }
        } else if (entry->second == value) {
            return index;
        }
        index++;
    }
    return -1;
}
