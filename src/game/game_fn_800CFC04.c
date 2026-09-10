typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct Entry {
    s16 id;
    u16 value2;
    u16 value4;
    u16 value6;
} Entry;

extern Entry lbl_805FAA60[10];
extern u8 lbl_80300368[];

extern void *memcpy(void *, const void *, unsigned long);
extern void *memset(void *, int, unsigned long);
extern void fn_8011E918(void *);

void fn_800CFC04(void *state, Entry *entries, void *stream)
{
    int i;

    memcpy(state, lbl_80300368, 0x44);
    memset(lbl_80300368, 0, 0x44);
    for (i = 0; i < 10; i++) {
        if (lbl_805FAA60[i].value6 == 0 && lbl_805FAA60[i].value4 == 0) {
            memcpy(&entries[i], &lbl_805FAA60[i], sizeof(Entry));
            memset(&lbl_805FAA60[i], 0, sizeof(Entry));
        }
    }
    fn_8011E918(stream);
}
