typedef struct InputRecord {
    void* data;
    int first;
    int second;
} InputRecord;

typedef struct InputRecordArray {
    unsigned char pad00[0x34];
    int count;
    InputRecord* records;
} InputRecordArray;

#pragma use_lmw_stmw on

extern int LoadInt(void*, void*, int);
extern void* luaM_realloc(void*, void*, unsigned int, const char*, int);
extern void* LoadString(void*, void*, int);
extern const char lbl_8024FAF4[];

void LoadLocals(void* object, InputRecordArray* array, void* input, int reverse)
{
    int count = LoadInt(object, input, reverse);
    int offset;
    int i;

    array->count = count;
    array->records = luaM_realloc(object, 0, count * sizeof(InputRecord),
                                 lbl_8024FAF4, 118);
    i = 0;
    offset = 0;
    for (; i < count; i++) {
        *(void**)((unsigned char*)array->records + offset) =
            LoadString(object, input, reverse);
        *(int*)((unsigned char*)array->records + offset + 4) =
            LoadInt(object, input, reverse);
        *(int*)((unsigned char*)array->records + offset + 8) =
            LoadInt(object, input, reverse);
        offset += sizeof(InputRecord);
    }
}
