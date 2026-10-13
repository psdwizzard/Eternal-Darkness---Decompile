typedef struct StringEntry {
    unsigned char unknown[8];
    void (*destroy)(void *);
    char *text;
    unsigned char data[8];
} StringEntry;

extern int lbl_8064C3C8;
extern void *fn_8020AD80(int heap, unsigned long size);
extern void fn_8022C84C(StringEntry **entry);
extern unsigned long fn_8022C9BC(const char *text);

/* Allocate an entry and enough space for its null-terminated text. */
int fn_8022C720(StringEntry **entry, const char *text) {
    if (*entry != 0) {
        fn_8022C84C(entry);
    }

    *entry = fn_8020AD80(lbl_8064C3C8, sizeof(StringEntry));
    if (*entry == 0) {
        return 0;
    }

    (*entry)->text = fn_8020AD80(lbl_8064C3C8, fn_8022C9BC(text) + 1);
    if ((*entry)->text == 0) {
        return 0;
    }
    return 1;
}
