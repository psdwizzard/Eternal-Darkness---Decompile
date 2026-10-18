extern int rand(void);

void* fn_801A9F44(int count, void** values)
{
    void* result = 0;

    if (count != 0 && values != 0) {
        result = values[rand() % count];
    }
    return result;
}
