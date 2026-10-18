typedef struct InputStream InputStream;

struct InputStream {
    unsigned int remaining;
    unsigned char* cursor;
    int (*refill)(InputStream*);
};

extern void unexpectedEOZ(void*, InputStream*);

int ezgetc(void* object, InputStream* input)
{
    int result;

    if (input->remaining-- != 0) {
        result = *input->cursor++;
    } else {
        result = input->refill(input);
    }

    if (result == -1) {
        unexpectedEOZ(object, input);
    }
    return result;
}
