typedef struct EventData {
    unsigned char pad[0x5C];
    int value;
    unsigned char pad60[0xEC];
    short timer;
} EventData;

typedef struct Entry80201814 Entry80201814;
typedef struct Runtime Runtime;
typedef struct Queue Queue;
typedef struct Object80201D2C Object80201D2C;
typedef struct Object80201D14 Object80201D14;

extern Entry80201814 *fn_80201814(int);
extern void fn_801291F0(void *, void *, unsigned char);
extern unsigned char *fn_801294DC(void *, int, int, int);
extern void fn_80128C44(Runtime *, unsigned int, unsigned int);
extern void fn_80128C28(Runtime *, unsigned int, unsigned int);
extern void fn_801287C4(Queue *, void *, unsigned int, unsigned int);
extern void fn_80201D2C(Object80201D2C *, int);
extern void fn_80201D14(Object80201D14 *, unsigned char);
extern int fn_80204810(void *, int);

void fn_800E33B8(int id, void *resource, EventData *data)
{
    struct {
        void *object;
        int argument;
    } state;
    int mode;
    void *created;
    int value;

    {
        void *object = fn_80201814(id);
        state.object = object;
    }
    value = data->value;
    mode = 49;
    if (value != 0)
        mode = 48;
    state.argument = 12;
    if (value != 0)
        state.argument = 4;

    fn_801291F0(resource, (void *)mode,
                (unsigned char)(26 + ((-value | value) >> 31)));
    created = fn_801294DC(resource, mode, 48, 6);
    if (created != 0) {
        mode = id << 8;
        fn_80128C44(created, (unsigned int)fn_80204810, mode | 7);
        mode |= 6;
        fn_80128C28(created, (unsigned int)(void *)fn_80204810, mode);
        fn_801287C4(created, fn_80204810, mode, state.argument);
        fn_80201D2C(state.object, 124);
        fn_80201D14(state.object, 1);
        data->timer = 120;
    }
}
