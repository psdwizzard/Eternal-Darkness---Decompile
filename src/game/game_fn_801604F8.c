typedef struct Object {
    void* current;
    char* allocation;
    char* end;
    int count;
    void* start;
    char pad14[0x4c];
    char* limit;
} Object;

extern char lbl_8064BA58;
extern void* luaM_realloc(void*, int, unsigned int, const char*, int);

void luaD_init(Object* object, int count)
{
    object->allocation = luaM_realloc(object, 0, (count + 40) << 4,
                                    &lbl_8064BA58, 35);
    object->limit += count << 4;
    object->end = object->allocation + ((count - 1) << 4);
    object->count = count;
    object->start = object->current = object->allocation;
}
