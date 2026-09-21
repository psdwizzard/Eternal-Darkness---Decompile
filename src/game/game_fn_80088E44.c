typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef int (*Callback)(void*);

typedef struct Child {
    u8 pad[0x14];
    u32 value;
} Child;

typedef struct State {
    u8 pad[0x40];
    Callback callbacks[4];
    void* arguments[4];
    u16 values[4];
    u8 current;
    u8 previous;
    u8 first;
    u8 last;
} State;

typedef struct FullWork {
    u8 pad[0xC];
    Child* child;
    u8 pad10[0x48];
    State state;
} FullWork;

extern void fn_8006C9C0(Child*);
extern void fn_8006C9E4(Child*, int);

int fn_80088E44(FullWork* work)
{
    State* base;
    u8 current;
    u8 first;
    u8 last;
    int value;
    Child* child;
    u8* entry;
    Callback callback;
    void* argument;

    base = &work->state;
    child = work->child;
    if (child != 0) {
        value = child->value >> 16;
        entry = (u8*)base->callbacks;
        fn_8006C9C0(child);
        current = base->current;
        first = base->first;
        last = base->last;
        callback = *(Callback*)(entry + current * 4);
        argument = *(void**)(entry + 0x10 + current * 4);
        if (value == *(u16*)(entry + 0x20 + current * 2) && current < 4 &&
            callback != 0 && argument != 0) {
            callback(argument);
            fn_8006C9E4(child, 0);
            base->previous = current;
            current++;
            if (current >= last) {
                current = first;
            }
        }
        base->current = current;
    }
    return 0;
}
