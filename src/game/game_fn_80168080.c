extern unsigned int LoadSize(void*, void*, int);
extern void* luaO_openspace(void*, unsigned int);
extern void LoadBlock(void*, void*, unsigned int, void*, int);
extern void* luaS_newlstr(void*, void*, unsigned int);

void* LoadString(void* object, void* input, int reverse)
{
    unsigned int size = LoadSize(object, input, reverse);
    void* data;

    if (size == 0) {
        return 0;
    }
    data = luaO_openspace(object, size);
    LoadBlock(object, data, size, input, 0);
    return luaS_newlstr(object, data, size - 1);
}
