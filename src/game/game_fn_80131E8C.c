typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct Color { u8 r, g, b, a; } Color;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct VertexData { char data[0xE]; s8 active; char pad_F; } VertexData;
typedef struct MeshRecord {
    Vec3 position; char pad_C[0x18]; u16 count; char pad_26[0x12E];
    Vec3* vertices; void* attributes; char pad_15C[0x176]; u16 effect;
} MeshRecord;
typedef struct RuntimeRecord {
    MeshRecord* mesh;
    char pad_4[0x20];
    u16 count;
    char pad_26[2];
} RuntimeRecord;
typedef struct Runtime { char pad_0[7]; u8 flags; char pad_8[8]; RuntimeRecord* records; } Runtime;
typedef struct Pair { int index; float value; } Pair;
typedef struct SmallRecord { s16 value; u8 color; u8 pad_3; } SmallRecord;
typedef struct BatchEntry {
    Vec3 position; s8 pair_count; s8 small_count; s8 flags; char pad_F;
    Pair* pairs; SmallRecord* small; VertexData* vertices; s8* mask;
} BatchEntry;
typedef struct Batch {
    char pad_0[0x5C]; BatchEntry* entries; char pad_60[0x10];
    int* record_indices; char pad_74[8]; u8 count; char pad_7D[4];
    u8 transform_disabled;
} Batch;
typedef struct VertexAttribute { u32 words[4]; } VertexAttribute;
typedef struct ShortVec { s16 x, y, z; } ShortVec;
typedef struct Globals { char pad_0[0x1C8]; u32 flags; char pad_1CC[0x14]; s8 effect_mode; } Globals;

extern Globals lbl_8030F540;
extern float lbl_80650228, lbl_80650240, lbl_80650244, lbl_80650248;
extern Color lbl_80650238, lbl_8065023C, lbl_80651BA4;
extern void fn_80128058(MeshRecord*, int, VertexAttribute*, ShortVec*);
extern void fn_8012811C(VertexData*, VertexAttribute*);
extern void fn_8017974C(ShortVec*, ShortVec*, Vec3*, float);
extern int fn_8017A750(VertexAttribute*, VertexAttribute*);
extern void fn_8017A71C(VertexAttribute*);
extern void fn_8017A7D4(const VertexAttribute*, const VertexAttribute*, float, VertexAttribute*);
extern void fn_80124664(MeshRecord*, int, u32, float);
extern void* fn_8012C62C(MeshRecord*, int, Color*, Color*, Color*, int);
extern void fn_8012C478(MeshRecord*, int, int);
extern void fn_8011F0E8(MeshRecord*, Vec3*);
extern void fn_8011F114(Vec3*, MeshRecord*);
extern void fn_80120B4C(MeshRecord*);
extern void fn_80120AD0(MeshRecord*, int, int, int, float, float);
extern void fn_8012D0D0(MeshRecord*);

/* Indexed owner lookups intentionally remain expressions: caching them
 * across calls changes both alias behavior and retail codegen.
 * The masked loop snapshots its count and advances the source only on selected
 * entries; the unmasked loop reloads its runtime-record count each iteration. */
