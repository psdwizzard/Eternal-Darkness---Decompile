typedef unsigned int size_t;
typedef struct Input Input;
typedef int (*Reader)(Input*);

struct Input {
    unsigned int remaining;
    const unsigned char* cursor;
    Reader reader;
    int state;
    void* user;
};

extern void* memcpy(void*, const void*, size_t);

int luaZ_read(Input* input, unsigned char* output, unsigned int size)
{
    while (size != 0) {
        unsigned int count;
        if (input->remaining == 0) {
            if (input->reader(input) == -1) {
                return (int)size;
            }
            input->remaining++;
            input->cursor--;
        }
        count = input->remaining;
        if (size <= count) {
            count = size;
        }
        memcpy(output, input->cursor, count);
        output += count;
        size -= count;
        input->remaining -= count;
        input->cursor += count;
    }
    return 0;
}
