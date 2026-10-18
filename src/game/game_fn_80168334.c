typedef struct InputComposite {
    void* records;
    int record_count;
    void** first_values;
    int first_count;
    void** second_values;
    int second_count;
} InputComposite;

#pragma use_lmw_stmw on

extern int LoadInt(void*, void*, int);
extern void* luaM_realloc(void*, void*, unsigned int, const char*, int);
extern void LoadVector(void*, void*, int, unsigned int, void*, int);
extern void* LoadString(void*, void*, int);
extern void* LoadFunction(void*, void*, int);
extern const char lbl_8024FAF4[];

void LoadConstants(void* object, InputComposite* composite, void* input,
                 int reverse)
{
    int i;
    int n;

    composite->first_count = n = LoadInt(object, input, reverse);
    composite->first_values = luaM_realloc(object, 0,
                                           n * sizeof(void*),
                                           lbl_8024FAF4, 141);
    for (i = 0; i < n; i++)
        composite->first_values[i] = LoadString(object, input, reverse);

    composite->record_count = n = LoadInt(object, input, reverse);
    composite->records = luaM_realloc(object, 0,
                                      n * 8,
                                      lbl_8024FAF4, 145);
    LoadVector(object, composite->records, n, 8, input, reverse);

    composite->second_count = n = LoadInt(object, input, reverse);
    composite->second_values = luaM_realloc(object, 0,
                                            n * sizeof(void*),
                                            lbl_8024FAF4, 148);
    for (i = 0; i < n; i++)
        composite->second_values[i] = LoadFunction(object, input, reverse);
}
