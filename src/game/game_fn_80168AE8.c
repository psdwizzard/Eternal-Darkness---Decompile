#pragma use_lmw_stmw on

typedef struct Owner {
    void* first;
    void* second;
    int index;
    int state;
    int cursor;
} Owner;

typedef struct Inner {
    char pad00[0x18];
    char* base;
    char pad1C[0x10];
    void* context;
} Inner;

typedef struct Input {
    char* current;
} Input;

extern int fn_8015FF18(void*, int, int, int*);
extern void fn_80160848(void*, void*, int, int);

void fn_80168AE8(void* output, char* input, int value, int extra)
{
    Owner* owner = *(Owner**)(input - 8);
    Inner* inner = *(Inner**)owner->first;
    char* current = *(char**)owner->second;
    char* base = inner->base;
    void* context = inner->context;
    int index = (current - base) / 4 - 1;
    int result;

    if (index == 0) {
        owner->state = 1;
        owner->cursor = 0;
        owner->index = index + 1;
    }
    result = fn_8015FF18(context, index, owner->state, &owner->cursor);
    if (result == owner->state && index > owner->index)
        goto done;
    owner->state = result;
    *(int*)output = value;
    fn_80160848(output, input - 32, result, extra);
done:
    owner->index = index;
}
