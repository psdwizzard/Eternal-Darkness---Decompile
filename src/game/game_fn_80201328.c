typedef void (*Callback)(void);

typedef struct CallbackEntry {
    Callback callback;
    int index;
    unsigned int flags;
    unsigned int unused;
} CallbackEntry;

extern CallbackEntry lbl_80640448[];

void fn_80201328(Callback callback, int index, void *unused)
{
    lbl_80640448[index].callback = callback;
    lbl_80640448[index].index = index;
    lbl_80640448[index].flags |= 1;
}
