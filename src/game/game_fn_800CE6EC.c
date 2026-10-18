typedef unsigned char u8;
typedef signed short s16;

typedef struct Entry80201B3C Entry80201B3C;
typedef struct Object Object;

typedef union DataWord {
    int value;
    struct {
        u8 pad00[3];
        u8 index;
    } bytes;
} DataWord;

typedef struct OutputEntry {
    int values[4];
} OutputEntry;

typedef struct Data {
    DataWord first;
    u8 pad04[3];
    u8 limit;
    OutputEntry entries[14];
    u8 padE8[8];
    s16 step;
    s16 flags;
    u8 state;
} Data;

typedef struct RuntimeState {
    u8 pad00[0x20];
    Data *data;
} RuntimeState;

extern int lbl_8064D738;

extern int fn_80047178(void);
extern int fn_8012FA54(Object *object, int index);
extern Entry80201B3C *fn_80201B3C(void);
extern void *fn_80201B8C(unsigned char *object);
extern void *fn_80201BC8(void *object);

int fn_800CE6EC(void *object)
{
    Data *data;
    Object *other;

    data = ((RuntimeState *)fn_80201B8C((unsigned char *)object))->data;

    if (fn_80201B3C() != 0) {
        other = (Object *)fn_80201BC8(fn_80201B3C());
    } else {
        other = 0;
    }

    if ((fn_80047178() != 0 && fn_8012FA54(other, 15) != 0) ||
        (data->state & 0x10) == 0) {
        OutputEntry *base;
        int buffer;
        OutputEntry *output;

        buffer = lbl_8064D738;
        base = data->entries;
        data->first.bytes.index += data->step;
        if (data->first.bytes.index >= data->limit) {
            data->first.bytes.index = data->limit;
            data->flags |= 1;
        }

        output = base + buffer;
        output[3].values[0] = data->first.value;
        output[3].values[1] = data->first.value;
        output[3].values[2] = data->first.value;
        output[3].values[3] = data->first.value;
    }

    return data->flags;
}
