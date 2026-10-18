typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;

typedef float Mtx[3][4];

typedef struct Vertex {
    s16 x, y, z;
} Vertex;

typedef struct Delta {
    u16 matrix;
    u16 flags;
    u16 index;
} Delta;

typedef struct Entry {
    u8 pad0[0xA];
    u16 base;
    u8 padC[4];
    u16 count;
    u16 start;
    u8 pad14[0x100];
} Entry;

typedef struct Table {
    u8 pad0[0xC];
    u16 count;
    u8 padE[0x10];
    u16 vertex_count;
    u8 pad20[8];
    Entry* entries;
    u8 pad2C[4];
    Delta* deltas;
    u8 pad34[0x7C];
    u16* normals;
} Table;

typedef struct EntryFlags {
    u16 flags;
    u8 pad2[6];
} EntryFlags;

typedef struct Owner {
    u8 pad0[0x180];
    EntryFlags entries[1];
} Owner;

typedef struct TransferState {
    void* source;
    void* destination;
    u16 count;
    u16 pad;
    u32 remaining;
    u32 transferred;
    u8 pad14[8];
} TransferState;

extern void* volatile lbl_8064CEFC;
extern s32 lbl_804FA6D0[];
extern Vertex lbl_804FA740[];

extern s32 fn_801231C0(Table* table);
extern void fn_801252D8(s32 value);
extern void fn_8012214C(Table* table, s32 count, s32 mode, TransferState* state);
extern int fn_80121EC0(TransferState* state, void* buffer);
extern void fn_80125104(Mtx mtx, Vertex* src, Vertex* dst, u32 flags, u16* normal);
extern void PSMTXReorder(void* src, void* dst);
extern void PSMTXInvXpose(Mtx a, Mtx b);

void fn_80125300(Owner* owner, Table* table, Vertex* first, Vertex* second,
                 Vertex* first_buffer, Vertex* second_buffer, Mtx* matrices,
                 s32 first_count, s32 triple)
{
    TransferState first_state;
    TransferState second_state;
    Mtx matrix;
    Mtx transformed;
    s32 i;
    s32 entry_count;
    s32 vertex_count;
    u32 shift;
    s32 limit;
    Mtx* m;
    u16* normals;
    u8* first_work;
    u8* second_work;
    s32 mode;
    s32 is_triple = triple;
    s32 j;
    Entry* entry;
    Delta* delta;
    u16 base;
    Vertex* source;
    u16 flag;

    vertex_count = table->vertex_count;
    limit = vertex_count;
    entry_count = table->count;
    if (first_count < vertex_count) {
        limit = first_count;
    }

    mode = fn_801231C0(table);
    first_work = lbl_8064CEFC;
    second_work = first_work + 0x1000;
    shift = (limit * 6) << 16;
    fn_801252D8(mode);

    first_state.count = 0;
    second_state.count = 0;
    fn_8012214C(table, first_count, is_triple ? 1 : 7, &first_state);
    fn_8012214C(table, 0, 7, &second_state);
    if (first_state.count != 0) {
        fn_80121EC0(&first_state, first_work);
    }
    if (second_state.count != 0) {
        fn_80121EC0(&second_state, second_work);
    }

    normals = table->normals;
    for (i = 0; i < entry_count; i++) {
        entry = &table->entries[i];
        flag = owner->entries[i].flags;
        base = entry->base;
        delta = &table->deltas[entry->start];

        if (flag & 1) {
            owner->entries[i].flags = flag | 4;
            if (lbl_804FA6D0[i] != 0) {
                source = lbl_804FA740;
            } else {
                source = first;
            }

            for (j = 0; j < entry->count; delta++, j++) {
                u32 vflags;
                s32 index;

                m = &matrices[delta->matrix];
                vflags = delta->flags;
                index = delta->index + base;

                PSMTXReorder(*m, matrix);
                fn_80125104(matrix, source + index, first_buffer, vflags | shift, normals + index);
                PSMTXInvXpose(*m, matrix);
                PSMTXReorder(matrix, transformed);
                fn_80125104(transformed, second + index, second_buffer, vflags | shift, normals + index);
                if (first_state.count != 0) {
                    fn_80121EC0(&first_state, first_work);
                }
                if (second_state.count != 0) {
                    fn_80121EC0(&second_state, second_work);
                }
                if (is_triple) {
                    fn_80125104(transformed, second + (index + vertex_count), second_buffer + first_count, vflags | shift, normals + index);
                    fn_80125104(transformed, second + (index + vertex_count * 2), second_buffer + (first_count << 1), vflags | shift, normals + index);
                }
            }
        } else {
            owner->entries[i].flags = flag & ~4;
        }
    }

    if (first_state.count != 0) {
        while (fn_80121EC0(&first_state, first_work) == 0) {
        }
    }
    if (second_state.count != 0) {
        while (fn_80121EC0(&second_state, second_work) == 0) {
        }
    }
}
