typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct MessageEntry {
    u32 value;
    u32 state;
    int field_08;
    u8 kind;
    char text[35];
    u32 flags;
    u32 field_34;
    u64 time;
    u16 field_40;
    u16 pad_42;
    u32 user_data;
} MessageEntry;

typedef struct MessageQueue {
    u16 write_index;
    u16 read_index;
    u32 pad;
    MessageEntry entries[6];
} MessageQueue;

extern MessageQueue lbl_8064A7C8;
extern char* fn_800FD40C(char*, const char*);
extern u64 OSGetTime(void);

int fn_8017BBD0(u32 value, u8 kind, const char* text, u32 flags, u32 user_data)
{
    u16 index = lbl_8064A7C8.write_index;
    u16 next = index + 1;
    int difference = next - 6;
    MessageEntry* entry;

    next = difference < 0 ? next : 0;
    if (next != lbl_8064A7C8.read_index) {
        entry = &lbl_8064A7C8.entries[index];
        entry->value = value;
        entry->field_08 = -1;
        entry->kind = kind;
        if (text != 0) {
            fn_800FD40C(entry->text, text);
        }
        entry->flags = flags;
        entry->field_40 = 0;
        entry->time = OSGetTime();
        entry->user_data = user_data;
        if (entry->flags & 1) {
            entry->state = 3;
        } else {
            entry->state = 0;
        }
        lbl_8064A7C8.write_index = next;
        return 1;
    }
    return 0;
}
