typedef struct InputArray {
    unsigned char pad00[0x18];
    unsigned int* values;
} InputArray;

#pragma use_lmw_stmw on

extern int LoadInt(void*, void*, int);
extern void* luaM_realloc(void*, void*, unsigned int, const char*, int);
extern void LoadVector(void*, void*, int, unsigned int, void*, int);
extern int ZNAME(void*);
extern void luaO_verror(void*, const char*, ...);
extern void luaF_protook(void*, InputArray*, int);
extern const char lbl_8024FAF4[];
extern const char lbl_8024FB00[];

void LoadCode(void* object, InputArray* array, void* input, int reverse)
{
    int count = LoadInt(object, input, reverse);

    array->values = luaM_realloc(object, 0, count * sizeof(int),
                                lbl_8024FAF4, 108);
    LoadVector(object, array->values, count, sizeof(int), input, reverse);
    if (array->values[count - 1] != 0) {
        luaO_verror(object, lbl_8024FB00, ZNAME(input));
    }
    luaF_protook(object, array, count);
}
