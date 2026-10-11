typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Object {
    char pad0[0x250];
    int room;
} Object;

typedef struct Manager {
    char pad0[5];
    u8 count;
    char pad6[10];
    char* entries;
    char pad14[0x20];
    int time;
} Manager;

typedef struct Selection {
    char pad0[0x78];
    u16 room;
    u16 resource;
} Selection;

typedef struct Descriptor {
    char pad0[0x24];
    short resource;
    char pad26[2];
} Descriptor;

typedef struct Context {
    char pad0[0x1C8];
    u32 flags;
    char pad1CC[6];
    short resource;
    char pad1D4[6];
    u8 index;
    char pad1DB;
    s8 mode;
} Context;

typedef struct Request {
    int unused;
    int source;
    int room;
    int effect;
    u32 flags;
} Request;

extern Context lbl_8030F540;
extern Descriptor lbl_80241DE8[];
extern Request lbl_805AD550;
extern int lbl_8064CF68;
extern int lbl_8064C600;
extern void fn_8015C7D8(int);
extern void fn_80159630(Request*);
extern void fn_8015C948(int, int, int, int, int, int, int, int, int, int, int);
extern void fn_801AC350(s8, int, int);
extern void fn_80131A28(int);

void fn_80133D00(Manager* manager, Selection* selection, int time)
{
    int resource = lbl_80241DE8[lbl_8030F540.index].resource;

    if (manager->time - time == 100 && !(lbl_8030F540.flags & 1)) {
        if (lbl_8030F540.mode == 0 && resource != -1) {
            fn_8015C7D8(resource);
        } else if (lbl_8030F540.mode != 0) {
            fn_8015C7D8(lbl_8030F540.resource);
        }
    }
    if (selection->resource != 0 && !(lbl_8030F540.flags & 1)) {
        fn_8015C7D8(selection->resource);
    } else if (selection->room != 0 && !(lbl_8030F540.flags & 1)) {
        int offset;
        int i;

        lbl_8064CF68 = 1;
        lbl_8064C600 = 3;
        lbl_805AD550.unused = selection->room;
        lbl_805AD550.source = -2;
        lbl_805AD550.room = 0;
        lbl_805AD550.effect = 0;
        lbl_805AD550.flags = 0x44;
        fn_8015C948(selection->room, 0, 0, 0, 0x20, 1, 1, 0x11,
                   (int)fn_80159630, (int)&lbl_805AD550, 1);
        fn_801AC350(0, 1, 0);
        fn_80131A28(selection->room);
        i = 0;
        offset = 0;
        while (i < manager->count) {
            Object* object = *(Object**)(manager->entries + offset);
            if (object != 0) {
                object->room = selection->room;
            }
            offset += 0x28;
            i++;
        }
    }
}
