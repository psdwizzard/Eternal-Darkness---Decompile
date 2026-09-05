typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Resource {
    unsigned char pad[0x14];
    u16 count;
} Resource;

typedef struct Slot {
    int resource_id;
    unsigned char pad04[0x3C];
    unsigned char* start;
    Resource* resource;
    unsigned char* output;
    unsigned char state;
    unsigned char flag;
    unsigned char pad4E[2];
} Slot;

typedef struct State {
    int id;
    int arena_size;
    unsigned char pad08[0x2B0];
    Slot slots[2];
} State;

extern State lbl_805AE020;
extern char lbl_8024EF1C[];
extern char lbl_8024EF40[];

extern Resource* fn_80125664(void*, int);
extern void fn_8012B408(Resource*, void*);
extern void fn_80155BB0(char*, char*, ...);

void fn_80138FE4(int index, u32 end_address)
{
    lbl_805AE020.slots[index].resource = fn_80125664(lbl_805AE020.slots[index].start, 0);
    lbl_805AE020.slots[index].output = (unsigned char*)((end_address + 31) & ~31);
    fn_8012B408(lbl_805AE020.slots[index].resource, lbl_805AE020.slots[index].output);
    if (lbl_805AE020.slots[index].output + ((u32)lbl_805AE020.slots[index].resource->count << 4) >
        lbl_805AE020.slots[index].start + lbl_805AE020.arena_size) {
        fn_80155BB0(lbl_8024EF1C, lbl_8024EF40);
    }
    lbl_805AE020.slots[index].state = 2;
    lbl_805AE020.slots[index].flag = 0;
}
