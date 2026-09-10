typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Input {
    float x;
    float y;
    void* first;
    void* second;
    u32 value;
} Input;

typedef struct Output {
    u16 flags;
    u8 first_index;
    u8 second_index;
    float x;
    float y;
    u32 value;
} Output;

extern void* memset(void*, int, unsigned int);
extern int fn_801FB9D4(void*, int);

void fn_801FBAC8(Input* input, Output* output)
{
    int index;

    memset(output, 0, sizeof(Output));
    output->x = input->x;
    output->y = input->y;
    output->value = input->value;
    output->flags = 0;

    if (input->first != 0) {
        index = fn_801FB9D4(input->first, 0);
        if (index != -1) {
            output->flags |= 1;
            output->first_index = index;
        }
    }
    if (input->second != 0) {
        index = fn_801FB9D4(input->second, 1);
        if (index != -1) {
            output->flags |= 2;
            output->second_index = index;
        }
    }
}
