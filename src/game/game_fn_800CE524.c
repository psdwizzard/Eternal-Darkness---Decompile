typedef unsigned char u8;
typedef signed short s16;

typedef struct Entry {
    s16 pad0;
    s16 first_a;
    s16 neg_a;
    s16 pad6;
    s16 first_b;
    s16 neg_b;
    s16 padC;
    s16 second_a;
    s16 neg_c;
    s16 pad12;
    s16 second_b;
    s16 neg_d;
} Entry;

typedef struct Data {
    u8 pad[0xEC];
    s16 cursor;
    s16 span;
} Data;

typedef struct RuntimeState {
    u8 pad[0x1C];
    Data *data;
} RuntimeState;

extern int lbl_8064D738;
extern void *fn_80201B8C();

void fn_800CE524(void *object)
{
    Data *data = ((RuntimeState *)fn_80201B8C(object))->data;
    int index = lbl_8064D738;
    s16 span = data->span;
    Entry *entries = (Entry *)((u8 *)data + 0x78);
    s16 first;
    s16 second;

    data->cursor++;
    if (data->cursor > 480) {
        data->cursor = 0;
    }
    first = data->cursor;
    second = first + span;
    entries[index].first_a = first;
    entries[index].neg_a = -1;
    entries[index].first_b = first;
    entries[index].neg_b = -1;
    entries[index].second_a = second;
    entries[index].neg_c = -1;
    entries[index].second_b = second;
    entries[index].neg_d = -1;
}
