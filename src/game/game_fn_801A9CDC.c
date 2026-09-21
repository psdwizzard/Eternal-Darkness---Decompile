typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

typedef struct Entry {
    u8 value;
    s8 delta;
    u8 target;
    u8 timer;
    u16 state;
    u8 pad[2];
} Entry;

extern Entry lbl_80607CB0[4];
extern int fn_801A9B38(void);
extern void fn_801AD8B4(void);

void fn_801A9CDC(void)
{
    int previous = fn_801A9B38();
    int value;
    int old_distance;
    int target;
    int minimum = 100;
    int next;
    int new_distance;
    int count;

    for (count = 0; count < 4; count++) {
        Entry* entry = &lbl_80607CB0[count];
        if (entry->delta != 0) {
            value = entry->value;
            next = value + entry->delta;
            if (next <= 0) {
                entry->value = 0;
                entry->delta = 0;
            } else if (next >= 100) {
                entry->value = 100;
                entry->delta = 0;
            } else {
                target = entry->target;
                if (next != target) {
                    old_distance = target - value;
                    if (old_distance < 0) {
                        old_distance = -old_distance;
                    }
                    new_distance = target - next;
                    if (new_distance < 0) {
                        new_distance = -new_distance;
                    }
                    if (new_distance < old_distance) {
                        goto store_next;
                    }
                }
                entry->value = target;
                entry->delta = 0;
                goto updated;
store_next:
                entry->value = (u8)next;
            }
        }
updated:
        if (entry->value < minimum) {
            minimum = entry->value;
        }
    }

    if (minimum != previous) {
        fn_801AD8B4();
    }
}
