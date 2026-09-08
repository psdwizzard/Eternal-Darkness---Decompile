typedef struct Entry {
    int value0;
    int value4;
    int value8;
} Entry;

int fn_801EDF5C(Entry* left, Entry* right)
{
    int result = left->value8 - right->value8;

    if (result == 0) {
        result = left->value0 - right->value0;
    }
    return result;
}
