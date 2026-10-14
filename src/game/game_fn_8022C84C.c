typedef struct StringEntry {
    unsigned char unknown[8];
    void (*destroy)(void *);
    char *text;
    unsigned char data[8];
} StringEntry;

extern int lbl_8064C3C8;
extern void fn_8020AE7C(int heap, void *ptr);

/* Destroy the entry's payload and release its text and storage. */
void fn_8022C84C(StringEntry **entry)
{
    if (*entry != 0) {
        if ((*entry)->destroy != 0) {
            (*entry)->destroy((*entry)->data);
        }
        fn_8020AE7C(lbl_8064C3C8, (*entry)->text);
        fn_8020AE7C(lbl_8064C3C8, *entry);
        *entry = 0;
    }
}
