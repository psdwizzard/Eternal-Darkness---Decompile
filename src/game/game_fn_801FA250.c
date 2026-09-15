typedef unsigned char u8;
typedef unsigned short u16;

typedef struct ResourceEntry {
    u8 pad00[0x34];
    void* resource;
    u8 pad38[0x40];
} ResourceEntry;

typedef struct ResourceState {
    u8 pad00[0xA2];
    u16 count;
    ResourceEntry* entries;
    u8 padA8[0x809A];
    signed char ready_a;
    signed char ready_b;
} ResourceState;

extern ResourceState* fn_8015C28C(int);
extern void fn_8011F950(void*);
extern ResourceEntry* fn_8011F9E4(void*, int);
extern int fn_8011FA40(void*);

int fn_801FA250(void* resource, int selector, void* resource_handle)
{
    void* target = resource;
    ResourceState* state;
    int result;

    result = -1;
    state = fn_8015C28C(selector);

    if (resource_handle != 0) {
        ResourceEntry* initial_entry;
        int count;

        fn_8011F950(resource_handle);
        initial_entry = fn_8011F9E4(resource_handle, 0);
        count = fn_8011FA40(resource_handle);
        {
            ResourceEntry* entry = initial_entry;
            int i;
            for (i = 0; i < count; entry++, i++) {
                if (target == entry->resource) {
                    result = i;
                    break;
                }
            }
        }
    } else if (state->ready_a != 0 && state->ready_b != 0) {
        ResourceEntry* entry = state->entries;
        int i;

        for (i = 0; i < state->count; entry++, i++) {
            if (target == entry->resource) {
                result = i;
                break;
            }
        }
    }
    return result;
}
