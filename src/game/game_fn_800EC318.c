typedef struct State {
    unsigned char pad[0x48];
    unsigned int flags;
} State;

typedef struct Entry {
    unsigned char pad[0x20];
    int value;
} Entry;

extern unsigned char lbl_8024A59C[];
extern Entry lbl_8024A368[];
extern void fn_800F9D4C(void *, const char *, ...);
extern void fn_800FD39C(void *, Entry *);

int fn_800EC318(int value, State *state, void *output)
{
    Entry *entry;
    int i;
    int count = 0;
    int result = 3;

    fn_800F9D4C(output, (const char *)lbl_8024A59C + 0x28, value, state);
    for (i = 0; i < 13; i++) {
        entry = &lbl_8024A368[i];
        if (state->flags & (1 << i)) {
            fn_800FD39C(output, entry);
            result = entry->value;
            count++;
        }
    }
    if (count > 1) {
        result = 3;
    }
    return result;
}
