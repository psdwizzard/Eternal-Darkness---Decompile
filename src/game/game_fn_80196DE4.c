typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Entry {
    u8 data[0x38];
} Entry;

typedef struct Buffers {
    u8* vertices;
    u8* colors;
    u8* indices;
} Buffers;

extern Vec3 lbl_8023B088;
extern u8 lbl_80607120[];
extern void* lbl_8064C4E4;
extern int lbl_8064D738;
extern float lbl_80650B88;

void fn_8011F114(Vec3* value);
void fn_801F68B0(Vec3* value);
void fn_8018D788(int allocation, u8* self, Buffers* buffers, u16 offset);
void fn_8018E504(void* entry, void* channels);
void fn_8018E260(void* entry, int value, int type);
void fn_8018E230(void* entry, void* alpha, int type, int value, int count,
                 int stride);
void fn_8018E8B8(void* channels, int value, int channel);
void fn_80198420(void* values, void* entries, u8 count, void* output, u8 value);
void fn_80198724(void* state, void* output, u8 count);
void fn_8013CCEC(void* output, Vec3* start, void* source, int count, int stride);
int fn_801AC908(void* handle, void* value, int mask);
void* fn_801AC8AC(u16 value, int low, int high, void* position);
void fn_801AC980(void* handle, int value);

static inline void SetLevels(u8* object, int count, int split, u8 value)
{
    Entry* entry;
    int i;
    entry = *(Entry**)(object + 0x4c);
    for (i = 0; i < count; i++) {
        entry->data[0x2b] = value;
        entry++;
    }
    entry = *(Entry**)(object + 0x4c);
    for (i = 0; i < split; i++) {
        entry->data[0x2f] = value;
        entry++;
    }
}

static inline void AddLevels(u8* object, int count, int split, s8 step)
{
    Entry* entry;
    int i;
    entry = *(Entry**)(object + 0x4c);
    for (i = 0; i < count; i++) {
        entry->data[0x2b] += step;
        entry++;
    }
    entry = *(Entry**)(object + 0x4c);
    for (i = 0; i < split; i++) {
        entry->data[0x2f] += step;
        entry++;
    }
}

int fn_80196DE4(u8* object)
{
    Buffers buffers;
    Vec3 end;
    Vec3 position;
    u8* entry;
    u8 count;
    int tick;
    int i;
    u8* state = object + 0xd4;

    entry = *(u8**)(object + 0x4c);
    position = lbl_8023B088;
    if (lbl_8064C4E4 != 0) {
        fn_8011F114(&position);
        position.z += lbl_80650B88;
    } else {
        fn_801F68B0(&position);
    }
    fn_8018D788(lbl_8064D738, object, &buffers,
                *(u16*)(lbl_80607120 + 2));

    count = object[1];
    tick = *(u16*)(object + 0xa) % (*(u16*)(object + 0xc) + 1);
    *(u16*)(object + 0xa) += 1;

    if (object[0xa4] != 0) {
        if (object[0xa4] == 6) {
            if (entry[7] != 0) {
                entry[7]--;
                if (entry[7] == 0) {
                    u8 target = entry[4];
                    u8 split = count >> 1;
                    s8 step = entry[5];
                    u8 value = ((step / 2) * ((target - 150) / step)) + 60;
                    Entry* scan;
                    int j;
                    SetLevels(object, count, split, value);
                    scan = *(Entry**)(object + 0x4c) + split;
                    for (j = 0; j < split; j++) {
                        scan->data[0x2f] = target;
                        scan++;
                    }
                }
            } else {
                u8 split = count >> 1;
                Entry* half = *(Entry**)(object + 0x4c) + split;
                if (half->data[0x2f] != entry[1]) {
                    u8 speed = entry[5];
                    s8 step = (s8)speed / 2;
                    int j;
                    AddLevels(object, count, split, step);
                    for (j = 0; j < split; j++) {
                        half->data[0x2f] += speed;
                        half++;
                    }
                } else {
                    object[0xa4] = 0;
                }
            }
        } else {
            int active = 0;
            for (i = 0; i < count; entry += 0x38, i++) {
                if (entry[0] != 0) {
                    fn_8018E504(entry, entry + 0x20);
                    active = 1;
                }
            }
            if (!active)
                object[0xa4] = 0;
        }
    }

    {
        int entry_count = object[1];
        fn_80198420(object + 0x10, *(void**)(object + 0x4c), entry_count,
                     buffers.vertices, object[0x8c]);
    }
    if ((tick & object[0x8e]) == 0 && (s8)object[0xa1] != 0) {
        object[0x8c] += object[0xa1];
        if (object[0x8c] > object[0x8d] || object[0x8c] == 1)
            object[0xa1] = -object[0xa1];
    }

    if (*(u16*)(state + 0xc) & 1) {
        fn_80198724(state, buffers.vertices, object[1] >> 1);
        *(u16*)(state + 0xc) &= ~1;
    }

    if (!(object[0xa5] & 0x20) &&
        ((object[0xa5] & 1) || tick >= *(u16*)(object + 0xc))) {
        entry = *(u8**)(object + 0x4c);
        if (entry[0x2b] > 60)
            *(u16*)(object + 0xc) = *(u16*)(object + 0xa) + 120;
        else
            *(u16*)(object + 0xc) = *(u16*)(object + 0xa) + 60;
        object[0xa5] &= ~1;
        object[0xa4] = 1;
        for (i = 0; i < count; entry += 0x38, i++) {
            fn_8018E260(entry, entry[0x2b], 0);
            fn_8018E230(entry, entry + 0x2b, 2, entry[0x2b], -10, 0);
            fn_8018E8B8(entry + 0x20, entry[0x2b], 0);
            fn_8018E8B8(entry + 0x20, entry[0x2b], 1);
        }
        object[0xa5] |= 0x20;
    }

    fn_8013CCEC(&end, &position, buffers.vertices + (count + 1) * 6, count - 2,
                2);
    if (!fn_801AC908(*(void**)(object + 0x90), &end, 0xff)) {
        *(void**)(object + 0x90) =
            fn_801AC8AC(*(u16*)(object + 0x94), 100, 500, &end);
    }
    if (!(object[0xa5] & 1) && tick >= *(u16*)(object + 0xc)) {
        *(u16*)(object + 0x22) = 8;
        if (*(void**)(object + 0x90) != 0) {
            fn_801AC980(*(void**)(object + 0x90), 1);
            *(void**)(object + 0x90) = 0;
        }
    }
    return 0;
}
