typedef struct RuntimeState {
    unsigned char pad[0x14C];
    short timer;
} RuntimeState;

typedef struct EventData {
    unsigned char pad[0x5C];
    int value;
} EventData;

extern void *fn_80201814();
extern void fn_801291F0(void *, int, unsigned char);
extern void *fn_801294DC(void *, int, int, int);
extern void fn_80128C44(void *, void *, int);
extern void fn_80128C28();
extern void fn_801287C4(void *, void *, int, int);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_80204810(void);

void fn_800E33B8(int id, void *resource, EventData *data)
{
    EventData *event_data;
    int mode;
    void *object;
    int argument;
    void *created;
    int value;

    event_data = data;
    object = fn_80201814(id);
    value = event_data->value;
    mode = 49;
    if (value != 0)
        mode = 48;
    argument = 12;
    if (value != 0)
        argument = 4;

    fn_801291F0(resource, mode,
                (unsigned char)(26 + ((-value | value) >> 31)));
    created = fn_801294DC(resource, mode, 48, 6);
    if (created != 0) {
        mode = id << 8;
        fn_80128C44(created, fn_80204810, mode | 7);
        mode |= 6;
        fn_80128C28(created, fn_80204810, mode);
        fn_801287C4(created, fn_80204810, mode, argument);
        fn_80201D2C(object, 124);
        fn_80201D14(object, 1);
        ((RuntimeState *)event_data)->timer = 120;
    }
}
