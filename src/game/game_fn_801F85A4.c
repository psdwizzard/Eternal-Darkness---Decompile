typedef unsigned char u8;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct MotionState {
    Vec3 position;
    u8 pad0C[0x24];
    float value;
    float field_34;
    u8 pad38[8];
    int field_40;
    u8 pad44[4];
    Vec3 vector;
    u8 pad54[0x18];
    void (*callback)(struct MotionState*);
    struct MotionState* source;
    u8 pad74[0x14];
} MotionState;

typedef struct Entry {
    float first_value;
    float second_value;
    MotionState* first_source;
    MotionState* second_source;
    int index;
} Entry;

extern int lbl_8064D7BC;
extern int fn_801FA410(int index);

static MotionState first[12] = {0};
static MotionState second[12] = {0};
static MotionState current_first = {0};
static MotionState current_second = {0};
static Entry entries[5] = {0};

int fn_801F85A4(void)
{
    Entry* entry;
    int result = 0;

    if (lbl_8064D7BC > 0) {
        entry = &entries[--lbl_8064D7BC];
        current_first.value = entry->first_value;
        current_second.value = entry->second_value;
        current_first.source = entry->first_source;
        current_second.source = entry->second_source;
        fn_801FA410(entry->index);
        result = 1;
    }
    return result;
}
