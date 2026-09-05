typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    int state;
    u32 pad;
    void* object;
} Entry;

extern Entry lbl_80514AE0[];
extern Entry lbl_8056FA80[];
extern void fn_8011F7E0(void*, int);

void fn_80126084(void)
{
    int i;
    Entry* entry;

    for (i = 0; i < 20; i++) {
        entry = (Entry*)((u8*)lbl_80514AE0 + i * 0x48C8);
        if (entry->state == 1)
            fn_8011F7E0(entry->object, 0);
    }
    for (i = 0; i < 48; i++) {
        entry = (Entry*)((u8*)lbl_8056FA80 + i * 0x1238);
        if (entry->state == 1)
            fn_8011F7E0(entry->object, 0);
    }
}
