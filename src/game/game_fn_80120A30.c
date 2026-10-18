typedef struct QueueEntry {
    void* first;
    void* second;
    void* third;
    float distance_squared;
} QueueEntry;

extern unsigned lbl_8064CEE4;
extern QueueEntry lbl_804ED180[];
extern unsigned char lbl_8063D378[];
extern void PSVECSubtract();

void fn_80120A30(void* first, void* second, void* third)
{
    float position[3];
    unsigned index;

    PSVECSubtract(first, lbl_8063D378, position);
    index = lbl_8064CEE4++;
    lbl_804ED180[index].first = first;
    lbl_804ED180[index].second = second;
    lbl_804ED180[index].third = third;
    lbl_804ED180[index].distance_squared = position[0] * position[0] +
                                           position[1] * position[1] +
                                           position[2] * position[2];
}
