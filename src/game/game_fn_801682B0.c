typedef struct InputWords {
    unsigned char pad00[0x2c];
    unsigned int* values;
    int count;
} InputWords;

#pragma use_lmw_stmw on

extern int LoadInt(void*, void*, int);
extern void* luaM_realloc(void*, void*, unsigned int, const char*, int);
extern void LoadVector(void*, void*, int, unsigned int, void*, int);
extern const char lbl_8024FAF4[];

void LoadLines(void* object, InputWords* words, void* input, int reverse)
{
    int count = LoadInt(object, input, reverse);

    words->count = count;
    words->values = luaM_realloc(object, 0, count * sizeof(unsigned int),
                                lbl_8024FAF4, 131);
    LoadVector(object, words->values, count, sizeof(unsigned int), input,
                reverse);
}
