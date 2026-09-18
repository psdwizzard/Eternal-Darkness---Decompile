typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ResourceSource { u32 offset; u32 unknown4; u16 id; u8 padA[6]; } ResourceSource;
typedef struct ResourceHeader { u8 pad0[12]; int parent; int count; ResourceSource* items; } ResourceHeader;
typedef struct ResourceItem { u32 id; void* object; u32 pad8; void* data; } ResourceItem;
typedef struct ResourceSlot {
    u8 pad0[0x26]; char name[0x1E]; int count; ResourceItem* allocation;
    u8 clear[0x2A8]; u8 active; u8 pad2F5[3];
} ResourceSlot;
typedef struct FileInfo { u8 bytes[0x38]; } FileInfo;

extern ResourceSlot* lbl_8064CFF8;
extern char lbl_8024EF08[];
extern int fn_800467E8(void);
extern void* memset(void*, int, u32);
extern void* fn_8015D424(int*, void*);
extern void fn_8015D44C(void);
extern int fn_800F9D4C(char*, const char*, ...);
extern u32 fn_8015D6D0(void*, void*, int);
extern int fn_80213394(void*, FileInfo*);
extern void fn_8021345C(FileInfo*);
extern int fn_801382B4(int, ResourceHeader*, int*);
extern void* fn_80138A6C(int, int);
extern void* fn_80139B1C(ResourceHeader*, u32, ResourceSource*, int, FileInfo*, void*);
extern void fn_8012B408(void*, void*);
extern void fn_80138624(int, int);

/* NonMatching: complete mapped-resource load, object construction, data
 * layout, cleanup, and parent propagation paths. */
void fn_801383B4(int slot_index, int mode)
{
    ResourceSlot* slot = &lbl_8064CFF8[slot_index];
    ResourceHeader* header;
    ResourceSource* source;
    ResourceItem* dest;
    FileInfo file;
    int scratch_size;
    int data_offset;
    u32 read_size;
    int data_index;
    int count;
    int parent;
    int i;
    void* scratch;
    void* source_data;
    u8* data;

    if (slot_index <= -1) fn_800467E8();
    if (slot->allocation != 0) return;

    parent = -1;
    scratch = fn_8015D424(&scratch_size, (void*)1);
    source_data = (u8*)scratch + 0x8000;
    fn_800F9D4C(slot->name, lbl_8024EF08, slot_index);
    read_size = fn_8015D6D0(slot->name, scratch, 0x8000);
    fn_80213394(slot->name, &file);
    header = (ResourceHeader*)scratch;
    if (read_size == 0x20) {
        parent = header->parent;
    } else if (read_size != 0) {
        count = header->count;
        data_offset = 0;
        data_index = 0;
        header->items = (ResourceSource*)((u8*)header + (u32)header->items);
        slot->allocation = fn_80138A6C(fn_801382B4(count, header, &data_offset), mode);
        data = (u8*)slot->allocation + data_offset;
        slot->count = count;
        slot->active = (u8)mode;
        memset(slot->clear, 0, sizeof(slot->clear));
        dest = slot->allocation;
        source = header->items;
        for (i = 0; i < count; i++, source++, dest++) {
            dest->id = source->id;
            dest->object = fn_80139B1C(header, dest->id, source, mode, &file, source_data);
            dest->data = data + data_index * 16;
            data_index += *(u16*)((u8*)dest->object + 0x14);
            fn_8012B408(dest->object, dest->data);
        }
    }
    fn_8021345C(&file);
    fn_8015D44C();
    if (parent != -1) {
        fn_801383B4(parent, mode);
        fn_80138624(parent, slot_index);
    }
}
