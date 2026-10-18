extern unsigned int luaZ_read(void*, void*, void*);
extern void unexpectedEOZ(void*, void*);

void ezread(void* object, void* input, void* destination, void* size)
{
    if (luaZ_read(input, destination, size) != 0) {
        unexpectedEOZ(object, input);
    }
}
