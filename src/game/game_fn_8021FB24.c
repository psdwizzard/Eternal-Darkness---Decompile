typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct SaveState {
    u8 pad00[0x10];
    u16 entry_count;
    u8 pad12[0x6e];
    u8 *workspace;
    u8 *entries;
    u16 *links;
} SaveState;

typedef struct SaveEntry {
    u8 kind;
    u8 pad01[0x35];
    u16 first_link;
    u16 link_count;
    u8 pad3a[6];
} SaveEntry;

extern s32 fn_8021D2BC(s32, SaveState **);
extern s32 fn_8021D374(SaveState *, s32);
extern s32 fn_8021F350(SaveState *);
extern s32 fn_8021F5D4(SaveState *, s32 *);
extern s32 fn_8021F814(SaveState *, s32 *);
extern s32 fn_8021F0DC(s32, void (*)(s32, s32));
extern s32 fn_8021EE90(s32, u16 *, void (*)(s32, s32));
extern void *memcpy(void *, const void *, u32);
extern void *memset(void *, s32, u32);
extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int);

s32 fn_8021FB24(s32 channel, u32 *size, void (*callback)(s32, s32))
{
    SaveState *state;
    u8 *entry_pages[2];
    u8 *link_pages[2];
    s32 page_indices[2];
    s32 result;
    u16 *counts;
    s32 link_changed;
    s32 entry_changed;
    s32 changes;
    u32 block_index;
    u16 link;
    u16 depth;
    u16 limit; /* Retains the original scratch slot in CodeWarrior. */
    u32 offset;
    u16 *count_cursor;
    u16 entry_limit;
    u16 i;
    u16 unused_count;
    int saved_interrupts;

    link_changed = 0;
    entry_changed = 0;
    changes = 0;
    if (size != 0)
        *size = 0;
    result = fn_8021D2BC(channel, &state);
    if (result < 0)
        return result;
    result = fn_8021F350(state);
    if (result < 0)
        return fn_8021D374(state, result);
    result = fn_8021F5D4(state, &page_indices[0]);
    result += fn_8021F814(state, &page_indices[1]);
    if (result > 1)
        return fn_8021D374(state, -6);

    entry_pages[0] = state->workspace + 0x2000;
    link_pages[0] = state->workspace + 0x6000;
    entry_pages[1] = state->workspace + 0x4000;
    link_pages[1] = state->workspace + 0x8000;
    switch (result) {
    case 1:
        if (state->entries == 0) {
            state->entries = entry_pages[page_indices[0]];
            memcpy(entry_pages[page_indices[0]], entry_pages[page_indices[0] ^ 1], 0x2000);
            entry_changed = 1;
        } else {
            state->links = (u16 *)link_pages[page_indices[1]];
            memcpy(link_pages[page_indices[1]], link_pages[page_indices[1] ^ 1], 0x2000);
            link_changed = 1;
        }
        break;
    case 0:
        break;
    default:
        break;
    }

    /* The inactive link page serves as a temporary reference count map. */
    counts = (u16 *)link_pages[page_indices[1] ^ 1];
    memset(counts, 0, 0x2000);
    for (block_index = 0; block_index < 0x7f; ++block_index) {
        SaveEntry *entry = (SaveEntry *)(state->entries + block_index * 0x40);
        if (entry->kind == 0xff)
            continue;
        link = entry->first_link;
        depth = 0;
        while (link != 0xffff && depth < entry->link_count) {
            if (link < 5 || link >= state->entry_count || ++counts[link] > 1)
                return fn_8021D374(state, -6);
            link = state->links[link];
            ++depth;
        }
        if (depth != entry->link_count || link != 0xffff)
            return fn_8021D374(state, -6);
    }

    count_cursor = counts + 5;
    unused_count = 0;
    i = 5;
    offset = 0xa;
    while (i < (entry_limit = state->entry_count)) {
        u16 old_link = *(u16 *)((u8 *)state->links + offset);
        if (*count_cursor == 0) {
            if (old_link != 0) {
                *(u16 *)((u8 *)state->links + offset) = 0;
                changes = 1;
            }
            ++unused_count;
        } else if ((old_link < 5 || old_link >= entry_limit) && old_link != 0xffff) {
            return fn_8021D374(state, -6);
        }
        offset += 2;
        ++count_cursor;
        ++i;
    }
    if (unused_count != state->links[3]) {
        state->links[3] = unused_count;
        changes = 1;
    }
    if (changes) {
        u16 *data;
        u16 *sum;
        u16 *complement;
        s32 n = 0x1ffc;
        sum = state->links;
        complement = sum + 1;
        data = sum + 2;
        n /= 2;
        *complement = 0;
        *sum = 0;
        for (; n > 0; --n) {
            *sum += *data;
            *complement += ~*data;
            ++data;
        }
        if (*sum == 0xffff)
            *sum = 0;
        if (*complement == 0xffff)
            *complement = 0;
    }
    memcpy(link_pages[page_indices[1] ^ 1], link_pages[page_indices[1]], 0x2000);
    if (entry_changed) {
        if (size != 0)
            *size = 0x2000;
        return fn_8021F0DC(channel, callback);
    }
    if (link_changed | changes) {
        if (size != 0)
            *size = 0x2000;
        return fn_8021EE90(channel, state->links, callback);
    }
    fn_8021D374(state, 0);
    if (callback != 0) {
        saved_interrupts = OSDisableInterrupts();
        callback(channel, 0);
        OSRestoreInterrupts(saved_interrupts);
    }
    return 0;
}
