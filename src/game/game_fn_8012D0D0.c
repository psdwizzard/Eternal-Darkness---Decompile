typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct EntryRecord {
    u8 pad_0[0xE];
    u16 record_index;
} EntryRecord;

typedef struct EntrySlot {
    u8 pad_0[4];
    u16 flags;
    u8 pad_6[2];
} EntrySlot;

typedef struct Entry {
    int id;
    EntryRecord* record;
    EntrySlot slots[4];
} Entry;

typedef int (*RuntimeCallback)(void*);

typedef struct RuntimeFlags {
    u8 unk80 : 1;
    u8 busy : 3;
    u8 done : 1;
    u8 unk07 : 3;
} RuntimeFlags;

typedef struct RuntimeState {
    u8 pad_0[0xC];
    int ids[4];
    float scales[4];
    float values[4];
    float scale;
    float factor;
    int count;
    int delay;
    u8 pad_4C[4];
    RuntimeCallback callback;
    u8 flags;
} RuntimeState;

typedef struct Object {
    u8 pad_0[0x240];
    Entry** entries;
    u8 pad_244[0x10];
    u32 state_flags;
    u8 pad_258[0x38];
    RuntimeState* runtime;
} Object;

extern Vec3 lbl_805AADC8[3];
extern int lbl_8064CF30;
extern int lbl_8064CF34;

extern void fn_80125ECC(void*);
extern int fn_80128EAC(void*);
extern u8 fn_8012B8A8(Object*, RuntimeState*);
extern void fn_8012C478(void*, int, int);
extern void fn_8012D420(Entry*, int, void*, void*, void*, void*);
extern void fn_8012EC50(Object*, int, RuntimeState*, int, float, float);
extern void fn_8012F474(void*, int, int, int, const Vec3*, Vec3*, Vec3*);
extern void fn_80130434(void*, int);

extern void fn_8012C2D0();
extern void fn_8012C328();
extern void fn_8012C370();
extern void fn_8012C3B8();
extern void fn_8012C438();
extern void fn_8012C444();
extern void fn_8012C458();
extern void fn_8012C46C();
extern void fn_8012D5AC();
extern void fn_8012D66C();
extern void fn_8012D6C4();
extern void fn_8012D708();
extern void fn_8012D7AC();
extern void fn_8012D7F0();
extern void fn_8012D894();
extern void fn_8012D964();

void fn_8012D0D0(Object* object)
{
    int idle;
    Entry* entry;
    RuntimeState* runtime;
    int i;
    int ready;
    int active;
    u8 result;
    int start;
    int finish;
    Vec3* debug_vectors = lbl_805AADC8;

    fn_80125ECC(object);
    for (i = 0; i < 18; i++) {
        entry = object->entries[i];
        if (entry != 0) {
            if (entry->slots[0].flags & 1) {
                fn_8012D420(entry, 0, fn_8012D5AC, fn_8012C2D0, fn_8012D66C, fn_8012C438);
                if (!(entry->slots[0].flags & 1) && (entry->slots[0].flags & 0x40)) {
                    fn_8012C478(object, entry->id, 0);
                }
            }
            if (entry->slots[1].flags & 1) {
                fn_8012D420(entry, 1, fn_8012D6C4, fn_8012C328, fn_8012D708, fn_8012C444);
            }
            if (entry->slots[2].flags & 1) {
                fn_8012D420(entry, 2, fn_8012D7AC, fn_8012C370, fn_8012D7F0, fn_8012C458);
            }
            if (entry->slots[3].flags & 1) {
                fn_8012D420(entry, 3, fn_8012D894, fn_8012C3B8, fn_8012D964, fn_8012C46C);
            }
        }
    }

    if (object->state_flags & 0x8000) {
        return;
    }
    runtime = object->runtime;
    if (runtime->count <= 0) {
        return;
    }
    if (runtime->delay > 0) {
        runtime->delay--;
        return;
    }
    if (runtime->count <= 0) {
        return;
    }

    lbl_8064CF34 = 0;
    runtime->count--;
    active = !(runtime->flags & 8);
    idle = !(runtime->flags & 0x70);
    ready = idle;
    if (ready) {
        fn_80128EAC(object);
        if (runtime->callback != 0 && runtime->callback(object) != 0) {
            ready = 0;
        }
    }
    active = active && ready;

    result = fn_8012B8A8(object, runtime);
    start = runtime->count <= 0 && active;
    finish = active && !result;
    if (!result) {
        runtime->flags |= 8;
    } else {
        runtime->flags &= ~8;
    }

    if (runtime->count > 0 && result && ready) {
        for (i = 0; i < 4; i++) {
            if (runtime->ids[i] != -1) {
                fn_8012EC50(object, runtime->ids[i], runtime, 0x13,
                            runtime->factor * (runtime->scales[i] * runtime->scale),
                            runtime->values[i]);
            }
        }
    } else if (start || finish) {
        fn_80130434(object, runtime->count > 0 ? 0 : 1);
    }

    if (lbl_8064CF30 != 0 && runtime->count > 0) {
        fn_8012F474(object, object->entries[0]->record->record_index, 0, 0x13,
                    &debug_vectors[0], &debug_vectors[1], &debug_vectors[2]);
    }
}