Batch* fn_80131E8C(Runtime* runtime, Batch* batch)
{
    int outer;
    float low, high;
    for (outer = 0; outer < batch->count; outer++) {
        /* Re-evaluate owner lookups: calls and short stores may alias them. */
#define ENTRY (&batch->entries[outer])
#define RECORD (&runtime->records[batch->record_indices[outer]])
#define MESH (RECORD->mesh)
        s8 alternate = (s8)(ENTRY->flags & 2);
        s8 enabled = (s8)(ENTRY->flags & 1);
        if (MESH == 0) continue;
        if (!alternate && enabled) {
            int vertex;
            high = lbl_80650240;
            for (vertex = 0; vertex < (int)RECORD->count - 1; vertex++) {
                ShortVec position;
                VertexAttribute attribute;
                position.x = (s16)(MESH->vertices[vertex].x * high);
                position.y = (s16)(MESH->vertices[vertex].y * high);
                position.z = (s16)(MESH->vertices[vertex].z * high);
                attribute = ((VertexAttribute*)MESH->attributes)[vertex];
                fn_80128058(MESH, vertex, &attribute, &position);
            }
        } else {
            int vertex, pair_index, small_index;
            int source_index = 0;
            int count = (int)RECORD->count - 1;
#define SOURCE (&ENTRY->vertices[source_index])
            for (vertex = 0; vertex < count; vertex++) {
                s8 active;
                int selected = 1;
                if (ENTRY->mask != 0) selected = ENTRY->mask[vertex >> 3] & (1 << (vertex & 7));
                active = SOURCE->active;
                if (active && selected) {
                    VertexAttribute attribute;
                    VertexAttribute temporary;
                    VertexAttribute output;
                    ShortVec position;
                    fn_8012811C(SOURCE, &attribute);
                    if (!alternate && !batch->transform_disabled && !(lbl_8030F540.flags & 1)) {
                        ShortVec original;
                        Vec3 result;
                        original.x = (s16)(MESH->vertices[vertex].x * lbl_80650240);
                        original.y = (s16)(MESH->vertices[vertex].y * lbl_80650240);
                        original.z = (s16)(MESH->vertices[vertex].z * lbl_80650240);
                        temporary = ((VertexAttribute*)MESH->attributes)[vertex];
                        fn_8017974C(&original, (ShortVec*)(SOURCE->data + 8), &result, lbl_80650244);
                        position.x = (s16)result.x;
                        position.y = (s16)result.y;
                        position.z = (s16)result.z;
                        if (fn_8017A750(&temporary, &attribute)) fn_8017A71C(&attribute);
                        fn_8017A7D4(&temporary, &attribute, lbl_80650244, &output);
                    } else {
                        position = *(ShortVec*)(SOURCE->data + 8);
                        output = attribute;
                    }
                    fn_80128058(MESH, vertex, &output, &position);
                    source_index++;
                } else if (active && !selected) {
                    VertexAttribute attribute;
                    ShortVec position;
                    position.x = (s16)(MESH->vertices[vertex].x * lbl_80650240);
                    position.y = (s16)(MESH->vertices[vertex].y * lbl_80650240);
                    position.z = (s16)(MESH->vertices[vertex].z * lbl_80650240);
                    attribute = ((VertexAttribute*)MESH->attributes)[vertex];
                    fn_80128058(MESH, vertex, &attribute, &position);
                } else if (!active && selected) {
                    source_index++;
                }
            }
#undef SOURCE
            {
                low = lbl_80650248;
                high = lbl_80650228;
                for (pair_index = 0; pair_index < ENTRY->pair_count; pair_index++) {
#define PAIR (&ENTRY->pairs[pair_index])
                    if (PAIR->value < low) PAIR->value = low;
                    if (PAIR->value > high) PAIR->value = high;
                    fn_80124664(MESH, PAIR->index, 0, PAIR->value);
                }
#undef PAIR
            }
            {
                for (small_index = 0; small_index < ENTRY->small_count; small_index++) {
                    SmallRecord* small;
                    MeshRecord* color_mesh;
                    Color first, first_temp, middle, third, third_temp;
                    /* Resolve the mesh before the color record to preserve retail allocation. */
                    color_mesh = MESH;
                    small = &ENTRY->small[small_index];
                    third_temp = lbl_8065023C;
                    third_temp.a = small->color;
                    third = third_temp;
                    middle = lbl_80651BA4;
                    first_temp = lbl_80650238;
                    first_temp.a = small->color;
                    first = first_temp;
                    fn_8012C62C(color_mesh, small->value, &first, &middle, &third, 4);
                }
            }
            if (!ENTRY->small_count) fn_8012C478(MESH, 15, 1);
        }
        {
            Vec3 alternate_position, enabled_position, blended_position, returned;
            if (alternate) {
                alternate_position = MESH->position;
                alternate_position = ENTRY->position;
                if (!(runtime->flags & 1)) alternate_position.z = lbl_80650248;
                fn_8011F0E8(MESH, &alternate_position);
            } else if (enabled) {
                fn_8011F114(&returned, MESH);
                enabled_position = returned;
                if (!(runtime->flags & 1)) enabled_position.z = lbl_80650248;
                fn_8011F0E8(MESH, &enabled_position);
            } else {
                MeshRecord* current = MESH;
                blended_position = current->position;
                if (!batch->transform_disabled && !(lbl_8030F540.flags & 1)) {
                    {
                        float delta = ENTRY->position.x - current->position.x;
                        float amount = lbl_80650244;
                        blended_position.x += delta * amount;
                    }
                    {
                        float delta = ENTRY->position.y - current->position.y;
                        float amount = lbl_80650244;
                        blended_position.y += delta * amount;
                    }
                    {
                        float delta = ENTRY->position.z - current->position.z;
                        float amount = lbl_80650244;
                        blended_position.z += delta * amount;
                    }
                    if (!(runtime->flags & 1)) blended_position.z = lbl_80650248;
                    fn_8011F0E8(current, &blended_position);
                } else {
                    blended_position = ENTRY->position;
                    if (!(runtime->flags & 1)) blended_position.z = lbl_80650248;
                    fn_8011F0E8(MESH, &blended_position);
                }
                if (!(lbl_8030F540.flags & 1) && (ENTRY->flags & 4)) {
                    if (current->effect != 0) fn_80120B4C(current);
                    else if (lbl_8030F540.effect_mode == 1) fn_80120AD0(current, 0, 100, 0x22, lbl_80650228, lbl_80650248);
                    else if (lbl_8030F540.effect_mode == 2) fn_80120AD0(current, 0, 100, 10, lbl_80650228, lbl_80650248);
                    else fn_80120AD0(current, 0, 100, 0x12, lbl_80650228, lbl_80650248);
                }
            }
        }
        if (!enabled) fn_8012D0D0(MESH);
    }
#undef MESH
#undef RECORD
#undef ENTRY
    return batch;
}
