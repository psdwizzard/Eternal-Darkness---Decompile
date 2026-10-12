typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct MeshGroup {
    u16 count;
    u16 first;
    u8 pad[0x110];
} MeshGroup;

typedef struct MeshIndex {
    u16 vertex;
    u16 pad;
} MeshIndex;

typedef struct MeshInfo {
    u8 pad0[0x28];
    MeshGroup* groups;
    u8 pad2C[0x14];
    MeshIndex* indices;
} MeshInfo;

typedef struct Entry {
    u32 a, b, c;
    int group;
} Entry;

extern u8 lbl_804EE5CC[];
extern int lbl_8064CEC8;
extern u32* lbl_8064CECC;
extern Entry* lbl_8064CED4;
extern int lbl_8064CED8;

extern u32 fn_80130A14(MeshInfo*, MeshIndex*, int, u8*, Entry*, int*, u32*, int);
extern u32 fn_80130EAC(MeshInfo*, MeshIndex*, int, u8*, Entry*, int*, u32*, int);

void fn_80123080(MeshInfo* info, int group, int arg2, int mode)
{
    MeshGroup* mesh = &info->groups[group];
    MeshIndex* indices = &info->indices[mesh->first];
    int count = mesh->count;
    int entries = 0;
    u8* flags = lbl_804EE5CC;
    Entry* entry = lbl_8064CED4;
    u32 size = 0;
    int i;

    switch (mode) {
    case 1:
        size = fn_80130A14(info, indices, count, flags, entry,
                         &entries, lbl_8064CECC, arg2);
        break;
    case 7:
        size = fn_80130EAC(info, indices, count, flags, entry,
                         &entries, lbl_8064CECC, arg2);
        break;
    }
    if (size != 0) {
        lbl_8064CEC8 -= size;
        lbl_8064CED8 -= entries;
        for (i = 0; i < entries; i++) {
            entry->group = group;
            entry++;
        }
        lbl_8064CED4 += entries;
        lbl_8064CECC = (u32*)((u8*)lbl_8064CECC + size);
    }
}
