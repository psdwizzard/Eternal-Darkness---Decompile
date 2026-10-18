typedef struct TaggedValue {
    int type;
    int pad4;
    void* value;
} TaggedValue;

typedef struct IndexedValue {
    int first;
    int second;
} IndexedValue;

int luaT_tag(TaggedValue* value)
{
    switch (value->type) {
    case 0:
        return ((IndexedValue*)value->value)->first;
    case 4:
        return ((IndexedValue*)value->value)->second;
    default:
        return value->type;
    }
}
