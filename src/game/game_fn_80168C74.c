typedef struct Record {
    void* payload;
    char pad04[8];
    unsigned short flag;
} Record;

extern Record* luaV_closure(void*, int);

void luaV_Cclosure(void* state, void* payload, int count)
{
    Record* record = luaV_closure(state, count);
    record->payload = payload;
    record->flag = 1;
}
