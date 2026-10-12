typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;

typedef struct Pair {
    u32 start;
    u32 count;
} Pair;

typedef struct Delta {
    s32 index;
    s16 x, y, z;
    u8 pad[2];
} Delta;

typedef struct Entry {
    u8 pad0[8];
    u16 count;
    u16 start;
    u8 padC[8];
    Pair pairs[32];
} Entry;

typedef struct Table {
    u8 pad0[12];
    u16 count;
    u8 padE[26];
    Entry* entries;
    u8 pad2C[8];
    u32 second_output;
    u8 pad38[24];
    u32 first_output;
    u8 pad54[136];
    Delta* deltas;
} Table;

typedef struct Weight {
    float value;
    u8 pad4[32];
    u32 flags;
} Weight;

typedef struct OwnerSlot {
    u16 flags;
    u8 pad2[6];
} OwnerSlot;

typedef struct Owner {
    u8 pad0[0x180];
    OwnerSlot slots[35];
    u8 pad298[4];
    Weight* weights;
    u8 pad2A0[0x24];
    s32 enabled;
} Owner;

typedef struct Vertex {
    s16 x, y, z;
} Vertex;

extern u32 lbl_804FA6D0[];
extern Vertex lbl_804FA740[];

#pragma opt_dead_assignments off
void fn_80124A40(Owner* owner, Table* table, u32* first_output,
                 u32* second_output)
{
    u32 begin;
    u32 delta_index;
    s32 entry_index;
    u32 delta_end;
    s32 weight_index;
    u32 vertex_index;
    Vertex* source_vertices;
    s32 count;
    Pair* pairs;
    Delta* deltas;
    u32 end;
    Weight* weight;
    Entry* entry;

    source_vertices = (Vertex*)table->first_output;
    deltas = table->deltas;
    count = table->count;

    *first_output = table->first_output;
    *second_output = table->second_output;

    for (entry_index = 0; entry_index < count; entry_index++) {
        lbl_804FA6D0[entry_index] = 0;
    }

    for (entry_index = 0; entry_index < count; entry_index++) {
        entry = &table->entries[entry_index];
        begin = entry->start;
        end = begin + entry->count;
        pairs = entry->pairs;

        if (owner->enabled != 0 &&
            (owner->slots[entry_index].flags & 1)) {
            for (vertex_index = begin; vertex_index < end; vertex_index++) {
                lbl_804FA740[vertex_index] =
                    source_vertices[vertex_index];
            }

            for (weight_index = 0; weight_index < 32; weight_index++) {
                weight = &owner->weights[weight_index];

                if ((weight->flags & 1) != 0 &&
                    (delta_index = pairs[weight_index].start) != 0xFFFFFFFF) {

                    Delta* delta = 0;
                    delta_end = delta_index + pairs[weight_index].count;
                    lbl_804FA6D0[entry_index] = 1;
                    for (; delta_index < delta_end; delta_index++) {
                        delta = &deltas[delta_index];
                        vertex_index = entry->start + delta->index;
                        lbl_804FA740[vertex_index].x += (s32)(weight->value * delta->x);
                        lbl_804FA740[vertex_index].y += (s32)(weight->value * delta->y);
                        lbl_804FA740[vertex_index].z += (s32)(weight->value * delta->z);
                    }
                }
            }
        }
    }
}
#pragma opt_dead_assignments reset
