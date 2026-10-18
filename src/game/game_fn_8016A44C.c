typedef int (*Reader)(void);

typedef struct Input {
    unsigned int remaining;
    const unsigned char* cursor;
    Reader reader;
    int state;
    void* user;
} Input;

extern int zmfilbuf(void);

Input* luaZ_mopen(Input* input, const unsigned char* data,
                  unsigned int size, void* user)
{
    if (data == 0) {
        return 0;
    }
    input->remaining = size;
    input->cursor = data;
    input->reader = zmfilbuf;
    input->state = 0;
    input->user = user;
    return input;
}
