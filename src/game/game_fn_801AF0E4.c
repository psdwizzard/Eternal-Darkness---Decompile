typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry Entry;
struct Entry {
    u8 padding000[8];
    u8 first[0x3C];
    u8 second[0x3C];
    u8 padding080[0xF0];
    u8 state170[2];
    u8 state172[2];
    u8 padding174[0x10];
};

extern Entry lbl_8060B5E0[4];
extern void DVDClose(void*);

void fn_801AF0E4(u32 type, void* object)
{
    int which = -1;
    Entry* entry = lbl_8060B5E0;
    int i;

    for (i = 0; i < 4; i++, entry++) {
        if (entry->first == object) {
            which = 0;
        } else if (entry->second == object) {
            which = 1;
        }
        if (which != -1) {
            if (type != 0x60) {
                entry->state170[which] = 3;
                return;
            }
            entry->state170[which] = 0;
            entry->state172[which] = 0;
            break;
        }
    }
    DVDClose(object);
}
