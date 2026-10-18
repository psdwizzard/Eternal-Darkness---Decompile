typedef struct InputStream InputStream;

struct InputStream {
    unsigned int remaining;
    unsigned char* cursor;
    int (*refill)(InputStream*);
};

#pragma use_lmw_stmw on

extern void* LoadChunk(void*, InputStream*);
extern int ZNAME(InputStream*);
extern void luaO_verror(void*, const char*, ...);
extern const char lbl_8024FC84[];

void* luaU_undump(void* object, InputStream* input)
{
    void* result = 0;
    int byte;

    if (input->remaining-- != 0)
        byte = *input->cursor++;
    else
        byte = input->refill(input);

    if (byte == 0x1B)
        result = LoadChunk(object, input);

    if (input->remaining-- != 0)
        byte = *input->cursor++;
    else
        byte = input->refill(input);

    if (byte != -1)
        luaO_verror(object, lbl_8024FC84, ZNAME(input));

    return result;
}
