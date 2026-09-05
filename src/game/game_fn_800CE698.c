typedef unsigned char u8;

typedef struct Data {
    volatile int value;
    u8 pad04[4];
    u8 buffers[0x80];
} Data;

typedef struct RuntimeState {
    u8 pad[0x20];
    Data *data;
} RuntimeState;

extern int lbl_8064D738;
extern void *fn_80201B8C();

#pragma opt_propagation off
void fn_800CE698(void *object)
{
    Data *data = ((RuntimeState *)fn_80201B8C(object))->data;
    int index;
    u8 *base;
    int *output;

    index = lbl_8064D738;
    base = data->buffers;
    output = (int *)(base + index * 16);

    output[12] = data->value;
    output[13] = data->value;
    output[14] = data->value;
    output[15] = data->value;
}
#pragma opt_propagation reset
