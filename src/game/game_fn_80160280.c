typedef struct Entry {
    int type;
    char pad4[4];
    void* child;
    char padC[4];
} Entry;

typedef struct List {
    char pad0[4];
    Entry* entries;
} List;

typedef struct Link2 { void* root; } Link2;
typedef struct Link1 { Link2* link; } Link1;
typedef struct Root {
    char pad0[8];
    char** items;
} Root;

extern Entry* aux_stackedfunction(List*, int, Entry*);
extern int isLmark(Entry*);
extern int currentpc(Entry*);
extern unsigned int luaG_symbexec(Root*, int, int);
extern char* luaF_getlocalname(Root*, int, int);
extern char lbl_8064BA40;
extern char lbl_8064BA48;
extern char lbl_8064BA50;

char* getobjname(List* list, Entry* position, char** output)
{
    Entry* entry = aux_stackedfunction(list, 0, position);
    Root* root;
    int ordinal;
    unsigned int token;

    if (!isLmark(entry))
        return 0;

    root = (Root*)((Link1*)entry->child)->link->root;
    ordinal = currentpc(entry);
    token = luaG_symbexec(root, ordinal, (position - (entry + 1)));

    switch (token & 0x3f) {
    case 12:
        *output = *(char**)((char*)root->items +
                           ((token >> 4) & 0x0ffffffc)) + 0x14;
        return &lbl_8064BA40;
    case 11:
        *output = luaF_getlocalname(root, (token >> 6) + 1, ordinal);
        return &lbl_8064BA48;
    case 14:
    case 16:
        *output = *(char**)((char*)root->items +
                           ((token >> 4) & 0x0ffffffc)) + 0x14;
        return &lbl_8064BA50;
    default:
        return 0;
    }
}
