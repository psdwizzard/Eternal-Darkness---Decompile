typedef struct Buffer {
    char pad00[0x18];
    char* data;
    unsigned int capacity;
    char pad20[0x40];
    unsigned int accounting;
} Buffer;

extern void* luaM_realloc(void*, void*, unsigned int, char*, int);
extern char lbl_8024F750[];

char* luaO_openspace(Buffer* buffer, unsigned int requested)
{
    if (requested > buffer->capacity) {
        buffer->data = luaM_realloc(buffer, buffer->data, requested,
                                   lbl_8024F750, 0x3C);
        buffer->accounting += requested - buffer->capacity;
        buffer->capacity = requested;
    }
    return buffer->data;
}
