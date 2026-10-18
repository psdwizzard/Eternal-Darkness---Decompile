typedef unsigned short u16;

typedef struct ResourceEntry8 {
    u16 id;
    u16 count;
    void* value;
} ResourceEntry8;

extern ResourceEntry8 dataFXGroups[];
extern u16 dataFXGroupNum;
extern void hwDisableIrq(void);
extern void hwEnableIrq(void);

int dataRemoveFX(u16 id)
{
    int index;

    index = 0;
    while (index < dataFXGroupNum && dataFXGroups[index].id != id) {
        index++;
    }

    if (index != dataFXGroupNum) {
        int move_index;

        hwDisableIrq();
        for (move_index = index + 1; move_index < dataFXGroupNum; move_index++) {
            dataFXGroups[move_index - 1] = dataFXGroups[move_index];
        }
        dataFXGroupNum--;
        hwEnableIrq();
        return 1;
    }
    return 0;
}
