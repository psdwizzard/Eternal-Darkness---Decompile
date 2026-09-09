typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    u16 type;
    u16 field_2;
    u16 field_4;
    u16 field_6;
    void* animation;
} Entry;

extern u32 fn_801E741C(void*);

#pragma use_lmw_stmw on

void fn_801F62D0(u32 key, u16 value, Entry* entries, u16 count)
{
    u16 limit;
    u16 selected;
    u16 i;
    u16 zero;
    Entry* current;

    if (entries != 0) {
        current = entries;
        limit = count;
        selected = value;
        i = 0;
        zero = 0;
        while (i < limit) {
            if (current->type == 1) {
                unsigned char* animation = current->animation;
                if (selected < *(u16*)(animation + 0x102)) {
                    if (fn_801E741C(animation + 2) == key) {
                        current->field_2 = zero;
                        current->field_4 = value;
                    }
                } else {
                    fn_801E741C(animation + 2);
                }
            }
            i++;
            current++;
        }
    }
}
