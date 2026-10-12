typedef void (*Callback)(void);

typedef struct Object {
    unsigned int words[9];
} Object;

typedef struct Range {
    int first;
    int last;
    void* value;
} Range;

typedef struct Iterator {
    unsigned int capacity;
    unsigned int count;
    int* values;
} Iterator;

typedef struct Buffer {
    unsigned char reserved[0xF6C];
    Iterator iterator;
    unsigned char entries[0x1B8];
    int values[6];
    Object objects[3];
} Buffer;

extern Buffer lbl_8031F7C0;
extern Callback lbl_8064CA1C;
extern Object* lbl_8064CA24;
extern Object* lbl_8064CA28;
extern Object* lbl_8064CA2C;
extern unsigned char lbl_8064CA30;
extern unsigned char lbl_8064CA31;
extern int lbl_8064CA34;
extern int lbl_8064CA38;
extern void* lbl_8064CA3C;
extern int lbl_8064CA44;
extern int lbl_8064CA48;
extern int lbl_8064CA60;
extern int lbl_8064CA64;
extern unsigned int lbl_8064CA6C;

extern void* memset(void*, int, unsigned long);
extern int fn_800B1AA0(int);
extern void fn_800B1AB0(void);
extern void fn_800B19A4(void*);
extern void fn_8017B31C(int);
extern void fn_801E8A50(Object*);
extern void fn_801E8AEC(Range*, int, int, void*);
extern void fn_801E8B10(Object*, unsigned int, unsigned int, unsigned int, unsigned int);
extern void fn_801E8B24(Object*, int, int);
extern void fn_801E8E54(Iterator*, unsigned int, int*);

void fn_800B177C(int state, Callback callback)
{
    register Buffer* buffer;
    register Callback handler;
    register Object* object;
    register int task;
    register int one = 1;

    lbl_8064CA48 = state;
    lbl_8064CA3C = 0;
    /* ASM: lis/addi/stw retain the pooled BSS base and its flag store;
     * C rematerializes the base and moves the flag to another scheduling
     * region when the address is made opaque. */
    asm {
        lis r3, lbl_8031F7C0@ha
        addi buffer, r3, lbl_8031F7C0@l
        stw one, lbl_8064CA44(r13)
    }
    lbl_8064CA1C = callback;
    lbl_8064CA38 = 0;
    lbl_8064CA34 = 0;
    lbl_8064CA6C = 0;
    lbl_8064CA31 = 0;
    lbl_8064CA30 = one;
    fn_800B1AA0(0);
    lbl_8064CA64 = 0;
    lbl_8064CA60 = 0;
    memset(buffer->entries, 0, 0x1B8);
    fn_801E8E54(&buffer->iterator, 6, buffer->values);

    lbl_8064CA2C = &buffer->objects[0];
    fn_801E8A50(lbl_8064CA2C);
    fn_801E8AEC((Range*)lbl_8064CA2C, 0, 1, (void*)2);
    fn_801E8B24(lbl_8064CA2C, 0, 0);
    /* ASM: lis/lwz/addi load the object and callback address together;
     * converting the callback address to an integer in C retains it
     * across registrations instead of materializing it for each call. */
    asm {
        lis r4, fn_800B1AB0@ha
        lwz object, lbl_8064CA2C(r13)
        addi handler, r4, fn_800B1AB0@l
    }
    fn_801E8B10(object, 1, 0, 0, (unsigned int)handler);

    lbl_8064CA28 = &buffer->objects[1];
    fn_801E8A50(lbl_8064CA28);
    fn_801E8AEC((Range*)lbl_8064CA28, 0, 1, (void*)2);
    fn_801E8B24(lbl_8064CA28, 0, 0);
    /* ASM: lis/lwz/addi load the object and callback address together;
     * converting the callback address to an integer in C retains it
     * across registrations instead of materializing it for each call. */
    asm {
        lis r4, fn_800B1AB0@ha
        lwz object, lbl_8064CA28(r13)
        addi handler, r4, fn_800B1AB0@l
    }
    fn_801E8B10(object, 1, 0, 0, (unsigned int)handler);

    lbl_8064CA24 = &buffer->objects[2];
    fn_801E8A50(lbl_8064CA24);
    fn_801E8AEC((Range*)lbl_8064CA24, 0, 6, (void*)4);
    fn_801E8B24(lbl_8064CA24, 0, 0);
    /* ASM: lis/lwz/addi load the object and callback address together;
     * converting the callback address to an integer in C retains it
     * across registrations instead of materializing it for each call. */
    asm {
        lis r4, fn_800B1AB0@ha
        lwz object, lbl_8064CA24(r13)
        addi handler, r4, fn_800B1AB0@l
    }
    fn_801E8B10(object, 1, 0, 0, (unsigned int)handler);
    /* ASM: lis/addi form the callback directly in the argument register;
     * the integer cast in C uses a different register for the high part. */
    asm {
        lis r3, fn_800B19A4@ha
        addi task, r3, fn_800B19A4@l
    }
    fn_8017B31C(task);
}
