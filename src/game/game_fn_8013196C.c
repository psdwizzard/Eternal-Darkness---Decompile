typedef unsigned char u8;
typedef struct Runtime Runtime;
typedef struct Entry Entry;

struct Runtime {
    char pad_0[0x10];
    char* records;
};

struct Entry {
    char pad_0[0x10];
    void* resource;
    char pad_14[0x14];
};

typedef struct Selection {
    char pad_0[0x70];
    int* indices;
    char pad_74[8];
    u8 count;
} Selection;

extern char lbl_8030F540[];
extern Runtime* fn_8015E4A4(void);
extern Selection* fn_8015E1A8(int);
extern void fn_80124DBC(Entry*);
extern void fn_801568B8(void*, void*);
extern void fn_8002AC60(void);

void fn_8013196C(void)
{
    Runtime* runtime;
    int offset;
    int index;
    register Selection* selection;

    runtime = fn_8015E4A4();
    selection = 0;
    {
        int selected = *(int*)(lbl_8030F540 + 0x1C8) >> 1;
        if (selected >= 0) {
            selection = fn_8015E1A8(selected);
        }
    }
    if (selection != 0) {
        index = 0;
        offset = 0;
        while (index < selection->count) {
            int record = *(int*)((char*)selection->indices + offset) * 0x28;
            if (*(Entry**)(runtime->records + record) != 0) {
                fn_80124DBC(*(Entry**)(runtime->records + record));
                record = *(int*)((char*)selection->indices + offset) * 0x28;
                fn_801568B8(*(void**)(runtime->records + record + 0x10),
                            (void*)fn_8002AC60);
            }
            offset += 4;
            index++;
        }
    }
}
