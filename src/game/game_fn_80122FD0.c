typedef unsigned char u8;
typedef unsigned short u16;

typedef struct MeshIndex {
    u16 vertex;
    u16 pad;
} MeshIndex;

typedef struct MeshInfo {
    u8 pad[0x44];
    MeshIndex* indices;
} MeshInfo;

typedef struct MeshGroup {
    u8 pad;
    u8 count;
    u16 first;
} MeshGroup;

extern u8 lbl_804EE5CC[];
extern u16 lbl_805AAE40[];

void fn_80122FD0(MeshInfo* info, MeshGroup* groups, int count)
{
    u8* result;
    int i;
    u16* table;
    MeshIndex* index;
    MeshIndex* first;
    int j;
    int vertex_count;
    int a;
    int b;
    int c;

    result = lbl_804EE5CC;
    i = 0;
    table = lbl_805AAE40;
    while (i < count) {
        first = info->indices + groups->first;
        vertex_count = groups->count;
        *result = 0;
        index = first;
        for (j = 0; j < vertex_count - 2; j++) {
            a = table[index[0].vertex];
            b = table[index[1].vertex];
            c = table[index[2].vertex];

            if (a != b && b != c && a != c) {
                *result = 1;
                break;
            }
            index++;
        }
        result++;
        groups++;
        i++;
    }
}
